#! /usr/bin/python

import hashlib, inspect, os, re, select, subprocess, sys, time
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
	mutator = './MutantHorse/MutantHorse'
	tofuzz = 'ffmpeg'
	inputfn = '"/Users/jsfn660/Dropbox/Security Workshop Project/Video files for Testing/test.flv"'
	debug = 'lldb'

	i = 0
	while True:
		crashed = 0
		i += 1

		# calls the mutator
		outputfn =  'output.flv'
		cmd = ' '.join([mutator, inputfn, outputfn])
		os.system(cmd)

		# opens the program to be fuzzed
		cmd = [debug, tofuzz, '--', '-i' ,outputfn, 'pisspot.flv']
		process = subprocess.Popen(cmd, stdin=subprocess.PIPE,  stdout=subprocess.PIPE,  stderr=subprocess.PIPE)

		# reads stdout + stderr from the fuzzed program
		while True:
				sys.stdout.write(process.stdout.readline())
		crashed = process.poll()
		print crashed
		if(crashed != 0):
			print 'crashed'
		else:
			print 'no crash detected'

		break
