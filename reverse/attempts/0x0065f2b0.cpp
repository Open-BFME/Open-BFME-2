// ?buildRva007F27C0@@YGXPAVRva007E8810Message@@PBDPBURva007F27C0User@@H@Z
// partial score=0.9926605505 date=2026-10-09
// ?buildRva007F27C0@@YGXPAVRva007E8810Message@@PBDPBURva007F27C0User@@H@Z
// Evidence: targets/game/reverse/identity_evidence/007f27c0-rank-request.md
// cl: /GS
#include <stdio.h>

typedef __int64 FeslInt64;

// Descriptive name for the mutable pointer read at native VA 0x00E0A0AC.
// Its original name is unknown; the image stores this word in zero-fill data.
extern const char *FeslRankRequestTransaction;

class Rva007E8AC0
{
public:
	void run();
};

class Rva007E8810Message
{
public:
	void addString( const char *key, const char *value );
	void addInt( const char *key, int value );
	void addInt64( const char *key, FeslInt64 value );

	char m_head[ 0x1C ];
	unsigned int m_category;
};

struct Rva007F27C0Stat
{
	int userType;
	const char *key;
	float value;
	const char *text;
};

struct Rva007F27C0UserHeader
{
	FeslInt64 owner;
	int ownerType;
	unsigned char field0C[ 4 ];
};

struct Rva007F27C0UserData
{
	int statCount;
	Rva007F27C0Stat *stats;
};

struct Rva007F27C0User
{
	Rva007F27C0UserHeader header;
	Rva007F27C0UserData data;
};

void __stdcall buildRva007F27C0( Rva007E8810Message *msg, const char *gsid,
	const Rva007F27C0User *users, int userCount )
{
	register Rva007E8810Message *message;
	register const char *txn;
	char name[ 0x40 ];
	char value[ 0x40 ];
	int i;

	message = msg;
	txn = FeslRankRequestTransaction;
	((Rva007E8AC0 *)message)->run();
	message->m_category = 'rank';
	message->addString( "TXN", txn );
	message->addString( "gsid", gsid );
	for( i = 0; i < userCount; ++i )
	{
		const Rva007F27C0UserData *data = &users[ i ].data;
		Rva007F27C0UserHeader header = users[ i ].header;

		if( header.owner )
		{
			sprintf( name, "u.%d.o", i );
			message->addInt64( name, header.owner );
			sprintf( name, "u.%d.ot", i );
			message->addInt( name, header.ownerType );
		}

		{
			int j;
			for( j = 0; j < data->statCount; ++j )
			{
				sprintf( name, "u.%d.s.%d.ut", i, j );
				message->addInt( name, data->stats[ j ].userType );
				sprintf( name, "u.%d.s.%d.k", i, j );
				message->addString( name, data->stats[ j ].key );
				sprintf( name, "u.%d.s.%d.v", i, j );
				sprintf( value, "%.4f", data->stats[ j ].value );
				message->addString( name, value );
				sprintf( name, "u.%d.s.%d.t", i, j );
				message->addString( name, data->stats[ j ].text );
			}
		}

		sprintf( name, "u.%d.s.[]", i );
		message->addInt( name, data->statCount );
	}
	message->addInt( "u.[]", userCount );
}

const char *FeslRankRequestTransaction;
