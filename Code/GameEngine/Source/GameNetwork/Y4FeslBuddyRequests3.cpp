#include <string.h>

// EA FESL client SDK ("jabba") -- buddy/presence transaction request builders.
//
// Same SDK and same message object as Y4FeslBuddyRequests.cpp; see that file
// for the range evidence.  Split into its own translation unit only to keep
// these ICF-folded bodies (ambiguous twins in lotrbfme.exe, served as T3 by
// bfme1_sweep) from disturbing rows already verified there.

typedef __int64 FeslInt64;

#include "../../Include/GameNetwork/Rva007E8AC0.h"

#include "../../Include/GameNetwork/BfmeThingCIB.h"

class BfmeThingCIC
{
public:
	void bfmeGoCIC( void *key, void *value );
};

// Class name is the claimed pin (ctor 0x007E8810).  Layout is the same object
// V2FeslTxnRequests.cpp already recovered from reset()/add* stores.
class Rva007E8810Message
{
public:
	void addInt64( const char *key, FeslInt64 value );               // 0x007E8E90
	void addBool( const char *key, bool value );                     // 0x007E8980
	void setError( int code );                                       // 0x007E88C0

	char m_pad00[ 0x10 ];
	char *m_output;                                                  // +0x10
	int m_bufferSize;                                                // +0x14
	int m_writeCursor;                                               // +0x18
	unsigned int m_category;                                         // +0x1C
	char m_pad20[ 4 ];
	int m_errorCode;                                                 // +0x24
	char m_pad28[ 4 ];
	int m_depth;                                                     // +0x2C
};

#define FESL_RESET(message) ((Rva007E8AC0 *)(message))->run()
#define FESL_ADD_STRING(message, key, value) \
	((BfmeThingCIC *)(message))->bfmeGoCIC((void *)(key), (void *)(value))
#define FESL_ADD_INT(message, key, value) \
	((BfmeThingCIB *)(message))->bfmeGoCIB((void *)(key), (void *)(value))

typedef Rva007E8810Message FeslTxnMessage;

// ---- 'AUTH' ---------------------------------------------------------------

void __stdcall Rva007FAE40( FeslTxnMessage *msg, const char *lkey,
	const char *prod, const char *vers, const char *pres, const char *rsrc )
{
	FESL_RESET(msg);
	msg->m_category = 'AUTH';
	msg->m_depth = 3;
	FESL_ADD_STRING(msg, "LKEY", lkey);
	FESL_ADD_STRING(msg, "PROD", prod);
	FESL_ADD_STRING(msg, "VERS", vers);
	FESL_ADD_STRING(msg, "PRES", pres);
	if( rsrc && *rsrc )
		FESL_ADD_STRING(msg, "RSRC", rsrc);
	else
		FESL_ADD_STRING(msg, "RSRC", "CSO");
}

void __stdcall Rva007FAEE0( FeslTxnMessage *msg, const char *user,
	const char *pass, const char *prod, const char *vers, const char *pres,
	const char *rsrc )
{
	FESL_RESET(msg);
	msg->m_category = 'AUTH';
	msg->m_depth = 3;
	FESL_ADD_STRING(msg, "USER", user);
	FESL_ADD_STRING(msg, "PASS", pass);
	FESL_ADD_STRING(msg, "PROD", prod);
	FESL_ADD_STRING(msg, "VERS", vers);
	FESL_ADD_STRING(msg, "PRES", pres);
	if( rsrc && *rsrc )
		FESL_ADD_STRING(msg, "RSRC", rsrc);
	else
		FESL_ADD_STRING(msg, "RSRC", "CSO");
}

// ---- 'USCH' ---------------------------------------------------------------

void __stdcall Rva007FAFB0( FeslTxnMessage *msg, const char *user,
	const char *domain, const char *rsrc, bool dist, int maxResults )
{
	FESL_RESET(msg);
	msg->m_category = 'USCH';
	msg->m_depth = 3;
	FESL_ADD_STRING(msg, "USER", user);
	if( domain && strlen( domain ) != 0 )
		FESL_ADD_STRING(msg, "DOMN", domain);
	if( rsrc && strlen( rsrc ) != 0 )
		FESL_ADD_STRING(msg, "RSRC", rsrc);
	if( dist )
		FESL_ADD_STRING(msg, "DIST", "T");
	else
		FESL_ADD_STRING(msg, "DIST", "F");
	FESL_ADD_INT(msg, "MAXR", maxResults);
}

// ---- 'RDEM' -----------------------------------------------------------------

void __stdcall Rva007FB620( FeslTxnMessage *msg, const char *user,
	const char *group, const char *lsrc, bool pres )
{
	FESL_RESET(msg);
	msg->m_category = 'RDEM';
	msg->m_depth = 3;
	FESL_ADD_STRING(msg, "USER", user);
	if( group && strlen( group ) != 0 )
		FESL_ADD_STRING(msg, "GROUP", group);
	if( lsrc && strlen( lsrc ) != 0 )
		FESL_ADD_STRING(msg, "LSRC", lsrc);
	FESL_ADD_STRING(msg, "PRES", pres ? "Y" : "N");
}
