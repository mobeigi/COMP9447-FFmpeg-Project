#! /usr/bin/python

import os
import signal
import subprocess

check_process_exists(process_path, devnull):
	try:
		process = subprocess.Popen([process_path], stdout=devnull, stder=devnull).communicate()
	except OSError as err:
		if err.errno == os.errno.ENOENT:
			return False
	return True

sigterm_handler(a, b):
	print "%s, %s" % (a, b)

if __name__ == '__main__':
	devnull = open(os.devnull, 'w')
	signal.signal(signal.SIGTERM, sigterm_handler)

	# check if our mutator and program we are fuzzing exists
	check_process_exists("MutantHorse/MutantHorse", devnull)
	check_process_exists("../ffmpeg/ffmpeg", devnull)

	while True:

		# calls the mutator
		cmd = "MutantHorse/MutantHorse ../test.flv ../mutated.flv".split()
		mutator = subprocess.Popen(cmd, stdout=devnull, stderr=devnull)

		# call process to print out "r"
		cmd = ['echo', 'r']
		print_r = subprocess.Popen(cmd, stdout=subprocess.PIPE)

		# call the program to be fuzzed
		cmd = "gdb --silent --return-child-result --args ../ffmpeg/ffmpeg -i ../mutated.flv ../output.avi".split()
		gdb_output = subprocess.Popen(cmd, stdin=print_r.stdout, stdout=devnull, stderr=devnull)

		# wait for gdb to terminate
		gdb_output.wait()

		# get return signal
		return_code = gdb_output.poll()

		# if return_code is normal, delete mutated and mutated output
		if return_code == 0 or return_code  == 1:
			files_to_remove = ["../mutated.flv", "../output.avi"]
			for file in files_to_remove:
				if os.path.exists(file):
					os.remove(file)
			continue

		# otherwise store the mutated output file in a new folder and continue
		os.mkdir('')
