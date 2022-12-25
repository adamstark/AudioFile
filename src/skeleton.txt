#include "4rer.h"

int schroeder (int argc, char**argv) {
	AudioFile<double> file;
	AudioFile<double>::AudioBuffer buffer;
	int numSamples;
	if (argc > 4) {
        	file.load(argv[4]);
		numSamples = readSamplesFromFile(&buffer, file);
		//numSamples = file.getNumSamplesPerChannel();
        } else {
		numSamples = readSamplesFromInput(&buffer);
	}
	float g = stod(argv[1]);
	int delay = atoi(argv[3]);
	for (int f = 0; f < atoi(argv[2]); f++) {
                	for (int channel = 0; channel < 2; channel++) { // for each channel
				for (int j = delay; j < numSamples; j++) {
					buffer[channel][j] = (1-g)*buffer[channel][j] + g*buffer[channel][j-delay];
				}
        	        }
	}
	if (argc == 6) { saveFile(argv[5], buffer, 44100, 24); }
	else if (argc==5) { saveFile(argv[4], buffer, 44100, 24);}
	else { writeBuffer(&buffer, numSamples); }
	return 0;
}

int main(int argc, char**argv) {
	if (argc < 4 || argc > 6) {
		die("usage: ./schroeder <g> <# iterations> <delay in samples> <source file path> <destination file path>");
	}
	if (stod(argv[1]) > 1 || stod(argv[1]) < 0)
		die("g must be between 0 and 1");
	schroeder(argc, argv);
	return 0;
}
