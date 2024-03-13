//
//  KMap.hpp
//  COSC2425_PS1_KMap
//
//  Created by Greg Norz on 3/7/24.
//

#ifndef KMap_hpp
#define KMap_hpp

// ----------------------------------------------------------------------------

#include <list>
#include <vector>
#include <string>

using namespace std; // I wouldn't normally do this kind of thing, but...

// ----------------------------------------------------------------------------

typedef vector<char>            var_list_t;
typedef vector<unsigned int>    minterm_vec_t;
typedef vector<bool>            flat_kmap_t;
typedef vector< vector<bool> >  kmap_t;

typedef pair<string, string>    rowColNamePair_t;
typedef pair<string, string>    kmap_letters_t; // Splits between row and column letters

// ----------------------------------------------------------------------------

struct KMapCell
{
    bool            Minterm;
    unsigned int    Index;  // The decimal value of the index
    string          Binary; // The binary string of the index
};

class KMap
{
public :
    KMap( unsigned int variableCount, var_list_t variableList, minterm_vec_t mintermLocations );
    
    // Rather than store these, we calculate on the fly
    unsigned int GetRowCount() const;
    unsigned int GetColumnCount() const;
    
    void PrintFlatKMap();
    void PrintKMap();
    
private :
    void ResetKmap();
    void Unflatten(); // Will convert flatKmap --> kmap
    void MakeKMap();
    
    // Utility methods
    rowColNamePair_t SplitLetterVariables() const;
    
    // These three member vars mimic the input we receive from the user
    unsigned int    variableCount;
    var_list_t      variableList;
    minterm_vec_t   mintermLocations;
    
    // How to keep these 2 sync'd up...
    vector<KMapCell>    flatKmap2;
    flat_kmap_t         flatKmap;
    kmap_t              kmap;
};

#endif /* KMap_hpp */
