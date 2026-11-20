// cl: /GS
#include <stdio.h>
#include <string.h>

// BFME1 Y4 FESL attribute request builder, trimmed donor.
// Source: reference/open-bfme-1/Code/GameEngine/Source/GameNetwork/Y4FeslAttributeRequests.cpp
// b1 0x007FC810 214B; b2 0x00668D10. Immediate-only drift is a DIR32 string
// literal the patcher fills, so the body below is the donor verbatim.



#include "../../Include/GameNetwork/Rva007E8810Message.h"

#include "../../Include/GameNetwork/Rva007FC810Attribute.h"

void __stdcall Rva007FC810( Rva007E8810Message *msg, const char *name,
	const Rva007FC810Attribute *attributes, int numAttributes, int join )
{
	int index;

	msg->reset();
	msg->m_1C = 'UGAM';
	msg->m_2C = 3;
	msg->addString( "NAME", name );
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "B-%s", attributes[ index ].m_key );
		msg->addString( key, attributes[ index ].m_value );
	}
	switch( join )
	{
		case 0:
			msg->addString( "JOIN", "O" );
			break;
		case 1:
			msg->addString( "JOIN", "W" );
			break;
		case 2:
			msg->addString( "JOIN", "C" );
			break;
	}
}
