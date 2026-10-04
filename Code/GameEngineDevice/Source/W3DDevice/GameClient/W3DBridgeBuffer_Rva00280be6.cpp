// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -DWIN32 -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Os -Ireference/open-bfme-1/game/GameEngineDevice/Source/W3DDevice/GameClient
// stlport
//
// ?getTowerObjectName@TerrainRoadType@@QAE?AVAsciiString@@W4BridgeTowerType@@@Z
// retail 0x00280BE6, 31 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp
// (reference/open-bfme-1 @ 6d943426). Compiled /Os the donor emits this body
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here; the donor's other
// definitions are omitted.
//
// Retail's shape: the hidden return pointer arrives at [ebp+8], the tower type
// at [ebp+0xC], the names sit at this+0x54 indexed by type (four bytes each),
// and the callee-clean `ret 8` pops the type -- a thiscall returning AsciiString
// by value, whose one callee 0x000365F0 is already rowed as the narrow
// StringBase copy-set. The same hidden-result copy at this+0x54+4*index is
// recorded independently by BridgeObjectCtor.cpp's own ILT note.

// BFME2's shared AsciiString (reference/shims/bfme2_ascii/ascii_string.h).
// Retail's copy callee 0x000365F0 is the narrow StringBase copy-set this
// header's own copy constructor compiles to.
#include "ascii_string.h"

// Retail's row names the tower type as a scoped enumeration (W4), not the
// unscoped struct MSVC would otherwise mangle as U.
enum BridgeTowerType
{
	BRIDGE_TOWER_FROM_LEFT = 0,
	BRIDGE_TOWER_TO_LEFT = 1,
	BRIDGE_TOWER_FROM_RIGHT = 2,
	BRIDGE_TOWER_TO_RIGHT = 3
};

// The rowed narrow StringBase copy-set, at this+0x54 indexed by tower type
	// (four bytes per entry) and with its own slot kept at the front of the
	// class so the entry address is this + entry*4.
struct Rva00280BE6TowerNameTable
{
	AsciiString m_slot0;
};

class TerrainRoadType
{
public:
	AsciiString getTowerObjectName(BridgeTowerType type);

protected:
	char m_pad00[0x54];
	Rva00280BE6TowerNameTable m_towerObjectNames;
};

class Rva00280BE6Names : public TerrainRoadType
{
public:
	// The rowed narrow StringBase copy-set. Retail's `lea eax,[ecx+eax*4+0x54]`
	// gives the table its own first entry at this+0x54 and walks it by entry
	// size, which is the AsciiString pointer the copy reads.
	Rva00280BE6TowerNameTable &entry(int index)
	{
		return *(Rva00280BE6TowerNameTable *)((char *)&m_towerObjectNames + 4 * index);
	}
};

// Nothing else in this unit constructs one, so a scope-exit handler is what
// keeps the destructor from being discarded as unused. Not retail data.
void Rva00280BE6Scope()
{
	TerrainRoadType *road = 0;
}

AsciiString TerrainRoadType::getTowerObjectName(BridgeTowerType type)
{
	return ((Rva00280BE6Names *)this)->entry(type).m_slot0;
}