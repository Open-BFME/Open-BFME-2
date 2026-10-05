// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG
// Native Ghidra [0x003F348F,0x003F34DD),78B. FieldParse entry at
// VA0x00C36650 pairs "Connection" with this callback and store offset0x60.
// It constructs the rowed24B LivingWorldRegionConnection view; native constructor
// 36B and destructor69B independently establish its vptr and consumed fields.
// Only constructor/destructor ABI and size are needed here; the declarations
// do not assert the base class or unconsumed virtual method identities.
// Connection name follows existing verified provider identities. Parser name is
// descriptive/address-derived; no original owning class asserted.
// Native48B subtable C36FD4 is Region/AsciiString at+4 and DetourPoint/Coord2D
// vector parser at+12, followed by a null FieldParse. This definition also makes
// the table's dependencies explicit to the linker.
// Clean BFME1 LivingWorldRegionParseConnections.cpp@6583b3c1 is a different
// string-list ConnectsTo callback; compile/placement found no matching bodies.
#include "ascii_string.h"
class INI;typedef void(*Parser)(INI*,void*,void*,const void*);
struct FieldParse {const char*name;Parser parse;const void*data;unsigned offset;};
class INI {public:void initFromINI(void*,const FieldParse*);
 static void parseAsciiString(INI*,void*,void*,const void*);
 static void Rva002F592_ParseArmyPlacementPos(INI*,void*,void*,const void*);
};
class LivingWorldRegionConnection {public:
 LivingWorldRegionConnection();virtual ~LivingWorldRegionConnection();
 private:unsigned char nativeFields[20];
};
class Rva003F309AVector {public:void append(const LivingWorldRegionConnection&);};
extern const FieldParse g_Va00C36FD4[];
const FieldParse g_Va00C36FD4[]={
 {"Region",INI::parseAsciiString,0,4},
 {"DetourPoint",INI::Rva002F592_ParseArmyPlacementPos,0,12},
 {0,0,0,0}};
void parseConnectionRva003F348F(INI*ini,void*,void*store,const void*) {
 LivingWorldRegionConnection connection;
 ini->initFromINI(&connection,g_Va00C36FD4);
 reinterpret_cast<Rva003F309AVector*>(store)->append(connection);
}

#pragma comment(linker, "/alternatename:?append@Rva003F309AVector@@QAEXABVLivingWorldRegionConnection@@@Z=?push_back@?$vector@VLivingWorldRegionConnection@@V?$allocator@VLivingWorldRegionConnection@@@_STL@@@_STL@@QAEXABVLivingWorldRegionConnection@@@Z")
