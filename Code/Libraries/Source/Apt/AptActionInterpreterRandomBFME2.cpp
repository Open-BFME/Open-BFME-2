// cl: /O2 /MD
// ActionScript opcode 0x30 handler. Stack assertions, value calls, and RNG
// flow follow the retail body at 0x007020B0.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class BfmeAptValue006DCD20
{
public:
	virtual void AddRef();
	virtual void Release();
	bool isUndefined() const;
	int toInteger() const;
};

class AptInteger
{
public:
	static BfmeAptValue006DCD20 *Create(int nValue);
};

extern unsigned int bfmeNext1221();

class AptBasePtrStack
{
public:
	BfmeAptValue006DCD20 *At(int nPos)
	{
		if (!(m_nElements - nPos > 0)) {
			g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 266);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
		return m_aElements[m_nElements - nPos - 1];
	}
	void Push(BfmeAptValue006DCD20 *pValue);

	int m_nElements;
	int m_nCapacity;
	BfmeAptValue006DCD20 **m_aElements;
};

struct AptActionInterpreter
{
	static void _FunctionAptActionRandom(AptActionInterpreter *const pInterpreter);

	AptBasePtrStack stack;
};

void AptActionInterpreter::_FunctionAptActionRandom(AptActionInterpreter *const pInterpreter)
{
	BfmeAptValue006DCD20 *pValue = pInterpreter->stack.At(0);
	int nResult;
	if (pValue->isUndefined()) {
		nResult = 0;
	} else {
		int nMaximum = pValue->toInteger();
		nResult = bfmeNext1221() % nMaximum;
	}

	BfmeAptValue006DCD20 *pResult = AptInteger::Create(nResult);
	if (!(pInterpreter->stack.m_nElements > 0)) {
		g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping from Stack with 0 elements. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 152);
		// Retail places this breakpoint before setting up the shared Push call.
		if (g_bfmeAptBreakOnAssertAtDDC01C) __asm { int 3 }
	} else {
		BfmeAptValue006DCD20 *pOldValue = pInterpreter->stack.m_aElements[pInterpreter->stack.m_nElements - 1];
		pOldValue->Release();
		--pInterpreter->stack.m_nElements;
	}
	pInterpreter->stack.Push(pResult);
}
