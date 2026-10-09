// cl: /GS

#include <stdio.h>

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	FeslInt64 getInt64( const char *key, FeslInt64 defaultValue );
 void addString(const char *key, const char *value);
 void addInt(const char *key, int value);
 void addInt64(const char *key, FeslInt64 value);
 char m_head[0x1C];
 unsigned int m_category;
};

class BfmeThingRF
{
public:
	void *bfmeGoRF( void *key, void *defaultValue );
};

class BfmeThingUPB
{
public:
	char bfmeGoUPB( void *key, char *dest, void *destSize );
};

class Rva007F2350StatsRecord
{
public:
	FeslInt64 m_owner;
	char m_pad08[ 8 ];
	char m_name[ 0x20 ];
	char m_30;
	char m_pad31[ 0x1F ];
	int m_value;
	char m_addStat[ 0x100 ];
	int m_rank;
};

class Rva007F2350StatsCursor
{
public:
	bool next( Rva007F2350StatsRecord *record );
	bool rva007F2230( Rva007F2350StatsRecord *record );
	bool rva007F24A0( Rva007F2350StatsRecord *record );

	Rva007E8810Message *m_msg;
	int m_index;
	int m_state;
};

bool Rva007F2350StatsCursor::next( Rva007F2350StatsRecord *record )
{
	char name[ 0x40 ];
	char valueText[ 0x40 ];
	int value;

	record->m_name[ 0 ] = 0;
	record->m_30 = 0;
	record->m_value = 0;
	record->m_addStat[ 0 ] = 0;
	record->m_rank = 0;

	sprintf( name, "stats.%d.value", m_index );
	if ( !((BfmeThingUPB *)m_msg)->bfmeGoUPB( (void *)name, valueText, (void *)0x40 ) )
		return false;
	sscanf( valueText, "%f", &value );
	record->m_value = value;

	sprintf( name, "stats.%d.rank", m_index );
	record->m_rank = (int)(long)((BfmeThingRF *)m_msg)->bfmeGoRF( (void *)name, (void *)0 );

	sprintf( name, "stats.%d.owner", m_index );
	record->m_owner = m_msg->getInt64( name, 0 );

	sprintf( name, "stats.%d.name", m_index );
	((BfmeThingUPB *)m_msg)->bfmeGoUPB( (void *)name, record->m_name, (void *)0x20 );

	sprintf( name, "stats.%d.text", m_index );
	((BfmeThingUPB *)m_msg)->bfmeGoUPB( (void *)name, record->m_addStat, (void *)0xff );

	++m_index;
	m_state = 0;
	return true;
}

// BFME2 0x0065ED20; body from Open-BFME-1 (submodule 10af19f44a, BFME1 0x007F2230),
// byte-identical, written with this file's row-name calls. BFME 1 folded it
// with next; here next is the separate 0x0065EE40 body, so the address-derived
// name is the one this keeps. Retail 0x007F2230 (BFME 1): int3 at 0x007F222F,
// ret 4 at 0x007F2348, then five int3 bytes. The stats.* strings prove this
// shares the cursor and output record layout with next; its +0x30 output is
// the key string.
bool Rva007F2350StatsCursor::rva007F2230(Rva007F2350StatsRecord *record)
{
 char name[0x40];
 char valueText[0x40];
 union { float number; int bits; } value;
 record->m_name[0] = 0;
 record->m_30 = 0;
 record->m_value = 0;
 record->m_addStat[0] = 0;
 record->m_rank = 0;
 sprintf(name, "stats.%d.key", m_index);
 if (!((BfmeThingUPB *)m_msg)->bfmeGoUPB((void *)name, &record->m_30, (void *)0x20)) return false;
 sprintf(name, "stats.%d.value", m_index);
 ((BfmeThingUPB *)m_msg)->bfmeGoUPB((void *)name, valueText, (void *)0x40);
 sscanf(valueText, "%f", &value.number);
 record->m_value = value.bits;
 sprintf(name, "stats.%d.rank", m_index);
 record->m_rank = (int)(long)((BfmeThingRF *)m_msg)->bfmeGoRF((void *)name, (void *)0);
 sprintf(name, "stats.%d.text", m_index);
 ((BfmeThingUPB *)m_msg)->bfmeGoUPB((void *)name, record->m_addStat, (void *)0xff);
 ++m_index;
 return true;
}

