#!/bin/sh

sudo cpupower frequency-set --governor performance
../../build/linux/performance_tests "$@"
sudo cpupower frequency-set --governor powersave
