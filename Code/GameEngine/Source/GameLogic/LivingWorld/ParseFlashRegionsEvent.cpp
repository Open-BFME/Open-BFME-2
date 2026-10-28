// cl: -DNDEBUG -DWIN32 -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/LivingWorld
// BFME 1 donor: game/GameEngine/Source/GameLogic/LivingWorld/
// ParseFlashRegionsEvent.cpp at 6d943426, recompiled /Os for BFME 2.
// Target identity: native exception text names ParseFlashRegionsEvent.
// BFME 2 parser4E14E8/118 creates a16-byte local; ctor4E14CD and copy52BB9A
// independently witness vptrC619A0 and fields4/8/C. TableC619E0 and append
// thunk56655F come from the native call operands, not donor addresses.
// The original record class name is unknown. Its function-scope lifetime
// preserves VC7.1's separate8-byte exception and16-byte record EH slots.
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
};

class Rva003B7190Record
{
public:
	Rva003B7190Record() : m_delayFromActStart( 0 ), m_flag08( false ), m_flashTime( 0 ) {}
	virtual ~Rva003B7190Record() {}

private:
	Int m_delayFromActStart;
	bool m_flag08;
	Int m_flashTime;
};

// BFME 2's complete table at RVA 0x008619E0. Each callback and offset
// comes from the native table, independently of the donor's addresses.
extern const FieldParse FlashRegionsEventFieldParseTable[4] = {
    { "DelayFromActStart", INI::dup_002F0F7, 0, 4 },
    { "FlashTime", INI::dup_002F0F7, 0, 12 },
    { "SummaryEvent", INI::parseBool, 0, 8 },
    { 0, 0, 0, 0 }
};

struct Elem003AF9E0;

class Rva0056655FOwner
{
public:
	void rva0056655F(const Elem003AF9E0 &record);
};

// ?ParseFlashRegionsEvent@@YAXPAVINI@@PAX1PBX@Z
void ParseFlashRegionsEvent(INI *ini, void *instance, void *, const void *)
{
    if (!ini || !instance)
        throw INIException(3, "ParseFlashRegionsEvent::Invalid data passed in.");

    Rva003B7190Record record;
    ini->initFromINI(&record, FlashRegionsEventFieldParseTable);
    // The rowed 0x0056655F thunk has the native reference ABI. Its element
    // spelling is a callable view, not an assertion of this record's identity.
    static_cast<Rva0056655FOwner *>(instance)->rva0056655F(
        reinterpret_cast<const Elem003AF9E0 &>(record));
}
