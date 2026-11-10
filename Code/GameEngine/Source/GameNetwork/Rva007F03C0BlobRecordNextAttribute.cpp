// cl: /GS

// The blob record's message and attribute cursor fields are independently
// witnessed by its matched constructor/populator at 0x007F0CB0/0x007F0D40.

#include <stdio.h>

#include "../../Include/GameNetwork/BfmeThingUPB.h"

class Rva007E8810Message;

class Rva007F0CB0BlobRecord
{
public:
	bool nextAttribute( char *key, int keySize, char *value, int valueSize );

private:
	Rva007E8810Message *m_message;
	char m_pad004[ 0x220 ];
	int m_224;
};

bool Rva007F0CB0BlobRecord::nextAttribute(
	char *key, int keySize, char *value, int valueSize )
{
	char name[ 0x40 ];

	if( m_message == 0 )
		goto failure;
	sprintf( name, "attributes.%d.key", m_224 );
	if( ((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)name, key, (void *)keySize ) )
	{
		sprintf( name, "attributes.%d.value", m_224 );
		((BfmeThingUPB *)m_message)->bfmeGoUPB( (void *)name, value, (void *)valueSize );
		++m_224;
		return true;
	}

failure:
	return false;
}
