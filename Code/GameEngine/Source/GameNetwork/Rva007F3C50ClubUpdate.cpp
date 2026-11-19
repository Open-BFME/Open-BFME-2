// cl: /GS

#include <stdio.h>
#include <string.h>

// Retail 0x007F3C50 builds the FESL club update request. The field keys and
// indexed attribute and removal arrays come from the retail literals.

#include "../../Include/Common/ScalarTypes/Source/FeslInt64.h"

class Rva007E8810Message
{
public:
	void reset( void );
	void addString( const char *key, const char *value );
	void addInt( const char *key, int value );
	void addInt64( const char *key, FeslInt64 value );

	char m_head[ 0x1C ];
	unsigned int m_category;
	char m_tail[ 0x0C ];
	int m_depth;
};

struct Rva007F3C50Attribute
{
	const char *key;
	const char *value;
};

struct Rva007B55E0TxnName
{
	__declspec(noinline) Rva007B55E0TxnName( const char *type, const char *name );

	const char *m_type;
	const char *m_name;
	int m_reserved;
};

// The club/UpdateClub TXN value is this record's m_name at VA 0x00E0A184.
extern Rva007B55E0TxnName TheClubUpdateTransaction;
// Provider for RecordRequest.cpp; keeping this const pointer in a sibling TU
// prevents the compiler from folding its matched load. VA 0x00E0A100 (.data,
// zero-filled tail); retail's initial pointer value is zero.

void __stdcall Rva007F3C50( Rva007E8810Message *msg, FeslInt64 clubId,
	const char *name, const char *description, int access, int state,
	FeslInt64 userId, const Rva007F3C50Attribute *attributes,
	unsigned int numAttributes, const char * const *removeKeys,
	unsigned int numRemoveKeys )
{
	const char *txn = TheClubUpdateTransaction.m_name;
	unsigned int i;

	msg->reset();
	msg->m_category = 'club';
	msg->addString( "TXN", txn );
	msg->addInt64( "clubId", clubId );
	if( name && strlen( name ) != 0 )
		msg->addString( "name", name );
	if( description && strlen( description ) != 0 )
		msg->addString( "description", description );
	if( access )
		msg->addInt( "access", access );
	if( state )
		msg->addInt( "state", state );
	if( userId )
		msg->addInt64( "owner", userId );
	if( numAttributes > 0 )
		msg->addInt( "attributes.[]", numAttributes );
	for( i = 0; i < numAttributes; ++i )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "attributes.%d.key", i );
		msg->addString( key, attributes[ i ].key );
		sprintf( key, "attributes.%d.value", i );
		msg->addString( key, attributes[ i ].value );
	}
	if( numRemoveKeys > 0 )
		msg->addInt( "removeKeys.[]", numRemoveKeys );
	for( i = 0; i < numRemoveKeys; ++i )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "removeKeys.%d", i );
		msg->addString( key, removeKeys[ i ] );
	}
}
