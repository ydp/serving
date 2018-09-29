#!/bin/bash

git config --global push.default matching
git config --global user.email "ydp5237@gmail.com"
git config --global user.name "ydp5237"
git add .
git commit -m "$1"

git push
