// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva005D25F2@@UAE@XZ @0x005D25F2 91B: virtual dtor, derived vtable 0x00875800 then base 0x008078DC.
// Evidence: array ??_M at +0x1C count 6 stride 0x1C via unclaimed 0x005D258E, rowed 0x0052413E at +0xC,
// rowed releaseBuffer 0x00036410 at +0x8, layout matches sibling Rva005D2664 header 0x1C + 6x0x1C,
// precedents Rva005794EDDtor Rva00579AB7Dtor Rva005FFBCBDtor, callers 0x00578532 0x0057866D 0x00578690.
#include "ascii_string.h"

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[0x0C];
};

struct Elem005D25F2
{
	char m_pad[0x1C];
	~Elem005D25F2();
};

// ??1Elem005D25F2@@QAE@XZ present-unmatched
Elem005D25F2::~Elem005D25F2()
{
}

extern const void *const g_00C75800[];
extern const void *const g_00C078DC[];

class Rva005D25F2Base
{
public:
	virtual ~Rva005D25F2Base();
};

// ??1Rva005D25F2Base@@UAE@XZ present-unmatched
inline Rva005D25F2Base::~Rva005D25F2Base()
{
	*(const void **)this = g_00C078DC;
}

class Rva005D25F2 : public Rva005D25F2Base
{
public:
	virtual ~Rva005D25F2();
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0C;
	int m_18;
	Elem005D25F2 m_1C[6];
};

Rva005D25F2::~Rva005D25F2()
{
}
