// ?rva005D20C1@Rva005D20C1@@QAEXXZ
// partial score=0.9 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// Twins 2x36B: 0x005D1CAF and 0x005D20C1.
// Empty 0x00B3FD0 (reuses pinned empty), then hybrid-bool forward:
// b is a full dword (union int/members) whose high bytes are garbage
// (caller entry garbage or middle-return high) and only b.c[0] is
// meaningful; the pinned Last takes int and reads only the low byte,
// so no normalization is emitted: test al,al / mov al,1 / push eax.
// Middles are pinned this-only int getters (0x0056A989 / 0x00318F42).
// Ret void, this only. Address-derived.
class Rva000B3FD0Empty
{
public:
	void rva000B3FD0Empty();
};

class Rva0056A989
{
public:
	int rva0056A989();
};

class Rva00318F42
{
public:
	int rva00318F42();
};

class Rva005CCB7B
{
public:
	void rva005CCB7B(int b);
};

class Rva005D1CAF
{
public:
	void rva005D1CAF();
protected:
	unsigned char m_pad[0x14];
	Rva0056A989 *m_14;
};

void Rva005D1CAF::rva005D1CAF()
{
	unsigned char b;
	Rva0056A989 *o;
	((Rva000B3FD0Empty *)this)->rva000B3FD0Empty();
	o = m_14;
	if (!o)
		goto set1;
	b = o->rva0056A989();
	if (b == 0)
		goto push;
set1:
	b = 1;
push:
	((Rva005CCB7B *)this)->rva005CCB7B(b);
}

class Rva005D20C1
{
public:
	void rva005D20C1();
protected:
	unsigned char m_pad[0x14];
	Rva00318F42 *m_14;
};

void Rva005D20C1::rva005D20C1()
{
	unsigned char b;
	Rva00318F42 *o;
	((Rva000B3FD0Empty *)this)->rva000B3FD0Empty();
	o = m_14;
	if (!o)
		goto set1;
	b = o->rva00318F42();
	if (b == 0)
		goto push;
set1:
	b = 1;
push:
	((Rva005CCB7B *)this)->rva005CCB7B(b);
}
