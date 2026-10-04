// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva005794ED@@UAE@XZ @0x005794ED 85B: virtual dtor with AsciiString at +8 plus Rva0052413E at +0xC plus TargetRef at +0x18.
// Evidence: deleting-dtor callers 0x0042D4EB 0x0042D7A3 0x0042D7C6 plus rowed Release 0x0007DEEF plus rowed 0x0052413E plus rowed releaseBuffer 0x00036410 plus vtables 0x00C6ECBC 0x00C6EE28; prev Rva004FAC6BCtor.
#include "ascii_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[0xC];
};

extern const void *const g_00C6ECBC[];
extern const void *const g_00C6EE28[];

class Rva005794EDBase
{
public:
	virtual ~Rva005794EDBase();
};

// ??1Rva005794EDBase@@UAE@XZ present-unmatched
inline Rva005794EDBase::~Rva005794EDBase()
{
	*(const void **)this = g_00C6EE28;
}

struct Rva005794EDHolder18
{
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva005794EDHolder18() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class __declspec(novtable) Rva005794ED : public Rva005794EDBase
{
public:
	virtual ~Rva005794ED();
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	Rva005794EDHolder18 m_18;
};

Rva005794ED::~Rva005794ED()
{
	*(const void **)this = g_00C6ECBC;
}