// BFME2 0x0065EF90; body from Open-BFME-1 5cae4bdff (BFME1 0x007F24A0), unchanged.
// Retail 0x007F24A0: the per-stat addStats reader.  It formats the keys with
// the index the cursor has already stepped past (m_index - 1, read once) and
// the addStats counter in m_state, which it advances instead of m_index.
bool Rva007F2350StatsCursor::rva007F24A0(Rva007F2350StatsRecord *record)
{
 char name[0x40];
 char valueText[0x40];
 union { float number; int bits; } value;
 record->m_name[0] = 0;
 record->m_30 = 0;
 record->m_value = 0;
 record->m_addStat[0] = 0;
 record->m_rank = 0;
 int stat = m_index - 1;
 sprintf(name, "stats.%d.addStats.%d.value", stat, m_state);
	if (!((BfmeThingUPB *)m_msg)->bfmeGoUPB((void *)name, valueText, (void *)0x40)) return false;
 sscanf(valueText, "%f", &value.number);
 record->m_value = value.bits;
 sprintf(name, "stats.%d.addStats.%d.key", stat, m_state);
	((BfmeThingUPB *)m_msg)->bfmeGoUPB((void *)name, &record->m_30, (void *)0x20);
 sprintf(name, "stats.%d.addStats.%d.text", stat, m_state);
	((BfmeThingUPB *)m_msg)->bfmeGoUPB((void *)name, record->m_addStat, (void *)0xff);
 ++m_state;
 return true;
}

// BF1 f98983a7d clean RankRequest donor. Native65F2B0..65F4D1/RET16,
// rank category and11 field formats establish behavior; original target
// type/function names remain unknown. User24/stat16/header16 are native.
// The adjacent65ED20/65EE40/65EF90 statistics readers above already prove
// this SDK cluster's /O2 blend /GS configuration. Reuse that established
// configuration; four inline scalar getters preserve native SIB register
// selection. The named12B UpdateStats record is independently initialized
// by7B5AA0. Its data owner and request are verified together.
class Rva007E8AC0 {public:void run();};
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
 __forceinline int GetType(int index)const{return stats[index].userType;}
 __forceinline const char * GetKey(int index)const{return stats[index].key;}
 __forceinline float GetValue(int index)const{return stats[index].value;}
 __forceinline const char * GetText(int index)const{return stats[index].text;}
};

struct Rva007F27C0User
{
	Rva007F27C0UserHeader header;
	Rva007F27C0UserData data;
};

// Existing target UpdateStats transaction record: pointer field at +4.
struct Rva007B55E0TxnName
{
    Rva007B55E0TxnName(const char *type, const char *name);
    const char *m_type;
    const char *m_name;
    int m_reserved;
};
extern Rva007B55E0TxnName TheRankUpdateStatsTransaction;

void __stdcall buildRva007F27C0( Rva007E8810Message *msg, const char *gsid,
	const Rva007F27C0User *users, int userCount )
{
	register Rva007E8810Message *message;
	register const char *txn;
	char name[ 0x40 ];
	char value[ 0x40 ];
	int i;

	message = msg;
	txn = *(&TheRankUpdateStatsTransaction.m_name);
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
				message->addInt( name, data->GetType(j) );
				sprintf( name, "u.%d.s.%d.k", i, j );
				message->addString( name, data->GetKey(j) );
				sprintf( name, "u.%d.s.%d.v", i, j );
				sprintf( value, "%.4f", data->GetValue(j) );
				message->addString( name, value );
				sprintf( name, "u.%d.s.%d.t", i, j );
				message->addString( name, data->GetText(j) );
			}
		}

		sprintf( name, "u.%d.s.[]", i );
		message->addInt( name, data->statCount );
	}
	message->addInt( "u.[]", userCount );
}
