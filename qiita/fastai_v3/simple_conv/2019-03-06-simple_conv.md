---
layout: post
title: "Simple Conv"
categories:
  - fast.ai
tags:
  - Python
---

# 概要

本記事はfast.aiのlayersのなかの`simple_cnn`の仕組みがどうなっているかを深掘りしたものになっております。
筆者の理解した範囲内で記載します。
なお、[こちらのノートブック](https://github.com/shunkakinoki/outputbook/blob/master/fastai_v3/jupyter/simple_cnn.ipynb)へ全コードが載っております。（英語）

fast.aiの`simple_cnn`を理解し、fast.aiフレームワークの知見を高める。

公式ドキュメントは[こちら](https://docs.fast.ai/layers.html#simple_cnn)を参照にしてください。

## 実際のコード

```py
def simple_cnn(actns:Collection[int], kernel_szs:Collection[int]=None,
               strides:Collection[int]=None, bn=False) -> nn.Sequential:
    "CNN with `conv_layer` defined by `actns`, `kernel_szs` and `strides`, plus batchnorm if `bn`."
    nl = len(actns)-1
    kernel_szs = ifnone(kernel_szs, [3]*nl)
    strides    = ifnone(strides   , [2]*nl)
    layers = [conv_layer(actns[i], actns[i+1], kernel_szs[i], stride=strides[i],
              norm_type=(NormType.Batch if bn and i<(len(strides)-1) else None)) for i in range_of(strides)]
    layers.append(PoolFlatten())
    return nn.Sequential(*layers)
```

`kernel_szs`のszが複数形なのは、kernel_size(s)で、layerごとに指定できるから。
他のstride(s)も同様。

##　実装

```py
model = simple_cnn((3,16,16,2))
```

```py
model.parameters
```

><bound method Module.parameters of Sequential(
  (0): Sequential(
    (0): Conv2d(3, 16, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1))
    (1): ReLU(inplace)
  )
  (1): Sequential(
    (0): Conv2d(16, 16, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1))
    (1): ReLU(inplace)
  )
  (2): Sequential(
    (0): Conv2d(16, 2, kernel_size=(3, 3), stride=(2, 2), padding=(1, 1))
    (1): ReLU(inplace)
  )
  (3): Sequential(
    (0): AdaptiveAvgPool2d(output_size=1)
    (1): Flatten()
  )
)>

## conv_layer

では、肝心の`conv_layer`はどのようになっているのか？

```py
def conv_layer(ni:int, nf:int, ks:int=3, stride:int=1, padding:int=None, bias:bool=None, is_1d:bool=False,
               norm_type:Optional[NormType]=NormType.Batch,  use_activ:bool=True, leaky:float=None,
               transpose:bool=False, init:Callable=nn.init.kaiming_normal_, self_attention:bool=False):
    "Create a sequence of convolutional (`ni` to `nf`), ReLU (if `use_activ`) and batchnorm (if `bn`) layers."
    if padding is None: padding = (ks-1)//2 if not transpose else 0
    bn = norm_type in (NormType.Batch, NormType.BatchZero)
    if bias is None: bias = not bn
    conv_func = nn.ConvTranspose2d if transpose else nn.Conv1d if is_1d else nn.Conv2d
    conv = init_default(conv_func(ni, nf, kernel_size=ks, bias=bias, stride=stride, padding=padding), init)
    if   norm_type==NormType.Weight:   conv = weight_norm(conv)
    elif norm_type==NormType.Spectral: conv = spectral_norm(conv)
    layers = [conv]
    if use_activ: layers.append(relu(True, leaky=leaky))
    if bn: layers.append((nn.BatchNorm1d if is_1d else nn.BatchNorm2d)(nf))
    if self_attention: layers.append(SelfAttention(nf))
    return nn.Sequential(*layers)
```

初期設定ではkaiming_normal initalizationを用いたconv2dとrelu

## PoolFlatten()

```py
def PoolFlatten()->nn.Sequential:
    "Apply `nn.AdaptiveAvgPool2d` to `x` and then flatten the result."
    return nn.Sequential(nn.AdaptiveAvgPool2d(1), Flatten())
```

最後に、nn.AdaptiveApgPool2dを追加

# 最後に

1. pytorchのfunctionを掘り下げていきたい
2. AdaptiveConcatPool2dを解説
3. 理解するまでやり切る

間違いやご指摘などが御座いましたらご教示願います！