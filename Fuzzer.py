#! /usr/bin/python

import hashlib, inspect, os, re, select, sys, time

from subprocess import Popen, PIPE

if __name__ == '__main__':


	while True:

		# calls the mutator
		cmd = "".split() # add mutator <input> <output>
		mutator = Popen(cmd, stdin=PIPE, stdout=PIPE, stderr=PIPE)
		
		# call the program to be fuzzed
		cmd = "(echo r) | gdb --silent --return-child-result --args ffmpeg/ffmeg -i mutated.flv output.avi > /dev/null 2>&1; echo $?".split()
		check_return_code = Popen(cmd, stdin=PIPE, stdout=PIPE, stderr=PIPE)
		
		# print return code and display
		return_code = check_return_code.poll()
		print return_code
		break
			
