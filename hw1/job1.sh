#!/bin/bash
# test job script. submit using "sbatch <script name>"
#SBATCH -a 0-9
#SBATCH -p development
#SBATCH -n 1
#SBATCH -o output/timing1.%j.out
#SBATCH -e output/timing1.%j.err
#SBATCH -t 00:05:00
#SBATCH -A TG-ASC150014

bin/timing1 5000000
