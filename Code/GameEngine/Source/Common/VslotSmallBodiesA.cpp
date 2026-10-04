// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Small vtable-slot bodies with no ledger owner and no Ghidra size (sized from
// their bytes: every path ends in ret), batch A. Each class and method is
// address-derived and models only the fields and slots its body touches; the
// comment above each gives the vtable and slot that reach it. Argument and
// return types are what the bytes require (an unused stack argument is
// typed Int); meanings are not recovered.

typedef int Int;
typedef bool Bool;
typedef float Real;

template <int N> class VslotPad : public VslotPad<N - 1>
{
public:
	virtual void pad(char (*)[N]);
};
template <> class VslotPad<0>
{
public:
	virtual void pad0();
};

// vtable 0x00BC55B0#9: own slot 14 with 1.
class Rva00051173 : public VslotPad<13>
{
public:
	virtual void slot14(Int value);
	void rva00051173();
};
void Rva00051173::rva00051173() { slot14(1); }

// vtable 0x00C10F40#16: own slot 5 with 1.
class Rva00340744 : public VslotPad<4>
{
public:
	virtual void slot5(Int value);
	void rva00340744();
};
void Rva00340744::rva00340744() { slot5(1); }

// vtable 0x00C16510#6 and 0x00C1661C#6: own slot 2 with 6 and with 8.
class Rva0035E2DE : public VslotPad<1>
{
public:
	virtual void slot2(Int value);
	void rva0035E2DE();
};
void Rva0035E2DE::rva0035E2DE() { slot2(6); }

class Rva0035EE5E : public VslotPad<1>
{
public:
	virtual void slot2(Int value);
	void rva0035EE5E();
};
void Rva0035EE5E::rva0035EE5E() { slot2(8); }

// vtable 0x00C163D8#6: own slot 2 with the field at +0x14.
class Rva0035D1E7 : public VslotPad<1>
{
public:
	virtual void slot2(Int value);
	void rva0035D1E7();
private:
	char m_pad04[0x14 - 0x04];
	Int m_14;
};
void Rva0035D1E7::rva0035D1E7() { slot2(m_14); }

// vtable 0x00C02114#7: own slot 3, its one stack argument unused.
class Rva002C941C : public VslotPad<2>
{
public:
	virtual void slot3();
	void rva002C941C(Int unused);
};
void Rva002C941C::rva002C941C(Int) { slot3(); }

// vtable 0x00BC7F20#4: own slot 10 with the field at +0x48 plus one.
class Rva00090F72 : public VslotPad<9>
{
public:
	virtual void slot10(Int value);
	void rva00090F72();
	Bool rva00090F7D();
private:
	char m_pad04[0x3C - 0x04];
	Int m_3C;
	char m_pad40[0x48 - 0x40];
	Int m_48;
};
void Rva00090F72::rva00090F72() { slot10(m_48 + 1); }

// vtable 0x00BC7F20#13: is +0x48 at or past +0x3C less one.
Bool Rva00090F72::rva00090F7D() { return m_48 >= m_3C - 1 ? true : false; }

// vtable 0x00BC8208#15: is the field at +0xC0 set.
class Rva00094DA8
{
public:
	Bool rva00094DA8();
private:
	char m_pad00[0xC0];
	void *m_C0;
};
Bool Rva00094DA8::rva00094DA8() { return m_C0 ? true : false; }

// vtable 0x00C112C0#9: own slot 8 negated, as an Int.
class Rva0034B167 : public VslotPad<7>
{
public:
	virtual Bool slot8();
	Int rva0034B167();
};
Int Rva0034B167::rva0034B167() { return !slot8(); }

// vtable 0x00C6DAF0#1: the cdecl function at +8 with the stack argument.
class Rva00380A75
{
public:
	void rva00380A75(Int value);
private:
	char m_pad00[0x08];
	void (__cdecl *m_function08)(Int);
};
void Rva00380A75::rva00380A75(Int value) { m_function08(value); }

// vtable 0x00BC89C8#23 and 0x00BF6178#24: own slot 21 with the first of
// two and of six stack arguments.
class Rva0009B0AB : public VslotPad<20>
{
public:
	virtual void slot21(Int value);
	void rva0009B0AB(Int value, Int unused);
};
void Rva0009B0AB::rva0009B0AB(Int value, Int) { slot21(value); }

class Rva0025EEF5 : public VslotPad<20>
{
public:
	virtual void slot21(Int value);
	void rva0025EEF5(Int value, Int, Int, Int, Int, Int);
};
void Rva0025EEF5::rva0025EEF5(Int value, Int, Int, Int, Int, Int) { slot21(value); }

// vtable 0x00C1FDE0#2: the field at +8, complemented unless the byte at +0xC.
class Rva002613A3
{
public:
	Int rva002613A3();
private:
	char m_pad00[0x08];
	Int m_08;
	Bool m_0C;
};
Int Rva002613A3::rva002613A3() { return m_0C ? m_08 : ~m_08; }

// vtable 0x00C07190#1: does the stack argument differ from +8.
class Rva002614DF
{
public:
	Bool rva002614DF(Int value);
private:
	char m_pad00[0x08];
	Int m_08;
};
Bool Rva002614DF::rva002614DF(Int value) { return value != m_08 ? true : false; }

// vtable 0x00BC7568#85: store the float argument at +0x50.
class Rva0008BB5C
{
public:
	void rva0008BB5C(Real value);
private:
	char m_pad00[0x50];
	Real m_50;
};
void Rva0008BB5C::rva0008BB5C(Real value) { m_50 = value; }

// vtable 0x00BE4340#3: are the two stack arguments equal.
class Rva003F7133
{
public:
	Bool rva003F7133(Int a, Int b);
};
Bool Rva003F7133::rva003F7133(Int a, Int b) { return a == b ? true : false; }

// vtable 0x00BF6040#32 and #33: set or clear the byte at +0x12134 of the
// object at +0xC, if any.
class Rva0025DC38Target
{
public:
	char m_pad00[0x12134];
	Bool m_12134;
};
class Rva0025DC38
{
public:
	void rva0025DC38();
	void rva0025DC47();
private:
	char m_pad00[0x0C];
	Rva0025DC38Target *m_0C;
};
void Rva0025DC38::rva0025DC38() { if (m_0C) m_0C->m_12134 = true; }
void Rva0025DC38::rva0025DC47() { if (m_0C) m_0C->m_12134 = false; }
