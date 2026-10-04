// ??0Rva0035E00F@@QAE@XZ
// cl: /O1 /MD
//
// ??0Rva0035E00F@@QAE@XZ @0x0035E206 86B: derived ctor calling base
// ??0Rva001DBAA4 at 0x001DBAA4. Layout from FamilyTailDtors1DBAC3.cpp
// (Rva0035E00F: base members +4/+8/+9/+0xA/+0xC, derived +0x10/+0x14/+0x28/
// +0x4C window) plus the zeroed ranges the body touches. Caller at 0x0035E29A
// proves ctor shape; vtable 0x00816594 same as dtor 0x0035E25C slot family.
//
// Three levers, each independently pinned by measurement, reproduce retail's
// store order:
//   __declspec(novtable) stops the compiler emitting its own vptr store so the
//     explicit one names the existing vtable proven at retail VA 0x00C16594
//     through a linker alias, so it follows the linked table;
//   writing m_18 through a pointer splits the +0x10..+0x24 eax run into two
//     nodes, which is what lets m_14 and the vtable store land in between
//     rather than the whole run hoisting above the literal 5;
//   reading m_14 back right after m_48 (not at the end) makes the reload use
//     ecx, matching retail's 8b 4e 14 / 89 4e 04 instead of an eax CSE.
extern "C" const void *const vtbl_00C16594[];  // ??_7Rva0035E00F@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C16594=??_7Rva0035E00F@@6B@")

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_4;
	bool m_8;
	bool m_9;
	bool m_A;
	int m_C;
};
class __declspec(novtable) Rva0035E00F : public Rva001DBAA4
{
public:
	virtual ~Rva0035E00F();
	Rva0035E00F();
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;
};
Rva0035E00F::Rva0035E00F()
{
	int *p28 = &m_28;
	int *p14 = &m_14;
	m_10 = 0;
	m_14 = 5;
	*(unsigned int *)this = ((unsigned int)vtbl_00C16594);
	int *p18 = &m_18;
	*p18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_24 = 0;
	*p28 = -1;
	m_2C = 0;
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_3C = 0;
	m_40 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4 = *p14;
	m_4C = 0;
	m_C = 0;
	m_9 = true;
}
