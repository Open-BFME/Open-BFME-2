// ?rva006D5690@EAStringC@@QAEPAXPAV1@H@Z
// partial score=0.9 date=2026-10-05
// ?rva006D5690@EAStringC@@QAEPAXPAV1@H@Z
// finish attempt for ?rva006D5690@EAStringC@@QAEPAXPAV1@H@Z @0x006D5690, 215B.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva006D5690@EAStringC@@QAEPAXPAV1@H@Z @0x006D5690 215B (thiscall, ret 8).
// Writes the tail of *this from `offset` into `source`, returning `source`.
// arg1 EAStringC* at [esp+0x18] after the prologue, arg2 the signed int at
// [esp+0x1c]. Class view, empty-singleton handling and the ChangeBuffer /
// FreeData / copy-ctor spellings come from rowed EAStringCRefCount.cpp
// (FreeData 0x006D2EB0, ctor 0x006D2FC0) and EAStringCChangeBuffer.cpp
// (ChangeBuffer 0x006D4AA0).
//
// Retail body, read off the disassembly:
//   - offset <= 0 stores the empty singleton into source and bumps its
//     refcount with a direct `inc word ptr [0x00DDC020]`, returning source;
//   - remaining = m_uSize - offset; a non-positive remaining copy-constructs
//     source from *this through the rowed ctor (mov ecx,esi / call 0x6D2FC0);
//   - otherwise a scoped EAStringC is copy-constructed from *this, grown by
//     ChangeBuffer(offset, remaining, offset, CB_PUSH_ZERO, offset), and
//     source is copy-constructed from it before its data is released.
//
// The ChangeBuffer argument order is read off retail's five pushes at
// 0x6D5711 (esi, 1, esi, edi, esi with esi=offset and edi=remaining): read
// right-to-left at the return address that is (offset, remaining, offset,
// CB_PUSH_ZERO, offset) -- the push-zero flag is the FOURTH parameter, the
// position the rowed ChangeBuffer signature actually declares it in. The
// earlier bank had it second, which called a signature that does not exist
// in the ledger and left the call unresolved.
//
// The two destination writes are placement new on `source` rather than field
// assignment, because retail calls the copy ctor with `source` as the this
// receiver in both the early exit and the general path.
//
// The destructor is defined inline (FreeData(m_pData)) as in the matched
// sibling EAStringCMid.cpp, which is what lets the scoped temporary produce
// the exact push -1 / push handler / mov eax,fs:[0] prologue retail has.
//
// 0x006D4AA0 (ChangeBuffer), 0x006D2EB0 (FreeData) and 0x006D2FC0 (the
// copy-constructor) are all rowed bodies; only the calls are reproduced here.
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)
#include <new.h>

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

private:
	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	void ChangeBuffer(unsigned int uSizeToReserve, unsigned int uOffsetCopy,
		unsigned int uSizeCopy, CBPushZero ePushZero, unsigned int uInternalSize);

public:
	EAStringC(const EAStringC &other);
	EAStringC &operator=(const EAStringC &other);
	~EAStringC()
	{
		FreeData(m_pData);
	}
	void *rva006D5690(EAStringC *source, int offset);
};

extern EAStringC::StringDataC g_eaEmptyStringData;

// ?rva006D5690@EAStringC@@QAEPAXPAV1@H@Z present-unmatched
void *EAStringC::rva006D5690(EAStringC *source, int offset)
{
	if (offset <= 0)
	{
		source->m_pData = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
		return source;
	}

	int remaining = m_pData->m_uSize - offset;
	if (remaining <= 0)
	{
		new (source) EAStringC(*this);
		return source;
	}

	{
		EAStringC result(*this);
		result.ChangeBuffer(offset, remaining, offset, CB_PUSH_ZERO, offset);
		new (source) EAStringC(result);
		FreeData(result.m_pData);
	}
	return source;
}
