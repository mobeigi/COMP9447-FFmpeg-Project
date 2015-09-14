#! /usr/bin/python

import hashlib, inspect, os, re, select, sys, time

from subprocess import Popen, PIPE
def ck(a):
	try:
		d = open(os.devnull, 'w')
		subprocess.Popen([a], stdout = d, stderr = d).communicate()
		d.close()
	except OSError as e:
		# ENOENT
		if e.errno == os.errno.ENOENT:
			return False
	return True

def fe(ms):
	return
if __name__ == '__main__':


	while True:

		# calls the mutator
		cmd = "MutantHorse/MutantHorse ../test.flv ../mutated.flv".split()
		mutator = Popen(cmd, stdin=PIPE, stdout=PIPE, stderr=PIPE)
		
		
		# call process to print out "r"
		
		cmd = ['echo', 'r']
		print_r = Popen(cmd, stdout=PIPE)
		
		# call the program to be fuzzed
		cmd = "gdb --silent --return-child-result --args ../ffmpeg/ffmeg -i ../mutated.flv ../output.avi".split()
		check_return_code = Popen(cmd, stdin=print_r.stdout, stdout=PIPE, stderr=PIPE)
		
		# print return code and display
		print check_return_code.stdout.read();
		return_code = check_return_code.poll()
		print return_code
		break
				
