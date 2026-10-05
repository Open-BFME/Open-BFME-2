// ?rva00083D54@Rva00083D54@@QAEXXZ
// partial score=0.94 date=2026-10-05
// cl: /O1 /G7 /Ireference/shims/bfmeterraintracks /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
//
// ?rva00083D54@Rva00083D54@@QAEXXZ @ 0x00083D54 264B, retail rebuild of the
// renderer's index buffer and vertex buffer for one terrain snapshot: release
// the two existing buffers, allocate a 0x18-byte DX8IndexBufferClass sized
// (m_1C-1)*6, fill it with 6 indices per triangle through a scoped
// WriteLockClass, then allocate a 0x20-byte BfmeDynamicNativeVB whose second
// argument is (WORD)m_1C * (WORD)m_10C * 2. Both allocations go through the test
// allocator 0x0002FDA0, which retail calls directly (push size / call / pop
// ecx / mov ecx,eax) with the null-result branch inline -- an `operator new`
// spelling emits its own throwing new-handler tail instead, which is what an
// earlier bank did and why it compiled 322B against a 264B target.
//
// The frame is retail's 0x00629188 EH prolog (mov eax,0xB5FA6E; call
// __EH_prolog) over sub esp,0x14; the scoped WriteLockClass and the two
// RefCountClass releases are what install it.
//
// The index-fill loop is written the way retail folds it: the loop counter i
// lives in edi and the doubled base is recomputed each iteration as
// `lea ecx,[edi+edi]`, with v+1 and v+3 both materialised in edx and v+2
// produced by `add ecx,2`. The store pointer is biased one element so that
// `p[-1]` is the first index and the six stores land at p[-1], p[2], p[0], p[4],
// p[1], p[3] -- retail's exact order and offsets.
typedef unsigned int Uint;
typedef int Int;
// The test allocator, called directly rather than through `operator new`.
void *__cdecl bfmeTestOperatorNew(Uint s);
typedef unsigned short UShort;

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
class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock();
	~BFMEDX8DeviceLock();
};
class IndexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(IndexBufferClass *b, int flags);
		~WriteLockClass();
		UShort *Get_Index_Array() { return m_indices; }
	private:
		IndexBufferClass *m_buf;
		UShort *m_indices;
		BFMEDX8DeviceLock m_lock;
	};
};
class DX8IndexBufferClass : public RefCountClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };
	DX8IndexBufferClass(Uint count, UsageType u);
private:
	char _t[0x10];
};
class BfmeDynamicNativeVB : public RefCountClass
{
public:
	void rva00083D54Ctor(Uint a, UShort b, Uint c, Uint d);
private:
	char _t[0x18];
};
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
	RefCountClass *m_0;
	RefCountClass *m_4;
	char _pad08[0x14];
	Int m_1C;
};
// ?rva00083D54@Rva00083D54@@QAEXXZ present-unmatched
void Rva00083D54::rva00083D54()
{
	Int save10C = TheTestGlobal->m_10C;
	REF_PTR_RELEASE(m_4);
	REF_PTR_RELEASE(m_0);
	DX8IndexBufferClass *ib = new DX8IndexBufferClass((m_1C - 1) * 6, DX8IndexBufferClass::USAGE_DEFAULT);
	m_4 = ib;
	{
		IndexBufferClass::WriteLockClass lock((IndexBufferClass *)ib, 0);
		UShort *p = lock.Get_Index_Array() + 1;
		for (Int i = 0; i < m_1C - 1; i++)
		{
			UShort v = (UShort)(i + i);
			UShort v1 = (UShort)(v + 1);
			UShort v3 = (UShort)(v + 3);
			p[-1] = v;
			p[2] = v;
			p[0] = v1;
			p[4] = (UShort)(v + 2);
			p[1] = v3;
			p[3] = v3;
			p += 6;
		}
	}
	void *raw = bfmeTestOperatorNew(0x20);
	if (raw)
	{
		BfmeDynamicNativeVB *vb = (BfmeDynamicNativeVB *)raw;
		vb->rva00083D54Ctor(0x142, (UShort)((UShort)m_1C * (UShort)save10C * 2), 1, 0);
		m_0 = vb;
	}
}