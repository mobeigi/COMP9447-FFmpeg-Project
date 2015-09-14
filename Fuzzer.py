#! /usr/bin/python

import hashlib, inspect, os, re, select, sys, time

import subprocess
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
	devnull = open(os.devnull, 'w')

	while True:

		# calls the mutator
		cmd = "MutantHorse/MutantHorse ../test.flv ../mutated.flv".split()
		mutator = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
		
		
		# call process to print out "r"
		
		cmd = ['echo', 'r']
		print_r = subprocess.Popen(cmd, stdout=subprocess.PIPE)
		
		# call the program to be fuzzed
		cmd = "gdb --silent --return-child-result --args ../ffmpeg/ffmpeg -i ../mutated.flv ../output.avi".split()
		gdb_output = subprocess.Popen(cmd, stdin=print_r.stdout, stdout=devnull, stderr=devnull)

		gdb_output.wait()		
		
		# print return code and display
		return_code = gdb_output.poll()
		print return_code
		break
				

