// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Open-BFME5: BoxDynamicVBAccessClass::~BoxDynamicVBAccessClass, retail
// 0x0091D9E0, 79 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// In BFME2 (0x0013A780) it is DynamicVBAccessClass::~DynamicVBAccessClass:
// Flush_Sorting_Pool (0x0012E8C0) constructs [esp+38h] with
// DynamicVBAccessClass::DynamicVBAccessClass (0x0013B040) and destroys the same
// object here, and the body sits with that class's _Deinit, WriteLock and _Reset.
//
// It is WW3D's dynamic vertex-buffer release, with one BFME change: the
// dynamic-DX8 arm indexes a pair of globals by the slot at +8 rather than
// using single variables, so this build keeps several dynamic buffers rather
// than one. The sorting arm still uses the plain pair of globals.
//
// The two arms also order their stores differently -- the indexed arm clears
// the in-use flag first, the sorting arm adds the count first -- and the
// indexed arm reloads the slot from +8 for the second global rather than
// keeping it, because the store to the first may alias it.
//
// The release at the end is the ordinary reference-count drop: the buffer has
// its vtable at +0 and its count at +4, and slot 0 is called with no argument
// when the count reaches zero.

typedef unsigned short UnsignedShort;

// The matched target-side deinit traverses 15 slots; the adjacent
// bfmeDynamicVBs table at VA 0x00DF2A04 rules out the 21-slot donor view.
enum { BFME_MAX_DYNAMIC_BUFFERS = 15 };

class BfmeDynamicVertexBuffer
{
public:
	virtual void bfmeDeleteThis(void);			// vtable slot 0

	int m_bfmeNumRefs;					// +0x04

	void bfmeReleaseRef(void)
	{
		--m_bfmeNumRefs;
		if (m_bfmeNumRefs == 0)
			bfmeDeleteThis();
	}
};

extern bool BfmeDynamicDX8VertexBufferInUse[BFME_MAX_DYNAMIC_BUFFERS];		// 0x01346740
extern UnsignedShort BfmeDynamicDX8VertexBufferOffset[BFME_MAX_DYNAMIC_BUFFERS];	// 0x01346794
// BFME2 retail zero-filled .data storage. Matched DIR32 witnesses pin both
// starts; the shared 15-slot deinit and adjacent arrays bound these extents.
bool BfmeDynamicDX8VertexBufferInUse[BFME_MAX_DYNAMIC_BUFFERS];		// VA 0x00DF29F0, RVA 0x009F29F0
UnsignedShort BfmeDynamicDX8VertexBufferOffset[BFME_MAX_DYNAMIC_BUFFERS];	// VA 0x00DF2A44, RVA 0x009F2A44
extern UnsignedShort BfmeDynamicSortingVertexArrayOffset;			// 0x013467E4
// BfmeDynamicSortingVertexArrayOffset: VA 0xdf2a94 (zero-filled .bss).
UnsignedShort BfmeDynamicSortingVertexArrayOffset;
extern bool BfmeDynamicSortingVertexArrayInUse;					// 0x013467D8
// BfmeDynamicSortingVertexArrayInUse: VA 0xdf2a88 (zero-filled .bss).
bool BfmeDynamicSortingVertexArrayInUse;

enum { BFME_BUFFER_TYPE_DYNAMIC_DX8 = 2 };

class DynamicVBAccessClass
{
public:
	~DynamicVBAccessClass(void);

private:
	int m_bfmeField00;					// +0x00
	int m_bfmeType;						// +0x04
	int m_bfmeSlot;						// +0x08
	int m_bfmeField0C;					// +0x0C
	UnsignedShort m_bfmeVertexCount;			// +0x10
	UnsignedShort m_bfmeField12;
	BfmeDynamicVertexBuffer *m_bfmeVertexBuffer;		// +0x14
};

// ??1DynamicVBAccessClass@@QAE@XZ
DynamicVBAccessClass::~DynamicVBAccessClass(void)
{
	if (m_bfmeType == BFME_BUFFER_TYPE_DYNAMIC_DX8)
	{
		BfmeDynamicDX8VertexBufferInUse[m_bfmeSlot] = false;
		BfmeDynamicDX8VertexBufferOffset[m_bfmeSlot] =
			(UnsignedShort)(BfmeDynamicDX8VertexBufferOffset[m_bfmeSlot] + m_bfmeVertexCount);
	}
	else
	{
		BfmeDynamicSortingVertexArrayOffset =
			(UnsignedShort)(BfmeDynamicSortingVertexArrayOffset + m_bfmeVertexCount);
		BfmeDynamicSortingVertexArrayInUse = false;
	}

	if (m_bfmeVertexBuffer)
	{
		m_bfmeVertexBuffer->bfmeReleaseRef();
		m_bfmeVertexBuffer = 0;
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1BfmeSortingVBAccess@@QAE@XZ=??1DynamicVBAccessClass@@QAE@XZ")
