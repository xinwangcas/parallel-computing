#!/bin/sh

for ((n = 1; n < 1000; n++))
do
./p2 -g 514 > cat.txt
awk 'BEGIN{a=0;b=0}{if(NR==3)a=$2;if(NR==4)b=$2}END{printf("%f\n",a/b)}' cat.txt
./p2 -g 1026 > cat.txt
awk 'BEGIN{a=0;b=0}{if(NR==3)a=$2;if(NR==4)b=$2}END{printf("%f\n",a/b)}' cat.txt
done
