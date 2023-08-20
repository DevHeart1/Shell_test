#!/bin/bash

max_pid_limit=$(cat /proc/sys/kernel/pid_max)

echo "The maximum process ID (PID) value is: $max_pid_limit"
