// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// stlport
// ?Rva0042700FParse@@YAXPAVINI@@HPAV?$vector@UBfmeStringRecord00426A5B@@V?$allocator@UBfmeStringRecord00426A5B@@@_STL@@@_STL@@H@Z @0x0042700F 89B
// retail 0x0042700F 89B: INI token loop filling vector<BfmeStringRecord00426A5B> via rowed getNextTokenOrNull 0x2DEED plus default ctor 0x4267CC plus StringBase::set 0x55F5 plus push_back 0x426EE0 plus releaseBuffer 0x36410; prev Rva00426F17Xfer shares flags; caller 0x427068 passes INI in +8 and vec in +0x10
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include "ascii_string.h"
#include "Common/Snapshot.h"

struct BfmeStringRecord00426A5B
{
	AsciiString text;
	unsigned char flag0;
	unsigned char flag1;
	unsigned char flag2;
	BfmeStringRecord00426A5B();
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
};

typedef _STL::vector<BfmeStringRecord00426A5B> BfmeVec00426A5B;

void Rva0042700FParse(INI *ini, int dummy1, BfmeVec00426A5B *vec, int dummy2)
{
	const char *token;
	while ((token = ini->getNextTokenOrNull(0)) != 0)
	{
		BfmeStringRecord00426A5B rec;
		rec.text.set(token);
		vec->push_back(rec);
	}
}

void Rva00427068Parse(INI *ini, int dummy1, BfmeVec00426A5B *vec, int dummy2)
{
	unsigned int oldCount = vec->size();
	Rva0042700FParse(ini, dummy1, vec, dummy2);
	for (unsigned int i = oldCount; i < vec->size(); ++i)
		(*vec)[i].flag0 = 1;
}

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool isLoading();
	virtual bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion &version);
};

Xfer *Rva00426F17Xfer(Xfer *xfer, BfmeVec00426A5B *vec);

class Rva00426EB0 : public Snapshot
{
public:
	virtual ~Rva00426EB0();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);
private:
	BfmeVec00426A5B m_vec;
};


void Rva00426EB0::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);
	if (xfer->isLoading())
	{
		m_vec.clear();
	}
	Rva00426F17Xfer(xfer, &m_vec);
}

