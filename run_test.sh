#!/bin/bash

# Case parameters
n="1000"
m="10000"
m_member="0.99"
m_insert="0.005"
m_delete="0.005"
case_version=1

program_list=("parallelOneMutex" "parallelReadWrite")
thread_list=("1" "2" "4" "8")

for program in "${program_list[@]}"; do

    # echo $program
    code=$program".c"
    executable=$program

    gcc $code -o $executable -g
    
    for threads in "${thread_list[@]}"; do

        filename="./results/"$program"_c"$case_version"_"$threads"t.txt"

        command="./$executable $threads $n $m $m_member $m_insert $m_delete $filename"

        num_times=385

        for i in $(seq 1 $num_times);
        do
            $command
        done
    done
done