#include <iostream>
#include "wordfrequency.h"

int main(int argc, char** argv) {
    if (argc < 3) {
	std::cerr << "Error: missing an argument" << std::endl;
	return 1;
    }
    WordsFrequency wf = WordsFrequency(argv[1], argv[2]);
    wf.process();
    wf.print();
    return 0;
}
