#!/bin/bash


name=main.c
dll=../doubly-linked-list/$name 
da=../dynamic-array/$name 
st=../seq-of-trees/$name 
sl=../skip-list/$name 
py=/test.py

declare -a arr=( $st )

name_py=main.py

gcc -o ./tmp/test $dll
./test < test.txt > ./tmp/out.a

for i in "${arr[*]}"
do
gcc -o ./tmp/test2 $i
./test2 < test.txt > ./tmp/out.b
diff ./tmp/out.b ./tmp/out.a
done

