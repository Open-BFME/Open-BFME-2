// cl: /GS
#include <stdio.h>
#include <string.h>

// BFME1 Y4 FESL attribute request builders, third part: the PID-carrying
// pair. Source: reference/open-bfme-1/.../Y4FeslAttributeRequests.cpp
// (verbatim bodies). The b1 ICF fold is resolved by the FourCC each b2 body
// stores to m_category+0x1C -- an imm32 with no relocation, so hard evidence:
// b1 0x007FC990 168B -> b2 0x00668E90 stores 'UPLA' (player attributes + PID)
// b1 0x007FCBA0 168B -> b2 0x006690A0 stores 'PENT' (presence entries + PID)
// String-literal drift is DIR32 auto-patch; callees pre-pinned. Like the
// sibling TU this one needs `// cl: /GS` for the 0x44-byte cookie frame.

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	void reset( void );
	void addString( const char *key, const char *value );
	void addInt( const char *key, int value );
	void addBool( const char *key, bool value );

	char m_head[ 0x1C ];
	unsigned int m_category;
	char m_tail[ 0x0C ];
	int m_depth;
};

#include "../../Include/GameNetwork/Rva007FC810Attribute.h"

void __stdcall Rva007FC990( Rva007E8810Message *msg, int pid,
	const Rva007FC810Attribute *attributes, int numAttributes )
{
	int index;

	msg->reset();
	msg->m_category = 'UPLA';
	msg->m_depth = 3;
	msg->addInt( "PID", pid );
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "P-%s", attributes[ index ].m_key );
		msg->addString( key, attributes[ index ].m_value );
	}
}

void __stdcall Rva007FCBA0( Rva007E8810Message *msg, int pid,
	const Rva007FC810Attribute *attributes, int numAttributes )
{
	int index;

	msg->reset();
	msg->m_category = 'PENT';
	msg->m_depth = 3;
	msg->addInt( "PID", pid );
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "P-%s", attributes[ index ].m_key );
		msg->addString( key, attributes[ index ].m_value );
	}
}
