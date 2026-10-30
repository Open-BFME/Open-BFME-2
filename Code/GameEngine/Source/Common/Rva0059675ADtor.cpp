// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1FadeInTextRender@@UAE@XZ @0x0059675A 89B
// Dtor with EH frame: vptr store, delete of interface ptr at +0x1c via virtual
// slot0 plus operator delete, StringBase<char> at +0x24 via releaseBuffer,
// then base vtable store. Empty body plus delete.
// Evidence: mov [esi] 0x00870A70, virtual call [eax] with push 0, call delete
// at 0x2FD60, lea ecx [esi+24] call 0x36410, mov [esi] 0x00870A5C.
// The canonical frozen StringBase replaces the private copy; its switch makes
// the member dtor reachable and keeps the teardown an out-of-line call to the
// rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"


struct Rva0059675ABase
{
	virtual ~Rva0059675ABase();
};
struct Rva0059675AInner
{
	virtual void *slot0(int flag);
};
struct FadeInTextRender : Rva0059675ABase
{
	char m_pad04[0x18];
	Rva0059675AInner *m_1c;
	char m_pad20[0x4];
	StringBase<char> m_24;
	virtual ~FadeInTextRender();
	virtual void LoadAssets();
};
Rva0059675ABase::~Rva0059675ABase()
{
}
FadeInTextRender::~FadeInTextRender()
{
	void *tmp = m_1c ? m_1c->slot0(0) : 0;
	::operator delete(tmp);
	m_1c = 0;
}
