// ?rva0056A378@LargeGroupAudioKeyMap@@QAEXABV1@@Z
// partial score=0.92 date=2026-10-07
// ?rva0056A378@LargeGroupAudioKeyMap@@QAEXABV1@@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD
//
// Retail 0x0056A378 135B. Copy/assign on LargeGroupAudioKeyMap, evidenced by
// the rowed assignment call and matching caller context; field operations
// follow the target body and rowed/pinned callees.
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
	void rva0056A378(const LargeGroupAudioKeyMap &other);
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

void LargeGroupAudioKeyMap::rva0056A378(const LargeGroupAudioKeyMap &other)
{
	const LargeGroupAudioKeyMap *o = &other;
	if (o == this)
		return;
	Rva005C8565 **slot = m_slots;
	int count = 4;
	do {
		Rva005C8565 *s = *slot;
		if (s != 0) {
			s->rva005C8565();
			::operator delete(s);
			*slot = 0;
		}
		++slot;
	} while (--count != 0);
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
