// cl: /O1 /DNDEBUG /MD /EHsc
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

class GlobalData
{
public:
	unsigned char m_unmodelled_0000[0x11C9];
	Bool m_bfmeFlag11C9;						// +0x11C9, unnamed
};

class SubsystemInterfaceList
{
public:
	// Returns a byte its caller normalises to Bool (test al, al; setne al).
	unsigned char rva001B505F();
	Bool rva001B5140();
	void rva001B4FE9();
};

class GameLogic
{
public:
	Bool rva0024877A();
};

class RecorderClass
{
public:
	Bool isMultiplayer();						///< matched 0x0037B18C
};

extern GlobalData *TheWritableGlobalData;
extern SubsystemInterfaceList *TheSubsystemList;
extern GameLogic *TheGameLogic;
extern RecorderClass *TheRecorder;

class GameEngine
{
public:
	virtual Bool rva00225AD5();
	virtual Bool rva00225AFF();
	virtual Bool isMultiplayerSession();
};

Bool GameEngine::rva00225AD5()
{
	if (TheWritableGlobalData == 0 || TheWritableGlobalData->m_bfmeFlag11C9 != 0)
	{
		if (TheSubsystemList == 0)
			return false;
		return TheSubsystemList->rva001B505F();
	}
	return false;
}

Bool GameEngine::rva00225AFF()
{
	if (TheWritableGlobalData && !TheWritableGlobalData->m_bfmeFlag11C9)
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
