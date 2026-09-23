// cl: /O2 /MD
// Ghidra body at 0x006FE6E0: checked stack append, slot write, count increment,
// and first virtual call. Layout and checks are read from BFME2 retail.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class BfmeAptValue006DCD20
{
public:
    virtual void AddRef();
    int isLookup() const;
    int isRegister() const;
};

class AptBasePtrStack
{
public:
    void Push(BfmeAptValue006DCD20 *pValue);

    int m_nElements;
    int m_nCapacity;
    BfmeAptValue006DCD20 **m_aElements;
};

void AptBasePtrStack::Push(BfmeAptValue006DCD20 *pValue)
{
    if (!pValue) {
        g_bfmeAptAssertAtE17734("pValue", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptActionInterpreter.inl", 133);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (static_cast<unsigned char>(pValue->isLookup())) {
        g_bfmeAptAssertAtE17734("pValue->isLookup() == false", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptActionInterpreter.inl", 134);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (static_cast<unsigned char>(pValue->isRegister())) {
        g_bfmeAptAssertAtE17734("pValue->isRegister() == false", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptActionInterpreter.inl", 135);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (m_nElements >= m_nCapacity) {
        g_bfmeAptAssertAtE17734("m_nElements < m_nCapacity", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 128);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    m_aElements[m_nElements] = pValue;
    ++m_nElements;
    pValue->AddRef();
}
