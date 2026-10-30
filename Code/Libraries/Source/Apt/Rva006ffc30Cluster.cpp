// cl: /MD /EHsc
// Address-derived recovery of 0x006FFC30 (174B), an AptActionInterpreter string
// worker sibling of the recovered 0x006FFCE0. Retail clears the EAStringC out
// parameter through the const char* ctor 0x006D4C80 (empty literal 0x00BBAC1C)
// and operator= 0x006D3030, calls the unrowed filler 0x006FF980 with
// (value, sBuf, 0), and when the resulting string is empty assigns the default
// literal "/" at 0x00BD60D0. The SEH frame is the EAStringC temporary
// destructor 0x006D3010; because this body holds a second temporary slot the
// prolog reserves 8 bytes (sub esp,8) instead of the sibling's single push ecx,
// and the second block's EH state is 1 rather than 0. The handler and callee
// names are address-derived; the "/" default string address is read from the
// retail DIR32 immediate.

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

void rva006ffc30(AptValue *value, EAStringC &sBuf)
{
    {
        EAStringC tmp("");
        sBuf = tmp;
    }
    rva006ff980(value, sBuf, 0);
    if (sBuf.rva006D3750() == 0) {
        EAStringC tmp2("/");
        sBuf = tmp2;
    }
}
