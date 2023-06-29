/*
 * Metodología de la Programación: Language5
 * Curso 2022/2023
 */

/** 
 * @file CLASSIFY.cpp
 * @author estudiante1: Zapata De la Hoz, Sergio
 * 
 * Created on 29 January 2023, 11:00
 */



using namespace std;
#include <fstream>
#include <iostream>

#include "Language.h"
#include "BigramCounter.h"
/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "CLASSIFY <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ....]" << endl;
    outputStream << "          Obtains the identifier of the closest language to the input text file" << endl;
    outputStream << endl;
}

/**
 * This program print the language identifier of the closest language 
 * for an input text file (<text.txt>) among the set of provided models:
 * <lang1.bgr>, <lang2.bgr>, ...
 * 
 * Running example:
 * > CLASSIFY  <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ...]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char *argv[]) {
    
    if(argc < 3){
      showEnglishHelp(cout);
      exit(1);
    } else {
        double min_distance, distance; 
        Language final_lang, aux_lang;
        BigramCounter bc_aux;
        bc_aux.calculateFrequencies(argv[1]); 
        final_lang = bc_aux.toLanguage();
        final_lang.sort();
        
        // lectura anticipada para la distancia minima (se coge el primero)
        aux_lang.load(argv[2]);
        min_distance = final_lang.getDistance(aux_lang);
        for(int i = 2; i < argc; i++){
            aux_lang.load(argv[i]);
            distance = final_lang.getDistance(aux_lang);
            if(distance <= min_distance){
                min_distance = distance;
                final_lang.setLanguageId(aux_lang.getLanguageId());
            }
        }
        
        cout << "Final decision: language " << final_lang.getLanguageId() << " with a distance of " << min_distance << endl;
    }
    return 0;
}

