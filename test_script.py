#!/usr/bin/python

import os
import subprocess


#benchmarks = ['fwt4']
benchmarks = ['convtex', 'dct', 'dxtc', 'hist', 'fwt', 'Blackscholes']
#works = ['bin','bin_new_journal','bin_XYYX', 'bin_new', 'bin_DA2', 'bin_cfnoc']
count = 0
for bench in benchmarks:
	subprocess.call(['./test_script_faster.sh', bench, str(count)])
	count += 1
	
