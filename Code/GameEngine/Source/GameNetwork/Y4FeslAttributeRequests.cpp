// cl: /GS
#include <stdio.h>
#include <string.h>

// EA FESL client SDK ("jabba") -- request builders that emit a variable-length
// run of attribute fields.
//
// Same SDK cluster and same message object as Y4FeslBuddyRequests.cpp.  Each
// row here formats one wire key per attribute with sprintf into a 64-byte
// stack scratch ("B-%s" for buddy attributes, "P-%s" for player attributes),
// which is why these three bodies carry a /GS cookie prologue reading
// 0x012DBDB0 and check it at 0x009F74F4 -- so this translation unit needs its
// own `// cl: /GS` directive.  The scratch length is hard evidence: the cookie
// slot sits at +0x40 of a 0x44-byte frame.
//
// The attribute array element is 8 bytes read as [base + i*8] and
// [base + i*8 + 4], i.e. a { key, value } pair of pointers -- also hard
// evidence, from the scaled index.  The pair's C++ member names are not.

typedef __int64 FeslInt64;

class Rva007E8810Message
{
public:
	void reset( void );                                              // 0x007E8AC0
	void addString( const char *key, const char *value );            // 0x007E8A10
	void addInt( const char *key, int value );                       // 0x007E88D0
	void addBool( const char *key, bool value );                     // 0x007E8980

	char m_head[ 0x1C ];
	unsigned int m_category;
	char m_tail[ 0x0C ];
	int m_depth;
};

#include "../../Include/GameNetwork/Rva007FC810Attribute.h"

// Rva007FC810: defined in Y4FeslAttributeRequest.cpp (its row's unit).
void __stdcall Rva007FC810( Rva007E8810Message *msg, const char *name,
	const Rva007FC810Attribute *attributes, int numAttributes, int join );

void __stdcall Rva007FC8F0( Rva007E8810Message *msg,
	const Rva007FC810Attribute *attributes, int numAttributes )
{
	int index;

	msg->reset();
	msg->m_category = 'UGDE';
	msg->m_depth = 3;
	for( index = 0; index < numAttributes; index++ )
	{
		char key[ 0x40 ] = "";

		sprintf( key, "D-%s", attributes[ index ].m_key );
		msg->addString( key, attributes[ index ].m_value );
	}
}

// Rva007FC990: defined in Y4FeslAttributeRequestPid.cpp (its row's unit).
void __stdcall Rva007FC990( Rva007E8810Message *msg, int pid,
	const Rva007FC810Attribute *attributes, int numAttributes );

// Rva007FCBA0: defined in Y4FeslAttributeRequestPid.cpp (its row's unit).
void __stdcall Rva007FCBA0( Rva007E8810Message *msg, int pid,
	const Rva007FC810Attribute *attributes, int numAttributes );

void __stdcall Rva007FCB10( Rva007E8810Message *msg, bool allowed, int pid,
	int reason )
{
	char text[ 28 ];

	msg->reset();
	msg->m_category = 'EGRS';
	msg->m_depth = 3;
	msg->addBool( "ALLOWED", allowed );
	msg->addInt( "PID", pid );
	sprintf( text, "%d", reason );
	if( !allowed )
		msg->addString( "REASON", text );
}

void __stdcall Rva007FCCC0( Rva007E8810Message *msg, int lid, int gid, int pid,
	int type, const char *reason )
{
	const char *typeName = 0;

	msg->reset();
	msg->m_category = 'ABUS';
	msg->m_depth = 3;
	msg->addInt( "LID", lid );
	msg->addInt( "GID", gid );
	if( pid )
		msg->addInt( "PID", pid );
	switch( type )
	{
		case 1:
			typeName = "Language";
			break;
		case 2:
			typeName = "Harassment";
			break;
		case 3:
			typeName = "Cheating";
			break;
		case 4:
			typeName = "Illegal";
			break;
		case 5:
			typeName = "General";
			break;
		case 6:
			typeName = "Other";
			break;
	}
	if( typeName )
		msg->addString( "TYPE", typeName );
	if( reason && strlen( reason ) != 0 )
		msg->addString( "REASON", reason );
}
