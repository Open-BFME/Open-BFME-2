// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// String-slot cluster around 0x000B82F9. Members carry a flag byte, a raw
// name pointer and AsciiString slots; destruction of by-value AsciiString
// parameters emits the shared releaseBuffer worker (0x00036410) through the
// shim destructor, and slot fills go through StringBase::set (0x000366F0)
// via AsciiString::operator= (the operator= inline schedules the member-add
// ahead of the argument push where a direct set call does not).
// Class and member names are address-derived; sibling probes 0xB82F9/0xB83A7
// are banked (epilog load-order wall) with the wider layout, and rejoin here
// when that lever is found.

#include "ascii_string.h"

class Rva000B4BED
{
public:
	void *rva000B4C9D(const void *entry);
	void *rva000B4CBE(const void *entry);
};

struct Rva000B8F5AOuter
{
	void rva000BF9FC(void *entry, int a, int b);
	void rva000BEE25(void *entry, float value, int zero, int oneA, int oneB);
	void rva000BFB51(float value);
	void rva000C0386();

private:
	char m_pad00[0x18];
	void *m_18;
	char m_pad1C[0x28C - 0x1C];
	bool m_flag28C;
};

struct Rva000C144AEntry
{
	void *m_ptr00;
	char m_pad04[0x1C - 0x04];
};

struct Rva000C14BDTarget
{
	virtual void v00();
	virtual void v01();
	virtual const char *v02();
	virtual void *v03();
};

class Rva000B8F5A
{
public:
	AsciiString rva000C146D(int i);
	void rva000B8F5A(char *a, AsciiString b);
	void rva000BFD77();
	void rva000BFD9F();
	int rva000C144A();
	void *rva000C14BD(int i);

private:
	char m_pad00[0x0C];
	void *m_ptr0C;
	char m_pad10[0x94 - 0x10];
	bool m_94;
	char m_pad95[0x98 - 0x95];
	char *m_98;
	char m_pad9C[0xA8 - 0x9C];
	AsciiString m_A8;
	char m_padAC[0x104 - 0xAC];
	Rva000C144AEntry m_entries104[3];
	char m_pad158[0x258 - 0x158];
	char m_pad258[0x280 - 0x258];
	bool m_flag280;
};

// ?rva000B8F5A@Rva000B8F5A@@QAEXPADVAsciiString@@@Z @0x000B8F5A 71B
void Rva000B8F5A::rva000B8F5A(char *a, AsciiString b)
{
	m_98 = a;
	m_94 = false;
	m_A8 = b;
}

// ?rva000BFB51@Rva000B8F5AOuter@@QAEXM@Z @0x000BFB51 37B
// Refill setter: when the +0x18 entry is live, clears the +0x28C flag first
// and refills through the outer 0xBEE25 body with (entry, value, 0, 1, 1).
void Rva000B8F5AOuter::rva000BFB51(float value)
{
	void *entry = m_18;
	if (entry != 0)
	{
		m_flag28C = false;
		rva000BEE25(entry, value, 0, 1, 1);
	}
}

// ?rva000BFD77@Rva000B8F5A@@QAEXXZ @0x000BFD77 40B
// Table-probe refill: looks the +0x0C entry up in the outer table; on a hit
// raises the +0x280 flag first and refills through the outer 0xBF9FC body.
void Rva000B8F5A::rva000BFD77()
{
	void *e = (*(Rva000B4BED **)((char *)this - 8))->rva000B4C9D(m_ptr0C);
	if (e != 0)
	{
		m_flag280 = true;
		((Rva000B8F5AOuter *)((char *)this - 12))->rva000BF9FC(e, 1, 0);
	}
}

// ?rva000BFD9F@Rva000B8F5A@@QAEXXZ @0x000BFD9F 40B
// Twin of 0xBFD77 through the get-next sibling probe (0xB4CBE).
void Rva000B8F5A::rva000BFD9F()
{
	void *e = (*(Rva000B4BED **)((char *)this - 8))->rva000B4CBE(m_ptr0C);
	if (e != 0)
	{
		m_flag280 = true;
		((Rva000B8F5AOuter *)((char *)this - 12))->rva000BF9FC(e, 1, 0);
	}
}

// ?rva000C144A@Rva000B8F5A@@QAEHXZ @0x000C144A 35B
// Leading-live counter: runs the outer 0xC0386 probe, then counts the
// leading non-null +0x104 entries (3 x 0x1C, testing the first pointer).
int Rva000B8F5A::rva000C144A()
{
	((Rva000B8F5AOuter *)((char *)this - 12))->rva000C0386();
	unsigned n = 0;
	Rva000C144AEntry *e = m_entries104;
	do
	{
		if (e->m_ptr00 == 0)
			break;
		n++;
		e++;
	} while (n < 3);
	return n;
}

// ?rva000C14BD@Rva000B8F5A@@QAEPAXH@Z @0x000C14BD 56B
// Indexed entry fetch: runs the outer 0xC0386 probe, bounds-checks the
// index against the 3 x 0x1C +0x104 entries, and returns the entry target's
// slot-3 virtual (or null when out of range or empty).
void *Rva000B8F5A::rva000C14BD(int i)
{
	((Rva000B8F5AOuter *)((char *)this - 12))->rva000C0386();
	if (i < 0 || (unsigned)i >= 3)
		return 0;
	Rva000C144AEntry *e = &m_entries104[i];
	// Volatile view: retail tests the slot in memory (cmp [eax],0) and
	// reloads it for the call instead of forwarding one load.
	Rva000C144AEntry volatile *ve = e;
	if (ve->m_ptr00 == 0)
		return 0;
	return ((Rva000C14BDTarget *)ve->m_ptr00)->v03();
}

// ?rva000C146D@Rva000B8F5A@@QAE?AVAsciiString@@H@Z @0x000C146D 80B
// Returns a string by value: runs the outer 0xC0386 probe; when the index hits
// a live +0x104 entry, builds it from the entry target's slot-2 text (0x37BA0),
// otherwise returns an empty string. The return-object flag at [ebp-4] is the
// by-value return; indexing the entry twice keeps retail's test-then-reload.
AsciiString Rva000B8F5A::rva000C146D(int i)
{
	((Rva000B8F5AOuter *)((char *)this - 12))->rva000C0386();
	if (i >= 0 && (unsigned)i < 3)
	{
		if (m_entries104[i].m_ptr00 != 0)
			return AsciiString(((Rva000C14BDTarget *)m_entries104[i].m_ptr00)->v02());
	}
	return AsciiString();
}
