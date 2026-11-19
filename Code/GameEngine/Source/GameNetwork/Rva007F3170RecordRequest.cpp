// cl: /GS

#include <stdio.h>

// Retail 0x007F3170 builds the FESL `recp` record request. The owner layout,
// field keys, and two indexed arrays come from the retail loads and literals.

#include "../../Include/Common/ScalarTypes/Source/FeslInt64.h"

#include "../../Include/GameNetwork/Rva007E8810Message.h"

struct Rva007F3170Owner
{
	FeslInt64 owner;
	int ownerType;
};

struct Rva007F3170Value
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

// The recp/UpdateRecord TXN value is this record's m_name at VA 0x00E0A100.
extern Rva007B55E0TxnName TheRecordUpdateTransaction;

void __stdcall Rva007F3170( Rva007E8810Message *msg,
	const Rva007F3170Owner *owner, const char *recordName,
	const Rva007F3170Value *values, unsigned int count, int ttl,
	const char * const *remove, unsigned int removeCount )
{
	const char *txn = TheRecordUpdateTransaction.m_name;
	unsigned int i;
	const Rva007F3170Value *entries = values;

	msg->reset();
	msg->m_1C = 'recp';
	msg->addString( "TXN", txn );
	if( owner )
	{
		if( owner->ownerType == 1 )
		{
			msg->addInt64( "owner", owner->owner );
			msg->addInt( "ownerType", owner->ownerType );
		}
		else
		{
			msg->setError( -113 );
			return;
		}
	}
	msg->addString( "recordName", recordName );
	msg->addInt( "values.[]", count );
	for( i = 0; i < count; ++i )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "values.%d.key", i );
		msg->addString( key, entries[ i ].key );
		sprintf( key, "values.%d.value", i );
		msg->addString( key, entries[ i ].value );
	}
	msg->addInt( "TTL", ttl );
	msg->addInt( "remove.[]", removeCount );
	for( i = 0; i < removeCount; ++i )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "remove.%d", i );
		msg->addString( key, remove[ i ] );
	}
}
