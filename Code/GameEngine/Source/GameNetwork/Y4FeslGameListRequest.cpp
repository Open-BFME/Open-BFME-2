// cl: /GS
#include <stdio.h>

// EA FESL client SDK ("jabba") -- the game-list ('GLST') query builder.
//
// Same SDK cluster and same message object as Y4FeslBuddyRequests.cpp.  This
// is the widest row in the span: fourteen __stdcall arguments, `ret 0x38`.
// Its literal keys are the whole filter vocabulary of the EA game browser --
// FILTER-FAV-ONLY, FILTER-NOT-FULL, FILTER-NOT-PRIVATE, FILTER-MIN-SIZE,
// FILTER-ATTR-%s, FAV-PLAYER, FAV-GAME, FAV-PLAYER-UID, FAV-GAME-UID -- which
// is the strongest single piece of evidence that 0x007F96C0..0x007FCF80 is the
// FESL browser/buddy client and not game code.
//
// The attribute filters are formatted one key per array element with sprintf
// into a 64-byte stack scratch, so the body carries a /GS cookie prologue and
// this TU needs its own `// cl: /GS`.  The attribute count is compared with
// `jbe`/`jb`, so it is UNSIGNED -- that is hard evidence and it differs from
// the otherwise identical loop in Y4FeslAttributeRequests.cpp, which uses
// signed `jle`/`jl`.

typedef __int64 FeslInt64;

class Rva007E8AC0
{
public:
	void run( void );
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB( void *key, void *value );
};

class BfmeThingCIC
{
public:
	void bfmeGoCIC( void *key, void *value );
};

class Rva007E8980
{
public:
	void go( int key, unsigned char value );
};

class Rva007E8810Message
{
public:
	char m_head[ 0x1C ];
	unsigned int m_category;
	char m_tail[ 0x0C ];
	int m_depth;
};

#define FESL_RESET(message) ((Rva007E8AC0 *)(message))->run()
#define FESL_ADD_STRING(message, key, value) \
	((BfmeThingCIC *)(message))->bfmeGoCIC((void *)(key), (void *)(value))
#define FESL_ADD_INT(message, key, value) \
	((BfmeThingCIB *)(message))->bfmeGoCIB((void *)(key), (void *)(value))
#define FESL_ADD_BOOL(message, key, value) \
	((Rva007E8980 *)(message))->go((int)(void *)(key), (unsigned char)(value))

struct FeslAttributeFilter
{
	const char *m_key;
	const char *m_value;
};

void __stdcall Rva007FC3B0( Rva007E8810Message *msg, int lid, bool favOnly,
	bool notFull, bool notPrivate, int minSize,
	const FeslAttributeFilter *attributes, unsigned int numAttributes,
	const char *favPlayer, const char *favGame, int gid, int count,
	const char *favPlayerUid, const char *favGameUid )
{
	unsigned int index;

	FESL_RESET( msg );
	msg->m_category = 'GLST';
	msg->m_depth = 3;
	FESL_ADD_INT( msg, "LID", lid );
	FESL_ADD_BOOL( msg, "FILTER-FAV-ONLY", favOnly );
	FESL_ADD_BOOL( msg, "FILTER-NOT-FULL", notFull );
	FESL_ADD_BOOL( msg, "FILTER-NOT-PRIVATE", notPrivate );
	FESL_ADD_INT( msg, "FILTER-MIN-SIZE", minSize );
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "FILTER-ATTR-%s", attributes[ index ].m_key );
		FESL_ADD_STRING( msg, key, attributes[ index ].m_value );
	}
	FESL_ADD_STRING( msg, "FAV-PLAYER", favPlayer );
	FESL_ADD_STRING( msg, "FAV-GAME", favGame );
	if( gid )
		FESL_ADD_INT( msg, "GID", gid );
	FESL_ADD_INT( msg, "COUNT", count );
	FESL_ADD_STRING( msg, "FAV-PLAYER-UID", favPlayerUid );
	FESL_ADD_STRING( msg, "FAV-GAME-UID", favGameUid );
}

void __stdcall Rva007FC290( Rva007E8810Message *msg, bool favOnly,
	bool notFull, bool notPrivate, int minSize,
	const FeslAttributeFilter *attributes, unsigned int numAttributes,
	const char *favPlayer, const char *favGame, const char *favPlayerUid,
	const char *favGameUid )
{
	unsigned int index;

	FESL_RESET( msg );
	msg->m_category = 'LLST';
	msg->m_depth = 3;
	FESL_ADD_BOOL( msg, "FILTER-FAV-ONLY", favOnly );
	FESL_ADD_BOOL( msg, "FILTER-NOT-FULL", notFull );
	FESL_ADD_BOOL( msg, "FILTER-NOT-PRIVATE", notPrivate );
	FESL_ADD_INT( msg, "FILTER-MIN-SIZE", minSize );
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "FILTER-ATTR-%s", attributes[ index ].m_key );
		FESL_ADD_STRING( msg, key, attributes[ index ].m_value );
	}
	FESL_ADD_STRING( msg, "FAV-PLAYER", favPlayer );
	FESL_ADD_STRING( msg, "FAV-GAME", favGame );
	FESL_ADD_STRING( msg, "FAV-PLAYER-UID", favPlayerUid );
	FESL_ADD_STRING( msg, "FAV-GAME-UID", favGameUid );
}
