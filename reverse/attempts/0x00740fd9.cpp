// ??0Rva00740FD9@@QAE@XZ
// partial score=0.93 date=2026-10-06
// cl: /O1 /Ob2 /EHsc /DNDEBUG /MD /arch:SSE
// ??0Rva00740FD9@@QAE@XZ @0x00740FD9 107B
// MI ctor: primary vtable CF1630 plus m04=-1, secondary pin at +8,
// derived vtables CF1648/CF1644, members +0x60 zeroed. Same class as
// dtor 0x0074104C (CF1648/CF1644) plus factory 0x0074109B (0x80 new).
// Prev/next share O1/EHsc.
extern const void *const g_00CF1630[];
extern const void *const g_00CF1648[];
extern const void *const g_00CF1644[];

class Rva002D2C34
{
public:
	void rva002D2C34();
};

class EmptyEH00740FD9
{
public:
	EmptyEH00740FD9() {}
	~EmptyEH00740FD9();
};

class Rva00740FD9 : public EmptyEH00740FD9
{
public:
	Rva00740FD9();
	void *m_vtbl0;
	int m_04;
	char m_sec[0x58];
	int m_60;
	int m_64;
	float m_68;
	float m_6c;
	int m_70;
	unsigned char m_74;
	unsigned char m_75;
	int m_78;
	int m_7c;
};

Rva00740FD9::Rva00740FD9()
{
	m_04 = -1;
	m_vtbl0 = (void *)g_00CF1630;
	Rva002D2C34 *sec = (Rva002D2C34 *)((char *)this + 8);
	sec->rva002D2C34();
	m_60 = 0;
	m_vtbl0 = (void *)g_00CF1648;
	*(void **)sec = (void *)g_00CF1644;
	m_64 = 0;
	m_68 = 0.0f;
	m_6c = 0.0f;
	m_70 = 0;
	m_74 = 0;
	m_75 = 0;
	m_78 = 0;
	m_7c = 0;
}
