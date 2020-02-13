---
layout: post
title: "Text Learner"
categories:
  - fast.ai
tags:
  - Python
---

# 概要

本記事は fast.ai の wiki の[text.learner](https://docs.fast.ai/text.learner.html)ページの要約となります。
筆者の理解した範囲内で記載します。

## NLP モデル作成と training

一番大事なのが `RNN Learner` で、その周りに様々な関数やテキストモデルが存在する。

## learner を素早く作成する

### `language_model_learner`

```py
language_model_learner(data:DataBunch, arch, config:dict=None, drop_mult:float=1.0, pretrained:bool=True, pretrained_fnames:OptStrTuple=None, **learn_kwargs) → LanguageLearner
```

Language Model の `Learner` を `data`と`arch`から作成する
モデルは`arch`と`config`から指定できる。

- `AWD_LSTM` [(Merity et al.)](https://arxiv.org/abs/1708.02182)
- a `Transformer` decoder [(Vaswani et al.)](https://arxiv.org/abs/1706.03762)
- a `a TransformerXL` [(Dai et al.)](https://arxiv.org/abs/1901.02860)

それぞれ`{lower_case_class_name}_lm_config`にて規定されているデフォルトのパラメーターがある。現段階では、AWD LSTM に関しては、`pretrained=True`しかサポートされていないが、`drop_mult`により dropouts weights に全て適用でき、`dropouts weights`は Learner に引き渡されます。

注記：QRNN を用いるには cuda のインストールが必須です。

例：

> path = untar_data(URLs.IMDB_SAMPLE)
> data = TextLMDataBunch.from_csv(path, 'texts.csv')
> learn = language_model_learner(data, AWD_LSTM, drop_mult=0.5)

### `text_classifier_learner`

```py
text_classifier_learner(data:DataBunch, arch:Callable, bptt:int=70, max_len:int=1400, config:dict=None, pretrained:bool=True, drop_mult:float=1.0, lin_ftrs:Collection[int]=None, ps:Collection[float]=None, **learn_kwargs) → TextClassifierLearner
```

`Learner` を `data`と`arch`から作成する
こちらでも、モデルは`arch`と`config`から指定できる。
入力されるテキストは`bptt`のバッチとして処理され、`max_len`activation しか考慮されません。これがモデルの backbone で、head は

- RNN の最終的なアウトプットの最大値と中間層のアウトプットの平均（sequence length dimension)を連結させる layer
- `nn.BatchNorm1d`, `nn.Dropout`, `nn.Linear`, `nn.ReLU`ブロックの 複数の layer

ブロックは全て`lin_ftrs`と`drops`によって規定されており、最初のブロックの backbone であり、最後は`data.c`によりクラス数が規定され、`lin_ftrs`により中間層のインプットとアウトプットが規定されています。（当然前のブロックの output が口のブロックの input の数と同じになります。）dropout に関しては 浮動小数点の`ps`を引き渡して、リスト形式にすることができます。デフォルトでは中間層はサイズが 50 で、(2 つのブロックの model_activation -> 50 -> `n_classes`)でドロップアウトが 0.1 となっております。

> path = untar_data(URLs.IMDB_SAMPLE)
> data = TextClasDataBunch.from_csv(path, 'texts.csv')
> learn = text_classifier_learner(data, AWD_LSTM, drop_mult=0.5)

## class RNNLearner

```py
RNNLearner(data:DataBunch, model:Module, split_func:OptSplitFunc=None, clip:float=None, alpha:float=2.0, beta:float=1.0, metrics=None, **learn_kwargs) :: Learner
```

NLP のための基礎的なクラス。

テキストデータからのモデル作成を一定の`bptt`を用いて行う。`split_func`によりモデルを違うグループに仕分けたり gradual unfreezing と differential learning rates を用いることができる。Gradient clipping も同様に`clip`で適用可能。`alpha`と`beta`は RNNTrainer インスタンスを作成するために用いられる。language model もしくは RNN Classifier を作成するのに使うことができ、また pretrained model から重みを用いたり encoder を保存したりロードする用途にも適用することができる。

### `get_preds`

```py
get_preds(ds_type:DatasetType=<DatasetType.Valid: 2>, with_loss:bool=False, n_batch:Optional[int]=None, pbar:Union[MasterBar, ProgressBar, NoneType]=None, ordered:bool=False) → List[Tensor]
```

予測とターゲットを`valid` `train` or `test set`を`ds_type`に応じて返す。

`ordered=True` の場合、データセットの順番ごとに予測がはじき出されるが、そうではない場合 sampler により長いテキストから短いテキストに組み替えられる。 `Learner.get_preds`も同様に引数として用いることができる。

### 保存とロード

```py
load_encoder(name:str)
```

`name`でエンコーダーをモデルフォルダからロードする。

```py
save_encoder(name:str)
```

`name`でエンコーダーをモデルフォルダに保存する。

```py
load_pretrained(wgts_fname:str, itos_fname:str, strict:bool=True)
```

pretrained model をロードし、data vocabulary に適応させる。

`self.model_dir`の`wgts_fname`の weights と`itos_fname`の dictionary を開いて、pretrained_weights をデータの vocabulary に適応させる。二つのファイルは`learner.path`において同じフォルダになければいけない。

## Utility 関数

```py
convert_weights(wgts:Weights, stoi_wgts:Dict[str, int], itos_new:StrList) → Weights
```

モデル`wgts`を新しい vocabulary に変換させる。

`stoi_wgts`(string/word to id)の重みを新しい dictionary`itos_new`(mapping id to word)に変換する。

## 予測する

```py
LanguageLearner(data:DataBunch, model:Module, split_func:OptSplitFunc=None, clip:float=None, alpha:float=2.0, beta:float=1.0, metrics=None, **learn_kwargs) :: RNNLearner
```

予測のための RNNLearner のサブクラス。

```py
predict(text:str, n_words:int=1, no_unk:bool=True, temperature:float=1.0, min_p:float=None, sep:str=' ', decoder='decode_spec_tokens')
```

`n_words`に指定された単語数を`text`の後から予測として返す。

もし、`no_unk=True`であれば unknown token、つまり知らない単語は予測されない。単語はモデルの確率の分布よりランダムに抽出され、`min_p`が`None`ではない場合、そのあたいは単語の pool に当たって、それより低い値の単語は予測されない。また、`temperature`を低めることでテキストのランダム性は下がる。

```py
beam_search(text:str, n_words:int, no_unk:bool=True, top_k:int=10, beam_sz:int=1000, temperature:float=1.0, sep:str=' ', decoder='decode_spec_tokens')
```

beam search を用いて、`n_words`に指定された単語数を`text`の後から予測として返す。

## モデルを用いるための基礎的な関数

```py
get_language_model(arch:Callable, vocab_sz:int, config:dict=None, drop_mult:float=1.0)
```

Language Model の `Learner` を `data`と`arch`から作成する

```py
get_text_classifier(arch:Callable, vocab_sz:int, n_class:int, bptt:int=70, max_len:int=1400, config:dict=None, drop_mult:float=1.0, lin_ftrs:Collection[int]=None, ps:Collection[float]=None, pad_idx:int=1) → Module
```

Text classifier を`arch`と`config`から作成する(`pretrained`は任意)

このモデルは`arch`と`config`からの`encoder`を用いる。`encoder`は連続的なサイズの`bptt`から用いられるが、最後の`max_seq`を pooling layer として保存されない。

decoder は最後の output, 全ての output の`maxpooling`と全ての output の`AveragePooling`の連結体が用いられる。その後に、`BatchNorm`, `Dropout`, `Linear`, `ReLU`ブロック（最後のブロックは ReLU なし)が用いられ、3\*emb_sz の最初の layer サイズに n_layers が連続するようになっている。dropout 確率は`drops`にて表記されている。

モデルは 3 つの、最初の実際の output、他二つは中間層の dropout 前後の層（`RNNTrainer`によって用いられる)のリストを返り値としている。大概の loss function はただ一つの output を必要とするので、　`RNNTrainer`を用いない場合は、`Callback`を用いて他の二つを削除する必要がある。
