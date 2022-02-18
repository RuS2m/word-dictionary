#include <fstream>
#include <map>
#include <iostream>
#include <set>
#include <string>
#include "wordfrequency.h"

struct comp
{
    bool operator()(const std::pair<std::string, int> &l, const std::pair<std::string, int> &r) const
    {
        if (l.second != r.second) {
            return l.second > r.second;
        }
        return l.first < r.first;
    }
};

WordsFrequency::WordsFrequency(const char* in, const char* out) {
    input_file = in;
    output_file = out;
};

void WordsFrequency::process() {
    std::wifstream is;
    is.open(input_file);
    if (is.fail()) {
        fprintf(stderr, "Error: cannot open file %s\n", input_file);
	is.close();
	exit(1);
    }
    wchar_t wide_ch;
    std::string word;
    while(is.get(wide_ch)) {
        if (std::iswalpha(wide_ch)) {
	    word.push_back(static_cast<char>(wide_ch));
	} else if (!word.empty()) {
	    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
	    ++frequencies[word];
	    word.clear();
	}	
    }
    is.close();
}

void WordsFrequency::print() {
    std::ofstream os;
    os.open(output_file);
    if (os.fail()) {
        fprintf(stderr, "Error: cannot open file %s\n", output_file);
        os.close();
	exit(1);
    }
    std::set<std::pair<std::string, int>, comp> sorted_frequencies_pairs(frequencies.begin(), frequencies.end());
    for (auto elem : sorted_frequencies_pairs) {
        os << elem.second << " " << elem.first << std::endl;
    }
    os.close();
}
