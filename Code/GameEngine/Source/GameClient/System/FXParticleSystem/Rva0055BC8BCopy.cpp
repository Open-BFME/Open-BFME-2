// cl: /EHs-c-
// ??0Rva0055BC8B@@QAE@ABV0@@Z @0x003ADD9D 42B copy ctor vtable 0x0081D1A4 eight RGB keys at +4 plus float at +0x84. Evidence: rowed ctor 0x0055BC8B same vtable; caller 0x003ADD52; rep movsd 0x20 plus trailing mov.
class Xfer;
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
class Rva0055BC8B : public Snapshot
{
public:
	Rva0055BC8B(const Rva0055BC8B &that);
	virtual ~Rva0055BC8B();
private:
	struct Keys
	{
		unsigned int v[32];
	};
	Keys m_keys;
	float m_trailing;
public:
	// retail vftable slot: the rowed override
	virtual void xfer(Xfer *);
};
Rva0055BC8B::Rva0055BC8B(const Rva0055BC8B &that)
{
	m_keys = that.m_keys;
	m_trailing = that.m_trailing;
}
