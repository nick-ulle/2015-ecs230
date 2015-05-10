#!/bin/bash
# test job script. submit using "sbatch <script name>"
#SBATCH -p development
#SBATCH -n 1
#SBATCH -o output/timing1.%j.out
#SBATCH -e output/timing1.%j.err
#SBATCH -t 00:05:00
#SBATCH -A TG-ASC150014

#args="100 200 500 1000 2000 5000"
args="10 20"

#for i in {1..3}
#do
    echo '['
    for arg in $args
    do
        echo '{'
        bin/mult $arg
        echo '},'
    done
    echo ']'
#done

#echo ""
#echo 'Running `timing1 10000000`...'
#for i in {1..10}
#do
#    echo "Iteration $i:"
#    bin/timing1 10000000
#done
#
#echo ""
#echo 'Running `timing1 20000000`...'
#for i in {1..10}
#do
#    echo "Iteration $i:"
#    bin/timing1 20000000
#done

