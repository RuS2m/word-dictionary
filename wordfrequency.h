#ifndef WORDFREQUENCY_H
#define WORDFREQUENCY_H

#include <map>
#include <string>

class WordsFrequency {
private:
    const char* input_file;
    const char* output_file;
    std::map<std::string, int> frequencies;
    
public:
    WordsFrequency()=default;
    WordsFrequency(const char* in, const char* out);
    ~WordsFrequency()=default;
    void process();
    void print();
};

#endif
