// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Retail 0x0039981E, 315B: a CastleBehaviorModuleData INI field parser
// (cdecl, INI field-parse signature; the store is the third argument). It
// reads a name and a template name, keys the name through
// TheNameKeyGenerator, fills a {template name, two optional unsigned counts}
// record, inserts the key/record pair into the store map (make_pair
// 0x00396943, pair conversion 0x003962AE, insert 0x003992B0) and passes the
// template name to TheSidesList member 0x0032C2FF. Target evidence: the
// neighbouring CastleBehavior rows (0x00399800 record vector clear, map
// insert 0x003992B0 on Rva0039834C) and the call shapes above. The pair
// conversion copy is made inside the map's inline insert, as STLport's map
// insert does with its value_type, so the copy is addressed by its slot and
// destroyed before the make_pair temporary. Field name not established:
// address-derived.

#include "ascii_string.h"

typedef unsigned int UnsignedInt;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	const char *getNextTokenOrNull(const char *seps = 0);
	UnsignedInt scanUnsignedInt(const char *token);
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class SidesList
{
public:
	void rva0032C2FF(const AsciiString &templateName);
};

extern SidesList *TheSidesList;

struct BfmeStringRecord004071F7
{
	BfmeStringRecord004071F7() : m_count1(0), m_count2(0) {}
	AsciiString m_templateName;
	UnsignedInt m_count1;
	UnsignedInt m_count2;
};

struct Rva0039627D
{
	Rva0039627D(const Rva0039627D &other);
	void *m_key;
	BfmeStringRecord004071F7 m_record;
};

Rva0039627D __cdecl Rva00396943Construct(void **key, const BfmeStringRecord004071F7 &record);

static inline const Rva0039627D &asPairRef( const Rva0039627D &pair )
{
	return pair;
}

struct RvaInsertOut
{
	void *m_node;
};

class Rva0039834C
{
public:
	RvaInsertOut *rva003992B0(RvaInsertOut *out, const Rva0039627D *value);
};

class Rva0039981EMap
{
public:
	__forceinline void insert( const Rva0039627D &pair )
	{
		Rva0039627D value( pair );
		RvaInsertOut out;
		((Rva0039834C *)this)->rva003992B0( &out, &value );
	}
};

class CastleBehaviorModuleData
{
public:
	static void rva0039981E(INI *ini, void *instance, void *store, const void *userData);
};

void CastleBehaviorModuleData::rva0039981E( INI *ini, void * /*instance*/, void *store, const void * /*userData*/ )
{
	AsciiString name( "" );
	INI::parseAsciiString( ini, 0, &name, 0 );
	void *key = (void *)TheNameKeyGenerator->nameToKey( name );

	AsciiString templateName( "" );
	INI::parseAsciiString( ini, 0, &templateName, 0 );

	BfmeStringRecord004071F7 record;
	record.m_templateName = templateName;
	record.m_count1 = 0;

	const char *token = ini->getNextTokenOrNull();
	if( token )
		record.m_count1 = ini->scanUnsignedInt( token );

	token = ini->getNextTokenOrNull();
	if( token )
		record.m_count2 = ini->scanUnsignedInt( token );

	((Rva0039981EMap *)store)->insert( Rva00396943Construct( &key, record ) );

	TheSidesList->rva0032C2FF( templateName );
}
