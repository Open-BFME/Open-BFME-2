// cl: /O2 /MD
// ActionScript bitwise opcode handlers 0x60-0x64. Each is named by its slot in
// the {opcode, handler} dispatch table at 0x009DC960; names, parameters and
// locals follow the Apt debug info of The Sims 2: Castaway (CC0). Stack layout
// and the _AptBasePtrStack.h At() assertion (line 266) are read from retail.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

#define APT_BASE_PTR_STACK_ASSERT(expr) \
	if (!(expr)) { \
		g_bfmeAptAssertAtE17734(#expr, "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 266); \
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); \
	}

class BfmeAptValue006DCD20
{
public:
	bool isUndefined() const;
	int toInteger() const;
};

class AptInteger
{
public:
	static BfmeAptValue006DCD20 *Create(int nValue);
};

extern BfmeAptValue006DCD20 *gpUndefinedValue;
int Rva006CD220Get();

class AptBasePtrStack
{
public:
	BfmeAptValue006DCD20 *At(int nPos)
	{
		APT_BASE_PTR_STACK_ASSERT(m_nElements - nPos > 0);
		return m_aElements[m_nElements - nPos - 1];
	}
	void PopAndPush(int nItems, BfmeAptValue006DCD20 *element);

	int m_nElements;
	int m_nCapacity;
	BfmeAptValue006DCD20 **m_aElements;
};

struct AptActionInterpreter
{
	static void _FunctionAptActionBitAnd(AptActionInterpreter *const pInterpreter);
	static void _FunctionAptActionBitOr(AptActionInterpreter *const pInterpreter);
	static void _FunctionAptActionBitXor(AptActionInterpreter *const pInterpreter);
	static void _FunctionAptActionBitLShift(AptActionInterpreter *const pInterpreter);
	static void _FunctionAptActionBitRShift(AptActionInterpreter *const pInterpreter);

	AptBasePtrStack stack;
};

void AptActionInterpreter::_FunctionAptActionBitAnd(AptActionInterpreter *const pInterpreter)
{
	BfmeAptValue006DCD20 *pA = pInterpreter->stack.At(0);
	BfmeAptValue006DCD20 *pB = pInterpreter->stack.At(1);
	BfmeAptValue006DCD20 *pResult;
	if (!(Rva006CD220Get() == 7 && (pA->isUndefined() || pB->isUndefined())
		&& (pResult = gpUndefinedValue) != 0))
	{
		int nA = pA->toInteger();
		int nB = pB->toInteger();
		pResult = AptInteger::Create(nB & nA);
	}
	pInterpreter->stack.PopAndPush(2, pResult);
}

void AptActionInterpreter::_FunctionAptActionBitOr(AptActionInterpreter *const pInterpreter)
{
	BfmeAptValue006DCD20 *pA = pInterpreter->stack.At(0);
	BfmeAptValue006DCD20 *pB = pInterpreter->stack.At(1);
	BfmeAptValue006DCD20 *pResult;
	if (!(Rva006CD220Get() == 7 && (pA->isUndefined() || pB->isUndefined())
		&& (pResult = gpUndefinedValue) != 0))
	{
		int nA = pA->toInteger();
		int nB = pB->toInteger();
		pResult = AptInteger::Create(nB | nA);
	}
	pInterpreter->stack.PopAndPush(2, pResult);
}

void AptActionInterpreter::_FunctionAptActionBitXor(AptActionInterpreter *const pInterpreter)
{
	BfmeAptValue006DCD20 *pA = pInterpreter->stack.At(0);
	BfmeAptValue006DCD20 *pB = pInterpreter->stack.At(1);
	BfmeAptValue006DCD20 *pResult;
	if (!(Rva006CD220Get() == 7 && (pA->isUndefined() || pB->isUndefined())
		&& (pResult = gpUndefinedValue) != 0))
	{
		int nA = pA->toInteger();
		int nB = pB->toInteger();
		pResult = AptInteger::Create(nB ^ nA);
	}
	pInterpreter->stack.PopAndPush(2, pResult);
}

void AptActionInterpreter::_FunctionAptActionBitLShift(AptActionInterpreter *const pInterpreter)
{
	BfmeAptValue006DCD20 *pA = pInterpreter->stack.At(0);
	BfmeAptValue006DCD20 *pB = pInterpreter->stack.At(1);
	BfmeAptValue006DCD20 *pResult;
	if (!(Rva006CD220Get() == 7 && (pB->isUndefined() || pA->isUndefined())
		&& (pResult = gpUndefinedValue) != 0))
	{
		int nA = pA->toInteger();
		int nB = pB->toInteger();
		pResult = AptInteger::Create(nB << nA);
	}
	pInterpreter->stack.PopAndPush(2, pResult);
}

void AptActionInterpreter::_FunctionAptActionBitRShift(AptActionInterpreter *const pInterpreter)
{
	BfmeAptValue006DCD20 *pA = pInterpreter->stack.At(0);
	BfmeAptValue006DCD20 *pB = pInterpreter->stack.At(1);
	BfmeAptValue006DCD20 *pResult;
	if (!(Rva006CD220Get() == 7 && (pB->isUndefined() || pA->isUndefined())
		&& (pResult = gpUndefinedValue) != 0))
	{
		int nA = pA->toInteger();
		int nB = pB->toInteger();
		pResult = AptInteger::Create(nB >> nA);
	}
	pInterpreter->stack.PopAndPush(2, pResult);
}
