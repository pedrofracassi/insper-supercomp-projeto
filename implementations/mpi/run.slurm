#!/bin/bash

#SBATCH --job-name=q5
#SBATCH --output=./out/%j.txt
#SBATCH --time=00:00:10
#SBATCH --nodes=2
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=5
#SBATCH --mem=1G
#SBATCH --partition=espec

export OMP_NUM_THREADS=5

mpirun -np 4 ./mat