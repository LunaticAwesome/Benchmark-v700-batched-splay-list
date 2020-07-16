#!/bin/bash

docker exec -t setbench bash -c "cd microbench_experiments/example ; ./run_testing.sh"
docker exec -t setbench bash -c "cd macrobench_experiments/istree_exp1 ; ./run_testing.sh"
ssh -oStrictHostKeyChecking=no -p 2222 root@localhost -t "ls"
