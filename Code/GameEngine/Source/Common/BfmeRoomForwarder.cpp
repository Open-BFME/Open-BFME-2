// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

// A reference parameter forwarded to a sibling member taking the object BY
// VALUE: the copy is built in the argument area by the StringBase<char>
// copy ctor alias at 0x00887B60. IDENTITY NOT RECOVERED; BfmeRoomZC is named
// to match the rowed callee ?bfmeRunZC@BfmeOwnZC@@QAEPAXVBfmeRoomZC@@PAX@Z.

#include "ascii_string.h"

class BfmeRoomZC
{
public:
	BfmeRoomZC( const BfmeRoomZC &other ) : m_name( other.m_name ) {}
	~BfmeRoomZC() {}

private:
	AsciiString m_name;
};

class BfmeOwnZC
{
public:
	void bfmeCallZC( const BfmeRoomZC &name, void *extra );
	void *bfmeRunZC( BfmeRoomZC name, void *extra );
};

void BfmeOwnZC::bfmeCallZC( const BfmeRoomZC &name, void *extra )
{
	bfmeRunZC( name, extra );
}
