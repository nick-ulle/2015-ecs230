#!/bin/bash
# test job script. submit using "sbatch <script name>"
#SBATCH -p development
#SBATCH -n 1
#SBATCH -o output/timing1.%j.out
#SBATCH -e output/timing1.%j.err
#SBATCH -t 00:05:00
#SBATCH -A TG-ASC150014

echo 'Running `timing1 5000000`...'
for i in {1..10}
do
    echo "Iteration $i:"
    bin/timing1 5000000
done

echo ""
echo 'Running `timing1 10000000`...'
for i in {1..10}
do
    echo "Iteration $i:"
    bin/timing1 10000000
done

echo ""
echo 'Running `timing1 20000000`...'
for i in {1..10}
do
    echo "Iteration $i:"
    bin/timing1 20000000
done

