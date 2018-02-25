#!/usr/bin/python

import os
import subprocess


#benchmarks = ['fwt4']
benchmarks = ['dct', 'dxtc','convtex','fwt', 'hist', 'Blackscholes']
#works = ['bin','bin_new_journal','bin_XYYX', 'bin_new', 'bin_DA2', 'bin_cfnoc']

for bench in benchmarks:
	subprocess.call(['./test_script_faster.sh', bench])
	
