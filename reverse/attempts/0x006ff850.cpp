// ?rva006ff850@@YAPAVAptValue@@PAUAptActionInterpreter@@H@Z
// partial score=0.8 date=2026-10-06
// cl: /O2 /MD
// Target calls and caller family identify this as an address-derived
// AptActionInterpreter argument handler. Ghidra extent: 0x006FF850..0x006FF97D.

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

class BfmeAptValue006DCD20
{
public:
    BfmeAptValue006DCD20 *rva006DCEA0();
    float rva006DD460();
};

class AptValue
{
public:
    bool isCIH(bool bUndefOK) const;
    bool isObject() const;
    bool isFloat() const;
    bool isInteger() const;
    bool isBoolean() const;
};

class AptBoolean
{
public:
    bool GetBool() const;
};

#pragma comment(linker, "/alternatename:?GetBool@AptBoolean@@QBE_NXZ=?get@Rva006D89D0ByteField@@QBEEXZ")

class Rva006D89D0ByteField
{
public:
    unsigned char get() const;
};

extern AptValue *gpUndefinedValue;
#pragma comment(linker, "/alternatename:?gpUndefinedValue@@3PAVAptValue@@A=?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A")

// Retail uses the shared stack and assert layouts above. The source name
// remains address-derived.
AptValue *rva006ff850(AptActionInterpreter *pInterpreter, int nParams)
{
    if (!(nParams <= 1)) {
        g_bfmeAptAssertAtE17734("nParams <= 1", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x5C1);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (nParams == 0)
        return gpUndefinedValue;

    AptValue *value = g_aptDateInterpreter.stack.At(0);
    BfmeAptValue006DCD20 *typed = (BfmeAptValue006DCD20 *)value;
    if (value->isCIH(false) || value->isObject())
        return Rva006D88C0MakeBool(true);
    if (value == gpUndefinedValue)
        return Rva006D88C0MakeBool(false);

    if (value->isFloat() || value->isInteger()) {
        if (value->isBoolean())
            return Rva006D88C0MakeBool(
                ((AptBoolean *)typed->rva006DCEA0())->GetBool());
        if (value->isFloat() || value->isInteger())
            return Rva006D88C0MakeBool(typed->rva006DD460() != 0.0f);
        return Rva006D88C0MakeBool(false);
    }

    if (rva006fc370(value))
        return Rva006D88C0MakeBool(false);
    return Rva006D88C0MakeBool(typed->rva006DD460() != 0.0f);
}
