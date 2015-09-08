#! /usr/bin/python

import inspect, os, re, subprocess, sys 
# cmd output for the ck() function
def ec(a):
	c = ''
	print ' - - - - - - - - - - - - - - - - - - - - '	
	for b in a:
		if ck(b) == True:
			print ' + %s: Found... ' % b
			c = b
		else:
			print ' + %s: Not Found... ' % b
	if not c:
		fi = inspect.getframeinfo(inspect.currentframe())
		print ' - - - - - - - - - - - - - - - - - - - - '	
		print ' + sys.exit() ' + inspect.stack()[0][3] + ' ' + str(fi.lineno)
		print ' - - - - - - - - - - - - - - - - - - - - '	
		sys.exit()
	print ' - - - - - - - - - - - - - - - - - - - - '	

# check if subprocess exists...	
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
	for i in sys.argv:
		if re.s
	ps = []
	ms = []
	ec(ps)
	ec(ms)
	
	# RUN MS - START LOOP HERE?
