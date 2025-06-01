#!/bin/bash

docker build -t latex .
docker run --rm -i -v "$PWD":/data latex pdflatex resume.tex
