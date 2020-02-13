---
layout: post
title: "Text Overview"
categories:
  - fast.ai
tags:
  - Python
---

# 概要

本記事はfast.aiのwikiの[Text](https://docs.fast.ai/text.html#Text-models,-data,-and-training)ページの要約となります。  
筆者の理解した範囲内で記載します。

## Text モデル、データ、トレーニング

fast.aiライブラリのText モジュールは、DatasetをNLP (Natural Language Processing)目的へ最適化するための関数を多数備えています。具体的には：

* [text.transform](https://docs.fast.ai/text.transform.html#text.transform) にてデータの前処理実施し、テキストをidへと変換する
* [text.data](https://docs.fast.ai/text.data.html#text.data) にて [TextDataBunch](https://docs.fast.ai/text.data.html#TextDataBunch) を用いてNLPに必要なDatasetのクラスを規定する
* [text.learner](https://docs.fast.ai/text.learner.html#text.learner) にて素早くlanguage model や RNN classifierを作成できる

上のリンクを辿って各モジュールのAPIを参考にしてみて下さい。

## 早速やってみる： ULMFiTでimdbの感情modelを鍛える

早速fast.ai textモジュールを使ってみましょう。以下の例では名の知れたimdbデータを用いて、感情分類モデルを4ステップで鍛えていきます。

1) Imdbデータを読み込み俯瞰する
2) データをモデルに最適化する
3) language modelをfine-tuneする
4) 分類モデルを作成する

### 1) Imdbデータを読み込み俯瞰する

text に必要なパッケージを読み込みましょう。

```py
from fastai.text import *
```

画像認識とは異なり、テキストは直接モデルに読み込むことができません。従って、最初にデータを前処理してテキストをトークンへと変換して(tokenization)それを数字へと変換する(numericalization)必要があります。これらの数字 embedding layer へと引き渡されることで浮動小数点の配列へと変換されます。

