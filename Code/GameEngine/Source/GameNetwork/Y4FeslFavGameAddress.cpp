// cl: /GS
// Retail 0x0080A9B0 copies a game address record and sends its IP through ->L.

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

#include "../../Include/GameNetwork/Rva007EB810Diag.h"

class GenAlloc; GenAlloc *Gen007EFFC0();
Rva007EB810Diag *Rva007EB810Get();
int Rva00656B60Get();

// Rva00809500Sink::accept: defined in Y4FeslFavGameAddress_accept.cpp (its row's unit).

void *Rva007F93E0( void *message, void *route, void *owner );
// The copy is msvcr71's strncpy (import thunk 0x0062983E), from <string.h>
// with _CRTIMP empty (the header's own guard) so the call is direct.
#define _CRTIMP
#include <string.h>

void Rva00655700(char *dest, unsigned int capacity, const char *source);

class Rva00808900Owner
{
public:
	void copy(char *source);

private:
	char m_pad[0x18];
	char m_dest[0x20];
};

void Rva00808900Owner::copy(char *source)
{
	strncpy(m_dest, source, 0x20);
}

class Rva00808AC0Owner
{
public:
	void copy(char *source);

private:
	char m_pad[0x0c];
	char m_dest[0x80];
};

void Rva00808AC0Owner::copy(char *source)
{
	strncpy(m_dest, source, 0x80);
}

// The BFME1 donor also defines Rva00808AF0Owner::copy here, but BFME2 range
// 0x00674A50 is already matched by Y2FeslSafeStrCopy.cpp as
// ?set@Rva00674A50Holder@@QAEXPBD@Z. Omit that duplicate range without
// transferring the donor's identity to the existing BFME2 body.

class LanTheaterEmulator
{
public:
	void notifyAddress( Rva00809500Entry *entry );
	char m_pad00[ 0x10 ];
	void *m_field10;
};

// LanTheaterEmulator::notifyAddress: defined in Y4FeslFavGameAddress_notify.cpp (its row's unit).
