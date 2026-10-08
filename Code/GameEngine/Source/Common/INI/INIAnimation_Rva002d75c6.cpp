// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?Rva002D75C6@@YAXXZ, retail 0x002D75C6, 18 bytes.
// Target facts (retail bytes, relocations masked): push the parse callback
// 0x002D7554 (INI::parseAnim2DDefinition), push the "Animation2D" literal, call
// IniLoad 0x003397D8, pop the two cdecl arguments, ret. The return value of
// IniLoad is discarded. Nothing else reads or writes state at this address.
//
// Identity evidence: 0x002D75C6 is vftable 0x00C0331C slot 1 (VA 0x006D75C6)
// of the class constructed at 0x002D6C02. The name is address-based because
// no other evidence names it; the vtable slot is not a semantic identity.

class INI;
typedef void (*INIBlockParse)( INI *ini );

// inihelp.cpp: loads every INI file the legend lists under the name.
bool IniLoad( const char *name, INIBlockParse parse );

class INI
{
public:
	static void parseAnim2DDefinition( INI *ini );
};

void Rva002D75C6( void )
{
	IniLoad( "Animation2D", INI::parseAnim2DDefinition );
}
