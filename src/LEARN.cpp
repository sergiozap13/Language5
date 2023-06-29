/*
 * Metodolog√≠a de la Programaci√≥n: Language5
 * Curso 2022/2023
 */

/** 
 * @file LEARN.cpp
 * @author estudiante1: Zapata De la Hoz, Sergio
 * 
 * Created on 29 January 2023, 11:00
 */
using namespace std;


#include <iostream>
#include <fstream>
#include "BigramCounter.h"

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> .... ]" << endl;
    outputStream << "           learn the model for the language languageId from the text files <text1.txt> <text2.txt> <text3.txt> ..." << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-l languageId: language identifier (unknown by default)" << endl;
    outputStream << "-o outputFilename: name of the output file (output.bgr by default)" << endl;
    outputStream << "<text1.txt> <text2.txt> <text3.txt> ....: names of the input files (at least one is mandatory)" << endl;
}

/**
 * This program learns a Language model from a set of input tex files (tex1.txt,
 * tex2.txt, ...
 * Running example:
 * > LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> ....]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */

//"${OUTPUT_PATH}" fichero_texto1.txt fichero2

int main(int argc, char *argv[]) {   
    /*
       -t | -b paramÈtro opcional, respectivamente modo texto o modo binario
       para el fichero de salida (-t) es por defecto.
       -l indica el nombre del idioma que se aprende, valor (unknown por defecto
       si no hay par·metro -l).
       -o indica el nombre del fichero de salida <.bgr> (output.bgr por defecto,
       si no hay par·metro -o).
       Nota: Los par·metros se pueden introducir en cualquier orden, pero solo
       los que comienzan con ?
    */
    
    // variables
    bool params_ok = true;
    
    // procesamiento de par·metros
    if(argc < 2){
        showEnglishHelp(cout);
        exit(1);
    } else {
        // variables
        int pos_param_t = 0, pos_param_b = 0, pos_param_l = 0, pos_param_o= 0, salto = 1;
        bool param_t = false, param_b = false, param_l = false, param_o = false;
        
        // procesamiento de par·metros
        for(int i = 1; i < argc && params_ok; i++){
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
            } else if(param == "-l"){
                param_l = true;
                pos_param_l = i;
                salto += 2;
            } else if(param == "-o"){
                param_o = true;
                pos_param_o = i;
                salto += 2;
            } else if(param.length() > 4){ // para los que no sean parametros opcionales (-t -o -l -b) 
                if(param.substr(param.length() - 4) == ".txt" || param.substr(param.length() - 4) == ".bgr")
                    continue;
            } else {
                params_ok = false;
            }           
        }
        
        if(!params_ok){
            showEnglishHelp(cout);
            exit(1);
        } else {
            Language lang_learnt, lang_aux;
            if(param_l){
                lang_learnt.setLanguageId(argv[pos_param_l + 1]);
            }
            
            for(int i = salto; i < argc; i++){
                BigramCounter bc_aux;
                bc_aux.calculateFrequencies(argv[i]);
                lang_aux = bc_aux.toLanguage();
                lang_learnt += lang_aux;
            }
            
            lang_learnt.sort();

            if(param_o){
                param_b ? lang_learnt.save(argv[pos_param_o + 1], 'b') : lang_learnt.save(argv[pos_param_o + 1]); 
            } else {
                lang_learnt.save("output.bgr");
            }
            
            return 0;
        }
    }
 }
    
    



