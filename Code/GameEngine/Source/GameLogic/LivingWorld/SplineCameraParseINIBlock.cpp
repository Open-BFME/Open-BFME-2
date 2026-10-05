// cl: /O1 /DNDEBUG /DWIN32 /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameLogic/LivingWorld/SplineCameraParseINIBlock.cpp (donor
// revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1).
// Compiled that way each body below places uniquely on unclaimed game.dat
// .text by masked whole-.text search, and ./build.sh reproduces it byte for
// byte: SplineCameraParseINIBlock 0x004E3300 (130B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Open-BFME7: SplineCamera::ParseINIBlock (retail 0x003BA660 165 B; a gap
// claimed through its exception text; a plain callback despite the name).
// With no INI or instance it throws INIException(3 "SplineCamera::
// ParseINIBlock::Invalid data passed in."); otherwise a 0x18-byte polymorphic
// record built by the out-of-line constructor at 0x003BA5F0 -- two dwords and
// an embedded map<int X> (the _Rb_tree destructor at 0x003AB460 is in the
// ledger) -- is filled through INI::initFromINI with the table at VA
// 0x010ED4C0 and handed to the instance's append routine (0x003B2890); the
// inline virtual destructor restores the vtable (VA 0x010EC84C) and destroys
// the map.  Address-derived names.

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

struct Rva003AB460Tree
{
	~Rva003AB460Tree();
	char m_body[ 0x0C ];
};

class Rva003BA660Record
{
public:
	Rva003BA660Record();
	virtual ~Rva003BA660Record() {}

private:
	Int m_04;
	Int m_08;
	Rva003AB460Tree m_tree;
};

extern const FieldParse Rva003BA660FieldParseTable[];

class Rva003BA660Owner
{
public:
	void append( Rva003BA660Record *record );
};

// ?SplineCameraParseINIBlock@@YAXPAVINI@@PAX1PBX@Z
void SplineCameraParseINIBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003BA660Record record;
		ini->initFromINI( &record, Rva003BA660FieldParseTable );
		((Rva003BA660Owner *)instance)->append( &record );
	}
	else
		throw INIException( 3, "SplineCamera::ParseINIBlock::Invalid data passed in." );
}
