#!/bin/bash


name=main.c
dll=../doubly-linked-list/$name 
da=../dynamic-array/$name 
st=../seq-of-trees/$name 
sl=../skip-list/$name 
py=/test.py


declare -a names=("stree" "sl" "dll")

declare -a arr=( $st $sl $dll )

name_py=main.py

tc=$1
testfile=$tc.txt

gcc -o ./tmp/test $dll
./tmp/test < $testfile > ./tmp/out.a

for i in $(seq 0 2)
do
echo ${names[$i]}
gcc -o ./tmp/test2${names[$i]} ${arr[$i]}
./tmp/test2${names[$i]} < $testfile > ./tmp/out.b

if diff ./tmp/out.b ./tmp/out.a; then
echo "Output correct"
else
echo "Output incorrect!"
fi

done

