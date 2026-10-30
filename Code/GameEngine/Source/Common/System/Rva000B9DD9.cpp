// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// ?rva000B9DD9@Rva000B9DD9@@QAEXABVAsciiString@@@Z 0x000B9DD9 233B
// Evidence: leaf slot 19 offset 0x4C of 6 W3D Draw vtables Horde Quadruped Supply Truck Tank Sail; prev own 0x000B9C8C; Shadow::ShadowTypeInfo ctor (0x00079514) set dtor (0x000793FA) rows; StringBase isEmpty set rows; TheProjectedShadowManager vcall slot 0xC; m_5c vcall slot 8.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "ascii_string.h"

class AudioManager0029E159;
class ProjectedShadowManager;
extern ProjectedShadowManager *TheProjectedShadowManager;	// retail singleton at VA 0x00DEC2D4

struct Rva000B9DD9Node
{
	void *m00;
	void *m04;
};

struct Rva000B9DD9Inner
{
	void *m00;
	Rva000B9DD9Node *m04;
};

struct Rva000B9DD9Cached
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
};

struct Rva000B9DD9Mgr
{
	virtual void m0();
	virtual void m1();
	virtual void m2();
	virtual void *m3(void *a, void *b, int c, int d);
};

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		ShadowTypeInfo();
		~ShadowTypeInfo();
		AsciiString m_first;
		AsciiString m_second;
		int m08;
		float m0c;
		float m10;
		float m14;
		float m18;
		float m1c;
		float m20;
		unsigned char m24;
		unsigned char m25;
		unsigned char m26;
	};
};

struct Rva000B9DD9Floats
{
	char m_pad[0x4e8];
	float m4e8;
	float m4ec;
	float m4f0;
	float m4f4;
};

class Rva000B9DD9
{
public:
	void rva000B9DD9(const AsciiString &s);
private:
	char m_pad00[0x8];
	Rva000B9DD9Inner *m08;
	char m_pad0c[0x49 - 0x0c];
	unsigned char m49;
	unsigned char m4a;
	unsigned char m4b;
	char m_pad4c[0x50 - 0x4c];
	void *m50;
	char m_pad54[0x5c - 0x54];
	Rva000B9DD9Cached *m5c;
};

void Rva000B9DD9::rva000B9DD9(const AsciiString &asciiString)
{
	if (m5c != 0)
		m5c->v2();
	m5c = 0;
	if (((const StringBase<char> &)asciiString).isEmpty())
		return;
	Rva000B9DD9Floats *f = (Rva000B9DD9Floats *)m08->m04;
	Shadow::ShadowTypeInfo ev;
	ev.m25 = 0;
	ev.m26 = 1;
	ev.m08 = 0x20;
	((StringBase<char> &)ev.m_first).set((const StringBase<char> &)asciiString);
	ev.m0c = f->m4e8;
	ev.m10 = f->m4ec;
	ev.m14 = f->m4f0;
	ev.m18 = f->m4f4;
	Rva000B9DD9Mgr *mgr = (Rva000B9DD9Mgr *)TheProjectedShadowManager;
	if (mgr != 0)
		m5c = (Rva000B9DD9Cached *)mgr->m3(m50, &ev, 1, 0);
	if (m5c != 0)
	{
		unsigned char a49 = m49;
		*(unsigned char *)((char *)m5c + 5) = a49;
		unsigned char b;
		if (m4a != 0 && m4b == 0)
			b = 1;
		else
			b = 0;
		Rva000B9DD9Cached *shadow = m5c;
		*(unsigned char *)((char *)shadow + 4) = b;
	}
}
