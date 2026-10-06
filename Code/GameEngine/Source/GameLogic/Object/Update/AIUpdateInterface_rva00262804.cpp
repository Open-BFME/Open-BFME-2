// cl: /DNDEBUG /MD
//
// ?rva00262804@AIUpdateInterface@@QAEXE@Z, retail 0x00262804, 38 bytes.
// Sibling of wakeUpNow 0x00262871 and setQueueForPathTime 0x0026282A in the
// same AIUpdateInterface tail: stores the byte arg at +0x3B9 then when the
// int at +0x1F4 is 0 or 1 issues the virtual at slot 142 (offset 0x238) with
// 0. m_object-adjacent layout and the +0x3C2 guard in the landed siblings
// prove AIUpdateInterface; the virtual slot is spelled via TU-local
// BfmeVirtualSlots so the gate sees the rowed neighbours only.

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<142>
{
	char m_pad04[0x1F4 - 4];
	int m_field1F4;
	char m_pad1F8[0x3B9 - 0x1F8];
	unsigned char m_flag3B9;
public:
	virtual void slot142(int);
	void rva00262804(unsigned char val);
};

void AIUpdateInterface::rva00262804(unsigned char val)
{
	m_flag3B9 = val;
	if (m_field1F4 == 0 || m_field1F4 == 1)
		slot142(0);
}
