//
//  main.cpp
//  COSC2425_PS1_KMap
//
//  Created by Greg Norz on 3/7/24.
//

#include <iostream>
#include <sstream>
#include "KMap.hpp"

using namespace std; // I wouldn't normally do this kind of thing

// ----------------------------------------------------------------------------

int main()
{
//    unsigned int variableCount = 2;
//    string variableLetters{ "XY" };
//    minterm_vec_t mintermLocationVec{ 2, 3 };
    
    unsigned int variableCount = 3;
    string variableLetters( "XYZ" );
    minterm_vec_t mintermLocationVec{ 2, 3, 5, 6, 7 };
    // stringstream locationStream( string("23567") );
    
//    unsigned int variableCount = 4;
//    string variableLetters{ "WXYZ" };
//    minterm_vec_t mintermLocationVec{ 0, 2, 4, 5, 6, 7, 8, 12 };
    
    // Convert string-based vars to the types we need in the KMap ctor
    var_list_t variableList;
    for ( char& letter : variableLetters )
    {
        variableList.push_back( letter );
    }

    // All of our information has been collected and converted. LET'S GOOOOO!
    KMap kmap( variableCount, variableList, mintermLocationVec );
    
    cout << "===== Flat K-map =====" << endl;
    kmap.PrintFlatKMap();
    cout << endl << endl;
    
    cout << "===== K-map =====" << endl;
    kmap.PrintKMap();
    cout << endl;
}

// ----------------------------------------------------------------------------
