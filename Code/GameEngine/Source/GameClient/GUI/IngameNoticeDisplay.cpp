// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// BFME1 donor: game/GameEngine/Source/GameClient/GUI/IngameNoticeDisplay.cpp
// at ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f. Its display-resource owner
// constructor is the semantic lead. Native 0x004E594E..0x004E59AE (96 bytes)
// has the same descriptor/resource/unused/identifier fields and operations;
// BFME2 creates the display through manager slot 14 rather than slot 9.
// Use BFME2's shared UnicodeString for the by-value virtual argument, so the
// receiver is reloaded after its owned 0x00037050 copy constructor.
// The 0x004E5B0A caller allocates 0x18 bytes; the last eight bytes are opaque.
// The original owner class name is unproven: retain an RVA-derived name.
#include "unicode_string.h"
class DisplayStringManager;
struct Rva004E594EDescriptor
{
	unsigned int field0;
	unsigned int field4;
};

class NoticeResource
{
public:
	virtual void f0();
	virtual void setText(UnicodeString text);
	virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
	virtual void setDescriptor(unsigned int value);
	virtual void f7(); virtual void f8(); virtual void f9();
	virtual void finish(int first, int second);
};

class NoticeManager
{
public:
	virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3();
	virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7();
	virtual void f8(); virtual void f9(); virtual void f10(); virtual void f11();
    virtual void f12(); virtual void f13();
	virtual NoticeResource *create(void);
};

extern DisplayStringManager *TheDisplayStringManager;

class Rva004E594E
{
public:
	Rva004E594E(const UnicodeString &text,
		Rva004E594EDescriptor *descriptor, int identifier);
private:
	Rva004E594EDescriptor *m_descriptor;
	NoticeResource *m_resource;
	unsigned int m_unused;
	int m_identifier;
    unsigned char unknown10[8];
};

Rva004E594E::Rva004E594E(
	const UnicodeString &text, Rva004E594EDescriptor *descriptor,
	int identifier)
{
	Rva004E594EDescriptor *desc = descriptor;
	m_descriptor = desc;
	m_resource = 0;
	m_unused = 0;
	m_identifier = identifier;
	m_resource = reinterpret_cast<NoticeManager *>(TheDisplayStringManager)->create();
	if (m_resource)
	{
		m_resource->setDescriptor(desc->field4);
		m_resource->setText(text);
		m_resource->finish(0, 0);
	}
}
