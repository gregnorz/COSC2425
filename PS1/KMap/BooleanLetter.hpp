//
//  BooleanLetter.hpp
//  COSC2425_PS1_KMap
//
//  Created by Greg Norz on 3/8/24.
//

#ifndef BooleanLetter_hpp
#define BooleanLetter_hpp

#include <string>

using namespace std; // I wouldn't normally do this kind of thing

class BooleanLetter
{
public:
    BooleanLetter( char letter );
    
    string GetLetter() const;
    string GetNotLetter() const;
    
private:
    string letter;
    string notLetter;
};

#endif /* BooleanLetter_hpp */
