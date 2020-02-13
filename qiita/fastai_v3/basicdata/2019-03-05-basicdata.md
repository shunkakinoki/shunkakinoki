---
layout: post
title: "Basic Data"
categories:
  - fast.ai
tags:
  - Python
---

# 概要

本記事は fast.ai の wiki の[Basic Data](https://docs.fast.ai/basic_data.html)ページの要約となります。
筆者の理解した範囲内で記載します。

Training のための Data を準備するための簡易 API。
具体的には、Learner モジュールに用いる Data Bunch オブジェクトを用いる。

## Data Bunch

```py
DataBunch(train_dl:DataLoader, valid_dl:DataLoader, fix_dl:DataLoader=None, test_dl:Optional[DataLoader]=None, device:device=None, dl_tfms:Optional[Collection[Callable]]=None, path:PathOrStr='.', collate_fn:Callable='data_collate', no_check:bool=False)
```

Data オブジェクトに`train_dl` `valid_dl,` `test_dl`(随意)を結びつける。(dl は dataloader の省略形)
全ての dataloader が device に取り付けられていることと、`tfms`で data augmentation がなされていることを保証し、
`collate_fn`にて PyTorch の`Dataloader`に batch ごとのデータとファイル名の照合を促す。
なお、`train_dl` `valid_dl` `test_dl`(随意) は`DeviceDataLoader`に包まれている。

### create

```py
create(train_ds:Dataset, valid_ds:Dataset, test_ds:Optional[Dataset]=None, path:PathOrStr='.', bs:int=64, val_bs:int=None, num_workers:int=4, dl_tfms:Optional[Collection[Callable]]=None, device:device=None, collate_fn:Callable='data_collate', no_check:bool=False, **dl_kwargs) → DataBunch
```

`Data Bunch`クラスを`bs`(batch size)で`train_dl` `valid_dl` `test_dl`より生成。

### show_batch

```py
show_batch(rows:int=5, ds_type:DatasetType=<DatasetType.Train: 1>, **kwargs)
```

指定した`row`にて data の batch を表示。

### dl

```py
dl(ds_type:DatasetType=<DatasetType.Valid: 2>) → DeviceDataLoader
```

`ds_type`にて指定された validation,training,test の`Dataset`を返す。

### one_batch

```py
one_batch(ds_type:DatasetType=<DatasetType.Train: 1>, detach:bool=True, denorm:bool=True, cpu:bool=True) → Collection[Tensor]
```

1 つの batch を DataLoader より持ってくる。

### one_item

```py
one_item(item, detach:bool=False, denorm:bool=False, cpu:bool=False)
```

item を batch へ持ってくる。

### sanity_check

```py
sanity_check()
```

sanity check を行い、データを確認する。

### save

```py
save(fname:PathOrStr='data_save.pkl')
```

`DataBunch`を`self.path/fname`へ保存。

### load_data

```py
load_data(path:PathOrStr, fname:str='data_save.pkl', bs:int=64, val_bs:int=None, num_workers:int=4, dl_tfms:Optional[Collection[Callable]]=None, device:device=None, collate_fn:Callable='data_collate', no_check:bool=False, **kwargs) → DataBunch
```

`DataBunch`を`path/fname`から読み込む。

## PyTorch の Dataset との互換性

PyTorch の`Dataset`との互換性は部分的にサポートされている。詳しくは[こちら](https://docs.fast.ai/basic_data.html#Using-a-custom-Dataset-in-fastai)

## DeviceDataLoader

```py
DeviceDataLoader(dl:DataLoader, device:device, tfms:List[Callable]=None, collate_fn:Callable='data_collate')
```

`DataLoader`を`torch.device`に結びつける。
`tfms`を行った後に`dl`のバッチを`device`へ結ぶ。全ての`DataLoader`はこのタイプ。

### create (with DeviceDataLoader)

```py
create(dataset:Dataset, bs:int=64, shuffle:bool=False, device:device=device(type='cuda'), tfms:Collection[Callable]=None, num_workers:int=4, collate_fn:Callable='data_collate', **kwargs:Any)
```

`shuffle`で`bs`の`dataset`を`num_workers`用いて`DeviceDataLoader`を生成。
`collate_fn`によって、1 つの batch へとサンプルを照合する。
`shuffle`を用いると data がシャッフルされ、`tfms`は data augmmentation に用いられる。

### add_tfm

```py
add_tfm(tfm:Callable)
```

`self.tfms`に`tfm`を追加。

### remove_tfm

```py
remove_tfm(tfm:Callable)
```

`self.tfms`より`tfm`を削除。

### new

```py
new(**kwargs)
```

kwags を用いてコピーを生成。

### proc_batch

```py
proc_batch(b:Tensor) → Tensor
```

`TensorImage`の batch`b`を処理。

# 最後に

1. basic_data を用いて自作の dataloader を作成してみる。
2. PyTorch からの実際の移植作業をやってみたい。
3. 自作のノートブックを用いて、実例の用法を紹介してみる。

間違いやご指摘などが御座いましたらご教示願います！
