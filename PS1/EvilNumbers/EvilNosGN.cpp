// EvilNumbers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <bitset>

using namespace std;

// ----------------------------------------------------------------------------
//
// Handles the conversion of y/n for us. We don't do much checking thus converting
// anything not 'y' or 'Y' to "false" 
//

inline bool yesNoToBool( char input )
{
	input = static_cast<char>(std::toupper( input ));
	return ('Y' == input);
}

// ----------------------------------------------------------------------------

string decimalToBinary( int decimalNum )
{
	// For purposes of the class, I'm capping this @ 32-bits
	bitset<32> binaryBitset( decimalNum );
	string binaryString( binaryBitset.to_string() );
	binaryString.erase( 0, binaryString.find_first_not_of( '0' ) ); // Strip leading zeros

	return binaryString;
}

// ----------------------------------------------------------------------------

bool amIEvil( int decimalNumber )
{
	unsigned int bitCount = 0;

	while ( decimalNumber )
	{
		bitCount += decimalNumber & 1;
		decimalNumber >>= 1;
	}

	return ( (bitCount % 2) == 0 );
}

// ----------------------------------------------------------------------------

int main()
{
	char yesOrNo = 'y';
	do
	{
		int decimalNumber = -1;
		while ( decimalNumber < 0 || decimalNumber > 1000 )
		{
			cout << "Enter a number [0 - 1000]: ";
			cin >> decimalNumber;
		}

		string binaryString( decimalToBinary(decimalNumber) );
		bool evil( amIEvil( decimalNumber ) );

		cout << decimalNumber << " in binary: " << binaryString << endl;

		string notString( evil ? " " : " not " );
		string smileString( evil ? ">:)" : ":)" );

		cout << decimalNumber << " is" << notString << "an evil number " << smileString << endl;
 
		cout << "\nRun again? (Y/N): ";
		cin >> yesOrNo;
		cout << endl;
	}
	while ( yesNoToBool( yesOrNo ) );
}