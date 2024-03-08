//
//  BooleanLetter.cpp
//  COSC2425_PS1_KMap
//
//  Created by Greg Norz on 3/8/24.
//

#include "BooleanLetter.hpp"

// ----------------------------------------------------------------------------

BooleanLetter::BooleanLetter( char c )
:
letter( string(1, c) ),
notLetter( letter + "'" )
{
}

// ----------------------------------------------------------------------------

string BooleanLetter::GetLetter() const
{
    return letter;
}

// ----------------------------------------------------------------------------

string BooleanLetter::GetNotLetter() const
{
    return notLetter;
}

// ----------------------------------------------------------------------------
