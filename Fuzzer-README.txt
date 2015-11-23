== MutantHorse, Fuzzer.py (LINUX) ==

1. In config.conf, make these 2 lines consistent:
	- fuzzer_path: change it to where the MutantHorse program is located
	- program_path: change it to where the program to fuzz is located

2. Go into the MutantHorse directory, and compile the MutantHorse program using the command 'make'

3. Run using the terminal command: 
	python Fuzzer.py

4. Sit back and relax. Make sure to skim through the results folder inside FileVault
	Note: Use screen if you don't want to keep an active shell open
