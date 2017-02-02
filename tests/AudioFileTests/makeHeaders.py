from scikits.audiolab import wavread
import sys
import os

wavFiles = []

#==================================================================
def makeHeader (fileName, audioSignal, numChannels, bitRate, sampleRate, format):

	fileName = fileName.split (".")[0]
	variableName = fileName

	numSamples = audioSignal.shape[0]

	header = ""

	header += "#include <vector>"
	header += "\n\n"

	header += "namespace " + variableName + " { "
	header += "\n\n"

	header += "int numSamplesPerChannel = " + str (numSamples) + ";\n"
	header += "int bitDepth = " + str(bitRate) + ";\n"
	header += "int sampleRate = " + str(sampleRate) + ";\n"
	header += "\n"
	if numChannels == 1:
		header += "std::vector<double> testBuffer = "
	elif numChannels == 2:
		header += "std::vector<std::vector<double>> testBuffer = {"

	numSamples = 500 # override to prevent enormous file sizes

	for k in range (numChannels):

		header += "{"

		for i in range (numSamples):

			header += str (audioSignal.T[k][i])
			if i < (numSamples - 1): 
				header += ", "

		header += "}"
		if k < numChannels - 1:
			header += ", "

	if numChannels == 2:
		header += "}"

	header += ";"

	header += "\n\n"
	header += "}; // end namespace"

	text_file = open ("test-headers/" + variableName + ".h", "w")
	text_file.write (header)
	text_file.close()

# get all wav files
for fileName in os.listdir("test-audio"):
    if fileName.endswith(".wav"):
      	
		audioSignal,  fs,  enc  =  wavread ("test-audio/" + fileName)
		if len (audioSignal.shape) == 1:
			numChannels = 1
		elif len (audioSignal.shape) == 2:
			numChannels = 2
		else:
			assert (False)

		if enc == "pcmu8":
			makeHeader (fileName, audioSignal, numChannels, 8, fs, "wav")
		elif enc == "pcm16":
			makeHeader (fileName, audioSignal, numChannels, 16, fs, "wav")
		elif enc == "pcm24":
			makeHeader (fileName, audioSignal, numChannels, 24, fs, "wav")
		else:
			assert (False)
	



