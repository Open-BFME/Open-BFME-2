// ?rva0031996D@Rva003193EC@@QAEPAXPAPAXABV?$StringBase@D@@@Z
// partial score=0.9 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva00319904@Rva003193EC@@QAEXPAV1@@Z @0x00319904 32B
// Method of Rva003193EC (this+arg are Rva003193EC* proven by rowed second
// callee 0x003198B8 ?rva003198B8@Rva003193EC@@QAEXPAV1@@Z). Drains other's
// +0x78 Rva0040ECCF entry list into this +0x78 via rowed
// 0x0040ED4F ?rva0040ED4F@Rva0040ECCF@@QAEXAAV1@@Z then forwards to rva003198B8.
// Evidence: packet disasm ret-4 single ptr arg plus callers 0x002B4A8D 0x002B672F.
#include "ascii_string.h"

class Rva0040ECCF
{
public:
	void rva0040ED4F(Rva0040ECCF &other);
	char m_pad00[0x40];
	struct RvaEntry *m_begin;
	struct RvaEntry *m_end;
};

struct RvaEntry
{
	int first;
	int second;
};

class Rva0040CB2CIndexedField
{
public:
	int get(int index) const;
};

class Rva0040CC0EIndexedField
{
public:
	int get(int index) const;
};

class Rva0040CBD7Vec
{
public:
	void rva0040CBD7(void **out, int value);
};

class Rva003193EC
{
public:
	void rva003198B8(Rva003193EC *other);
	void rva00319904(Rva003193EC *other);
	void *rva0031996D(void **out, const StringBase<char> &key);
private:
	char m_pad00[0x78];
	Rva0040ECCF *m_78;
};

void Rva003193EC::rva00319904(Rva003193EC *other)
{
	m_78->rva0040ED4F(*other->m_78);
	rva003198B8(other);
}

// ?rva0031996D@Rva003193EC@@QAEPAXPAPAXABV?$StringBase@D@@@Z @0x0031996D 101B
// Searches m_78 8-byte entries backwards for second field whose +4 StringBase
// matches key via rowed compare; forwards matching (or entry 0) first field
// to rowed vec append with out. Evidence: retail loop with getSecond 0x40CB2C
// compare StringBase and getFirst 0x40CC0E plus vec pin 0x40CBD7; caller
// 0x002B3A9C passes out and +0x18 key; class +0x78 from neighbours.
void *Rva003193EC::rva0031996D(void **out, const StringBase<char> &key)
{
	Rva0040ECCF *vec = m_78;
	int endBytes = *(int *)((char *)vec + 0x44);
	int *beginSlot = (int *)((char *)vec + 0x40);
	int total = (endBytes - *beginSlot) >> 3;
	int idx = total;
	int value;
	goto check;
loop:
	{
		int second = ((Rva0040CB2CIndexedField *)m_78)->get(idx);
		if (((const StringBase<char> *)(second + 4))->compare(key) == 0)
		{
			value = ((Rva0040CC0EIndexedField *)m_78)->get(idx);
			goto emit;
		}
	}
check:
	--idx;
	if (idx >= 0)
		goto loop;
	{
		Rva0040ECCF *after = m_78;
		value = ((Rva0040CC0EIndexedField *)after)->get(0);
		((Rva0040CBD7Vec *)after)->rva0040CBD7(out, value);
		return out;
	}
emit:
	((Rva0040CBD7Vec *)m_78)->rva0040CBD7(out, value);
	return out;
}
