// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI

//
// ?createAptScreenObjectives@@YGPAXPAX@Z
// retail 0x002D1EC9, 58 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/GUI/AptScreenFactories.cpp
// (reference/open-bfme-1). The donor body is byte-identical to retail once
// relocations are masked (unique masked placement on unclaimed .text, donor
// recompiled /Os). Only the placed body is defined here; the donor's other 42
// definitions are omitted.
//
// Objectives.apt and PlayerStatus.apt share this one factory. The body is the
// same three lines as every other screen factory: allocate the fixed-size
// object, hand the argument to its constructor, return the pointer or null if
// the allocation failed. It touches no member, so only the object's size
// matters and no layout is invented. The constructor is called out-of-line, so
// only its retail address matters; it is pinned in reverse/symbols.csv at
// 0x00513558.

#include "../../../Include/GameClient/BfmeAptScreenBaseLayout.h"

// stlport
#include <vector>

class AsciiString;
typedef int GameWindow;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/BfmeAptScreenBaseLayout.h
class Rva0050F8B0FunctorHolder;
class Rva0050F920FunctorHolder;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/BfmeAptScreenBaseLayout.h
class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow( void *context );
	virtual ~_bfme_AptGameWindow();
	void _bfme_showAptScreen( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );
	void _bfme_showAptScreenWithArg( const AsciiString &name, void *argument,
		Rva0050F920FunctorHolder callback );

private:
	char m_unmodelled[ 0x254 ];
};

// The two vftables are written by the constructor, not by this factory; they
// are declared only so the class declaration matches the donor.
extern const void *BfmeAptScreenObjectivesVftable[];
extern const void *BfmeAptScreenObjectivesSecondaryVftable[];

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/BfmeAptScreenBaseLayout.h
class BfmeAptFunctorMarker {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/BfmeAptScreenBaseLayout.h
class BfmeAptScreenObjectivesVtableBase : public BfmeAptFunctorMarker
{
public:
	__forceinline BfmeAptScreenObjectivesVtableBase( void *owner )
	{
		*(const void * volatile *)owner =
			BfmeAptScreenObjectivesVftable;
		*(const void **)( (char *)owner + 0x218 ) =
			BfmeAptScreenObjectivesSecondaryVftable;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/BfmeAptScreenBaseLayout.h
class __declspec(novtable) __multiple_inheritance BfmeAptScreenObjectives
	: public _bfme_AptGameWindow, public BfmeAptScreenObjectivesVtableBase
{
public:
	BfmeAptScreenObjectives( void *context );

private:
	_STL::vector<int> m_players;
	int m_screenType;
	GameWindow *m_playerControls[ 8 ];
	signed char m_playerSlots[ 8 ];
};

// ?createAptScreenObjectives@@YGPAXPAX@Z
void * __stdcall createAptScreenObjectives( void *context )
{
	return new BfmeAptScreenObjectives( context );
}
