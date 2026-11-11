// cl: /GS
#include <stdio.h>
#include <string.h>

#include "../../Include/GameNetwork/Rva007E8AC0.h"

#include "../../Include/GameNetwork/BfmeThingCIB.h"

#include "../../Include/GameNetwork/BfmeThingCIC.h"

#include "../../Include/GameNetwork/Rva007E8980.h"

class Rva007E8810Message
{
public:

	char m_head[ 0x1C ];
	unsigned int m_category;
	char m_tail[ 0x0C ];
	int m_depth;
};

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( int size, int flags );
	virtual void release( void *block, int flags );
};

extern GenAlloc *Gen007EFFC0();

#define FESL_RESET(message) ((Rva007E8AC0 *)(message))->run()
#define FESL_ADD_STRING(message, key, value) \
	((BfmeThingCIC *)(message))->bfmeGoCIC((void *)(key), (void *)(value))
#define FESL_ADD_INT(message, key, value) \
	((BfmeThingCIB *)(message))->bfmeGoCIB((void *)(key), (void *)(value))
#define FESL_ADD_BOOL(message, key, value) \
	((Rva007E8980 *)(message))->go((int)(void *)(key), (unsigned char)(value))

struct Rva007FC550Attribute
{
	const char *m_key;
	const char *m_value;
};

struct Rva007FC550Reservation
{
	__int64 m_id;
	int m_slot;
	int m_pad;
};

void __stdcall Rva007FC550( Rva007E8810Message *msg, int rid, int lid,
	bool reserveHost, const char *name, int port, int maxPlayers,
	const char *password, const Rva007FC550Attribute *attributes,
	unsigned int numAttributes, const Rva007FC550Reservation *reservations,
	unsigned int numReservations, int reserveTimeout, const char *userId,
	const char *secret )
{
	unsigned int index;
	FESL_RESET( msg );
	msg->m_category = 'CGAM';
	msg->m_depth = 3;
	FESL_ADD_INT( msg, "RID", rid );
	FESL_ADD_INT( msg, "LID", lid );
	FESL_ADD_BOOL( msg, "RESERVE-HOST", reserveHost );
	FESL_ADD_STRING( msg, "NAME", name );
	FESL_ADD_INT( msg, "PORT", port );
	FESL_ADD_INT( msg, "MAX-PLAYERS", maxPlayers );
	if( password && strlen( password ) != 0 )
		FESL_ADD_STRING( msg, "PASSWORD", password );
	if( userId )
	{
		FESL_ADD_STRING( msg, "UGID", userId );
		FESL_ADD_STRING( msg, "SECRET", secret );
	}
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "B-%s", attributes[ index ].m_key );
		FESL_ADD_STRING( msg, key, attributes[ index ].m_value );
	}
	if( reservations && numReservations )
	{
		char *ids = (char *)Gen007EFFC0()->allocate(
			numReservations * 0x23, 0 );
		char key[ 0x40 ];

		ids[ 0 ] = 0;
		unsigned int reservationIndex = 0;
		if( numReservations > 0 )
		{
			const Rva007FC550Reservation *reservation = reservations;
			do
			{
				sprintf( key, "%I64d", reservation->m_id );
				strcat( ids, key );
				strcat( ids, "-" );
				sprintf( key, "%d", reservation->m_slot );
				strcat( ids, key );
				if( reservationIndex < numReservations - 1 )
					strcat( ids, ";" );
				reservationIndex++;
				reservation++;
			} while( reservationIndex < numReservations );
		}
		FESL_ADD_STRING( msg, "RESERVE-IDS", ids );
		FESL_ADD_INT( msg, "RESERVE-TIMEOUT", reserveTimeout );
		Gen007EFFC0()->release( ids, 0 );
	}
}
