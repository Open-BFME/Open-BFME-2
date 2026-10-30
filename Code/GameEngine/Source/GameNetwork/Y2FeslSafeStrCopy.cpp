// cl: /O2 /DNDEBUG /MD /D_CRTIMP=

// FESL bounded string copy at 0x00655700 (98B) plus the string/int setter at
// 0x006557F0 (33B) that uses it. Both live in the GameSpy zone (16 and 3
// callers respectively, all in 0x65xxxx-0x67xxxx) and share the FESL assert
// channel proven by Y2FeslAddressParse.cpp: the 0x006587A0 getter hands out
// the diag object whose virtual slot 0xC reports (expression, file, line).
// Retail litters the body with the util.h path and the two assert texts
// ("src" at line 33, "strlen(src) < dstSize" at line 34); the copy itself
// rides the pre-existing _strncpy thunk pin at 0x0062983E, so no new pins.
// Use string.h's declaration with _CRTIMP empty to preserve retail's direct
// call to the _strncpy thunk rather than an indirect call through the IAT.

#include <string.h>

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();

void Rva00655700(char *dst, unsigned dstSize, const char *src)
{
	if (src == 0)
		Rva007EB810Get()->fail(
			"src",
			"..\\..\\source\\include\\fesl/internal/util.h",
			33);
	if (!(strlen(src) < dstSize))
		Rva007EB810Get()->fail(
			"strlen(src) < dstSize",
			"..\\..\\source\\include\\fesl/internal/util.h",
			34);
	strncpy(dst, src, dstSize);
}

class Rva006557F0Holder
{
public:
	void set(const char *src, int value);

private:
	char m_pad[8];
	char m_text[28];
	int m_value;
};

void Rva006557F0Holder::set(const char *src, int value)
{
	Rva00655700(m_text, 28, src);
	m_value = value;
}

class Rva0065F0D0Holder
{
public:
	void set(const char *src);

private:
	char m_pad[16];
	char m_text[32];
};

void Rva0065F0D0Holder::set(const char *src)
{
	Rva00655700(m_text, 32, src);
}

class Rva0065F0F0Holder
{
public:
	void set(const char *src);

private:
	char m_pad[48];
	char m_text[32];
};

void Rva0065F0F0Holder::set(const char *src)
{
	Rva00655700(m_text, 32, src);
}

class Rva0065F110Holder
{
public:
	void set(const char *src);

private:
	char m_pad[84];
	char m_text[255];
};

void Rva0065F110Holder::set(const char *src)
{
	Rva00655700(m_text, 255, src);
}

class Rva0065E8B0Holder
{
public:
	void set(const char *src);

private:
	char m_pad[8];
	char m_text[512];
};

void Rva0065E8B0Holder::set(const char *src)
{
	Rva00655700(m_text, 512, src);
}

class Rva0066D7B0Holder
{
public:
	void set(const char *src);

private:
	char m_pad[48];
	char m_text[37];
};

void Rva0066D7B0Holder::set(const char *src)
{
	Rva00655700(m_text, 37, src);
}

struct Rva00657420Inner
{
	char m_pad[225];
	char m_text[32];
};

class Rva00657420Holder
{
public:
	void set(const char *src);

private:
	char m_pad[4];
	Rva00657420Inner *m_inner;
};

void Rva00657420Holder::set(const char *src)
{
	Rva00655700(m_inner->m_text, 32, src);
}

class Rva0066D7E0Holder
{
public:
	void set(const char *src);

private:
	char m_pad[85];
	char m_text[128];
};

void Rva0066D7E0Holder::set(const char *src)
{
	Rva00655700(m_text, 128, src);
}

class Rva00674A50Holder
{
public:
	void set(const char *src);

private:
	char m_pad[140];
	char m_text[37];
};

void Rva00674A50Holder::set(const char *src)
{
	Rva00655700(m_text, 37, src);
}

struct Rva00657480Inner
{
	char m_pad[144];
	char m_text[16];
};

class Rva00657480Holder
{
public:
	void set(const char *src);

private:
	char m_pad[4];
	Rva00657480Inner *m_inner;
};

void Rva00657480Holder::set(const char *src)
{
	Rva00655700(m_inner->m_text, 16, src);
}

struct Rva00657470Inner
{
	char m_pad[560];
	unsigned char m_flag;
};

class Rva00657470Holder
{
public:
	void set(unsigned char value);

private:
	char m_pad[4];
	Rva00657470Inner *m_inner;
};

void Rva00657470Holder::set(unsigned char value)
{
	m_inner->m_flag = value;
}

struct Rva006573B0Inner
{
	char m_padA0[0xA0];
	char m_strA[0x41];
	char m_padE1[0x20];
	char m_strB[0x41];
	char m_strC[0x41];
};

class Rva006573B0Holder
{
public:
	void set(const char *a, const char *b, const char *c);

private:
	char m_pad[4];
	Rva006573B0Inner *m_inner;
};

// ?set@Rva006573B0Holder@@QAEXPBD00@Z
void Rva006573B0Holder::set(const char *a, const char *b, const char *c)
{
	Rva00655700(m_inner->m_strA, 0x41, a);
	Rva00655700(m_inner->m_strB, 0x41, b ? b : "");
	Rva00655700(m_inner->m_strC, 0x41, c ? c : "");
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
