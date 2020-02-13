---
layout: post
title: "【Kaggle日記】 2019/04/10 LightGBMと樹木モデルのアンサンブル学習について"
categories:
  - Kaggle
tags:
  - ML, LightGBM
---

# 概要

文系大学3年生が  
2019年度内までにKaggle Masterになる  
過程において、
その日学んだことをアウトプットしていきます。
間違いやご指摘などが御座いましたらご教示願います！

# LightGBMとは一体何なのか

KaggleのKernelでよく用いられているLightGBM。

そもそもLightGBMとは一体何なのか。簡潔に自分なりにまとめてみました。

結論から言うと、

LightGBMは、アンサンブル(Ensemble)学習を用いた樹木モデルフレームワークの一種です。

では、アンサンブル学習とは一体何なのでしょう。

## アンサンブル学習とは

アンサンブル学習には、

1. バッギング(Bagging)
2. 勾配ブースティング(Gradient Boosting)

の2種類があり、
LightGBMが用いているのは後者の
勾配ブースティング(Gradient Boosting)です。

順番に説明していきます。

### 1. バッギング(Bagging)

バッギング(Bagging)とは、
すべての弱学習器を独立に学習させ作成していく手法。
ex) Random Forests など

### 2. 勾配ブースティング(Gradient Boosting)

勾配ブースティング(Boosting)とは、
一つずつ順番に前のを反映させて学習させた上で弱学習器を作成していく手法。
ex) Xgboost, LightGBMなど

## 分かりやすい比喩

まず、バッギング(Bagging)について説明します。

fast.aiの創始者であるJeremy Howardは、
Random Forestが用いている バッギング(Bagging)手法については
"Create a bunch of crappy models, and join them together to create a really good model"と言及していたのですが、

バッギング(Bagging)は一言で言うと
**平均化**で
ゴミレベルの学習器を作成し、それを合わせて良いモデルをつくる手法

つまり、入試に例えると

多種多様の凡人たちに問題を解かせ、その解答を全部組み合わせて神解答をつくる手法

です。

それに対して、

勾配ブースティング(Boosting)は一言で言うと
**最適化**で
ゴミレベルの学習器を作成し、それを合わせて良いモデルをつくる手法

つまり、同じく入試に例えると

ある凡人に問題を解かせ、その解答を最適化させた上で、他の人もどんどん問題を解いてもらい、
その都度最適化して次に引き渡すことで神解答をつくる手法

となります。

## それぞれの特徴

### 1. バッギング(Bagging)

得意領域 理解が容易でありシンプル
不得意領域 複雑なデータに対してはパフォーマンスが低い

### 2. 勾配ブースティング(Gradient Boosting)

得意領域 パフォーマンスが高い (Kaggleによく用いられる)
不得意領域 予測の根拠が比較的ブラックボックス・小さなデータの違いによりモデルに大きな差異をもたらす

## 参考・引用文献

- 神資料[https://www.analyticsvidhya.com/blog/2016/02/complete-guide-parameter-tuning-gradient-boosting-gbm-python/](https://www.analyticsvidhya.com/blog/2016/02/complete-guide-parameter-tuning-gradient-boosting-gbm-python/)
- [https://thereputationalgorithm.com/2017/01/21/top-predictive-algorithms-infographic/](https://thereputationalgorithm.com/2017/01/21/top-predictive-algorithms-infographic/)
- [An Overview of LightGBM](https://www.avanwyk.com/an-overview-of-lightgbm/)
- [Parameters Tuning](https://lightgbm.readthedocs.io/en/latest/Parameters-Tuning.html)
- [What is LightGBM, How to implement it? How to fine tune the parameters?](https://medium.com/@pushkarmandot/https-medium-com-pushkarmandot-what-is-lightgbm-how-to-implement-it-how-to-fine-tune-the-parameters-60347819b7fc)
- [Python 勾配ブースティングにおけるパラメータと調整方法について](http://rautaku.hatenablog.com/entry/2018/01/13/190818)
- [Introduction to Machine Learning for Coders!](http://course18.fast.ai/ml)
- [「樹木モデルとランダムフォレスト－機械学習による分類・予測－」－データマイニングセミナー様のスライド](https://www.slideshare.net/hamadakoichi/tree-basedmodelsandrandomforests)

## 最後に

改めてこうしてMLの手法を学び直してみると再発見が多かったです。

1. LightGBMのパラメーターを理解していく
2. LightGBMやXGBoost のソースコードのぞいてみる
3. Highest Scoring Kernel を何としてでも一度超える

最後に  
間違いやご指摘などが御座いましたらご教示願います！