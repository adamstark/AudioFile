#include "4rer.h"

int open (int argc, char**argv) {
	AudioFile<double> file;
        file.load(argv[1]);
	int numSamples = file.getNumSamplesPerChannel();
        fwrite(&numSamples, sizeof(int), 1, stdout);
	fprintf(stderr, "num samples: %d\n size of sample: %d\n", numSamples, sizeof(file.samples[0][0]));
	for (int channel = 0; channel < 2; channel++) { // for each channel
        	for (int j = 0; j < numSamples; j++) {
                	fwrite(&file.samples[channel][j], sizeof(file.samples[0][0]), 1, stdout);
                }
        }
	return 0;
}

int main(int argc, char**argv) {
	if (argc != 2) {
		die("usage: ./open <source file path>");
	}
	open(argc, argv);
	return 0;
}
