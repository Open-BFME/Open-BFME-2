// cl: /DNDEBUG /MD /EHsc
//
// Wave-3 F24 shape family: single-base constructors forwarding one int (or
// the constant 1) to a pinned base constructor, then stamping the derived
// vtable and returning `this`. Identities beyond these shapes are not
// recovered.
//

// 0x00210EF1 forwards its one argument to the rowed 0x003FAE68 constructor
// Rva003FAFB9(const AsciiString &) (LivingWorldSound.cpp), so it takes the
// same reference.
class AsciiString;

class Rva003FAFB9
{
public:
	Rva003FAFB9(const AsciiString &name);
	virtual void f0() = 0;
};

class Rva00210EF1 : public Rva003FAFB9
{
public:
	Rva00210EF1(const AsciiString &name);
};

Rva00210EF1::Rva00210EF1(const AsciiString &name) : Rva003FAFB9(name)
{
}




// The rowed chain constructor 0x005AFE86 (Rva005AFE86Ctor.cpp).
struct Rva005AFD89Param;
class UnicodeString;
class GameWindow;

// Retail table 0x00C6FFFC: two __purecall slots.
class Rva005AFE3FBase
{
public:
	virtual void rva005AFD89(int id, const Rva005AFD89Param *p) = 0;
	virtual void rva005AFCEC(int id) = 0;
	~Rva005AFE3FBase() {}
};

// Retail table 0x00C728B8 (six slots); see Rva005AFE86Ctor.cpp.
class Rva005AFE3F : public Rva005AFE3FBase
{
public:
	Rva005AFE3F(void *p);
	virtual void rva005AFD89(int id, const Rva005AFD89Param *p);
	virtual void rva005AFCEC(int id);
	virtual ~Rva005AFE3F();
	virtual bool PopulatePlayerList() = 0;
	virtual bool vslot04(const UnicodeString &text, GameWindow *window) = 0;
	virtual void vslot05(const AsciiString &name) {}

	void *m_04;
	int m_08;
	GameWindow *m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
};

// ??0Rva005D5095Base@@QAE@H@Z retail 0x005D5095 24B (the pinned base of the
// two constructors below): forwards its int to 0x005AFE86 and stamps vtable
// 0x00875AC4, the one ??1Rva005D50D8 restores.
class Rva005D5095Base : public Rva005AFE3F
{
public:
	Rva005D5095Base(int a);
	virtual ~Rva005D5095Base();
	virtual bool vslot04(const UnicodeString &text, GameWindow *window);
	virtual bool vslot06() = 0;
};

Rva005D5095Base::Rva005D5095Base(int a) : Rva005AFE3F((void *)a)
{
}

// ??0Rva005AF9EF@@QAE@XZ retail 0x005AF9EF 20B: the same chain with the
// constant 1 and vtable 0x0087287C, the one ??1Rva005AFA03 restores (caller
// 0x00511826).
class Rva005AF9EF : public Rva005AFE3F
{
public:
	Rva005AF9EF();
};

Rva005AF9EF::Rva005AF9EF() : Rva005AFE3F((void *)1)
{
}

class Rva005D50C4 : public Rva005D5095Base
{
public:
	Rva005D50C4();
};

Rva005D50C4::Rva005D50C4() : Rva005D5095Base(1)
{
}

// ??0Rva005D50E3@@QAE@XZ retail 0x005D50E3 20B
// Evidence: leaf lane; base Rva005D5095Base(0) pin plus vtable 0x00875AFC; caller 0x005AE368; sibling Rva005D50C4 same TU same flags.
class Rva005D50E3 : public Rva005D5095Base
{
public:
	Rva005D50E3();
};

Rva005D50E3::Rva005D50E3() : Rva005D5095Base(0)
{
}