これらトークンを浮動小数点へと変換する[Word Embeddings](https://en.wikipedia.org/wiki/Word_embedding)はweb上で掲載されています。これらのWord Embeddingsはwikipediaなどの膨大なサイズのcorpusで鍛えられたものです。ULMFiTの手法を用いて、fast.aiライブラリはpre-trained Language Modelsを用いて、fine-tuneすることに焦点を絞っています。Word embeddingsとは、具体的に300から400の小数点を異なる単語を表すために鍛えられたもので、pre-trained language model はこれらの特性を備えているだけではなく、文や文章を表現する性質も備わっております。

### 注記： ライブラリは以下の3ステップで構成されています。

1. データを最小限のコードで前処理を済ませる
2. pre-trained された language model をベースに、データセットを用いてfine-tuneする
3. 分類器などのモデルをlanguage modelの上に載せる。

#### 1000レビューに抽出されたIMDBデータセットを用いる（陽性または陰性）

```py
path = untar_data(URLs.IMDB_SAMPLE)
path
```

> PosixPath('/home/ubuntu/.fastai/data/imdb_sample')

#### データセットをテキストから作成するには以下の方法がベストです

* ImageNet スタイルにフォルダへ整理されている
* csv ファイルへラベルの欄とテキスト欄へ整理されている

こちらの例ではimdbをtexts.csvファイルから読み込んで以下のようになっております。

```py
df = pd.read_csv(path/'texts.csv')
df.head()
```

|label|text|is_valid|
|-----|-----|-----|
|0|negative|Un-bleeping-believable! Meg Ryan doesn't even ...|False|
|1|positive|This is a extremely well-made film. The acting...|False|
|2|negative|Every once in a long while a movie will come a...|False|
|3|positive|Name just says it all. I watched this movie wi...|False|
|4|negative|This movie succeeds at being one of the most u...|False|

### 2) データをモデルに最適化する

DataBunchを準備するためには、複数のfactory methodsがデータの構成に応じて存在します。詳細は[text.data](https://docs.fast.ai/text.data.html#text.data)。こちらでは`from_csv`メソッドを用いてTextLMDataBunch(Language Modelのためのデータ処理)とTextClasDataBunch(Text Classifierのためのデータ処理)クラスを用います。

```py
# Language model データ処理
data_lm = TextLMDataBunch.from_csv(path, 'texts.csv')
# Classifier model データ処理
data_clas = TextClasDataBunch.from_csv(path, 'texts.csv', vocab=data_lm.train_ds.vocab, bs=32)
```

これで必要なデータの前処理がなされます。分類器には、vocabulary(wordからidを引き渡す役目)を引き渡すことによって、data_clasがdata_lmと同じdictionaryを用いる点は注意して下さい。

この処理は時間がかかるため、結果を保存するために以下のコードを実行しましょう。

```py
data_lm.save('data_lm_export.pkl')
data_clas.save('data_clas_export.pkl')
```

これで全ての結果を保存するための`tmp`directoryが作成されます。ロードするためには以下のコードを実行しましょう。

```py
data_lm = load_data(path, fname='data_lm_export.pkl')
data_clas = load_data(path, fname='data_clas_export.pkl', bs=16)
```

注記：`DataBunch`のパラメータを設定できます。(`batch size`, `bptt`,...)

### 3) language modelをfine-tuneする

`data_lm`を用いてlanguage modelをfine-tuneしましょう。fast.ai は、AWD-LSTM architectureの英語モデルを用意してるので、それとpretrained weightsをダウンロードし、fine-tuneするための`learner`オブジェクトを作成しましょう

```py
learn = language_model_learner(data_lm, AWD_LSTM, drop_mult=0.5)
learn.fit_one_cycle(1, 1e-2)
```

>Total time:00:13
>
>|epoch|train_loss|valid_loss|accuracy|
>|-----|-----|-----|-----|
>|1|4.514897|3.974741|0.282455|

画像認識モデルと同様に、モデルを`unfreeze`することでさらにfine-tuneすることができます。

```py
learn.unfreeze()
learn.fit_one_cycle(1, 1e-3)
```

>Total time: 00:17
>
>|epoch|train_loss|valid_loss|accuracy|
>|-----|-----|-----|-----|
>|1|4.159299|3.886238|0.289092|

モデルを評価するために、以下の`Learner.predict`を実行することで、単語とその数を指定し予測させることができます。

```py
learn.predict("This is a review about", n_words=10)
```

>'This is a review about dog - twist credited , and that , along with'

あまり意味は通じませんが（小さいvocabularyのため）ここでは基本的な文法をmodelが習得していることは驚愕すべきことです。（pretrained modelが可能にしたもの)

最後にencoderを保存して分類モデルに用いるようにできるようにしましょう。

```py
learn.save_encoder('ft_enc')
```

### 4) 分類モデルを作成する

ここでは、先述して作成した`data_clas`オブジェクトを用いて、分類器をencoderを用いて新たに作成します。`learner`オブジェクト自体はたった一行のコードで作成できます。

```py
learn = text_classifier_learner(data_clas, AWD_LSTM, drop_mult=0.5)
learn.load_encoder('ft_enc')
```

```py
data_clas.show_batch()
```

>|text|target|
>|-----|-----|
>|xxbos xxmaj raising xxmaj victor xxmaj vargas : a xxmaj review \n \n xxmaj you know , xxmaj raising xxmaj victor xxmaj vargas is like sticking your hands into a big , xxunk bowl of xxunk . xxmaj it 's warm and gooey , but you 're not sure if it feels right . xxmaj try as i might , no matter how warm and gooey xxmaj raising xxmaj|negative|
>|xxbos xxmaj now that xxmaj che(2008 ) has finished its relatively short xxmaj australian cinema run ( extremely limited xxunk screen in xxmaj xxunk , after xxunk ) , i can xxunk join both xxunk of " xxmaj at xxmaj the xxmaj movies " in taking xxmaj steven xxmaj soderbergh to task . \n \n xxmaj it 's usually satisfying to watch a film director change his style /|negative|
>|xxbos i really wanted to love this show . i truly , honestly did . \n \n xxmaj for the first time , gay viewers get their own version of the " xxmaj the xxmaj xxunk " . xxmaj with the help of his obligatory " hag " xxmaj xxunk , xxmaj james , a good looking , well - to - do thirty - something has the chance|negative|
>|xxbos xxmaj to review this movie , i without any doubt would have to quote that memorable scene in xxmaj tarantino 's " xxmaj pulp xxmaj fiction " ( xxunk ) when xxmaj jules and xxmaj vincent are talking about xxmaj mia xxmaj wallace and what she does for a living . xxmaj jules tells xxmaj vincent that the " xxmaj only thing she did worthwhile was pilot " .|negative|
>|xxbos xxmaj how viewers react to this new " adaption " of xxmaj shirley xxmaj jackson 's book , which was promoted as xxup not being a remake of the original 1963 movie ( true enough ) , will be based , i suspect , on the following : those who were big fans of either the book or original movie are not going to think much of this one|negative|

```py
learn.fit_one_cycle(1, 1e-2)
```

>Total time: 00:33
>
>|epoch|train_loss|valid_loss|accuracy|
>|-----|-----|-----|-----|
>|1|0.650518|0.599687|0.691542|

再度modelをunfreezeしてfine-tuneしましょう。

```py
learn.freeze_to(-2)
learn.fit_one_cycle(1, slice(5e-3/2., 5e-3))
```

>Total time: 00:38
>
>|epoch|train_loss|valid_loss|accuracy|
>|-----|-----|-----|-----|
>|1|0.628320|0.563579|0.716418|

```py
learn.unfreeze()
learn.fit_one_cycle(1, slice(2e-3/100, 2e-3))
```

>Total time: 00:56
>
>|epoch|train_loss|valid_loss|accuracy|
>|-----|-----|-----|-----|
>|1|0.533411|0.539693|0.721393|

そして、`Learner.predict`を用いてテキストを予測してみましょう。

```py
learn.predict("This was a great movie!")
```

>(Category positive, tensor(1), tensor([0.0118, 0.9882]))
