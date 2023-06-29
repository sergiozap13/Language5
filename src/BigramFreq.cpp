/*
 * Metodología de la Programación: Language3
 * Curso 2022/2023
 */

/**
 * @file BigramFreq.cpp
 * @author estudiante1: Zapata De la Hoz, Sergio
 * Created on 12 February 2023, 10:40
 */

#include <string>

#include "BigramFreq.h"

using namespace std;

BigramFreq::BigramFreq():_bigram("__"), _frequency(0) {
}

const Bigram& BigramFreq::getBigram() const {
    return _bigram;
}
int BigramFreq::getFrequency() const {
    return _frequency;
}

void BigramFreq::setBigram(const Bigram& bigram) {
    this->_bigram = bigram;
}

void BigramFreq::setFrequency(int frequency) {
    if(frequency<0){
        throw  std::out_of_range(string("void BigramFreq::setFrequency(int frequency): ") +
                "invalid frecuency " + to_string(frequency));
    }
    this->_frequency = frequency;
}

string BigramFreq::toString() const {
    return _bigram.toString() + " " + to_string(_frequency);
}

std::ostream& operator<<(std::ostream &os, const BigramFreq &bigramFreq){
    os << bigramFreq.toString();
    return os;
}

std::istream& operator>>(std::istream &is, BigramFreq &bigramFreq){
    Bigram b;
    is >> b;
    bigramFreq.setBigram(b);
    int f = 0;
    is >> f;
    
    
    bigramFreq.setFrequency(f);
    
    return is;
}

bool operator>(const BigramFreq &bigramFreq1, const BigramFreq &bigramFreq2){
return (bigramFreq1.getFrequency() > bigramFreq2.getFrequency()) ||
           ((bigramFreq1.getFrequency() == bigramFreq2.getFrequency()) &&
            bigramFreq1.getBigram().getText() < bigramFreq2.getBigram().getText());
}

bool operator<(const BigramFreq &bigramFreq1, const BigramFreq &bigramFreq2){
    return (bigramFreq1.getFrequency() < bigramFreq2.getFrequency()) ||
           ((bigramFreq1.getFrequency() == bigramFreq2.getFrequency()) &&
            bigramFreq1.getBigram().getText() > bigramFreq2.getBigram().getText());
}

bool operator==(const BigramFreq &bigramFreq1, const BigramFreq &bigramFreq2){
    // @return true if the two bigrams contains the same pair Bigram-Frequency;
 //  * false otherwise
    return ((bigramFreq1.getBigram().getText() == bigramFreq2.getBigram().getText()) &&
                bigramFreq1.getFrequency() == bigramFreq2.getFrequency());
}

bool operator!=(const BigramFreq &bigramFreq1, const BigramFreq &bigramFreq2){
    //@return true if the two bigramFreq1 are not equals (see operator==); 
 //* false otherwise
    return !((bigramFreq1.getBigram().getText() == bigramFreq2.getBigram().getText()) &&
                bigramFreq1.getFrequency() == bigramFreq2.getFrequency());
}

bool operator<=(const BigramFreq &bigramFreq1, const BigramFreq &bigramFreq2){
    // @return true if the bigramFreq1 <= bigramFreq2; false otherwise
    return bigramFreq1 < bigramFreq2 || bigramFreq1 == bigramFreq2;
}

bool operator>=(const BigramFreq &bigramFreq1, const BigramFreq &bigramFreq2){
    // @return true if the bigramFreq1 >= bigramFreq2
    return bigramFreq1 > bigramFreq2 || bigramFreq1 == bigramFreq2;
}




