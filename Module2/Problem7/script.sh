#!/usr/bin/env bash

for ((i=10;i<=100;i++))
do
    echo "Cutoff = $i /n" >> result.txt
    for ((j=0;j<=10;j++))
    do
        ./a.out i < test1.txt >> result.txt
    done
done