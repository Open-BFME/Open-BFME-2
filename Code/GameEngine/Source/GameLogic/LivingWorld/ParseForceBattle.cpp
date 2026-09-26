// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc
// ParseForceBattle, retail RVA 0x004E16D9 (123 bytes). Target evidence:
// the callback table at VA 0x00C6CD60 registers ForceBattle to this body, and
// its error branch uses the matching literal at VA 0x00C61ABC. The local record
// spans 0x28 bytes, its target FieldParse table is at VA 0x00C61AE8, and the
// append thunk at RVA 0x0056652F adjusts owner this by +0x14. The record's
// target class identity is unknown; its name is address-derived.
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/
// LivingWorld/ParseForceBattle.cpp (RVA 0x003B7DC0, 157 bytes). It corroborates
// parser behavior and the eight field names/offsets. Donor type naming is not
// asserted as a target identity.

typedef int Int;

struct FieldParse;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
};

class Rva004E16D9Record
{
public:
	Rva004E16D9Record();
	~Rva004E16D9Record();

private:
	char m_body[ 0x28 ];
};

class Rva0056652FOwner
{
public:
	void append( Rva004E16D9Record *record );
};

// ?ParseForceBattle@@YAXPAVINI@@PAX1PBX@Z
void ParseForceBattle( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva004E16D9Record record;
		ini->initFromINI( &record, (const FieldParse *)0x00C61AE8 );
		((Rva0056652FOwner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "ParseForceBattle::Invalid data passed in." );
}
