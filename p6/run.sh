#!/bin/sh

for R in 0 33 100
do
	for m in 16 64 256
	do
		for t in 1 2 3
		do
			for p in 1 2 4 6 8 10
			do
				./task_$t/p6 -p$p -r$R -m$m | tee -a task_$t/result.txt
			done
		done
	done
done
