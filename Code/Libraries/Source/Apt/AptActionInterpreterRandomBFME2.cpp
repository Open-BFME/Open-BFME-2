// cl: /MD
// ActionScript opcode 0x30 handler. Stack assertions, value calls, and RNG
// flow follow the retail body at 0x007020B0.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class EAStringC;
class BfmeAptValue006DCD20
{
public:
	int rva006E02B0() const; // rowed provider at 0x006E02B0; callers test AL
	int isNativeFunction() const;
	bool rva006DCA60() const;
	int isObject() const;
	int isInteger() const;
	int isFloat() const;
	int isString() const;
	int toInteger() const;
	float rva006DD460();
	BfmeAptValue006DCD20 *rva006DCF60(bool);
	BfmeAptValue006DCD20 *checkedString();
	int isScriptFunction() const;
	bool isUndefined() const;
	int rva006E03A0() const;
	BfmeAptValue006DCD20 *rva006DCF20();
	BfmeAptValue006DCD20 *rva006DCEE0();
	void rva006DD6C0(EAStringC *out);
	// These call-site views follow the retail test-al instruction at 0x6FED89
	// and 0x6FEF02; the matched predicate declarations keep their own names.
	int rva006E0260() const;
	int rva006DCC60(bool) const;
	void *rva006E04A0() const;
	virtual void AddRef();
	virtual void Release();
};

class AptValue;

class AptInteger
{
public:
	static AptValue *Create(int nValue);
};

extern unsigned int bfmeNext1221();

class AptBasePtrStack
{
public:
	AptValue *At(int nPos)
	{
		if (!(count - nPos > 0)) {
			g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 266);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
		return items[count - nPos - 1];
	}
	void Push(BfmeAptValue006DCD20 *pValue);

	int count;
	int capacity;
	AptValue **items;
};

struct AptActionInterpreter
{
	static void _FunctionAptActionRandom(AptActionInterpreter *const pInterpreter);

	AptBasePtrStack stack;
};

void AptActionInterpreter::_FunctionAptActionRandom(AptActionInterpreter *const pInterpreter)
{
	BfmeAptValue006DCD20 *pValue = (BfmeAptValue006DCD20 *)pInterpreter->stack.At(0);
	int nResult;
	if (pValue->isUndefined()) {
		nResult = 0;
	} else {
		int nMaximum = pValue->toInteger();
		nResult = bfmeNext1221() % nMaximum;
	}

	BfmeAptValue006DCD20 *pResult = (BfmeAptValue006DCD20 *)AptInteger::Create(nResult);
	if (!(pInterpreter->stack.count > 0)) {
		g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping from Stack with 0 elements. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 152);
		// Retail places this breakpoint before setting up the shared Push call.
		if (g_bfmeAptBreakOnAssertAtDDC01C) __asm { int 3 }
	} else {
		BfmeAptValue006DCD20 *pOldValue = (BfmeAptValue006DCD20 *)pInterpreter->stack.items[pInterpreter->stack.count - 1];
		pOldValue->Release();
		--pInterpreter->stack.count;
	}
	pInterpreter->stack.Push(pResult);
}
