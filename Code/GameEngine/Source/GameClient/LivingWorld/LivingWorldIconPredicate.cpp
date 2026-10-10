// cl: /O1 /MD
//
// ?rva005C4B26@Rva005C41C9@@QAEEXZ @ 0x005C4B26 (48B).
// Native5C4B26..5C4B56 RET0,48B. Original helper name remains unknown.
// Full-width virtual argument and flags word follow native PUSH EAX and
// PUSH DWORD[B8]; inner member is reread after the virtual call, preserving
// possible receiver mutation. Existing51B provider declaration is repaired
// in the same handoff and consumes only its flags low byte.
// Slot-17 helper: bool from this slot16 gates bool from inner slot0, then
// rowed Rva0056B76D predicate on this +0xB8. Vtable slot 17 of 0x8747B8 and
// 0x8766B8; tail-jumped from v17 at 0x5C417B; calls rowed 0x56B76D.
// Identity from vtable slots, pins and callers.

class Rva0056B76D
{
public:
	bool rva0056B76D(unsigned int flags);
};

struct Inner005C4B26
{
	virtual bool v00(int flag);
};

class Rva005C41C9
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual int d16();
	virtual unsigned char v17();
	virtual void v18(unsigned char a, unsigned char b, int c);
	unsigned char rva005C4B26();

private:
	char m_pad04[0xA8];
	Inner005C4B26 *m_ac;
	char m_padB0[8];
	int m_B8;
};

unsigned char Rva005C41C9::rva005C4B26()
{
	Inner005C4B26 *inner = m_ac;
	bool b = inner->v00(d16());
	if (!b)
		return b;
	return ((Rva0056B76D *)m_ac)->rva0056B76D(m_B8);
}
