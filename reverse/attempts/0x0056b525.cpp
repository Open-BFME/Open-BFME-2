// ??0Rva0056B525@@QAE@PAX00@Z
// partial score=0.93 date=2026-10-06
// cl: /O1 /EHsc /MD
// ??0Rva0056B525@@QAE@PAX00@Z @0x0056B525 116B. Ctor via base 0x0056AD80 then listener register.
// Evidence: calls pinned 0x0056AD80 with arg1; stores arg2/arg3 at +0x18/+0x1C and byte 0 at +0x20;
// two rowed 0x005A0B4C appends of this+0x14 into arg2+8 and arg3+8 lists; caller 0x003F88BC.
class Rva0056AD80
{
public:
	void rva0056AD80(void *arg);
};

struct Rva002BA8F1Listener
{
	~Rva002BA8F1Listener();
	char opaque[4];
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};

struct ListHolder
{
	char m_pad[8];
	Rva005A0B4CList m_list;
};

extern "C" const void *const vtbl_00C3702C[];
extern "C" const void *const vtbl_00C6D40C[];
extern "C" const void *const vtbl_00C6D3D0[];
extern "C" const void *const vtbl_00C6D3BC[];

extern "C" void __cdecl _ReadWriteBarrier();

struct UnwindB
{
	UnwindB() {}
	~UnwindB();
};

class Rva0056B525
{
public:
	Rva0056B525(void *a1, void *a2, void *a3);
private:
	volatile char m_pad[0x14];
	Rva002BA8F1Listener m_listener14;
	volatile void *m_18;
	volatile void *m_1C;
	volatile unsigned char m_20;
	UnwindB m_unwind;
};

// ??0Rva0056B525@@QAE@PAX00@Z present-unmatched
Rva0056B525::Rva0056B525(void *a1, void *a2, void *a3)
{
	((Rva0056AD80 *)this)->rva0056AD80(a1);
	*(volatile unsigned int *)((char *)this + 0x14) = ((unsigned int)vtbl_00C3702C);
	_ReadWriteBarrier();
	*(volatile unsigned int *)this = ((unsigned int)vtbl_00C6D40C);
	*(volatile unsigned int *)((char *)this + 8) = ((unsigned int)vtbl_00C6D3D0);
	*(volatile unsigned int *)((char *)this + 0x14) = ((unsigned int)vtbl_00C6D3BC);
	m_18 = a2;
	m_1C = a3;
	m_20 = 0;
	((ListHolder *)a2)->m_list.append((Rva002BA8F1Listener *)((char *)this + 0x14));
	((ListHolder *)a3)->m_list.append((Rva002BA8F1Listener *)((char *)this + 0x14));
}
