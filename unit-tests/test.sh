#!/bin/bash

name=main.c
dll=../doubly-linked-list/$name 
da=../dynamic-array/$name 
st=../seq-of-trees/$name 
sl=../skip-list/$name 


declare -a names=("doubly_linked_list" "dynamic_array" "skip_list" "sequence_of_trees")

declare -a arr=( $dll $da $sl $st )


tc=$1
testfile=$tc.txt



for i in $(seq 0 3)
do
printf "" > ./res/${names[$i]}.txt
for j in $(seq 0 3)
do
echo ${names[$i]}
gcc -o ./tmp/test${names[$i]} ${arr[$i]}
./tmp/test${names[$i]} < $testfile > ./tmp/out.a
if [$i == $j]; then
:
else

gcc -o ./tmp/test2${names[$j]} ${arr[$j]}
./tmp/test2${names[$j]} < $testfile > ./tmp/out.b

if diff ./tmp/out.b ./tmp/out.a; then
printf "Output correct: ${names[$j]}\n" >> ./res/${names[$i]}.txt
else
printf "Output incorrect!: ${names[$j]}\n" >> ./res/${names[$i]}.txt
fi

fi

done

done

