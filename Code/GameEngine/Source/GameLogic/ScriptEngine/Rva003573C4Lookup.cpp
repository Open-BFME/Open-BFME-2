// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc
//
// ?rva003573C4@Rva003573C4Owner@@QAEPAXABVAsciiString@@ABVBfmeRoomZC@@PAX@Z @0x003573C4 (82B).
// Runs the rowed forwarder 0x00357130 (it returns the value of its callee 0x00204F3B)
// with the restore-on-destruction guard 0x002048A2 / 0x002048EC bound to the
// AsciiString at +0x1A10C of the receiver. The receiver's own name is not
// recovered (the earlier ledger guess was ScriptEngine); the guard class is the
// rowed one from Rva002048A2Ctor.cpp, BfmeRoomZC / BfmeOwnZC the forwarder's views.
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
	void *bfmeCallZC( const BfmeRoomZC &name, void *extra );
};

struct Rva002048A2
{
	virtual ~Rva002048A2();
	AsciiString m_str;
	AsciiString *m_alias;
	Rva002048A2( AsciiString *a1, const AsciiString &a2 );
};

class Rva003573C4Owner : public BfmeOwnZC
{
public:
	void *rva003573C4( const AsciiString &replacement, const BfmeRoomZC &room, void *extra );

private:
	char m_pad[0x1A10C];
	AsciiString m_slot;
};

void *Rva003573C4Owner::rva003573C4( const AsciiString &replacement, const BfmeRoomZC &room, void *extra )
{
	Rva002048A2 guard( &m_slot, replacement );
	return bfmeCallZC( room, extra );
}
