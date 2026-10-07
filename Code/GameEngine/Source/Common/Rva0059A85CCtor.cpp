// cl: /DBFME_ASCII_DTOR_DECL /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// Fix over the banked 0.97 attempt, from the retail unwind map: state 0
// destroys the Rva00506B1B base through its 7-byte vptr setter 0x00506B28, so
// the base declares a virtual destructor; that restores the missing state-0
// store and the state numbering of the vector (+0x08) and set (+0x18).
// stlport
// ??0Rva0059A85C@@QAE@PAX@Z @0x0059A85C (123B)
// Derived ctor calls base Rva00506B1B then vector BfmeE16 at +8 then sets
// vtable g_00C70DE4 then set AsciiString at +0x18. Stores void arg to +0x14
// then walks circular list at arg+0x32c calling rowed rva0059A71C on each
// node+8 value. Ret 4. Caller 0x004EC430. Evidence chain lane calls just
// landed 0x0059A71C plus EH prolog plus vector_base set rows.
#include <vector>
#include <set>
class Rva00506B1B
{
public:
	Rva00506B1B();
	virtual ~Rva00506B1B();
	virtual void v0();
	virtual void v1();
	bool m_04;
};
struct BfmeE16 { float x, y, z, w; };
#include "ascii_string.h"
struct Arg;
class Rva0059A71C
{
public:
	void rva0059A71C(Arg *arg);
};
struct Node
{
	Node *m_next;
	char m_pad[4];
	Arg *m_val;
};
struct OuterLayout
{
	char m_pad[0x32c];
	Node *m_head;
};
extern const void *const g_00C70DE4[];
class Rva0059A85C : public Rva00506B1B
{
public:
	Rva0059A85C(void *outer);
private:
	_STL::vector<BfmeE16> m_vec;
	void *m_outer;
	_STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > m_set;
};
// ??0Rva0059A85C@@QAE@PAX@Z @0x0059A85C
Rva0059A85C::Rva0059A85C(void *outer) : m_vec(), m_outer(outer), m_set()
{
	Node *sent = ((OuterLayout *)m_outer)->m_head;
	Node *cur = *(Node **)sent;
	if (cur == sent)
		return;
	do {
		((Rva0059A71C *)this)->rva0059A71C(cur->m_val);
		cur = cur->m_next;
	} while (cur != ((OuterLayout *)m_outer)->m_head);
}
