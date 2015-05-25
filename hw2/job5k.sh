#!/bin/bash
# Usage:
#   sbatch <script>

#SBATCH -p normal
#SBATCH -n 1
#SBATCH -o output/task5k2.%j.out
#SBATCH -e output/task5k2.%j.err
#SBATCH -t 10:00:00
#SBATCH -A TG-ASC150014

dim="5000"
orders="ikj kij jik jki kji"
replications=3

echo "["
for order in $orders
do
    bin/task1 $dim $order $replications
done
echo "]"

