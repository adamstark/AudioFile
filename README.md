4rier - Digital Audio Workstation with Command Line Interface

Functions:

Print File Info: ./printInfo

	usage: ./printInfo <source file path>

Adjust Volume: ./vol

	usage: ./vol <volume multiplier> <source file path> <destination file path>

Append File: ./append

	usage: ./append <source file path> <source file path> ... <destination file path>

Bitcrusher: ./bcrush

	usage: ./bcrush <bit depth> <sample rate multiplier> <source file path> <target file path>

	Notes:
		<bit depth> must be 8, 16, or 24, and can't exceed the source file's current bit depth

Layer Files: ./layer

	usage: ./layer <source path> <source path> ... <destination path>

	Notes:
		Files will be merged together, all beginning at the start of the file.
		Destination file length will be the longest of the source files

Schroeder Comb Filter: ./schroeder
	
	usage: usage: ./schroeder <g> <# iterations> <delay in samples> <source file path> <destination file path>

	Notes: https://hajim.rochester.edu/ece/sites/zduan/teaching/ece472/reading/Schroeder_1962.pdf 


https://www.ee.columbia.edu/~dpwe/e4896/papers/StautP82-reverb.pdf

