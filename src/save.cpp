#include "4rer.h"

int save (int argc, char**argv) {
	int numSamples;
	if (fread(&numSamples, sizeof(int), 1, stdin)==0)
		die("fread failed");
	AudioFile<double>::AudioBuffer buffer;
        buffer.resize (2);
        buffer[0].resize (numSamples);
        buffer[1].resize (numSamples);
	fprintf(stderr, "num samples: %d\n size of sample: %d\n", numSamples, sizeof(buffer[0][0]));
        for (int channel = 0; channel < 2; channel++) { // for each channel
        	for (int j = 0; j < numSamples; j++) {
                	fread(&(buffer[channel][j]), sizeof(buffer[0][0]), 1, stdin);
		}
        }
	saveFile(argv[1], buffer, 44100, 24);
	return 0;
}

int main(int argc, char**argv) {
	if (argc != 2) {
		die("usage: ./save <destination file path>");
	}
	save(argc, argv);
	return 0;
}
