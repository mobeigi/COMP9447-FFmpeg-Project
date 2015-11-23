#! /usr/bin/python

import ConfigParser
import os, binascii
import signal
import subprocess
import sys

from shutil import copy2
import time

def check_process_exists(process_path, devnull):
	try:
		process = subprocess.Popen([process_path], stdout=devnull, stderr=devnull).communicate()
	except OSError as err:
		if err.errno == os.errno.ENOENT:
			return False
	return True

def sigterm_handler(a, b):
	print "%s, %s" % (a, b)
	sys.exit()

if __name__ == '__main__':
	devnull = open(os.devnull, 'w')

	config = ConfigParser.ConfigParser()
	config.read('Config.conf')

	signal.signal(signal.SIGTERM, sigterm_handler)

	# check if our mutator and program we are fuzzing exists
	if check_process_exists(config.get('General','fuzzer_path'), devnull) == False:
		print "Fuzzer process doesn't exist"
	if check_process_exists(config.get('General','program_path'), devnull) == False:
		print "Program path doesn't exist"



	# check if seed file exists
	if not os.path.exists(config.get('General','input_folder_path')):
		sys.exit(1)
	input_file_path = config.get('General','input_folder_path') + 'test.flv'
	if not os.path.exists(input_file_path):
		sys.exit(1)
	mutated_file_path = config.get('General','input_folder_path') + 'mutated.flv'
	output_file_path = config.get('General','output_folder_path') + 'output.avi'

	# check if file logging folder exists
	if not os.path.exists(config.get('General','output_folder_path')):
		os.mkdir(config.get('General','output_folder_path'))
	if not os.path.exists(config.get('General','results_folder_path')):
		os.mkdir(config.get('General','results_folder_path'))

	while (True):

		if (os.path.exists(output_file_path)):		
			print "File exists!! There is an issue, and You are AWESOME!"

		# calls the mutator
		cmd = [config.get('General','fuzzer_path'), input_file_path, mutated_file_path]
		mutator = subprocess.Popen(cmd, stdout=devnull, stderr=devnull)

		# call process to print out "r"
		cmd = ['echo', 'r']
		print_r = subprocess.Popen(cmd, stdout=subprocess.PIPE)

		# call the program to be fuzzed
		cmd = "gdb --silent --return-child-result --args".split()
		cmd = cmd + [config.get('General','program_path'), "-i", mutated_file_path, output_file_path]
		gdb_output = subprocess.Popen(cmd, stdin=print_r.stdout, stdout=devnull, stderr=devnull)

		# wait for gdb to terminate
		gdb_output.wait()

		# get return signal
		return_code = gdb_output.poll()

		# make mutated file our new seed
		copy2(mutated_file_path, input_file_path)
		os.remove(mutated_file_path)

		# otherwise store and clean up for repeat
		# 0: successful execution
		# 1: file exists, or empty file outputted
		# 69: conversion failure
		if (return_code != 0 and return_code != 1 and return_code != 69):

			files_to_copy = [input_file_path, output_file_path]
			while True:
				rand = time.strftime("%d%m%Y")
				rand += '_'  + binascii.b2a_hex(os.urandom(16)) + "_" + str(return_code)
				if not os.path.exists(config.get('General','results_folder_path') + rand):
					break
			os.mkdir(config.get('General','results_folder_path') + rand)
			files_to_copy.append(mutated_file_path)
			for fn in files_to_copy:
				if os.path.exists(fn):
					tempstr = config.get('General', 'results_folder_path') + rand + "/" + os.path.basename(fn)
					copy2(fn, tempstr)

		if (os.path.exists(output_file_path)):		
			os.remove(output_file_path)
			
