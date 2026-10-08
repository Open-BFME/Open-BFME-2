// Trimmed from Open-BFME-1
// (Code/GameEngine/Source/Common/R2GuardedGlobalCalls.cpp): only the placed
// ?run@Rva007E8AC0 and ?Rva007B7600 bodies are defined here. The donor's
// other members (guarded tail dispatches Rva0007C530/Rva002EEA30/Rva002EEA50,
// the guarded this-dispatch Rva002D9AC0::run, field writes Rva00588E40::run
// and Rva0073A860/Rva0073B540/Rva00739D20 plus Rva00739C10::release) stay out
// of this TU so the unmatched-definition gate passes.

class Rva007E8AC0
{
public:
	char m_leadingA[0x10];
	char *m_at10;
	char m_leadingB[4];
	int m_at18;
	char m_leadingC[8];
	int m_at24;
	char m_leadingD[4];
	int m_at2C;
	void run();
};

void Rva007E8AC0::run()
{
	*m_at10 = 0;
	m_at18 = 0;
	m_at24 = 0;
	m_at2C = 4;
}

// Guarded tail dispatch through a global receiver (the donor's fourth (A)
// member): the global holds the receiver directly and its vptr is at offset
// 0, so only the two leading virtual slots need declaring for slot004.
class R2GlobalReceiver
{
public:
	virtual void slot000();
	virtual void slot004();
};

extern class Rva00108660ResourceManager *Rva00DEC2D8Manager;

void Rva007B7600()
{
	if ((*(R2GlobalReceiver **)&Rva00DEC2D8Manager))
		(*(R2GlobalReceiver **)&Rva00DEC2D8Manager)->slot004();
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeBegin@BfmeSetupRecord@@QAEXXZ=?run@Rva007E8AC0@@QAEXXZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeRunVJA@BfmeMsgVJA@@QAEXXZ=?run@Rva007E8AC0@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeRunVJC@BfmeMsgVJC@@QAEXXZ=?run@Rva007E8AC0@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeRunVIR@BfmeMsgVIR@@QAEXXZ=?run@Rva007E8AC0@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeRunVJF@BfmeMsgVJF@@QAEXXZ=?run@Rva007E8AC0@@QAEXXZ")
