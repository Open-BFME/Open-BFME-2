// cl: /MD /DNDEBUG
//
// Three Rva004DD843 members, retail 0x004DDD6E / 0x004DDD80 / 0x004DDD92
// (18 bytes each), pinned from the Object forwarders through Object+0xA4:
// each hands its 0x18-byte slot (+0x1C / +0x34 / +0x04) to the member
// 0x004DD8FA unless the slot's first word holds the -666666 "unset"
// sentinel. The class and slot meanings are not recovered.

typedef int Int;

enum
{
	RVA004DD843_UNSET = -666666
};

struct Rva004DD843Slot
{
	Int m_value;
	unsigned char m_pad04[0x18 - 0x04];
};

class Rva004DD843
{
public:
	void rva004DDD6E();
	void rva004DDD80();
	void rva004DDD92();
	void rva004DD8FA(Rva004DD843Slot *slot);

private:
	void *m_vtable;
	Rva004DD843Slot m_slot04;
	Rva004DD843Slot m_slot1C;
	Rva004DD843Slot m_slot34;
};

void Rva004DD843::rva004DDD6E()
{
	if (m_slot1C.m_value != RVA004DD843_UNSET)
		rva004DD8FA(&m_slot1C);
}

void Rva004DD843::rva004DDD80()
{
	if (m_slot34.m_value != RVA004DD843_UNSET)
		rva004DD8FA(&m_slot34);
}

void Rva004DD843::rva004DDD92()
{
	if (m_slot04.m_value != RVA004DD843_UNSET)
		rva004DD8FA(&m_slot04);
}
