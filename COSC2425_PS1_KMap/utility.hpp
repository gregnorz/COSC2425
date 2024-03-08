//
//  utility.hpp
//  COSC2425_PS1_KMap
//
//  Created by Greg Norz on 3/7/24.
//
#ifndef utility_hpp
#define utility_hpp

#include <string>
#include <bitset>

using namespace std; // I wouldn't normally do this kind of thing

// ----------------------------------------------------------------------------

string DecimalToBinary( unsigned int decimal, unsigned int variableCount );
string BinaryToLetters( const string& binaryString, const var_list_t& variableList );

// ----------------------------------------------------------------------------

#endif /* utility_hpp */
