#!/bin/bash

for i in $(\ls -d $@)
do
gawk -f assign3.awk $i
done