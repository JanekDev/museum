#!/bin/bash

#clean the environment
rm /dev/shm/sem.SA
rm /dev/shm/sem.SB
rm /dev/shm/sem.mutexB

#compile with warning flags to ensure program correctness   
gcc reader.c -Wall -Wextra -o reader.out
gcc setup.c -Wall -Wextra -o setup.out

./setup.out $2 $3
#run producer and consumer
for ((i=0;i<$1;i++))
do
    gnome-terminal --title="Reader $i" -- sh -c "bash -c \"./reader.out; exec bash\""
done
