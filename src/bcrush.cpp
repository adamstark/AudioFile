#include "4rer.h"


double setDigits(double _number, int _digits)
{
    double tenth = pow((double)10,_digits);
    _number *= tenth;
    _number = floor(_number);
    _number /= tenth;

    return _number;
}

int bcrush (int bdCurr, int bdNew, double srMult, int numSamples, AudioFile<double>::AudioBuffer *buffer) {
	if (bdCurr < bdNew){
                die("bit depth can't exceed original bit depth"); }
                
        int shift = bdCurr - bdNew;

	for (int channel = 0; channel < 2; channel++) { // for each channel
                for (int j = 0; j < numSamples; j++) {
                        // cout << file.samples[channel][j] << endl;
                        if (shift > 0)
                               // (*buffer)[channel][j] = ((*buffer)[channel][j]) / (2^shift);
                        	(*buffer)[channel][j] = setDigits((double) (*buffer)[channel][j], bdNew);
				// cout << file.samples[channel][j] << endl; 
                }
        }

	return numSamples;
}

int main(int argc, char**argv) {
	if (argc < 3 || argc > 5) {
		die("usage: ./bcrush <bit depth> <sample rate multiplier> <source file path> <target file path>");
	}
	int bd = stoi(argv[1]);
	double sr  = stod(argv[2]);
	int bitDepth;
	int numSamples;
	AudioFile<double>::AudioBuffer buffer;
	if (argc>3) {
		AudioFile<double> file;
        	file.load(argv[3]);
		bitDepth = file.getBitDepth();
		numSamples = readSamplesFromFile(&buffer, file);
	} else {
		bitDepth = 24;
		numSamples = readSamplesFromInput(&buffer);
	}

	bcrush(bitDepth, bd, sr, numSamples, &buffer);
	
	if (argc == 5) { saveFile(argv[4], buffer, 44100, 24); }
	else if (argc==4) { saveFile(argv[3], buffer, 44100, 24);}
	else { writeBuffer(&buffer, numSamples); }

	return 0;
}
