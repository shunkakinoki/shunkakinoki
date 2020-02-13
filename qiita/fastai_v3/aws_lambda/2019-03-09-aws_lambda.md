---
layout: post
title: "AWS Lambda"
categories:
  - fast.ai
tags:
  - Python
---

# 概要

本記事は fast.ai の wiki の[AWS Lambda Deployment](https://course.fast.ai/deployment_aws_lambda.html)で model を AWS Lambda で production に移行する tutorial の日本語版です。
筆者の理解した範囲内で記載します。
都合上、local development は省き、直接 production へ deploy する方法を紹介させていただきます。

# AWS Lambda Deployment とは

このガイドは [Amazon API Gateway](https://aws.amazon.com/api-gateway/) と [AWS Lambda](https://aws.amazon.com/lambda/) を用いて　[Serverless Application Model (SAM)](https://aws.amazon.com/serverless/sam/) のフレームワークのを通して Lambda と API Gateway AWS services を相互に繋げるものとなっております。

**AWS Lambda**
[公式ページ](https://aws.amazon.com/jp/lambda/)から

> AWS Lambda を使用することで、サーバーのプロビジョニングや管理をすることなく、コードを実行できます。課金は実際に使用したコンピューティング時間に対してのみ発生し、コードが実行されていないときには料金も発生しません。

**Amazon API Gateway**
[公式ページ](https://aws.amazon.com/jp/api-gateway/)から

> API Gateway では、トラフィック管理、認可とアクセスコントロール、モニタリング、API バージョン管理など、最大数十万規模の同時 API コールの受け入れと処理に伴うすべてのタスクを取り扱います。

## 料金

GPU を継続的に動かすと、莫大な料金が発生しかねないですが、
**AWS Lambda** を用いると個人利用の範囲内でしたら実質ゼロ円に抑えることができます。

## 必要条件

以下のアプリケーションをローカルマシンにインストールして下さい。

- [AWS CLI](https://aws.amazon.com/cli/) （認証済み）
- [Python 3](https://www.python.org/downloads/)
- [Docker](https://www.docker.com/community-edition)
- [AWS SAM CLI](https://aws.amazon.com/serverless/sam/)

## 準備

### S3 Bucket 作成

最初に model と Lambda functions/layers を ZIP files にて deploy する`S3 bucket`を作成しましょう。以下のコードで作成できます。

```bash
aws s3 mb s3://あなたのS3 Bucket名
```

### S3 へ鍛えた model をアップロード

SAM application では PyTorch model を[TorchScript](https://pytorch.org/docs/stable/jit.html?highlight=jit#module-torch.jit) 形式で S3 に保存しなければいけません。

fast.ai lesson 1 をもとに、model を鍛えて、JIT format にて S3 へ鍛えた model をアップロードする手順は [こちらから](https://github.com/fastai/course-v3/blob/master/docs/production/lesson-1-export-jit.ipynb).

### SAM を用いて deploy

SAM を用いて deploy するので、以下のコマンドでプロジェクトをダウンロードして下さい。

```bash
wget https://github.com/fastai/course-v3/raw/master/docs/production/aws-lambda.zip

unzip aws-lambda.zip
```

## Application 概要

画像認識モデルを推論するために、lambda function は　 PyTorch model 　を S3 からダウンロードしてメモリに load します。

JSON object を通して画像の URL を読み込んで、アプリケーションは image をダウンロードして、ピクセルを PyTorch Tensor object に変換した後 PyTorch model へ予測を行い、最も確率の高いクラス名 とその係数を出力します。

グラフ化したアプリケーションの概要は以下の通りです。

```bash
.
├── event.json          <-- local testing のためのpayload
├── pytorch             <-- ソースコード
│   ├── __init__.py
│   ├── app.py          <-- Lambda function コード
└──template.yaml        <-- SAM テンプレート
```

SAM Template についての詳細は [こちら](https://docs.aws.amazon.com/serverless-application-model/latest/developerguide/serverless-sam-template-basics.html)

Python を用いた Lambda functions についての詳細は [こちら](https://docs.aws.amazon.com/lambda/latest/dg/python-programming-model-handler-types.html)

### **Request 方法**

Lambda function に向けて JSON 形式にて予測するための画像 URL を入力。

例:

```json
{
  "url": "画像URL"
}
```

### **リスポンス format**

Lambda function を通して、JSON object にてステータスコードとともに、body にて予測された class と confidence score が返ってきます。

例:

```json
{
  "statusCode": 200,
  "body": {
    "class": "english_cocker_spaniel",
    "confidence": 0.99
  }
}
```

### **Lambda Layer**

Lambda function に code を追加するために[Lambda Layer](https://docs.aws.amazon.com/lambda/latest/dg/configuration-layers.html)を用いることができます。Layer とは ZIP 形式にて、ライブラリやランタイムや他の依存環境を含んだもので、汎用的なものを直接自分のパッケージに含めずに用いることができます。

このプロジェクトでは PyTorch library が含まれている公開 Lambda Layer を用います。こちらの Lambda Layer は次の region にて用いることができます: _us-west-2,us-east-1,us-east-2,eu-west-1,ap-southeast-1,ap-southeast-2,ap-northeast-1,eu-central-1_. デフォルトは *us-east-1*です。

default region で(i.e. _us-east-1_)コードを実行しない場合は、 `template.yaml` にての `AWS_REGION` を正しい region に書き直して下さい。 (e.g. us-west-2).

```yaml
...
  LambdaLayerArn:
    Type: String
    Default: "arn:aws:lambda:AWS_REGION:934676248949:layer:pytorchv1-py36:1"
        ...
```

## パッケージ化して deploy

SAM は `CodeUri` property にてアプリケーションのライブラリや依存環境を規定します。

```yaml
...
    PyTorchFunction:
        Type: AWS::Serverless::Function
        Properties:
            CodeUri: pytorch/
            ...
```

次に、以下のコマンドで Lambda function を S3 へとパッケージ化しましょう。

```bash
sam package \
    --output-template-file packaged.yaml \
    --s3-bucket あなたのS3 Bucket名
```

次に、 Cloudformation Stack にて SAM resource を deploy しましょう。default parameters の S3 Bucket 名 と object key を`--parameter-overrides` option にて上書きし `deploy` コマンドを実行しましょう。

```bash
sam deploy \
    --template-file packaged.yaml \
    --stack-name pytorch-sam-app \
    --capabilities CAPABILITY_IAM \
    --parameter-overrides BucketName=REPLACE_WITH_YOUR_BUCKET_NAME ObjectKey=fastai-models/lesson1/model.tar.gz
```

> SAM(Serverless Application Model)についての詳細は[こちらから](https://docs.aws.amazon.com/serverless-application-model/latest/developerguide/serverless-quick-start.html)

deploy が完了した後以下のコマンドで API Gateway Endpoint URL を取得しましょう。

```bash
aws cloudformation describe-stacks \
    --stack-name pytorch-sam-app \
    --query 'Stacks[].Outputs[?OutputKey==`PyTorchApi`]' \
    --output table
```

## Lambda function のログを取得する。

問題解決の一環として、 SAM CLI は`sam logs`コマンドを通して Lambda Function のログを取得することができます。ただ単にログを記載するのみならず、debug に役立つ機能も兼ね備えています。

`NOTE`: SAM のみならず、全ての AWS Lambda functions に用いることができます。

```bash
sam logs -n PyTorchFunction --stack-name pytorch-sam-app --tail
```

Lambda function logs を取得する方法の詳細は [こちらから](https://docs.aws.amazon.com/serverless-application-model/latest/developerguide/serverless-sam-cli-logging.html)。

## 片付け

Serverless Application を削除するには以下の AWS CLI Command を実行して下さい。

```bash
aws cloudformation delete-stack --stack-name pytorch-sam-app
```
