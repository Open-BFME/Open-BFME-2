// ?rva007F97B0@Rva007FA2C0@@QAEXPAVRva007E8810Message@@PAURva007FA170Slot@@@Z
// cl: /O2 /GX-
// Retail 0x00665D20, 414 bytes (ret 8): FESL transactor reply reassembly.
// WorldBuilder twin VA 0x016C5620 (FESL transactor.cpp, asserts at lines
// 315/318) gives the locals, accessor calls
// and the early return; the reply header is a function-scope local after that
// return, which is what keeps the address constructor's zero stores (+0x2C,
// +0x30, +0x34) that a nested-block header loses to dead-store elimination.
#include <string.h>

class Rva007E86B0Base
{
public:
	Rva007E86B0Base();
	virtual ~Rva007E86B0Base();
	Rva007E86B0Base &operator=(const Rva007E86B0Base &other)
	{
		m_field04 = other.m_field04;
		return *this;
	}
	int m_field04;
};

class Rva00808CB0LanGameEntry : public Rva007E86B0Base
{
public:
	Rva00808CB0LanGameEntry()
	{
		m_field08 = 0;
		m_field0c = 0;
		setField04(0);
	}
	Rva00808CB0LanGameEntry &operator=(const Rva00808CB0LanGameEntry &other)
	{
		Rva007E86B0Base::operator=(other);
		m_field08 = other.m_field08;
		m_field0c = other.m_field0c;
		return *this;
	}
	virtual ~Rva00808CB0LanGameEntry();
	void setField04(int value) { m_field04 = value; }
	int m_field08;
	int m_field0c;
};

class Rva007E8810Message : public Rva00808CB0LanGameEntry
{
public:
	bool getString(const char *key, char *destination, int size);
	unsigned size() const { return m_14; }
	unsigned getType() const { return m_1C; }
	int getFlags() const { return m_20; }
	Rva00808CB0LanGameEntry &getAddress() { return *this; }
	char *m_10;
	unsigned m_14;
	unsigned m_18;
	unsigned m_1C;
	int m_20;
};

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *alloc(unsigned size, int flags);
	virtual void release(void *block, int flags);
};
GenAlloc *Gen007EFFC0();

#include "../../Include/GameNetwork/Rva007EB810Diag.h"
Rva007EB810Diag *Rva007EB810Get();
int rva007FF250Decode(int length, const char *source, unsigned char *dest);

class Gen007F0130
{
public:
	Gen007F0130() { reset(); }
	void reset()
	{
		m_received = 0;
		m_total = 0;
		m_buffer = 0;
	}
	static void *operator new(unsigned int size);
	unsigned m_total;
	unsigned m_received;
	unsigned char *m_buffer;
};

struct Rva007FA170Slot
{
	int m_00;
	int m_04;
	Rva007E8810Message *m_08;
	void *m_0C;
	void *m_10;
	int m_14;
	Gen007F0130 *m_18;
};

struct Rva00800E50Header
{
	Rva00800E50Header() : m_type(0), m_flags(0), m_text(0), m_textLength(0), m_10(false) {}
	unsigned m_type;
	int m_flags;
	const char *m_text;
	unsigned m_textLength;
	bool m_10;
	Rva00808CB0LanGameEntry m_entry;
};

class Rva007F9D00Handler
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void receive(Rva00800E50Header *header);
};

class Rva007F9D00Hub
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual unsigned totalSize(Rva007E8810Message *message);
};

class Rva007FA2C0
{
public:
	void rva007F97B0(Rva007E8810Message *message, Rva007FA170Slot *slot);
	void *m_vtable;
	Rva007F9D00Handler m_handler;
	char m_pad08[0x1C];
	Rva007F9D00Hub *m_hub;
};

void Rva007FA2C0::rva007F97B0(Rva007E8810Message *message, Rva007FA170Slot *slot)
{
	Gen007F0130 *record = slot->m_18;
	if (record == 0)
	{
		record = new Gen007F0130;
		slot->m_18 = record;
		record->m_total = m_hub->totalSize(message);
		record->m_buffer = (unsigned char *)Gen007EFFC0()->alloc(record->m_total + 4, 1);
	}
	char *text = (char *)Gen007EFFC0()->alloc(message->size(), 0);
	message->getString("data", text, message->size());
	unsigned len = strlen(text);
	if ((len & 0x3) != 0)
		Rva007EB810Get()->fail("(len & 0x3) == 0", "\\views\\feslbuild_main\\jabba\\fesl\\source\\transactor.cpp", 315);
	unsigned decoded = len / 4 * 3;
	int result = rva007FF250Decode(len, text, record->m_buffer + record->m_received);
	if (!result)
		Rva007EB810Get()->fail("result", "\\views\\feslbuild_main\\jabba\\fesl\\source\\transactor.cpp", 318);
	record->m_received += decoded;
	Gen007EFFC0()->release(text, 0);
	if (record->m_received < record->m_total)
		return;
	Rva00800E50Header header;
	header.m_type = message->getType();
	header.m_flags = message->getFlags();
	header.m_flags &= ~0x20000000;
	header.m_text = (const char *)record->m_buffer;
	header.m_textLength = record->m_total;
	header.m_entry = message->getAddress();
	m_handler.receive(&header);
}
