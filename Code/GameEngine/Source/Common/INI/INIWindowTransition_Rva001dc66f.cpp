// ?parseWindowTransitions@INI@@SAXPAV1@@Z, retail 0x001DC66F, 112 bytes.
// Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/INI/INIWindowTransition.cpp
// (reference/open-bfme-1). The donor body does not place at BFME 1's flags;
// compiled /Os it is byte-identical to retail once relocations are masked
// (unique hit on unclaimed .text). Only the placed body is defined here.
//
// The WindowTransition block. Reads the group name, asks the transition handler
// for a new group, and parses into it. TheTransitionHandler at 0x00DFDC14 is
// the same singleton GameWindowManager::reset and ::update call, both of which
// are byte-matched, so the receiver is not in doubt.
//
// getNewGroup is Zero Hour's declared signature --
// TransitionGroup *getNewGroup( AsciiString name ) -- and retail's call shape
// confirms it: the receiver is loaded into ECX and the name is copied into an
// argument slot by value, and the returned pointer is what initFromINI writes
// into. Retail calls the body at 0x001DC4D2 directly (not through an ILT thunk,
// as the donor assumed), and that body reuses the ledgered
// ?findGroup@GameWindowTransitionsHandler at 0x001DC01C before allocating a
// 0x14-byte group and inserting it into the +0x20 group list.
//
// Two adaptations to the donor, both from target evidence:
//  - retail calls the getNewGroup body at 0x001DC4D2 directly, so the member
//    pointer pun names that body rather than the ILT thunk at 0x000480C7 the
//    donor assumed;
//  - retail builds the name with StringBase<char>::set at 0x000055F5 (as the
//    sibling INI parsers do), not with AsciiString's assignment operator.
// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/ini -Ireference/open-bfme-1/inputs/reference/shims/iniexception -Ireference/open-bfme-1/inputs/reference/shims/ini_noinline -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/INI
// stlport
#include "PreRTS.h"
#include "Common/INI.h"

class TransitionGroup;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	TransitionGroup *getNewGroup( AsciiString name );
	static const FieldParse m_gameWindowTransitionsFieldParseTable[];
};

// __thiscall is not available in this compilation, so the callee is
// reinterpreted as a member-function pointer through the same union pun the
// Miles TUs use (SampleStarter006B4090.cpp) and BfmeConv1850.cpp; MSVC folds
// it back into a direct thiscall, which is retail's "receiver in ECX, name on
// the stack" shape. Retail calls the getNewGroup body at 0x001DC4D2 directly,
// so the pun names that body rather than the ILT thunk the donor assumed.
template <class M> inline M bfmeMemberOf(void (*fn)()) { union { void (*f)(); M m; } u; u.f = fn; return u.m; }
typedef TransitionGroup *(GameWindowTransitionsHandler::*GetNewGroup)(AsciiString name);

extern void getNewGroup_body_001dc4d2();

extern GameWindowTransitionsHandler *TheTransitionHandler;

void INI::parseWindowTransitions( INI* ini )
{
	AsciiString name;
	name.set( ini->getNextToken() );

	if( TheTransitionHandler )
	{
		TransitionGroup *group = (TheTransitionHandler->*bfmeMemberOf<GetNewGroup>(getNewGroup_body_001dc4d2))( name );
		ini->initFromINI( group, GameWindowTransitionsHandler::m_gameWindowTransitionsFieldParseTable );
	}
}
