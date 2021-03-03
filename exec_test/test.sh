#!/bin/bash

gcc search_env.c exec_cmd.c -o exec_test -L. -lft
./exec_test $1 #$(cmd)#
