#!/bin/sh

lscpu | grep "NUMA node[01]" | cut -d":" -f2 | tr -d " " | tr "\n" "," | sed 's/,$/\n/g'
