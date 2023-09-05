#!/bin/bash

executable="parallelOneMutex"
threads="3"
n="1000"
m="10000"
m_member="0.99"
m_insert="0.005"
m_delete="0.005"

command="./$executable $threads $n $m $m_member $m_insert $m_delete"

num_times=196

# for i in {1..$num_times}; do
#     $command
# done

for i in $(seq 1 $num_times);
do
    $command
done