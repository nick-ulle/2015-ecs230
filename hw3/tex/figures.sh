#!/bin/bash

for i in {3..10}
do
    stem=fit${i}
    ../scripts/extract.r ../data.dat ../output/${stem}.out figures/${stem}.pdf
    echo "Finished ${stem}."
done
