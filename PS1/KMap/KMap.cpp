//
//  KMap.cpp
//  COSC2425_PS1_KMap
//
//  Created by Greg Norz on 3/7/24.
//

#include <iostream>
#include <sstream>
#include "KMap.hpp"
#include "utility.hpp"
#include "BooleanLetter.hpp"

// ----------------------------------------------------------------------------

KMap::KMap( unsigned int variableCount, var_list_t variableList, minterm_vec_t mintermLocations )
:
variableCount( variableCount ),
variableList( variableList ),
mintermLocations( mintermLocations )
{
    // Step 0 - Get a flat representation of the K-map
    unsigned int cellCount = (1 << variableCount); // K-maps are powers of 2 with the cell count
    this->flatKmap.resize( cellCount, false ); // Init the flat K-map to all 0
    for ( auto minterm : mintermLocations )
    {
        flatKmap[minterm] = true;
    }
    
    // Step 1 -
    MakeKMap();
}

// ----------------------------------------------------------------------------

unsigned int KMap::GetRowCount() const
{
    return ( 1 << (variableCount / 2) );
}

// ----------------------------------------------------------------------------

unsigned int KMap::GetColumnCount() const
{
    return ( 1 << (variableCount - (variableCount / 2)) );
}

// ----------------------------------------------------------------------------

void KMap::PrintFlatKMap()
{
    // Print the indicies as a header row of sorts
//    for ( unsigned int index = 0; index < flatKmap.size(); ++ index )
//    {
//        cout << index << " ";
//    }
    
//    cout << endl;
    
    stringstream indiciesStream, binaryStream, booleanStream;
    
    // Print the binary of each index value (not the cell itself)
    for ( unsigned int index = 0; index < flatKmap.size(); ++ index )
    {
        indiciesStream << index << " ";
        
        string binaryString( DecimalToBinary(index, variableCount) );
        binaryStream << binaryString << " "; // | " << booleanVars << endl;
        
        //string booleanVars( BinaryToLetters( binaryString, variableList) );
    }
    
    cout << "K-map values" << endl;
    cout << indiciesStream.str() << endl;
    cout << binaryStream.str() << endl;
    
    cout << endl;
    
//    SplitLetterVariables();
    
    cout << "Cell values: " << endl;
    for ( auto cell : flatKmap )
    {
        cout << cell << " ";
    }
}

// ----------------------------------------------------------------------------

void KMap::PrintKMap()
{
    // We print the map in row-major order
    Unflatten();
    
    for ( auto row : kmap )
    {
        for ( auto column : row )
        {
            cout << column << " ";
        }
        
        cout << endl;
    }
}

// ----------------------------------------------------------------------------

void KMap::ResetKmap()
{
    unsigned int rowCount       = GetRowCount();
    unsigned int columnCount    = GetColumnCount();
    
    kmap.clear();
    kmap.resize( rowCount );
    for ( unsigned int row = 0; row < rowCount; ++row )
    {
        kmap[row].resize( columnCount, false );
    }
}

// ----------------------------------------------------------------------------

void KMap::Unflatten()
{
    ResetKmap();
    
    unsigned int rowCount       = GetRowCount();
    unsigned int columnCount    = GetColumnCount();
    
    for ( unsigned int row = 0; row < rowCount; ++row )
    {
        for ( unsigned int column = 0; column < columnCount; ++column )
        {
            unsigned int index = ( row * columnCount ) + column;
            // cout << "index = " << index << " | coords = (" << row << ", " << column << ")" << endl;
            kmap[row][column] = flatKmap[index];
        }
    }
}

// ----------------------------------------------------------------------------

rowColNamePair_t KMap::SplitLetterVariables() const
{
    unsigned int rowCount       = GetRowCount();
    unsigned int columnCount    = GetColumnCount();
    
    unsigned int rowVarCount = ( rowCount / 2 );
    unsigned int colVarCount = ( columnCount - (columnCount / 2) );
    
    std::stringstream rowStream, colStream;
    unsigned int variableListIndex = 0;
    for ( ; variableListIndex < rowVarCount; ++variableListIndex )
    {
        //cout << "rowvar = " << variableList[variableListIndex] << endl;
        rowStream << variableList[variableListIndex];
    }
    
    // Print the col vars
    for ( ; variableListIndex < (rowVarCount + colVarCount); ++variableListIndex )
    {
        //cout << "colvar = " << variableList[variableListIndex] << endl;
        colStream << variableList[variableListIndex];
    }
    
//    cout << endl << "**********" << endl;
//    cout << "rowCount = " << rowCount << endl;
//    cout << "colCount = " << columnCount << endl;
//
//    cout << "rowVars = " << rowVarCount << endl;
//    cout << "colVars = " << colVarCount << endl;
//
//    cout << "row letters = " << rowStream.str() << endl;
//    cout << "column letters = " << colStream.str() << endl;
//    cout << "**********" << endl << endl;
    
    vector<BooleanLetter> rowLetters;
    for ( char&c : rowStream.str() )
    {
        BooleanLetter letter( c );
        rowLetters.push_back( letter );
    }
    
    for ( auto letter : rowLetters )
    {
        cout << letter.GetLetter() << " " << letter.GetNotLetter() << endl;
    }
    
    vector<BooleanLetter> colLetters;
    for ( char&c : colStream.str() )
    {
        BooleanLetter letter( c );
        colLetters.push_back( letter );
    }
    
    for ( auto letter : colLetters )
    {
        cout << letter.GetLetter() << " " << letter.GetNotLetter() << endl;
    }
    
    // for each letter in rowLetters
        // create KarnaughLetter struct
        // set KarnaughLetter.letter = letter
        // set KarnuaghLetter.notLetter = letter + '
    
        // add to letter variable vector in proper location
    
    return make_pair( rowStream.str(), colStream.str() );
    
}

// ----------------------------------------------------------------------------

void KMap::MakeKMap()
{
    // Step 0 - Get a flat representation of the K-map
//    unsigned int cellCount = (1 << variableCount); // K-maps are powers of 2 with the cell count
//    for ( auto minterm : mintermLocations )
//    {
//        flatKmap[minterm] = true;
//    }
    
    int cellCount = 1 << variableCount;
    
    for ( int i = 0; i < cellCount; ++i )
    {
        KMapCell cell;
        cell.Index  = i;
        cell.Binary = DecimalToBinary( i, variableCount );
        
        flatKmap2.push_back( cell );
    }
    
    for ( auto minterm : mintermLocations )
    {
        flatKmap2[minterm].Minterm = true;
    }
    
    auto letter = SplitLetterVariables();
    cout << "row letters = " << letter.first << endl;
    cout << "col letters = " << letter.second << endl;
    
    stringstream indexStream, binaryStream, mintermStream;
    for ( auto cell : flatKmap2 )
    {
        indexStream << cell.Index << " ";
        binaryStream << cell.Binary << " ";
        mintermStream << cell.Minterm << " ";
    }
    
    cout << "===== MakeKMap =====" << endl;
    cout << indexStream.str() << endl;
    cout << binaryStream.str() << endl;
    cout << mintermStream.str() << endl;
    cout << endl;
}
