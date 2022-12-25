#include <iostream>
#include "../../lib/AudioFile/AudioFile.h"
#include <math.h>
using namespace std;

void die (const char*msg) {
	cout << msg << endl;
	exit(1);
}

int main(int argc, char**argv) {
	if (argc != 2) {
		die("usage: ./printInfo <source file path>");
	}
	AudioFile<double> file;
        file.load(argv[1]);
	file.printSummary();

	return 0;
}
