/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file JOIN.cpp
 * @author estudiante1: Zapata De la Hoz, Sergio
 * 
 * Created on 29 January 2023, 11:00
 */


using namespace std;
#include <fstream>
#include <iostream>

#include "Language.h"
/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>] " << endl;
    outputStream << "       join the Language files <file1.bgr> <file2.bgr> ... into <outputFile.bgr>" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-o <outputFile.bgr>: name of the output file (output.bgr by default)" << endl;
    outputStream << "<file*.bgr>: each one of the files to be joined" << endl;
}

/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally, the resulting Language is saved in an output file. The 
 * program must have at least an output file. 
 * Running example:
 * >  JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char* argv[]) {
    bool params_ok = true;
    
    // procesamiento de par�metros
    if(argc < 2){
        showEnglishHelp(cout);
        exit(1);
    } else {
        int pos_param_t = 0, pos_param_b = 0, pos_param_o = 0, salto = 1;
        bool param_t = false, param_b = false, param_o = false;
        
        for(int i = 1; i < argc; i++){
            string param = argv[i];
            
            if(param == "-t"){
                if(!param_b){
                   param_t = true;
                   pos_param_t = i;
                   salto += 1;
                   
                } else {
                    params_ok = false;
                    pos_param_t = 0;
                }
            } else if(param == "-b"){
                if(!param_t){
                    param_b = true;
                    pos_param_b = i;
                    salto += 1;
                } else{
                    params_ok = false;
                    pos_param_b = 0;
                }
            } else if(param == "-o"){
                param_o = true;
                pos_param_o = i;
                salto += 2;
            } else if(param.length() > 4){ // para los parametros que no sean opcionales (-l -o)
                if(param.substr(param.length() - 4) == ".bgr")
                    continue;
            } else {
                params_ok = false;
            }
        }
        
        if(!params_ok){
            showEnglishHelp(cout);
            exit(1);
        } else {
            Language result_lang, aux_lang; 
            
            for(int i = salto; i < argc; i++){
                aux_lang.load(argv[i]);
                if(i == salto)
                    result_lang.setLanguageId(aux_lang.getLanguageId());
                result_lang += aux_lang;
            }
            
            result_lang.sort();
            
            if(param_o){
                param_b ? result_lang.save(argv[pos_param_o + 1], 'b') : result_lang.save(argv[pos_param_o + 1]);
            } else {
                result_lang.save("outputFile.bgr");
            }
            return 0;
        }
    }
}
    



