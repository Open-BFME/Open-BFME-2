// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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
};

class Rva000B8F5A
{
public:
	void rva000B8F5A(char *a, AsciiString b);
	void rva000BFD77();
	void rva000BFD9F();

private:
	char m_pad00[0x0C];
	void *m_ptr0C;
	char m_pad10[0x94 - 0x10];
	bool m_94;
	char m_pad95[0x98 - 0x95];
	char *m_98;
	char m_pad9C[0xA8 - 0x9C];
	AsciiString m_A8;
	char m_padAC[0x258 - 0xAC];
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
