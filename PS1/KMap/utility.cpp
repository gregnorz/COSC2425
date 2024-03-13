//
//  utility.cpp
//  COSC2425_PS1_KMap
//
//  Created by Greg Norz on 3/7/24.
//

#include <iostream>
#include "KMap.hpp"
#include "utility.hpp"

// ----------------------------------------------------------------------------

string DecimalToBinary( unsigned int decimal, unsigned int variableCount )
{
    bitset<4> binary( decimal );
    string binaryString( binary.to_string() );
    
    // For this assignment, I'm taking the easy way out and just handling our 2, 3, 4 variable count.
    switch ( variableCount )
    {
        case 2:
            binaryString.erase( 0, 2 );
            break;
            
        case 3:
            binaryString.erase( 0, 1 );
            break;
            
        default:
            break; // Just leave it alone; something went wrong or it's 4
    }
    
    return binaryString;
}

// ----------------------------------------------------------------------------

string BinaryToLetters( const string& binaryString, const var_list_t& variableList )
{
    string booleanVars{ '\0' };
    
    for ( unsigned int index = 0; index < binaryString.length(); ++index )
    {
        booleanVars += variableList[index];
        
        if ( binaryString[index] == '0' )
        {
            booleanVars += "'";
        }
    }
    
    cout << "booleanVars = " << booleanVars << endl;
    
    return booleanVars;
}

// ----------------------------------------------------------------------------
