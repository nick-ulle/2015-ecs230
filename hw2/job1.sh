#!/bin/bash
# Usage:
#   sbatch <script>

#SBATCH -p normal
#SBATCH -n 1
#SBATCH -o output/timing1.%j.out
#SBATCH -e output/timing1.%j.err
#SBATCH -t 02:00:00
#SBATCH -A TG-ASC150014

dims="100 200 500 1000 2000 5000"
orders="ijk ikj kij jik jki kji"
replications=10

echo "["
for dim in $dims
do
    for order in $orders
    do
        bin/task1 $dim $order $replications
    done
done
echo "]"

