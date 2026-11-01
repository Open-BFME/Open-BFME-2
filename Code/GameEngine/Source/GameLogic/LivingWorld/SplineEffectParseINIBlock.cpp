// cl: -DNDEBUG -DWIN32 -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/LivingWorld
// Open-BFME7: SplineEffect::ParseINIBlock (retail 0x003BB730 214 B; a gap
// claimed through its own exception text -- despite the "::" the entry point
// takes no `this`.  Unlike its neighbours it checks THREE arguments for
// null, not two: ini, instance, and the third parameter, which here is not
// an opaque store pointer but a `const char *name` (it is fed straight into
// the AsciiString constructor as the text pointer).  With any of the three
// null it throws INIException(3
// "SplineEffect::ParseINIBlock::Invalid data passed in."); otherwise it
// copies the name into a local AsciiString, heap-allocates a 0x28-byte
// record with the plain global `operator new` (constructing it only if the
// allocation succeeds -- the classic MSVC "if (p) ctor(p);" shape for a bare
// `new T()`, matching Path::appendNode's node allocation), fills it through
// INI::initFromINI with the table at VA 0x010ED888 (called even if the
// allocation failed and the record pointer is null -- replicated as-is),
// hands the name and the (possibly heap-allocated, possibly null) record to
// the instance's add routine (thunk 0x0001FD4D), and releases the local
// name's buffer.  The record is never freed here: ownership passes to the
// instance.  Address-derived names.
// 0x00036410; the shared ascii_string.h header gives a different ctor/dtor codegen shape.

typedef int Int;
typedef unsigned int UInt;

#include <new>

#include "../../../Include/Common/INI/FieldParse.h"

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
	static void parseReal(INI *, void *, void *, const void *);
	static void parseBool(INI *, void *, void *, const void *);
};

class AsciiString;

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"


// Native 4E3F8B calls the already rowed 40-byte record constructor.
class Rva004E3CD0
{
public:
	Rva004E3CD0();

private:
	char m_body[ 0x28 ];
};

void Rva0050407AParseColorControlPointBlock(INI *, void *, void *, const void *);
class Rva00064680 { public: static void parseControlPointBlock(INI *, void *, void *, const void *); };
void SplineEffectParseGeometryName(INI *, void *, void *, const void *);
class Rva003B7140Owner;
class GenForwardedArg;
void Rva003B7140(Rva003B7140Owner *, GenForwardedArg *);

// Native table C62148: five fields and the null terminator. Both control
// point parsers receive the rowed +4-subobject forwarding callback 4E14BC.
extern const FieldParse Rva003BB730RecordFieldParseTable[] = {
    { "Opacity", INI::parseReal, 0, 0x24 },
    { "ColorIntensityControlPoint", Rva0050407AParseColorControlPointBlock, (const void *)Rva003B7140, 0 },
    { "ControlPoint", Rva00064680::parseControlPointBlock, (const void *)Rva003B7140, 0 },
    { "Geometry", SplineEffectParseGeometryName, 0, 0 },
    { "LoadInShell", INI::parseBool, 0, 0x22 },
    { 0, 0, 0, 0 }
};
class Rva003BB730Record;

class Rva003BB730Owner
{
public:
	void addEffect( AsciiString &name, Rva003BB730Record *record );
};

// ?SplineEffectParseINIBlock@@YAXPAVINI@@PAX1PBD@Z
void SplineEffectParseINIBlock( INI *ini, void *instance, void *, const char *name )
{
	if( ini && instance && name )
	{
		AsciiString token( name );
		Rva004E3CD0 *record = new Rva004E3CD0();
		ini->initFromINI( record, Rva003BB730RecordFieldParseTable );
		( (Rva003BB730Owner *)instance )->addEffect( token, (Rva003BB730Record *)record );
	}
	else
		throw INIException( 3, "SplineEffect::ParseINIBlock::Invalid data passed in." );
}
