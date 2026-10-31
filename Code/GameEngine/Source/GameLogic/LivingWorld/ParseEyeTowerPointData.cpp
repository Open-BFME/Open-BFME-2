// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/GameEngine/Source/Common /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/LivingWorld
// ParseEyeTowerPointData, retail RVA 0x004E383D (123 bytes), recovered from the
// ParseForceBattle recipe at 0x004E16D9. Same operand-masked shape: null-check
// INI and instance, construct a stack record, INI::initFromINI it against the
// type's FieldParse table, then append it to the owner, else throw
// INIException(3) with the type's literal. Only the record (a 0x0C-byte
// _STL::vector<BfmePod8>, ctor 0x004E364F / clear 0x004E366E), the table, the
// append thunk and the "ParseEyeTowerPointData::Invalid data passed in."
// literal differ from the template. Evidence: the retail literal at
// 0x00C62004 names the type; the 0x0C record size is read from sub esp,0x14
// with the record at ebp-0x20 and the exception buffer at ebp-0x14.
// stlport
#include <vector>

struct BfmePod8 { int a[2]; };

typedef int Int;

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse
{
    const char *token;
    FieldParseProc parse;
    const void *userData;
    int offset;
};

#include "../../../../../reference/shims/iniexception/Common/INIException.h"

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
	static void dup_002F0F7(INI *, void *, void *, const void *);
	static void parseBool(INI *, void *, void *, const void *);
	static void parseAsciiString( INI *, void *, void *, const void * );
	static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004E3816Parse(INI *, void *, void *, const void *);
};

// The record is the EyeTower temp built at ebp-0x20: a 0x0C-byte vector whose
// ctor row lives at 0x004E364F. Its destructor spelling is a new pin at the
// rowed clear body 0x004E366E (?rva004E366E@Rva004E366E@@QAEXXZ).
class Rva004E364F
{
public:
	Rva004E364F();
	~Rva004E364F();
private:
	_STL::vector<BfmePod8> m_vec;
};

struct Rva005668E9Element;

class Rva005669B7Owner
{
public:
	void rva005669B7(const Rva005668E9Element &record);
};

// Retail VA 0x00C62034: the LookPoint list callback and null sentinel.
extern const FieldParse g_00C62034[2] =
{
	{ "LookPoint", INI::Rva004E3816Parse, 0, 0 },
	{ 0, 0, 0, 0 }
};

void ParseEyeTowerPointData( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva004E364F record;
		ini->initFromINI( &record, g_00C62034 );
		((Rva005669B7Owner *)instance)->rva005669B7( *(const Rva005668E9Element *)&record );
	}
	else
		throw INIException( 3, "ParseEyeTowerPointData::Invalid data passed in." );
}

