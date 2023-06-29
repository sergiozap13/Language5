/*
 * Metodolog√≠a de la Programaci√≥n: Language5
 * Curso 2022/2023
 */

/** 
 * @file BigramCounter.cpp
 * @author estudiante1: Zapata De la Hoz, Sergio
 * 
 * Created on 12 February 2023, 11:00
 */
using namespace std;

#include <fstream>

#include "BigramCounter.h"

/**
 * DEFAULT_VALID_CHARACTERS is a c-string that contains the set of characters
 * that will be considered as part of a word (valid chars). 
 * The characters not in the c-string will be considered as separator of words.
 * The constructor of the class BigramCounter uses this c-string as a 
 * default parameter. It is possible to use a different c-string if that
 * constructor is used with a different c-string
 */
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";

BigramCounter::BigramCounter(std::string validChars){
  
    this->_validCharacters = validChars;
    int tam = this->_validCharacters.size();
    
    this->_frequency = allocate();
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            this->_frequency[i][j] = 0;
        }
    }
}
// constructor de copia
BigramCounter::BigramCounter(const BigramCounter &orig){
    this->_validCharacters = DEFAULT_VALID_CHARACTERS;
    if(this->getSize() > 0){
        this->_frequency = allocate();
        this->copyMatrix(orig);
    }
}

BigramCounter::~BigramCounter(){
    deallocate(this->_frequency);
}

int BigramCounter::getSize() const{
    return this->_validCharacters.size();
}

int BigramCounter::getNumberActiveBigrams() const{
    int counter = 0;
    for(int i = 0; i < this->getSize(); i++){
        for(int j = 0; j < this->getSize(); j++){
            if(this->_frequency[i][j] > 0){
                counter++;
            }
        }
    }
    return counter;
}

bool BigramCounter::setFrequency(const Bigram &bigram, int frequency){
    if(isValidCharacter(bigram.at(0), this->_validCharacters) && isValidCharacter(bigram.at(1), this->_validCharacters)){
        int pos1 = findChar(bigram.at(0)); // buscamos el 
        int pos2 = findChar(bigram.at(1));
        this->_frequency[pos1][pos2] = frequency;
        return true;
    }
    return false;
}

void BigramCounter::increaseFrequency(const Bigram &bigram, int frequency){
    if(!isValidCharacter(bigram.at(0), this->_validCharacters) || !isValidCharacter(bigram.at(1), this->_validCharacters)){
        throw std::out_of_range(std::string("void BigramCounter::increaseFrequency: bigram not found "));
    }
    this->_frequency[findChar(bigram.at(0))][findChar(bigram.at(1))] += frequency;
}

BigramCounter& BigramCounter::operator=(const BigramCounter &orig){
    if(this != &orig){
        if(this->getSize() > 0){
            deallocate(this->_frequency);
        }
        
        // reservar 
        this->_frequency = allocate();
        
        // copiar matriz
        this->copyMatrix(orig);
    }
    
    return *this;
}

BigramCounter& BigramCounter::operator+=(const BigramCounter &rhs){
    if(this->getSize() == rhs.getSize()){
        for(int i = 0; i < this->getSize(); i++){
            for(int j = 0; j < this->getSize(); j++){
                this->_frequency[i][j] += rhs(i,j);
            }
        }
    }
    
    return *this;
}

void BigramCounter::calculateFrequencies(char* fileName){
    ifstream file;
    file.open(fileName);
    if(!file){
        throw std::ios_base::failure("The file " + std::string(fileName) + " can¥t be opened ");
    }
    
    string text="";
    char primer_char, segundo_char;
    //Bigram bigram_aux;
    while(getline(file,text)){
        // si el texto no es vacÌo
        if(text != ""){
           for(int i = 0; i < text.size() -1; i++){
                primer_char = tolower(text.at(i));
                segundo_char = tolower(text.at(i+1));
                if(isValidCharacter(primer_char, this->_validCharacters) && isValidCharacter(segundo_char, this->_validCharacters)){
                   Bigram bigram_aux(primer_char, segundo_char);
                   increaseFrequency(bigram_aux, 1);
                }
            } 
        }
    }
    
    file.close();
}

Language BigramCounter::toLanguage() const{
    Language lang(this->getNumberActiveBigrams());
    BigramFreq bigram_freq_aux;
    int language_pos = 0;
    for(int i = 0; i < this->getSize(); i++){
        for(int j = 0; j < this->getSize(); j++){
            if(this->_frequency[i][j] > 0){
                Bigram b1(this->_validCharacters[i], this->_validCharacters[j]);
                bigram_freq_aux.setBigram(b1);
                bigram_freq_aux.setFrequency(this->_frequency[i][j]);
                lang.at(language_pos) = bigram_freq_aux;
                language_pos++;
            }
        }
    }
    
    return lang;
}

// mÈtodos privados

const int& BigramCounter::operator()(int row, int column) const{
    return this->_frequency[row][column];
}

int& BigramCounter::operator()(int row, int column){
    return this->_frequency[row][column];
}
// uso un array de punteros a array de enteros
// siempre se reserva n x n valores, siendo n el numero de caracteres validos
int** BigramCounter::allocate(){
    int **ptr = nullptr;
    if(this->_validCharacters.size() > 0){
        ptr = new int*[this->_validCharacters.size()];
        
        for(int i = 0; i < this->_validCharacters.size(); i++){
            ptr[i] = new int[this->_validCharacters.size()];
        }
    }
    return ptr;
}

void BigramCounter::deallocate(int ** ptr){
    for(int i = 0; i < this->_validCharacters.size(); i++){
        delete [] ptr[i];
    }
    delete [] ptr;
}

int BigramCounter::findChar(char bigram_caracter) const{
    for (int i = 0; i < getSize(); i++) {
        if (this->_validCharacters[i] == bigram_caracter) {
            return i;
        }
    }
}

void BigramCounter::copyMatrix(const BigramCounter &to_copy){
    for(int i = 0; i < this->getSize(); i++){
        for(int j = 0; j < this->getSize(); j++){
            this->_frequency[i][j] = to_copy(i,j);
        }
    }
}

