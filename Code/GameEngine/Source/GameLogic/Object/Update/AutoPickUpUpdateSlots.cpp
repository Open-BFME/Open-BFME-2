// cl: /DNDEBUG /MD
//
// ?rva00495C6E@AutoPickUpUpdate@@UAEXXZ, retail 0x00495C6E, 9 bytes: slot 2 of
// the vtable 0x00C4EF90 that AutoPickUpUpdate's ctors (0x00495C5C, 0x00495D77)
// install at +0x20; raises the bytes at +0x28 and +0x29. Compiled with the
// +0x20 subobject this. Names by address.
class UpdateModule
{
public:
	virtual ~UpdateModule();
private:
	unsigned char m_pad04[0x20 - 4];
};

class AutoPickUpUpdateInterface
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void rva00495C6E() = 0;
};

class AutoPickUpUpdate : public UpdateModule, public AutoPickUpUpdateInterface
{
public:
	virtual void rva00495C6E();
private:
	unsigned char m_pad24[0x28 - 0x24];
	bool m_28; // +0x28
	bool m_29; // +0x29
};

void AutoPickUpUpdate::rva00495C6E()
{
	m_28 = true;
	m_29 = true;
}
