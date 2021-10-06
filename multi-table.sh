#!/bin/bash

if [ ! $1 ]
then
	echo "There is no input"
	exit 1
	
elif [[ $1 -le 0 || ! $1 =~ ^[0-9]+$ ]]
then
	echo "The first argument input is wrong. Input condition is positive and integer."
	exit 1
	
elif [[ ! $2 || $2 -le 0 || ! $2 =~ ^[0-9]+$ ]]
then
	echo "The second argument input is wrong. Input condition is positive and integer."
	exit 1
	
fi


for i in $(seq 1 $1)
do

	for j in $(seq 1 $2)
	do
		mul=`expr $i \* $j`
		echo -n " $i * $j = $mul "
		
	done
	echo ""
	
done

exit 0

