#!/bin/bash

# Case parameters
n="1000"
m="10000"
m_member="0.5"
m_insert="0.25"
m_delete="0.25"
case_version=3

program_list=("parallelOneMutex" "parallelReadWrite")
thread_list=("1" "2" "4" "8")

for program in "${program_list[@]}"; do

    # echo $program
    code=$program".c"
    executable=$program

    gcc $code -o $executable linkedList.c -g
    
    for threads in "${thread_list[@]}"; do

        filename="./results2/"$program"_c"$case_version"_"$threads"t.txt"

        command="./$executable $threads $n $m $m_member $m_insert $m_delete $filename"

        num_times=500

        for i in $(seq 1 $num_times);
        do
            $command
        done
    done
done