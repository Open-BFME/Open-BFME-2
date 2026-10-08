// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva005CDDA4@@QAE@PAXHHHHH@Z, retail 0x005CDD32..0x005CDDA4 (114 bytes,
// EH, RET 24): the constructor matching the rowed Rva005CDDA4 destructor
// (vtables 0x00C750BC and 0x00C750E0). The first base is built through the
// rowed 0x005E663C from the six arguments and a temporary 8-byte callback on
// this (vtable 0x00C7508C), whose address that constructor takes as an int;
// the second base at +0x0C through 0x005D206B (not yet rowed; pinned) from
// the second, third and sixth arguments; +0x20 is cleared. WorldBuilder's
// twin (0x015C0980) is unnamed.

class Rva005E663C
{
public:
	Rva005E663C(void *a1, int a2, int a3, int a4, int a5, int a6, int callback);
	virtual ~Rva005E663C();
private:
	unsigned char m_pad04[0x0C - 0x04];
};

class Rva005D2015
{
public:
	Rva005D2015(int a2, int a3, int a6);
	virtual ~Rva005D2015();
private:
	unsigned char m_pad04[0x14 - 0x04];
};

class Rva005CDDA4;

class Rva005CDDA4Callback
{
public:
	Rva005CDDA4Callback(Rva005CDDA4 *owner) : m_owner(owner) {}
	virtual void c0();
	virtual void c1();
	virtual void c2();
private:
	Rva005CDDA4 *m_owner;
};

class Rva005CDDA4 : public Rva005E663C, public Rva005D2015
{
public:
	Rva005CDDA4(void *a1, int a2, int a3, int a4, int a5, int a6);
	virtual ~Rva005CDDA4();
private:
	void *m_20;								// +0x20
};

#pragma warning(disable: 4238)	// the callback temporary's address, as retail passes it
Rva005CDDA4::Rva005CDDA4(void *a1, int a2, int a3, int a4, int a5, int a6)
	: Rva005E663C(a1, a2, a3, a4, a5, a6, (int)&Rva005CDDA4Callback(this)),
	  Rva005D2015(a2, a3, a6),
	  m_20(0)
{
}
