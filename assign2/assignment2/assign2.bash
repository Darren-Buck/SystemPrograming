#!/bin/bash
cp /usr/local/courses/ssilvestro/cs3424/Spring23/assign2/inputProgram.c .

sed -i.bak -E -f assign2.sed $@ && cat $@
