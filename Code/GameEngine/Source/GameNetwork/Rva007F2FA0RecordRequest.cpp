// cl: /GS

#include <stdio.h>

#include "../../Include/Common/ScalarTypes/Source/FeslInt64.h"

#include "../../Include/GameNetwork/Rva007E8810Message.h"

struct Rva007F2FA0Owner
{
	FeslInt64 owner;
	int ownerType;
};

struct Rva007F2FA0Value
{
	const char *key;
	const char *value;
};

// The transaction name this record request writes as its "TXN" field, retail VA
// 0x00E0A0E8 (RVA 0x00A0A0E8): the rowed body loads it once (retail 0x0065FA8E
// `mov 0xe0a0e8,%esi`) and hands the pointer straight to addString. The address
// is past .data's raw end (0x009DE008) but inside its virtual size, so retail's
// image holds null -- the string is installed when the SDK is initialised, which
// no rowed body does.
// The definition is tentative with a mutable pointer, deliberately: MSVC must
// not learn the value at compile time. With an explicit `= 0` it folds the load
// into a literal and the rowed body pushes an immediate instead of reading the
// slot, which breaks the row (verified by ./build.sh). A const-qualified pointer
// cannot be left uninitialised (C2734), so this is also the only spelling that
// keeps the load while still defining the object.
// One plain definition line: it is an external-linkage object on its own, and
// keeping the separate `extern` declaration above it would add a third
// occurrence of the address-derived name (hatch register grants two for this
// file).
const char *g_Rva0130A6CC;

void __stdcall Rva007F2FA0( Rva007E8810Message *msg,
	const Rva007F2FA0Owner *owner, const char *recordName,
	const Rva007F2FA0Value *values, unsigned int count, int ttl )
{
	const char *txn = g_Rva0130A6CC;
	unsigned int i;
	const Rva007F2FA0Value *entries = values;

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
}

// ?Rva007F2FA0@@YGXPAVRva007E8810Message@@PBURva007F2FA0Owner@@PBDPBURva007F2FA0Value@@IH@Z
