// cl: /GX- /GS
// FESL game-browser record measurement at retail 0x0066DA40 (155B).
//
// The target is the measure sibling of the matched
// Rva00801EC0Owner::rva00801ec0 body at 0x0066E190.  That sibling establishes the
// owner offsets (+0x04 host, +0x1c buffer, +0x38 key array, +0x6c final
// string), calls the short Rva007FBEF0GameRecord accessor, and appends its
// +0x0c UGID field.  The target walks the same record use, so this TU keeps
// that genuine short-record view rather than borrowing the distinct
// data-bearing Rva007FBC60Game view used by 0x00801670.
//
// The host is a neutral receiver view.  The matched 0x007F76D0 helper has a
// two-stack-argument retail body with ret 8, but its demangler-family
// callers load the host into ECX before pushing vector/index.  The member
// declaration below records that independently observed ABI and preserves the
// target's own ECX load before the helper call; it makes no public class-name
// claim.
//
// Only measure is defined here.  The fill sibling lives in
// Rva00801EC0FeslFill.cpp and calls measure through the ledger; defining it
// here would capture that call locally instead of at its ledger address.

#include "../../Include/Common/BfmeSlotCZ.h"

#include "../../Include/Common/BfmeVecCZ.h"

class Rva00801670Host
{
public:
	int *rva007F76D0( BfmeVecCZ *vector, int index );

	unsigned char m_unreconstructed00[0x2A8];
	BfmeVecCZ m_gameKeys;
	BfmeVecCZ m_ugidKeys;
};

class Rva007FBEF0GameRecord
{
public:
	bool Rva007FBF40( const char *key, char *dest, unsigned int destSize );

	int m_lid;
	int m_gid;
	void *m_msg;
	char m_ugid[0x25];
};

class Rva00800290Buffer
{
public:
	void addPadded( int size );
	void addString( const char *text );
	void allocate();

	char *m_ptr;
	int m_size;
};

#include "../../Include/Common/Rva00800460Arena.h"

class Rva00801EC0Owner
{
public:
	void measure( Rva007FBEF0GameRecord *rec );

	void *m_bfme00;
	Rva00801670Host *m_host;
	char m_bfme08[0x14];
	Rva00800460Arena m_arena;
	char m_bfme28[0x10];
	char **m_keys;
	char m_bfme3c[0x30];
	char *m_ugid;
};

void Rva00801EC0Owner::measure( Rva007FBEF0GameRecord *rec )
{
	char buf[0x40];
	BfmeVecCZ *vector;
	int count;
	int i;
	int *slot;
	Rva00800290Buffer *buffer;
	*(volatile Rva00800290Buffer **)&buffer = (Rva00800290Buffer *)&m_arena;

	vector = &m_host->m_ugidKeys;
	count = vector->m_bfmeCount;
	buffer->addPadded( count * 4 );
	for( i = 0; i < count; i++ )
	{
		slot = m_host->rva007F76D0( vector, i );
		buf[0] = 0;
		if( rec->Rva007FBF40( (const char *)slot, buf, 0x40 ) )
			buffer->addString( buf );
	}
	buffer->addString( rec->m_ugid );
}
