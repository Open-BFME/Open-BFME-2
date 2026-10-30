// cl: /EHsc /MD /Ireference/shims/bfme2_ascii
//
// ??1Rva003F7EC7@@UAE@XZ retail 0x003F7EC7 105 bytes. Virtual dtor with EH
// storing derived then base vtables destroying pointer at +0x14 via slot0
// virtual plus operator delete AsciiString at +0x10 via releaseBuffer and
// ref at +0x08 via Release_Ref. Evidence is caller 0x003F845C deleting dtor
// plus rowed callees plus neighbour dtor flags.

#include <new>

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"



class DeleteInner
{
public:
	virtual void *Delete(int flags) = 0;
};

class Holder08
{
public:
	~Holder08() { if (m_ptr != 0) m_ptr->Release_Ref(); }
	OpaqueRefCounted *m_ptr;
};

class Holder14
{
public:
	~Holder14()
	{
		void *toDelete = m_ptr != 0 ? m_ptr->Delete(0) : 0;
		::operator delete(toDelete);
		m_ptr = 0;
	}
	DeleteInner *m_ptr;
};

class RvaBase
{
public:
	virtual ~RvaBase() {}
protected:
	int m_04;
};

class Rva003F7EC7 : public RvaBase
{
public:
	virtual ~Rva003F7EC7();
protected:
	Holder08 m_08;
	int m_0C;
	StringBase<char> m_10;
	DeleteInner *m_14;
};

Rva003F7EC7::~Rva003F7EC7()
{
	void *toDelete = m_14 != 0 ? m_14->Delete(0) : 0;
	::operator delete(toDelete);
	m_14 = 0;
}
