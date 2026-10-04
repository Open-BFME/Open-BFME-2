// ?rva006D5690@EAStringC@@QAEPAXPAV1@H@Z
// partial score=0.8 date=2026-10-04
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// /MD alone, matching the sibling EAStringCRemoveRange.cpp: retail installs its
// SEH frame with the `push -1 / push handler` pair ahead of the fs:[0] read,
// which is the shape /EHa and /EHsc both reorder.
// ?rva006D5690@@YAXPAVEAStringC@@H@Z @0x006D5690 215B (cdecl).
//
// EAStringC assignment from a source string and a start offset, sitting just
// above the rowed remove-range body 0x006D54B0 in EAStringCRemoveRange.cpp,
// which establishes the class view (m_pData at +0, StringDataC's
// m_uRefCount/m_uSize/m_uMaxSize/m_uHash), the empty-singleton handling and the
// ChangeBuffer / FreeData / copy-constructor spellings reused here.
//
// Retail body:
//   - a non-positive offset empties the destination through the empty singleton
//     (store the singleton pointer, bump its refcount) and returns this;
//   - otherwise the remaining length is size - offset; a non-positive remainder
//     copy-constructs the destination from the source and returns this;
//   - the general path builds the result in a scoped EAStringC: the tail from
//     `offset` onward is grown into it with ChangeBuffer(size - offset, offset,
//     1, CB_PUSH_ZERO, size - offset), the scoped temporary is copy-constructed
//     into the destination, and its data is released by FreeData.
//
// The SEH frame belongs to the scoped temporary's destructor, the same pairing
// EAStringCRemoveRange.cpp and Rva006e9730Cluster.cpp both record, so it is left
// to the compiler's automatic unwinder for a class with a non-trivial member
// rather than written as __try: MSVC rejects a __try in a function that requires
// object unwinding (C2712), and a __try body would add a __SEH_prolog call that
// retail does not have.
//
// 0x006D4AA0 (ChangeBuffer), 0x006D2EB0 (FreeData) and 0x006D2FC0 (the
// copy-constructor) are all rowed bodies; only the calls are reproduced here.

extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)

class EAStringC
{
public:
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	static void FreeData(StringDataC *data);

	StringDataC *m_pData;

	EAStringC(const EAStringC &other);
	EAStringC();
	EAStringC &operator=(const EAStringC &other);
	~EAStringC();

private:
	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
		unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize);

public:
	void *rva006D5690(EAStringC *source, int offset);
};

extern EAStringC::StringDataC g_eaEmptyStringData;

void *EAStringC::rva006D5690(EAStringC *source, int offset)
{
	if (offset <= 0)
	{
		m_pData = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
		return this;
	}

	int size = m_pData->m_uSize;
	int remaining = size - offset;
	if (remaining <= 0)
	{
		*this = *source;
		return this;
	}

	{
		// Retail copy-constructs a local from `this`, grows it with
		// ChangeBuffer, copy-constructs `this` from a second local, and hands
		// that second local's data to FreeData.
		EAStringC copy(*this);
		copy.ChangeBuffer(remaining, offset, offset, CB_PUSH_ZERO, 1);
		*this = copy;
		FreeData(copy.m_pData);
	}
	return this;
}