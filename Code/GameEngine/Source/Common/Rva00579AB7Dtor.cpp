// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva00579AB7@@UAE@XZ @0x00579AB7 96B: virtual dtor with AsciiString at +8 plus Rva0052413E at +0xC plus TargetRef at +0x1C plus rva005796B3 clear.
// Evidence: deleting-dtor callers 0x0042D507 0x0042D7E0 0x0042D803 plus rowed rva005796B3 0x005796B3 plus rowed Release 0x0007DEEF plus rowed 0x0052413E plus rowed releaseBuffer 0x00036410 plus vtables 0x00C6ED64 0x00BFBC9C; sibling Rva005794EDDtor.
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

class Rva005796B3
{
public:
	void rva005796B3(void *newObj);
};

extern const void *const g_00BFBC9C[];

class Rva00579AB7Base
{
public:
	virtual ~Rva00579AB7Base();
};

// ??1Rva00579AB7Base@@UAE@XZ present-unmatched
inline Rva00579AB7Base::~Rva00579AB7Base()
{
	*(const void **)this = g_00BFBC9C;
}

struct Rva00579AB7Holder1C
{
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva00579AB7Holder1C() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class Rva00579AB7 : public Rva00579AB7Base
{
public:
	virtual ~Rva00579AB7();
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	int m_18;
	Rva00579AB7Holder1C m_1C;
};

Rva00579AB7::~Rva00579AB7()
{
	((Rva005796B3 *)this)->rva005796B3(0);
}
