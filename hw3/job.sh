#!/bin/bash
# Usage:
#   sbatch <script>

#SBATCH -p normal
#SBATCH -n 1
#SBATCH -o output/task1.%j.out
#SBATCH -e output/task1.%j.err
#SBATCH -t 00:30:00
#SBATCH -A TG-ASC150014


for degree in {3..10}
do
    bin/poly $degree data.dat > output/fit${degree}.out
done

