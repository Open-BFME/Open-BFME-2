#include <string.h>

// EA FESL client SDK ("jabba") -- buddy/presence request builders whose
// argument selection is a small switch over an answer/message kind.
//
// Same SDK and same message object as Y4FeslBuddyRequests.cpp; see that file
// for the range evidence.  Split into its own translation unit only to keep
// the switch experiments from disturbing rows already verified there.

typedef __int64 FeslInt64;

class Rva007E8AC0
{
public:
	void run( void );
};

#include "../../Include/GameNetwork/BfmeThingCIB.h"

class BfmeThingCIC
{
public:
	void bfmeGoCIC( void *key, void *value );
};

class Rva007E8810Message
{
public:
	void addInt64( const char *key, FeslInt64 value );               // 0x007E8E90
	void addBool( const char *key, bool value );                     // 0x007E8980
	void setError( int code );                                       // 0x007E88C0

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

void __stdcall Rva007FB810( Rva007E8810Message *msg, const char *user, int answer )
{
	FESL_RESET(msg);
	msg->m_category = 'GRSP';
	msg->m_depth = 3;
	FESL_ADD_STRING(msg, "USER", user);
	switch( answer )
	{
		case 0:
			FESL_ADD_STRING(msg, "ANSW", "Y");
			break;
		case 1:
			FESL_ADD_STRING(msg, "ANSW", "N");
			break;
		case 2:
			FESL_ADD_STRING(msg, "ANSW", "R");
			break;
	}
}

void __stdcall Rva007FB8D0( Rva007E8810Message *msg, int kind, const char *user,
	const char *subject, const char *body, int secs )
{
	FESL_RESET(msg);
	msg->m_category = 'SEND';
	msg->m_depth = 3;
	switch( kind )
	{
		case 1:
			FESL_ADD_STRING(msg, "TYPE", "C");
			break;
		case 2:
			FESL_ADD_STRING(msg, "TYPE", "A");
			break;
	}
	FESL_ADD_STRING(msg, "USER", user);
	FESL_ADD_STRING(msg, "SUBJ", subject);
	FESL_ADD_STRING(msg, "BODY", body);
	FESL_ADD_INT(msg, "SECS", secs);
}

void __stdcall Rva007FB960( Rva007E8810Message *msg, int kind, const char *user,
	const char *subject, const char *body, int secs )
{
	FESL_RESET(msg);
	msg->m_category = 'BRDC';
	msg->m_depth = 3;
	switch( kind )
	{
		case 1:
			FESL_ADD_STRING(msg, "TYPE", "C");
			break;
		case 2:
			FESL_ADD_STRING(msg, "TYPE", "A");
			break;
	}
	FESL_ADD_STRING(msg, "USER", user);
	FESL_ADD_STRING(msg, "SUBJ", subject);
	FESL_ADD_STRING(msg, "BODY", body);
	FESL_ADD_INT(msg, "SECS", secs);
}

void __stdcall Rva007FB410( Rva007E8810Message *msg, const char *user,
	int answer, bool pres )
{
	FESL_RESET(msg);
	msg->m_category = 'RRSP';
	msg->m_depth = 3;
	FESL_ADD_STRING(msg, "USER", user);
	switch( answer )
	{
		case 0:
			FESL_ADD_STRING(msg, "ANSW", "Y");
			break;
		case 1:
			FESL_ADD_STRING(msg, "ANSW", "N");
			break;
		case 2:
			FESL_ADD_STRING(msg, "ANSW", "B");
			break;
	}
	if( answer == 0 )
		FESL_ADD_STRING(msg, "PRES", pres ? "Y" : "N");
}

void __stdcall Rva007FB6D0( Rva007E8810Message *msg, int list, const char *group,
	const char *lsrc, bool pres, bool pend )
{
	FESL_RESET(msg);
	msg->m_category = 'RGET';
	msg->m_depth = 3;
	switch( list )
	{
		case 1:
			FESL_ADD_STRING(msg, "LIST", "B");
			break;
		case 2:
			FESL_ADD_STRING(msg, "LIST", "I");
			break;
	}
	if( group && strlen( group ) != 0 )
		FESL_ADD_STRING(msg, "GROUP", group);
	if( lsrc && strlen( lsrc ) != 0 )
		FESL_ADD_STRING(msg, "LSRC", lsrc);
	FESL_ADD_STRING(msg, "PRES", pres ? "Y" : "N");
	FESL_ADD_STRING(msg, "PEND", pend ? "T" : "F");
}

// FESL 'RADD' friend-list request with an optional single-letter attribute.
// BFME 2: Open-BFME-1's body (submodule 10af19f44a), byte-identical in game.dat
// at 0x00667770, written with this file's row-name calls. Its strcat is the
// /Oi intrinsic: retail scans for the terminator and stores the letter inline.

void __stdcall Rva007FB260( Rva007E8810Message *msg, int list,
	const char *user, const char *group, const char *lsrc, bool pres,
	int attribute )
{
	FESL_RESET(msg);
	msg->m_category = 'RADD';
	msg->m_depth = 3;
	switch( list )
	{
		case 1: FESL_ADD_STRING(msg, "LIST", "B"); break;
		case 2: FESL_ADD_STRING(msg, "LIST", "I"); break;
	}
	FESL_ADD_STRING(msg, "USER", user);
	if( group )
		FESL_ADD_STRING(msg, "GROUP", group);
	if( lsrc )
		FESL_ADD_STRING(msg, "LSRC", lsrc);
	FESL_ADD_STRING(msg, "PRES", pres ? "Y" : "N");
	if( attribute )
	{
		char text[ 4 ] = "";
		if( attribute == 1 )
			strcat( text, "A" );
		else if( attribute == 2 )
			strcat( text, "M" );
		else if( attribute == 3 )
			strcat( text, "I" );
		FESL_ADD_STRING(msg, "ATTR", text);
	}
}
