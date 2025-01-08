#!/bin/bash


name=main.c
dll=../doubly-linked-list/$name 
da=../dynamic-array/$name 
st=../seq-of-trees/$name 
sl=../skip-list/$name 
py=/test.py

declare -a arr=( $st )

name_py=main.py

tc=$1


gcc -o ./tmp/test $dll
./test < $tc.txt > ./tmp/out.a

for i in "${arr[*]}"
do
gcc -o ./tmp/test2 $i
./test2 < $tc.txt > ./tmp/out.b
diff ./tmp/out.b ./tmp/out.a
done

