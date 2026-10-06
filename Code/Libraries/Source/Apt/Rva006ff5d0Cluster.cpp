// cl: /MD
// Address-derived recovery of 0x006FF5D0 (134B), an AptActionInterpreter
// argument handler. Retail asserts nParams <= 1 at AptActionInterpreter.cpp
// 0x57E, then returns MakeBool(true) for nParams == 0 and
// MakeBool(predicate(stack.At(0))) otherwise. The At() assertion
// (m_nElements - nPos > 0, _AptBasePtrStack.h 266) and shared assert triple
// match the recovered AptActionInterpreter handlers. MakeBool is the rowed pin
// 0x006D88C0; the predicate 0x006FC370 is unrowed and address-derived.
// The first argument is unused by the target body; the handler name is
// address-derived.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptValue;

AptValue *Rva006D88C0MakeBool(bool value);
bool rva006fc370(AptValue *value);

class AptBasePtrStack
{
public:
    AptValue *At(int nPos)
    {
        if (!(m_nElements - nPos > 0)) {
            g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 266);
            if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
        }
        return m_aElements[m_nElements - nPos - 1];
    }

    int m_nElements;
    int m_nCapacity;
    AptValue **m_aElements;
};

struct AptActionInterpreter
{
    AptBasePtrStack stack;
};

extern AptActionInterpreter g_aptDateInterpreter;

AptValue *rva006ff5d0(AptActionInterpreter *pInterpreter, int nParams)
{
    if (!(nParams <= 1)) {
        g_bfmeAptAssertAtE17734("nParams <= 1", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x57E);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (nParams == 0)
        return Rva006D88C0MakeBool(true);
    return Rva006D88C0MakeBool(rva006fc370(g_aptDateInterpreter.stack.At(0)));
}
