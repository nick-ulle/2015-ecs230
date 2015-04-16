#!/bin/bash
# test job script. submit using "sbatch <script name>"
#SBATCH -p development
#SBATCH -n 1
#SBATCH -o output/timing2.%j.out
#SBATCH -e output/timing2.%j.err
#SBATCH -t 00:05:00
#SBATCH -A TG-ASC150014

echo 'Running `timing2 5000000`...'
for i in {1..10}
do
    echo "Iteration $i:"
    bin/timing2 5000000
done

echo ""
echo 'Running `timing2 10000000`...'
for i in {1..10}
do
    echo "Iteration $i:"
    bin/timing2 10000000
done

echo ""
echo 'Running `timing2 20000000`...'
for i in {1..10}
do
    echo "Iteration $i:"
    bin/timing2 20000000
done

