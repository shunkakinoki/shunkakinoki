#!/bin/bash

curl -s https://api.github.com/repos/solana-labs/solana/releases/latest \
| grep "apple-darwin.tar.bz2" \
| cut -d : -f 2,3 \
| tr -d \" \
| wget -qi -

tar jxf solana-release-x86_64-apple-darwin.tar.bz2
cd solana-release/
export PATH=$PWD/bin:$PATH
