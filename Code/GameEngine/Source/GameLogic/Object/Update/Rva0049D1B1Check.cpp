// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?Check@Rva0049D1B1@@UAE_NH@Z, retail 0x0049CDF9, 47 bytes. Dedicated TU.
//
// Vtable slot9 of 0xC5146C (the Rva0049D1B1 vtable; slot9 dumped as
// 0x49CDF9 and slot10 abuts at 0x49CE28, proving the 47B boundary). The UAE
// letter is proven by that vtable membership. Walks the virtual chain:
// V21 (slot21, 0x49CEAE) yields the head object, V22 (slot22, 0x49CEE1)
// yields the next one; returns true for the first object whose +0x04
// discriminator is 2 with +0x0C equal to the argument.
//
// Placeholders fill slots 1-8 and 10-20 so the two callee virtuals land at
// indices 21/22 (snapshotCreateView precedent); they are declared-only and
// never constructed here, so no vtable is emitted. The dtor lives in
// Rva0049D1B1.cpp. Virtual calls need no pins.

class AsciiString
{
public:
	~AsciiString() throw();

	void *m_data;
};

class Rva0049D1B1
{
public:
	virtual ~Rva0049D1B1();
	virtual void u01();
	virtual void u02();
	virtual void u03();
	virtual void u04();
	virtual void u05();
	virtual void u06();
	virtual void u07();
	virtual void u08();
	virtual bool Check(int val);
	virtual void u10();
	virtual void u11();
	virtual void u12();
	virtual void u13();
	virtual void u14();
	virtual void u15();
	virtual void u16();
	virtual void u17();
	virtual void u18();
	virtual void u19();
	virtual void u20();
	virtual Rva0049D1B1 *V21();
	virtual Rva0049D1B1 *V22(Rva0049D1B1 *cur);

private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	float m_14;
	float m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	unsigned char m_34;
	int m_38;
	int m_3C;
	AsciiString m_name; // +0x40
	unsigned char m_44;
	int m_48;
	int m_4C;
};

// ?Check@Rva0049D1B1@@UAE_NH@Z @0x0049CDF9
bool Rva0049D1B1::Check(int val)
{
	Rva0049D1B1 *obj = V21();
	while (obj != 0)
	{
		if (obj->m_04 == 2 && obj->m_0C == val)
			return true;
		obj = V22(obj);
	}
	return false;
}
