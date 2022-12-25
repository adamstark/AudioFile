from scikits.audiolab import wavread, aiffread
import sys
import os

wavFiles = []

#==================================================================
def makeHeader (fileName, audioSignal, numChannels, bitRate, sampleRate, fileFormat):

	fileName = fileName.split (".")[0]
	variableName = fileName
	print fileName, bitRate
	numSamples = audioSignal.shape[0]

	header = ""

	header += "#include <vector>"
	header += "\n\n"

	header += "namespace " + variableName + " { "
	header += "\n\n"

	header += "int numSamplesPerChannel = " + str (numSamples) + ";\n"
	header += "int bitDepth = " + str(bitRate) + ";\n"
	header += "uint32_t sampleRate = " + str(sampleRate) + ";\n"
	header += "int numChannels = " + str(numChannels) + ";\n"
	header += "\n"
	if numChannels == 1:
		header += "std::vector<double> testBuffer = "
	else:
		header += "std::vector<std::vector<double>> testBuffer = {"

	numSamples = 500 # override to prevent enormous file sizes

	for k in range (numChannels):

		header += "{"

		for i in range (numSamples):

			if numChannels == 1:
				header += str (audioSignal[i])
			else:
				header += str (audioSignal.T[k][i])
			if i < (numSamples - 1):
				header += ", "

		header += "}"
		if k < numChannels - 1:
			header += ", "

	if numChannels > 1:
		header += "}"

	header += ";"

	header += "\n\n"
	header += "}; // end namespace"

	text_file = open ("test-headers/" + variableName + ".h", "w")
	text_file.write (header)
	text_file.close()

# get all wav files
for fileName in os.listdir("test-audio"):
    if fileName.endswith(".wav") or fileName.endswith(".aif"):

      	if fileName.endswith(".wav"):
      		audioSignal,  fs,  enc  =  wavread ("test-audio/" + fileName)
      		fileFormat = "wav"
      	elif fileName.endswith(".aif"):
      		audioSignal,  fs,  enc  =  aiffread ("test-audio/" + fileName)
      		fileFormat = "aif"
      	else:
      		assert (False)

      	if len (audioSignal.shape) == 1:
      		numChannels = 1
      	elif len (audioSignal.shape) == 2:
			numChannels = audioSignal.shape[1]
        else:
      	    assert (False)

      	#print fileName, enc

      	if enc == "pcmu8" or enc == "pcms8":
      		makeHeader (fileName, audioSignal, numChannels, 8, fs, fileFormat)
      	elif enc == "pcm16":
      		makeHeader (fileName, audioSignal, numChannels, 16, fs, fileFormat)
      	elif enc == "pcm24":
      		makeHeader (fileName, audioSignal, numChannels, 24, fs, fileFormat)
      	elif enc == "float32":
      		makeHeader (fileName, audioSignal, numChannels, 32, fs, fileFormat)
      	else:
      		print "Unknown bit depth:", enc
      		assert (False)
