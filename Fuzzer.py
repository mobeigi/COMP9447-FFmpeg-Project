#! /usr/bin/python

import ConfigParser
import os
import signal
import subprocess

from shutil import copy2

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

	config = ConfigParser.ConfigParser()
	config.read('Config.conf')

	signal.signal(signal.SIGTERM, sigterm_handler)

	# check if our mutator and program we are fuzzing exists
	check_process_exists(config.get('fuzzer_path'), devnull)
	check_process_exists(config.get('program_path'), devnull)

	# check if seed file exists
	if not os.path.exists('input_folder_path'):
		return 1
	input_file_path = config.get('input_folder_path') . 'input.flv'
	if not os.path.exists(input_file_path):
		return 1
	mutated_file_path = config.get('input_folder_path') . 'mutated.flv'
	output_file_path = config.get('input_folder_path') . 'output.avi'

	# check if file logging folder exists
	if not os.path.exists(config.get('output_folder_path')):
		os.mkdir(config.get('output_folder_path'))

	while True:

		# calls the mutator
		cmd = [config.get('fuzzer_path'), input_file_path, mutated_file_path]
		mutator = subprocess.Popen(cmd, stdout=devnull, stderr=devnull)

		# call process to print out "r"
		cmd = ['echo', 'r']
		print_r = subprocess.Popen(cmd, stdout=subprocess.PIPE)

		# call the program to be fuzzed
		cmd = "gdb --silent --return-child-result --args".split()
		cmd = cmd + [config.get('program_path'), mutated_file_path, output_file_path]
		gdb_output = subprocess.Popen(cmd, stdin=print_r.stdout, stdout=devnull, stderr=devnull)

		# wait for gdb to terminate
		gdb_output.wait()

		# get return signal
		return_code = gdb_output.poll()

		# if return_code is normal, delete mutated and mutated output
		files_to_remove = [input_file_path, output_file_path]
		if return_code == 0 or return_code == 1:
			for fn in files_to_remove:
				if os.path.exists(fn):
					os.remove(fn)
			continue

		# make mutated file our new seed
		copy2(mutated_file_path, input_file_path)
		os.remove(mutated_file_path)

		# otherwise store and clean up for repeat
		while True:
			rand = time.strftime("%d%m%Y")
			rand = '_'.join(rand, os.urandom(16))
			if not os.path.exists(config.get('output_folder_path') + rand):
				break
		os.mkdir(config('output_folder_path') + rand)
		file_to_remove.append(mu)
		for fn in file_to_remove:
			if os.path.exists(fn):
				copy2(fn, "/".join(config.get('output_folder_path'), rand, os.basename(fn)))
				os.remove(fn)
		break
