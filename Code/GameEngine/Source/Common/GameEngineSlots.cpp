// cl: /DNDEBUG /MD /EHsc
//
// Three of GameEngine's own virtuals (vtable 0x00BE7188, also reached
// through Win32GameEngine's 0x00BC2530 at the same slots):
//
//   slot 16  0x00225AD5  rva00225AD5          unnamed Bool query
//   slot 17  0x00225AFF  rva00225AFF          unnamed Bool query
//   slot 22  0x00225F76  isMultiplayerSession Zero Hour's body:
//                        `return TheRecorder->isMultiplayer();`
//
// Slots 16 and 17 both answer false while TheWritableGlobalData exists with
// its byte at +0x11C9 clear, and otherwise ask the list at 0x00DFD940 (the
// ledger's TheSubsystemList) through methods whose identities are not
// recovered; slot 17 also asks TheGameLogic (0x0024877A) and always calls
// 0x001B4FE9 on the list before answering. Their Zero Hour counterparts are
// not identified.

typedef bool Bool;

#include "../../Include/Common/GlobalData.h"

class Rva001B5140 { public: Bool rva001B5140(); };
class SubsystemInterfaceList
{
public:
	// Returns a byte its caller normalises to Bool (test al, al; setne al).
	unsigned char rva001B505F();/* the rowed Rva001B5140::rva001B5140 */ __declspec(dllimport) __forceinline Bool rva001B5140() { return ((Rva001B5140 *)this)->rva001B5140(); }
	void rva001B4FE9();
};

#include "GameLogicObjectLookupView.h"

class RecorderClass
{
public:
	Bool isMultiplayer();						///< matched 0x0037B18C
};

extern GlobalData *TheWritableGlobalData;
extern SubsystemInterfaceList *TheSubsystemList;
extern GameLogic *TheGameLogic;
class RecorderClass; extern RecorderClass *TheRecorder;

#include "../../Include/Common/GameEngine.h"

Bool GameEngine::rva00225AD5()
{
	if (TheWritableGlobalData == 0 || TheWritableGlobalData->field11C9 != 0)
	{
		if (TheSubsystemList == 0)
			return false;
		return TheSubsystemList->rva001B505F();
	}
	return false;
}

Bool GameEngine::rva00225AFF()
{
	if (TheWritableGlobalData && !TheWritableGlobalData->field11C9)
		return false;
	if (!TheSubsystemList)
		return false;
	Bool result = false;
	if (TheSubsystemList->rva001B5140() || TheGameLogic->rva0024877A())
		result = true;
	TheSubsystemList->rva001B4FE9();
	return result;
}

Bool GameEngine::isMultiplayerSession()
{
	return TheRecorder->isMultiplayer();
}
