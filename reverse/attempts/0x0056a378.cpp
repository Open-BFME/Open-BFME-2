// ?rva0056A378@LargeGroupAudioKeyMap@@QAEXPAX@Z
// partial score=0.9 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /MD
//
// ?rva0056A378@LargeGroupAudioKeyMap@@QAEXABV1@@Z @0x0056A378 135B.
// Copy/assign: self-guard, release the +0x2C slots through pinned 0x005C8565
// plus rowed ::operator delete 0x0002FD60 with nulling, run rowed
// LargeGroupAudioKeyMap::operator= 0x003ED989, copy the +0xC
// OpaqueRefElement4 via rowed operator= 0x00239099 and the +0x10 StringBase
// via rowed set 0x000366F0, refill the +0x14 vector-ish struct through pinned
// 0x00569F0C, then clear +0xC down the element range. Counter lives in the
// dead [ebp+8] home, slot spill in [ebp-4]. Method on the rowed
// LargeGroupAudioKeyMap (operator= call proves class); honest
// address-derived method name.
#include "ascii_string.h"

struct OpaqueRefElement4
{
	void *m_referent;
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

class Rva005C8565
{
public:
	void rva005C8565();
};

struct Rva00569F0CVec
{
	void *m_begin;
	void *m_end;
	void *m_pad;
	void rva00569F0C(void *a, void *b, bool *out);
};

class LargeGroupAudioKeyMap
{
public:
	LargeGroupAudioKeyMap &operator=(const LargeGroupAudioKeyMap &other);
	void rva0056A378(void *other);
private:
	char m_pad[0xC];
	OpaqueRefElement4 m_0C;
	StringBase<char> m_10;
	Rva00569F0CVec m_14;
	char m_pad20[0xC];
	Rva005C8565 *m_slots[4];
};

struct Rva0056A378Elem
{
	char m_pad[0xC];
	unsigned m_clear;
	char m_pad10[4];
};

// The int parameter carries the other's pointer bits and is reused as the
// slot-loop counter once the pointer is cached in edi (its home then dead).
void LargeGroupAudioKeyMap::rva0056A378(void *other)
{
	LargeGroupAudioKeyMap *o = (LargeGroupAudioKeyMap *)other;
	if (o == this)
		return;
	Rva005C8565 **slot = m_slots;
	// Counter reuses the dead [ebp+8] home: `other` is cached in edi/o and
	// never re-read via its home, so punning it as int lands the counter.
	((int &)other) = 4;
	do {
		Rva005C8565 *s = *slot;
		if (s != 0) {
			s->rva005C8565();
			::operator delete(s);
			*slot = 0;
		}
		++slot;
	} while (--((int &)other) != 0);
	operator=(*o);
	m_0C = o->m_0C;
	m_10.set(o->m_10);
	bool ok;
	Rva00569F0CVec *v = &m_14;
	v->rva00569F0C(o->m_14.m_begin, o->m_14.m_end, &ok);
	Rva0056A378Elem *e = (Rva0056A378Elem *)v->m_begin;
	for (; e != (Rva0056A378Elem *)m_14.m_end; ++e)
		e->m_clear = 0;
}
