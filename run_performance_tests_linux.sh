#!/bin/sh

sudo cpupower frequency-set --governor performance
./build/linux_x86/performance_tests
sudo cpupower frequency-set --governor powersave
