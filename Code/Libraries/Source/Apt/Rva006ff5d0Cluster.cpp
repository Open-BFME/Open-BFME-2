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

class EAStringC
{
public:
	class StringDataC { public: unsigned short m_uRefCount; unsigned short m_uSize; unsigned short m_uMaxSize; unsigned short m_uHash; };
	EAStringC();
	EAStringC(const char *value);
	~EAStringC();
	EAStringC &operator=(const EAStringC &);
	bool IsEmpty() const;
	bool rva006D3510(const char *) const;
	const char *rva00620090() const; // 0x00620090
	EAStringC(const EAStringC &);
	EAStringC &Rva006D4F00Append(const EAStringC &);
	EAStringC &Rva006D50A0Append(const char *);
	void __cdecl rva006D62C0(const char *, ...);
	EAStringC &clear();
	unsigned int rva006D3750() const;
	void rva006D3470();
	EAStringC &TrimRight(const char *);
	EAStringC(unsigned int,unsigned int);
	EAStringC rva006D5ED0(int) const;
	EAStringC rva006d5f30(int,int) const;
	int Find(char,int=0);
	EAStringC &Append(const char *const,unsigned int);
	bool IsEqualTo(const EAStringC *) const;
	bool rva006D3560(const EAStringC *) const;
	int rva006d6070(const char *,int=0);
	int GetAt(int) const;
	int rva006D54B0(int,int);
private:
	StringDataC *mpData; // +0x00
};
void rva006FD4C0(EAStringC *);
class AptValue { public: void toString(EAStringC &) const; };
class BfmeAptValue006DCD20 { public: int isString() const; };
class AptString { public: virtual void v0(); int flags; EAStringC str; static AptString *Create(); };
void rva006FD630(EAStringC *);
class AptBoolean
{
public:
	static AptValue *Create(bool value);
};
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
        return AptBoolean::Create(true);
    return AptBoolean::Create(rva006fc370(g_aptDateInterpreter.stack.At(0)));
}

// Retail 0x006FF660: string-result argument callback; decoder identity
// comes from the rowed percent-unescape transform at 0x006FD630.
// The native callback table/address push in AptValueInitialize owns this
// entry; stack.At(0) is unconditional even for nParams == 0.
AptValue *callback006FF660(AptValue *, int nParams)
{
    if (!(nParams <= 1)) {
        g_bfmeAptAssertAtE17734("nParams <= 1", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x58F);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    AptString *result = AptString::Create();
    AptValue *value = g_aptDateInterpreter.stack.At(0);
    if ((unsigned char)((BfmeAptValue006DCD20 *)value)->isString()) {
        EAStringC temp;
        value->toString(temp);
        rva006FD630(&temp);
        result->str = temp;
    }
    return (AptValue *)result;
}

// Retail 0x006FF750 (241B, RET): string-result argument callback, the
// appending sibling of 0x006FF660. Native initializer 0x006DF470 pushes this
// entry into the AptNativeFunction constructor 0x006D6500. It asserts
// nParams <= 1 (AptActionInterpreter.cpp 0x5A7), creates the result string,
// and returns it unchanged when there is no argument; otherwise a string
// argument passes through the rowed transform 0x006FD4C0 and is appended
// (rowed 0x006D4F00). The early return is what puts retail's nParams test
// ahead of the result copy after the Create call.
AptValue *callback006FF750(AptValue *, int nParams)
{
    if (!(nParams <= 1)) {
        g_bfmeAptAssertAtE17734("nParams <= 1", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x5A7);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    AptString *result = AptString::Create();
    if (!nParams)
        return (AptValue *)result;
    AptValue *value = g_aptDateInterpreter.stack.At(0);
    if ((unsigned char)((BfmeAptValue006DCD20 *)value)->isString()) {
        EAStringC temp;
        value->toString(temp);
        rva006FD4C0(&temp);
        result->str.Rva006D4F00Append(temp);
    }
    return (AptValue *)result;
}
