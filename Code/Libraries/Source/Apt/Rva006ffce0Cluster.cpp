// cl: /MD /EHsc
// Address-derived recovery of 0x006FFCE0 (155B), an AptActionInterpreter string
// worker. Retail clears the EAStringC out parameter through the const char*
// ctor 0x006D4C80 (empty literal 0x00BBAC1C) and operator= 0x006D3030, calls
// the unrowed filler 0x006FF980 with (value, sBuf, 1), then asserts
// sBuf.Size() != 0 at AptActionInterpreter.cpp 0x6C1 using the accessor
// 0x006D3750. The SEH frame is the EAStringC temporary's destructor 0x006D3010.
// The handler and callee names are address-derived.

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

class AptValue;

void rva006ff980(AptValue *value, EAStringC &sBuf, int arg);

void rva006ffce0(AptValue *value, EAStringC &sBuf)
{
    {
        EAStringC tmp("");
        sBuf = tmp;
    }
    rva006ff980(value, sBuf, 1);
    if (!(sBuf.rva006D3750() != 0)) {
        g_bfmeAptAssertAtE17734("sBuf.Size() != 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x6C1);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
}
