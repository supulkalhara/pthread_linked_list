#!/bin/bash
program="parallelOneMutex"

code=$program+".c"
executable=$program
n="1000"
m="10000"
m_member="0.99"
m_insert="0.005"
m_delete="0.005"

threads="1"
filename="./results/oneMutex_3t.txt"

gcc $code -o $executable -g

command="./$executable $threads $n $m $m_member $m_insert $m_delete"

num_times=385

for i in $(seq 1 $num_times);
do
    $command
done