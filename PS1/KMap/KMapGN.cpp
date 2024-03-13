/*
//
//  main.cpp
//  COSC2425_PS1_KMap
//
//  Created by Greg Norz on 2/29/24.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <utility>
#include <list>
#include <iomanip>

// ----------------------------------------------------------------------------

// Rows are .first; cols are .second
// The first pair<> is for the count; the next pair<> is for the string names of the vars
// Both are mostly for printing out the K-map
//
typedef std::pair<unsigned int, unsigned int> rowColCountPair_t;
typedef std::pair<std::string, std::string>   rowColNamePair_t;

// Mostly used by the KMap class
typedef std::list<char>                       varlist_t;
typedef std::vector<unsigned int>             minterms_t; // Locations of the minterms
typedef std::vector< std::vector<bool> >      kmap_t;

// ----------------------------------------------------------------------------

inline bool yesNoToBool( char input )
{
    input = std::toupper( input );
    return ( 'Y' == input );
}

// ----------------------------------------------------------------------------

class KMap
{
public:
    KMap( unsigned int variableCount,
          const std::string& variableLetters,
          const minterms_t& mintermLocations )
    {
        InitKMap( variableCount, variableLetters, mintermLocations );
    }
    
    // Utility functions that make generating/printing the map a bit easier. Also
    // VERY handy for debugging.
    unsigned int GetNumCells() const { return ( 1 << variableList.size() ); }
    unsigned int GetNumRows() const { return GetRowColCount().first; }
    unsigned int GetNumCols() const { return GetRowColCount().second; }
    
    std::string GetRowLabel() const { return GetRowColNames().first; }
    std::string GetColLabel() const { return GetRowColNames().second; }
    
    void Print()
    {
        size_t rowCount = karnaughMapMatrix.size();
        size_t colCount = karnaughMapMatrix[0].size();
        
        std::cout << "The K-map has " << rowCount << " row(s) and " << colCount << "col(s)." << std::endl;
        std::cout << std::endl;
        std::cout << "======== K Map ========" << std::endl;
        
        std::string rowLabel(GetRowLabel()), colLabel(GetColLabel());
        std::stringstream colStream, rowStream;
        
        // Print column variables
        colStream << std::string(rowLabel.length(), ' ') << "\\" << colLabel;
        if ( colLabel.length() == 1 ) colStream << " ";
        colStream << "|";

        std::cout << colStream.str() << std::endl;
//
//        // Stream out the row variables + the column headers
//        rowStream << rowLabel << " \\ |";
//        std::cout << rowStream.str() << std::endl;
        
        for ( auto row : karnaughMapMatrix )
        {
            for ( auto col : row )
            {
                std::cout << col << " ";
            }

            std::cout << std::endl;
        }
        
//        std::cout << "There are minterms at the following locations:" << std::endl;
//        for ( size_t row = 0; row < rowCount; ++row )
//        {
//            for ( size_t col = 0; col < colCount; ++col )
//            {
//                if ( karnaughMapMatrix[row][col] )
//                {
//                    std::cout << "Found a minterm at (" << row << ", " << col << ")" << std::endl;
//                    std::string rowVar = GetRowLabel();
//                    std::string colVar = GetColLabel();
//
//                    std::cout << "Row vars = " << rowVar << std::endl;
//                    std::cout << "Col vars = " << colVar << std::endl;
//
////                    for ( size_t k = 0; k < variableList.size(); ++k )
////                    {
////                        auto shift = 1 << k;
////                        auto varOrPrime = row & shift;
////                        std::cout << "Shift = " << shift << std::endl;
////                        std::cout << "varOrPrime = " << varOrPrime << std::endl;
////                    }
//
//                    std::cout << std::endl;
//                }
//            }
//        }
//
//        std::cout << std::endl;
        
//        size_t colPadding = rowLabel.size();
//        std::cout << std::setfill(' ') <<  std::setw(colPadding);
//        std::cout << "\\" << colLabel << "|" << std::endl;
//        std::cout << rowLabel << " \\ |" << std::endl;
    }
    
    // ----------------
    // A little debugging method that made my life a lot easier when testing out
    // the utility functions.
    //
    void PrintDebug() const
    {
        std::cout << "Number of variables = " << variableList.size() << std::endl;
        std::cout << "Variable letters = ";
        for ( auto c : variableList ) std::cout << c << " ";
        std::cout << std::endl;
        
//        std::cout << "Minterms = ";
//        for ( auto minterm : mintermLocations ) std::cout << minterm << " ";
//        std::cout << std::endl;
        
        std::cout << "The K-map has rows = " << GetNumRows() << std::endl;
        std::cout << "The K-map has cols = " << GetNumCols() << std::endl;
        std::cout << "The total number of cells in the K-map = " << GetNumCells() << std::endl;
        std::cout << std::endl;
        std::cout << "K-map row label = " << GetRowLabel() << std::endl;
        std::cout << "K-map col label = " << GetColLabel() << std::endl;
        
        std::cout << std::endl;
    }
    
private:
    void InitKMap( unsigned int variableCount,
                   const std::string& variableLetters,
                   const minterms_t& mintermLocations )
    {
        this->variableCount = variableCount;
        
        // Convert the string we get from input to a std::list<>
        // This could be done at input time; just a preference I do it here.
        //
        for ( auto letter : variableLetters )
        {
            variableList.push_back( letter );
        }
        
        karnaughMapMatrix.clear();
        
        rowColCountPair_t rowColCount = GetRowColCount();
        karnaughMapMatrix.resize( rowColCount.first );
        
        // Create the cols and zero each cell out
        for ( int i = 0; i < rowColCount.first; ++i )
            karnaughMapMatrix[i].resize( rowColCount.second, false );
        
        for ( auto loc : mintermLocations )
        {
            unsigned int row = loc / rowColCount.second;
            unsigned int col = loc % rowColCount.second;
            
            karnaughMapMatrix[row][col] = true;
        }
        
//        // Swap columns and rows to align with Gray code
//        if ( GetNumRows() == 4 ) // We only need to swap if there are 4 rows
//        {
//            std::swap( karnaughMapMatrix[2], karnaughMapMatrix[3] );
//        }
//
//        if ( GetNumCols() == 4) // We only need to swap if there are 4 columns
//        {
//            for ( auto row : karnaughMapMatrix )
//            {
//                std::swap( row[2], row[3] );
//            }
//        }
    }
    
    rowColCountPair_t GetRowColCount() const
    {
        
        rowColCountPair_t rowColPair;
        size_t numVars = variableList.size();
        rowColPair.first = 1 << (numVars / 2);
        rowColPair.second = 1 << (numVars - numVars / 2);
        
        return rowColPair;
    }
    
    rowColNamePair_t GetRowColNames() const
    {
        rowColCountPair_t rowsAndCols = GetRowColCount();
        unsigned int rowVars = (rowsAndCols.first / 2);
        unsigned int colVars = (rowsAndCols.second - rowsAndCols.second / 2);
        
        varlist_t::const_iterator iter = variableList.begin();
        
        // Print the row vars
        std::stringstream rowStream, colStream;
        for ( unsigned int i = 0; i < rowVars; ++i, ++iter )
        {
            rowStream << *iter;
        }
        
        // Print the col vars
        for ( unsigned int i = 0; i < colVars; ++i, ++iter )
        {
            colStream << *iter;
        }
        
        return std::make_pair( rowStream.str(), colStream.str() );
    }

    // For now, I'm not doing any error checking on these values. Basic checking is handled in main().
    // I'm trying to keep the code a bit simple for ease of the class and grading. :)
    unsigned int variableCount;
    varlist_t    variableList;
    kmap_t       karnaughMapMatrix;
};

// ----------------------------------------------------------------------------

int main( int argc, const char * argv[] )
{
    char response = 'y';
    do
    {
        unsigned int variableCount = 3;
        std::string variableLetters{ "xyz" };
        std::vector<unsigned int> mintermLocations{ 2, 3, 5, 6, 7 };
        
//        std::cout << "Enter number of variables: ";
//        std::cin >> variableCount;
//
//        std::cout << "Enter variable letters: ";
//        std::cin >> variableLetters;
//        std::transform( variableLetters.begin(), variableLetters.end(), variableLetters.begin(), ::toupper );
        
        // Do some basic checks here to make sure we have valid values. I just break out of the do-while
        // to make things easy; a better interfce would be to just go back to the top.
//        if ( variableCount < 2 || variableCount > 4 )
//        {
//            std::cout << "I can only support K-maps of 2, 3, or 4 variables. Sorry." << std::endl;
//            break;
//        }
//        
//        if ( variableCount != variableLetters.length() )
//        {
//            std::cout << "The number of variables does not match the variable count. Try again." << std::endl;
//            break;
//        }
//        
//        if ( mintermLocations.size() > (1 << variableCount) )
//        {
//            std::cout << "The number of cells in the K-map should be " << (1 << variableCount) << std::endl;
//            std::cout << "It looks like there are too many minterm locations. Try again." << std::endl;
//            break;
//        }
//
//        std::cout << "Enter locations of the 1 values: ";
//
//        std::cin.ignore();
//        std::string inputString{ '\0' };
//        std::getline( std::cin, inputString );
//
//        std::stringstream locationStream( inputString );
//        unsigned int loc = 0;
//        while ( locationStream >> loc )
//        {
//            mintermLocations.push_back( loc );
//        }
        
        // ------------
        
        std::cout << "Creating K-map" << std::endl;
        KMap kmap( variableCount, variableLetters, mintermLocations );
        std::cout << std::endl;
        kmap.PrintDebug();
        kmap.Print();
        
        std::cout << std::endl;
//        std::cout << "Run Again (Y/N): ";
//        std::cin >> response;
        response = 'N';
    }
    while ( yesNoToBool(response) );
    
    return 0;
}*/
