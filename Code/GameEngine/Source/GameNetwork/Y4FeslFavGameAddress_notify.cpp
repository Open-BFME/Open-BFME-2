// cl: /GS /GX-
//
// Retail 0x006768B0 (202B). FESL game-address notify path: builds a BfmeC994
// message from the sink entry, formats the address text and dispatches it
// through Rva007F93E0. Transferred from the BFME1 reconstruction (same
// Y4FeslFavGameAddress.cpp TU family as the accept sibling at 0x00674DF0).

#include "../../Include/GameNetwork/BfmeC994.h"

#include "../../Include/GameNetwork/BfmeThingCIC.h"

#include "../../Include/Common/Rva007E8760Addr.h"

struct Rva00809500Entry
{
	char m_pad00[ 0x10 ];
	const char *m_text;
	int m_gdatBufferSize;
	int m_pad18;
	int m_length;
};

struct Rva00809500Sink
{
	void accept( Rva00809500Entry *entry );

	int m_pad00;
	int m_value04;
	int m_value08;
	int m_value0c;
	int m_pad10;
	char *m_gdatBuffer;
	int m_gdatBufferSize;
	unsigned int m_gdatTimestamp;
};

class Rva00809010Finder
{
public:
	Rva00809500Sink *find( Rva00809500Entry *entry );
};

void *Rva007F93E0( void *message, void *route, void *owner );
// The copy is msvcr71's strncpy (import thunk 0x0062983E), from <string.h>
// with _CRTIMP empty (the header's own guard) so the call is direct.
#define _CRTIMP
#include <string.h>

class LanTheaterEmulator
{
public:
	void notifyAddress( Rva00809500Entry *entry );
	char m_pad00[ 0x10 ];
	void *m_field10;
};

void LanTheaterEmulator::notifyAddress( Rva00809500Entry *entry )
{
	char buffer[ 0x40 ];
	BfmeC994 message( buffer, sizeof( buffer ) );
	Rva00809500Sink *sink = reinterpret_cast< Rva00809010Finder * >( this )->find( entry );
	message.m_category = entry->m_length;
	message.m_field20 = (int)0xC0000000;
	strncpy( message.m_buffer, entry->m_text, message.m_capacity );
	char address[ 0x20 ];
	reinterpret_cast< Rva007E8760Addr * >( sink )->format( address, sizeof( address ) );
	message.m_field04 = sink->m_value04;
	message.m_field08 = sink->m_value08;
	message.m_field0c = sink->m_value0c;
	reinterpret_cast< BfmeThingCIC * >( &message )->bfmeGoCIC(
	(void *)"IP",
		address );
	Rva007F93E0( &message, (void *)"->L", m_field10 );
}

// ?rva0066F740@Rva0066F740@@QAEXPAURva00809500Entry@@@Z @0x0066F740 8B member
// forwarder to rowed ?notifyAddress@LanTheaterEmulator@@QAEXPAURva00809500Entry@@@Z
// (0x006768B0; entry arg passes through the shared stack slot). No callers.
// Honest address name.
class Rva0066F740
{
public:
	void rva0066F740(Rva00809500Entry *entry);
private:
	char m_pad[0x18];
	LanTheaterEmulator *m_member;
};
void Rva0066F740::rva0066F740(Rva00809500Entry *entry)
{
	return m_member->notifyAddress(entry);
}
