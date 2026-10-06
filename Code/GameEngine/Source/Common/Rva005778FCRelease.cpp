// cl: /MD
// AptRadialMenu::Impl::OnButtonDestroyed (WorldBuilder name, AptRadialMenu.cpp line 205: drop the +0x40 shared button count).
// was ?rva005778FC@Rva005778FC@@QAEXXZ @ 0x005778FC (24B):
// Guarded refcount release on double-indirect holder at +0x40; decrements count
// at +0x10 and clears flag at +0xC when it reaches zero. Evidence: sole caller
// 0x00578189 passes [esi+8] in ecx; volatile read reproduces retail redundant
// dec plus cmp shape under /O1.

struct Rva005778FCInner
{
	char m_pad[0xC];
	int m_flag;
	int m_count;
};

struct Rva005778FCHolder
{
	Rva005778FCInner *m_ptr;
};

class AptRadialMenu
{
public:
	class Impl;
};
class AptRadialMenu::Impl
{
	char m_pad[0x40];
	Rva005778FCHolder *m_holder;

public:
	void OnButtonDestroyed();
};

void AptRadialMenu::Impl::OnButtonDestroyed()
{
	Rva005778FCInner *p = m_holder->m_ptr;
	--p->m_count;
	if (*(volatile int *)&p->m_count != 0)
		return;
	p = m_holder->m_ptr;
	p->m_flag = 0;
}
