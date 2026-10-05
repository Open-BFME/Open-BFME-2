// ??0Rva005DAC85@@QAE@PAX@Z
// partial score=0.93 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /Os /MD /arch:SSE
// ??0Rva005DAC85@@QAE@PAX@Z @0x005DAC38 53B evidence: vtable 0x008765F8 store plus base ctor 0x0055B048 plus float zeros at +0x2C +0x30 +0x34 plus int zeros at +0x38 +0x3C plus arg to +0x40; callers 0x005986B5 0x00598BBF push +0x30; layout from sibling Rva005DAAB6Ctor plus dtor row
#include "ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0
};

class Rva0055B0CC
{
	friend class Rva005DAC85;
public:
	Rva0055B0CC();
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void Slot6(void *arg1, bool arg2);
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void Rva0055AED6(void *xfer, void *arg2);
	virtual ~Rva0055B0CC();
private:
	float m_04;
	ObjectID m_08;
	AsciiString m_0C;
	unsigned int m_10;
	int m_pad14;
	float m_18;
	int m_pad1C;
	bool m_20;
	bool m_21;
	ObjectID m_24;
	bool m_28;
};

class Rva005DAC85 : public Rva0055B0CC
{
public:
	Rva005DAC85(void *arg);
	virtual ~Rva005DAC85();
private:
	float m_2C;
	float m_30;
	float m_34;
	int m_38;
	int m_3C;
	void *m_40;
};

// ??0Rva005DAC85@@QAE@PAX@Z present-unmatched
Rva005DAC85::Rva005DAC85(void *arg)
	: m_2C(0.0f)
{
	m_30 = 0.0f;
	m_34 = 0.0f;
	m_38 = 0;
	m_3C = 0;
	m_40 = arg;
}
