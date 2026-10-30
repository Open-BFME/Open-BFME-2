// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/inputs/reference/shims/stringinline -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Map
// stlport

#include "ascii_string.h"

struct Rva0019B780Key
{
	AsciiString first;
	AsciiString second;
};

struct Rva0019B780Node
{
	unsigned char m_data[0x1c];
};

class Rva0019B780Tree
{
public:
	Rva0019B780Node *find( const Rva0019B780Key &key ) const throw();

private:
	unsigned char m_tree[12];
};

extern Rva0019B780Key __cdecl Rva00194810( const AsciiString &name );

struct Rva0019B780Entry
{
	unsigned char m_data[16];
};

class Rva0019C520Member
{
public:
	int lookup( AsciiString *name, int extra );

private:
	Rva0019B780Tree m_tree;
	Rva0019B780Entry *m_entries;
};

int Rva0019C520Member::lookup( AsciiString *name, int extra )
{
	AsciiString *input;
	input = name;
	Rva0019B780Node *found;
	{
		found = m_tree.find( Rva00194810( *input ) );
	}
	if (found == *(Rva0019B780Node **)&m_tree)
		return 0;
	int index = *(int *)((char *)found + 0x18);
	Rva0019B780Entry *entry = m_entries + index;
	if (extra)
		*(int *)extra = index;
	return (int)((char *)entry + 0x0c);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0032C07C reads ??$_M_find@U?$pair@VAsciiString@@V1@@_STL@@@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@UTeamLess0019B850@@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@1@ABU?$pair@VAsciiString@@V1@@1@@Z
#pragma comment(linker, "/alternatename:?find@Rva0019B780Tree@@QBEPAURva0019B780Node@@ABURva0019B780Key@@@Z=??$_M_find@U?$pair@VAsciiString@@V1@@_STL@@@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@UTeamLess0019B850@@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@H@_STL@@@1@ABU?$pair@VAsciiString@@V1@@1@@Z")
//   0x0032ABDA reads ?Rva00194810@@YA?AUBfmePairEL@@ABVBfmeWordEL@@@Z
#pragma comment(linker, "/alternatename:?Rva00194810@@YA?AURva0019B780Key@@ABVAsciiString@@@Z=?Rva00194810@@YA?AUBfmePairEL@@ABVBfmeWordEL@@@Z")
