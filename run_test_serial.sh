#!/bin/bash

# Case parameters
n="1000"
m="10000"
m_member="0.5"
m_insert="0.25"
m_delete="0.25"
case_version=3


filename="./results/serial_c"$case_version"_"$threads"t.txt"

command="./serial $n $m $m_member $m_insert $m_delete $filename"

num_times=385

for i in $(seq 1 $num_times);
do
    $command
done
