#include "4rer.h"
AudioFile<double>::AudioBuffer delay (int argc, char**argv) {
	AudioFile<double> src;
	src.load (argv[1]);
	AudioFile<double>::AudioBuffer buffer;
	float delayPercent = stod(argv[0]);
	int delay = delayPercent*src.getNumSamplesPerChannel();
        buffer.resize (2);
        buffer[0].resize (delay);
        buffer[1].resize (delay);
	memset(&buffer[0][0], 0, buffer[0].size() * sizeof(buffer[0][0]));
	memset(&buffer[1][0], 0, buffer[1].size() * sizeof(buffer[1][0]));
	saveFile(argv[2], buffer, 44100, 24);
//       	buffer = append(2, argv + 1);	
	// calculate delay time
	// create empty buffer with length of delay 
	// append to beginning of source
	// layer source and new file 

	for (int i = 0; i < argc-2; i++) {
                for (int channel = 0; channel < 2; channel++) { // for each channel
                        for (int j = 0; j < i; j++) {
                                
                        }
                }
        }

	return buffer;
}

int main(int argc, char**argv) {
	if (argc != 4) {
		die("usage: ./delay <delay percentage> <source file path> <destination file path>");
	}
	argv++;
	saveFile(argv[argc-2], delay(argc, argv), 44100, 24);
	return 0;
}
