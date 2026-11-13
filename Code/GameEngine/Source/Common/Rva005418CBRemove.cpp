// cl: /O1 /DNDEBUG /MD /EHsc /G7
//
// ?rva005418CB@Rva005418CB@@QAEXH@Z @ 0x005418CB 72B
// Evidence: guarded key removal on the 0x14-stride channel, twin of
// rowed 0x00541883 (same 0x9CB27E/0x9CB274 notify pair). Rejects
// non-positive keys, validates the hint through the pinned 200B
// locator 0x00541641 (sibling of banked 0x00541579), notifies through
// rowed forEach 0x005414E5 with the member-function pointer (MSVC vcall thunks
// ??_9@$BCA@AE / ??_9@$BBI@AE, slots +0x20 / +0x18),
// shrinks the hinted element through the rowed 0x00541311 single-shrink
// spelling on the +0x10 cursor subobject, then notifies again. The
// hint*0x14 offset needs /G7 for the real imul. Names are generated.
class Rva0054103E
{
public:
	char m_bytes[0x14];
};

#include "../../Include/Common/Rva005414E5Listener.h"

class Rva005414E5List
{
public:
	void forEach(void (Rva005414E5Listener::*notify)(void *, int), void *arg, int value);
private:
	Rva005414E5Listener **m_begin;
	Rva005414E5Listener **m_end;
	Rva005414E5Listener **m_capacity;
	unsigned int m_index;
};

class Rva00541311
{
public:
	void *erase(void *p);
};

class Rva005418CB
{
public:
	bool rva00541641(int key);
	void rva005418CB(int key);
private:
	Rva005414E5List m_list00;
	Rva0054103E *m_begin10;
	Rva0054103E *m_end14;
	int m_pad18;
	int m_hint1C;
};

void Rva005418CB::rva005418CB(int key)
{
	if (key <= 0)
		return;
	if (!rva00541641(key))
		return;
	m_list00.forEach(&Rva005414E5Listener::notify20, this, key);
	int off = m_hint1C * 0x14;
	Rva0054103E *elem = (Rva0054103E *)((char *)m_begin10 + off);
	((Rva00541311 *)&m_begin10)->erase(elem);
	m_list00.forEach(&Rva005414E5Listener::notify18, this, key);
}
