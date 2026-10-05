// ?rva00083D54@Rva00083D54@@QAEXXZ
// partial score=0.723 date=2026-10-05
// ?rva00083D54@Rva00083D54@@QAEXXZ
// partial score=0.72 date=2026-10-05
// ?rva00083D54@Rva00083D54@@QAEXXZ
// cl: /O1 /G7 /Ireference/shims/bfmeterraintracks /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva00083D54@Rva00083D54@@QAEXXZ @ 0x00083D54 264B.
//
// IMPROVED over reverse/attempts/0x00083d54.cpp: LCS 187 -> 191 of 264 against
// the relocation-resolved body, at the 264B retail extent in both cases.
//
// THE ALLOCATION NULL TEST IS NOT A BRANCH ON THE PLACEMENT-NEW SOURCE. The bank
// wrote `if (ibRaw) ib = new (ibRaw) ...`, which makes the constructed pointer
// live in callee-save edi across the operator new call and costs an extra
// `push edi` ABOVE `push 0x18` -- the defect the bank itself named as the sole
// remaining blocker. Retail has no such branch: it allocates unconditionally and
// lets the constructor's own result flow through, testing the RAW BLOCK against
// the persistent zero (mov ecx,eax / mov [ebp-0x14],ecx / cmp ecx,ebx /
// mov [ebp-0x4],ebx / je), with the zero-or-object eax selected by the branch
// afterwards. Writing the placement new as a single unconditional initialiser
// is what reproduces that, and it is byte-identical to folding the raw block
// into the constructor call directly.
//
// MEASURED AND REJECTED this pass, all worse or tied at 187-191: naming the
// lock's flags argument as a local `int flags = 0` rather than a literal (byte
// identical, kept); an explicit `if (ibRaw != 0) ... else ib = 0;` (184B); the
// raw block fed straight into the lock constructor with no `ib` local (183B);
// carrying a running `p` alongside the base (180B); a do/while with the trip
// test at the bottom (190B); a `static`-qualified operator new overload (245B);
// and intranitial bodies for DX8IndexBufferClass's constructor (246B) and for
// WriteLockClass's constructor/destructor (224B). The intranitial attempt is
// worth recording as a negative: it was the one that worked for 0x004320B1, and
// here it is strictly worse, because those constructors carry an SEH frame and
// MSVC 7.1's register allocation for a known-clobbering body is not the one
// retail used. The unlock question is whether `ib` must stay in edi at the
// operator new boundary at all.
// t=25min model=space-bunny-alpha
//
// One terrain snapshot rebuild: release the two existing buffers through
// REF_PTR_RELEASE, allocate a 0x18-byte DX8IndexBufferClass sized
// (m_1C-1)*6, fill six indices per triangle under a scoped
// IndexBufferClass::WriteLockClass, then allocate a 0x20-byte
// BfmeDynamicNativeVB sized (WORD)m_1C * (WORD)m_10C * 2 with base type
// 0x142. All five callees are rowed: __EH_prolog 0x00629188,
// operator new 0x0002FDA0, ??0DX8IndexBufferClass 0x00138980,
// ??0WriteLockClass 0x00138790 / ~~1WriteLockClass 0x00138840, and
// ??0BfmeDynamicNativeVB 0x0013AC00.
//
// Frame: retail's 0x00629188 EH prolog over sub esp,0x14, with `this` in
// esi and ebx reserved as a persistent zero that both REF_PTR_RELEASE
// bodies, the usage argument and the two allocation null tests compare
// against. Both allocations read the global test-data field through
// [0x00DFE758]+0x10C and stash it in [ebp-0x10] for the VB sizing.
//
// The allocation stores the CONSTRUCTOR'S RETURN VALUE into m_4 / m_0
// (mov DWORD PTR [esi+4],eax at 0x83DC9 and mov DWORD PTR [esi],eax at
// 0x83E4F) rather than the raw block the placement new was handed, which
// is why the members are typed as the constructed objects.
//
// The index-fill loop is written the way retail folds it: the store pointer
// is a single running base that advances by six shorts per iteration, so the
// six stores land at p[-1], p[2], p[0], p[4], p[1], p[3] -- retail's exact
// order and offsets -- and the doubled index is the loop counter itself
// (lea ecx,[counter+counter]), which is what keeps MSVC from parking a
// separate doubled index or trip count in a frame slot.
#include <new.h>

typedef unsigned int Uint;
typedef int Int;

class RefCountClass
{
public:
	virtual void Delete_This() {}
	void Release_Ref()
	{
		if (--m_refs == 0)
			Delete_This();
	}
	int m_refs;
};

#define REF_PTR_RELEASE(x) { if (x) { (x)->Release_Ref(); x = 0; } }

class IndexBufferClass : public RefCountClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(IndexBufferClass *b, int flags);
		~WriteLockClass();
		unsigned short *Get_Index_Array() { return indices; }
	private:
		IndexBufferClass *index_buffer;
		unsigned short *indices;
	};
};

class DX8IndexBufferClass : public IndexBufferClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };
	DX8IndexBufferClass(Uint count, UsageType u);
};

class BfmeDynamicNativeVB : public RefCountClass
{
public:
	BfmeDynamicNativeVB(Uint baseType, unsigned short size, Uint flags, Uint pad);
};

// The test-data global the renderer sizes its vertex buffers from: only the
// 0x10C field is touched, through the pointer at 0x00DFE758.
struct TestGlobal
{
	char _pad[0x10C];
	Int m_10C;
};

#define TheTestGlobal (*(TestGlobal **)0x00DFE758)

class Rva00083D54
{
public:
	void rva00083D54();
private:
	BfmeDynamicNativeVB *m_0;
	DX8IndexBufferClass *m_4;
	char _pad08[0x14];
	Int m_1C;
};

// ?rva00083D54@Rva00083D54@@QAEXXZ present-unmatched
void Rva00083D54::rva00083D54()
{
	Int save10C = TheTestGlobal->m_10C;
	REF_PTR_RELEASE(m_4);
	REF_PTR_RELEASE(m_0);

	{
		char *ibRaw = (char *)::operator new(0x18);
		DX8IndexBufferClass *ib = new (ibRaw) DX8IndexBufferClass(
			(Uint)((m_1C - 1) * 6), DX8IndexBufferClass::USAGE_DEFAULT);

		int flags = 0;
		IndexBufferClass::WriteLockClass lock(ib, flags);
		m_4 = ib;
		unsigned short *base = lock.Get_Index_Array();
		for (Int i = 0; i < m_1C - 1; i++, base += 6)
		{
			unsigned short *p = base + 2;
			unsigned short v = (unsigned short)(i + i);
			p[-2] = v;
			p[4] = v;
			p[0] = (unsigned short)(v + 1);
			p[8] = (unsigned short)(v + 2);
			p[2] = (unsigned short)(v + 3);
			p[6] = (unsigned short)(v + 3);
		}
	}

	{
		Uint vbSize = 0;
		char *vbRaw = (char *)::operator new(0x20);
		if (vbRaw)
			vbSize = 1;
		Uint vbBytes = (Uint)((Uint)(unsigned short)m_1C *
			(Uint)(unsigned short)save10C * 2);
		m_0 = (BfmeDynamicNativeVB *)new (vbRaw)
			BfmeDynamicNativeVB(0x142, (unsigned short)vbBytes, vbBytes, 0);
	}
}