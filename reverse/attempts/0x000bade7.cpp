// ?rva000BADE7@Rva000B8F5A@@QAEHPAM@Z
// partial score=0.9072649572649574 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
template<class T> static __forceinline T p4Operand(const T &v) { return *(const volatile T*)&v; }
// ?rva000BADE7@Rva000B8F5A@@QAEHPAM@Z
// partial score=0.88 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
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

struct Rva000B82F9Holder
{
	char m_pad00[0x10C];
	StringBase<char> m_str10C;
	StringBase<char> m_str110;
};

struct Rva000B82F9Item
{
	virtual void DeleteThis();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual int v05();
	int m_refs;
};

struct Rva000B82F9Product
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual Rva000B82F9Item *v32(const char *s, int a);
};

struct Rva000B8F5AOuter
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48();
	virtual Rva000B82F9Product *v49();
	int rva000B8440(float *out, int probe);
	int rva000B89E9(int probe, float *out);
	void rva000BF9FC(void *entry, int a, int b);
	void rva000BEE25(void *entry, float value, int zero, int oneA, int oneB);
	void rva000BFB51(float value);

	Rva000B82F9Holder *m_holder;
	char m_pad08[0x18 - 0x08];
	void *m_18;
	char m_pad1C[0x28C - 0x1C];
	bool m_flag28C;
};

class Rva000B8F5A
{
public:
	void rva000B8F5A(char *a, AsciiString b);
	void rva000BFD77();
	void rva000BFD9F();
	int rva000BADE7(float *out);

private:
	char m_pad00[0x0C];
	void *m_ptr0C;
	char m_pad10[0x94 - 0x10];
	bool m_94;
	char m_pad95[0x98 - 0x95];
	char *m_98;
	char m_pad9C[0xA8 - 0x9C];
	AsciiString m_A8;
	char m_padAC[0x254 - 0xAC];
	StringBase<char> m_sb254;
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

// ?rva000BADE7@Rva000B8F5A@@QAEHPAM@Z @0x000BADE7 216B
// Zeroing float-out probe, twin of 0xBAC53 except the tail: clears *out,
// runs the outer v49 lookup, fills a holder string (+0x10C, or +0x254 when
// empty) through virtual slot 0x80, releases a zero-report item, and returns
// the outer 0xB89E9 tail call on the probe (or zero when it is). The retail
// push order (out, then probe) proves the tail takes (probe, out).
int Rva000B8F5A::rva000BADE7(float *out)
{
	Rva000B8F5AOuter *outer = (Rva000B8F5AOuter *)((char *)this - 12);
	Rva000B82F9Product *prod = outer->v49();
	int result = 0;
	*out = 0.0f;
	if (prod == 0)
		return 0;
	AsciiString tmp;
	if (!m_sb254.isEmpty())
		((StringBase<char> &)tmp).set(m_sb254);
	else
	{
		Rva000B82F9Holder *holder = *(Rva000B82F9Holder **)((char *)this - 8);
		((StringBase<char> &)tmp).set(holder->m_str10C);
	}
	const char *s = tmp.str();
	Rva000B82F9Item *item = prod->v32(s, 0);
	int r;
	if (item != 0)
	{
		r = item->v05();
		if (r == 0)
		{
			if (--item->m_refs == 0)
				item->DeleteThis();
		}
	}
	else
		r = (outer?p4Operand(result):p4Operand(result));
 _ReadWriteBarrier();
	return r != 0 ? outer->rva000B89E9(r, out) : 0;
}