#!/bin/bash
# $1 is n.
g++ 190050038_3.cpp

> input
echo "$1 1 R" >> input 
i=0
while [ $i -ne $1 ]
do
	echo "$i" >> input
	((i++))
done

num_seq=$(./a.out < input) 
((num_seq++))
> input

echo "$num_seq"

echo "$1 $num_seq" >> input


i=0

while [ $i -ne $num_seq ]  
do
	echo "U $i" >> input
	((i++))
done

./a.out < input >output


> input_last
echo "$1 $num_seq" >>input_last

while read line 
do
	echo "R $line" >>input_last
done < output

./a.out < input_last

exit 0

