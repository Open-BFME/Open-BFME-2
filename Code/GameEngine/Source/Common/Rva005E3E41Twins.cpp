// cl: /O1 /DNDEBUG /MD
// Twins 2x31B: 0x005E3E41 and 0x005E4389.
// Each: lea this2 = (inner+this-0x14) then call rowed 8B forwarder
// (0x005F3F6B / 0x005F3FF4) then call pinned second (0x005E3AAA / 0x005E4087)
// with (this2member-0x10 as this, [this-0x0C] as int). Ret void, this only.
// Address-derived.
class Rva005F3F6B
{
public:
	void rva005F3F6B();
};

class Rva005F3FF4
{
public:
	void rva005F3FF4();
};

class Rva005E3AAA
{
public:
	void rva005E3AAA(int a);
};

class Rva005E4087
{
public:
	void rva005E4087(int a);
};

class Rva005E3E41Inner
{
public:
	int m_pad0;
	int m_4;
};

class Rva005E3E41
{
public:
	void rva005E3E41();
};

void Rva005E3E41::rva005E3E41()
{
	// Cannot directly express negative-offset this in portable C++; use
	// raw pointer arithmetic that MSVC 7.1 lowers to the same lea/movs.
	unsigned char *th = (unsigned char *)this;
	Rva005E3E41Inner **ppOuter = (Rva005E3E41Inner **)(th - 0x14);
	Rva005E3E41Inner *pOuter = *ppOuter;
	int inner4 = pOuter->m_4;
	Rva005F3F6B *pFirst = (Rva005F3F6B *)(inner4 + (int)th - 0x14);
	pFirst->rva005F3F6B();
	int arg = *(int *)(th - 0x0C);
	Rva005E3AAA *pSecond = *(Rva005E3AAA **)(th - 0x10);
	pSecond->rva005E3AAA(arg);
}

class Rva005E4389
{
public:
	void rva005E4389();
};

void Rva005E4389::rva005E4389()
{
	unsigned char *th = (unsigned char *)this;
	Rva005E3E41Inner **ppOuter = (Rva005E3E41Inner **)(th - 0x14);
	Rva005E3E41Inner *pOuter = *ppOuter;
	int inner4 = pOuter->m_4;
	Rva005F3FF4 *pFirst = (Rva005F3FF4 *)(inner4 + (int)th - 0x14);
	pFirst->rva005F3FF4();
	int arg = *(int *)(th - 0x0C);
	Rva005E4087 *pSecond = *(Rva005E4087 **)(th - 0x10);
	pSecond->rva005E4087(arg);
}
