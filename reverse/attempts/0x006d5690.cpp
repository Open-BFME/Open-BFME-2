// ?rva006D5690@EAStringC@@QAEPAXPAV1@H@Z
// partial score=0.94 date=2026-10-05
// ?rva006D5690@EAStringC@@QAEPAXPAV1@H@Z @0x006D5690 215B (thiscall, ret 8).
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// EAStringC::rva006D5690(EAStringC *dest, int offset): writes the tail of *this
// starting at `offset` into `dest`. Arg 1 (the EAStringC*, at [esp+0x18] after the
// prologue) is the destination the caller reads back; arg 2 (the int, at
// [esp+0x1c]) is the signed offset. Class view, empty-singleton handling and the
// ChangeBuffer / FreeData / copy-constructor spellings come from the rowed
// neighbours EAStringCRemoveRange.cpp (0x006D54B0) and EAStringCMid.cpp
// (0x006D5770), whose general path this body shares instruction for instruction
// apart from Mid's extra hidden-return-pointer push.
//
// Retail body, as recovered:
//   - offset <= 0 stores the empty singleton into the destination and bumps its
//     refcount, returning the destination;
//   - remaining = m_uSize - offset; a non-positive remaining copies *this into
//     the destination, sharing the data and bumping its refcount;
//   - otherwise a scoped EAStringC is copy-constructed from *this, grown with
//     ChangeBuffer(offset, 1, offset, remaining, offset), copy-assigned into the
//     destination and its data released with FreeData.
//
// The ChangeBuffer argument order is read off retail's five pushes at 0x6D5711
// (esi, edi, esi, 1, esi with esi=offset and edi=remaining): right-to-left that is
// (offset, 1, offset, remaining, offset), so the declared parameter order puts the
// push-zero flag SECOND, not fourth as the earlier bank had it. That correction
// is what took this body from 211B to an exact 215B.
//
// The SEH frame belongs to the scoped temporary's destructor, so it is left to the
// compiler's automatic unwinder for a class with a non-trivial member rather than
// written as __try: MSVC rejects a __try in a function that requires object
// unwinding (C2712), and a __try body would add a __SEH_prolog call retail does
// not have.
//
// Still unmatched: retail installs the frame with `push -1 / push handler` ahead
// of the fs:[0] read and keeps `this` in ecx with the two offset values in
// esi/edi; MSVC 7.1 hoists `mov eax, fs:[0xBA87E168]` to the front and pushes
// esi/edi for them. Re-measured across /MD, /MT, /EHa, /EHsc, /O1, /Ob1 and
// /GS- -- /O2 is the only size that matches, and no flag combination moves the
// prologue. See reverse/re_attempts.log for the full lever list.
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
	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int ePushZero,
		unsigned int uSizeCopy, unsigned int uOffsetCopy, unsigned int uInternalSize);

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
		source->m_pData = m_pData;
		return source;
	}

	int size = m_pData->m_uSize;
	int remaining = size - offset;
	if (remaining <= 0)
	{
		source->m_pData = m_pData;
		++m_pData->m_uRefCount;
		return source;
	}

	{
		EAStringC result(*this);
		result.ChangeBuffer(offset, 1, offset, remaining, offset);
		*source = result;
		FreeData(result.m_pData);
	}
	return source;
}