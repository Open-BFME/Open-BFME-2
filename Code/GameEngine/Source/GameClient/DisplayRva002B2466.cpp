// cl: /DNDEBUG /MD /EHsc

// ?rva002B2466@Display@@QAEXMMMM@Z, RVA 0x002B2466, 138 bytes.
// Display method scaling four normalized floats by the display dimensions.
// Evidence: five callers pass TheDisplay (0x009FE9D8) as this with four float
// stack args (three pass 0,0,1,1 full-screen; 0x00356724 passes constants at
// RVA 0x00814F7C); body calls own vtable slots 0x40/0x44 alternating, the
// proven BFME2 Display getWidth/getHeight slots (Mouse::setMouseLimits precedent
// plus BFMEDisplayWidthSlot); unsigned-to-float conversion shape (fild plus jge
// plus fadd 2^32) proves UnsignedInt returns; stores four floats at
// this+0xFC/0x100/0x104/0x108. Honest-address name: owner proven Display,
// signature void __thiscall(float,float,float,float) from ret 0x10.

class Display
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual unsigned getWidth();
	virtual unsigned getHeight();
	void rva002B2466(float a, float b, float c, float d);
private:
	unsigned char m_pad[0xFC - 4];
	float m_0FC;
	float m_100;
	float m_104;
	float m_108;
};

void Display::rva002B2466(float a, float b, float c, float d)
{
	m_0FC = (float)getWidth() * a;
	m_100 = (float)getHeight() * b;
	m_104 = (float)getWidth() * c;
	m_108 = (float)getHeight() * d;
}
