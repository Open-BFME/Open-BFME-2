// ?rva00083D54@Rva00083D54@@QAEXXZ
// partial score=0.93 date=2026-10-05
// ?rva00083D54@Rva00083D54@@QAEXXZ
// finish attempt for ?rva00083D54@Rva00083D54@@QAEXXZ @0x00083D54, 264B.
// cl: /O1 /G7 /Ireference/shims/bfmeterraintracks /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva00083D54@Rva00083D54@@QAEXXZ @ 0x00083D54 264B.
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
// The index-fill loop is written the way retail folds it: the loop counter
// lives in edi and the doubled base is recomputed each iteration as
// `lea ecx,[edi+edi]`, with v+1 and v+3 both materialised in edx and v+2
// produced by `add ecx,2`. The store pointer is biased one element so that
// `p[-1]` is the first index and the six stores land at p[-1], p[2], p[0],
// p[4], p[1], p[3] -- retail's exact order and offsets.
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
		void *ibRaw = ::operator new(0x18);
		DX8IndexBufferClass *ib = (DX8IndexBufferClass *)ibRaw;
		if (ibRaw)
			ib = new (ibRaw) DX8IndexBufferClass(
				(Uint)((m_1C - 1) * 6), DX8IndexBufferClass::USAGE_DEFAULT);

		IndexBufferClass::WriteLockClass lock(ib, 0);
		m_4 = ib;
		Int trip = m_1C - 1;
		for (Int i = 0; i < trip; i++)
		{
			unsigned short *p = lock.Get_Index_Array() + i * 6 + 1;
			unsigned short v = (unsigned short)(i + i);
			unsigned short v1 = (unsigned short)(v + 1);
			unsigned short v3 = (unsigned short)(v + 3);
			p[-1] = v;
			p[2] = v;
			p[0] = v1;
			p[4] = (unsigned short)(v + 2);
			p[1] = v3;
			p[3] = v3;
		}
	}

	{
		Uint vbSize = 0;
		void *vbRaw = ::operator new(0x20);
		if (vbRaw)
			vbSize = 1;
		Uint vbBytes = (Uint)((Uint)(unsigned short)m_1C *
			(Uint)(unsigned short)save10C * 2);
		m_0 = (BfmeDynamicNativeVB *)new (vbRaw)
			BfmeDynamicNativeVB(0x142, (unsigned short)vbBytes, vbBytes, 0);
	}
}