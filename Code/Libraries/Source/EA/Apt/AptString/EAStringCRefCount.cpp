// cl: /O2 /DNDEBUG /MD /D_CRTIMP=
// ?FreeData@EAStringC@@SAXPAVStringDataC@1@@Z, retail 0x006D2EB0 (118B).
// EA refcounted-string release worker: asserts the data refcount is live,
// drops it, and returns while shared; the last release frees the block
// through the sized deallocator at 0x006DB270 unless it is the immortal
// empty singleton at 0x00DDC020 (which trips the empty assertion).
// Assertion strings name .\string\EAString.inl; the empty-singleton
// evidence is the retail "(char *)pData != s_EmptyInternalData" message.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void __debugbreak();
#pragma intrinsic(__debugbreak)
#pragma intrinsic(memcmp)

#include <string.h>
#pragma intrinsic(memcpy)
#pragma intrinsic(strlen)
#pragma intrinsic(memset)
#pragma intrinsic(strcmp)

unsigned short __cdecl hashLower(const char *text);

#include "../../../../../GameEngine/Include/Common/Rva006DB270.h"

class Rva006DB270; extern Rva006DB270 *g_pChainBlockAllocator;

class Rva006DB160
{
public:
	void *allocBlock(int blockSize);
};

// Same pool instance, allocation side (companion pin to the freeBlock
// pin above). Matched DIR32 sites place this pointer at VA 0x00E176E8; its
// four retail bytes are zero, so it starts null.
// 0x00A176E8 (g_aptPoolAllocator here before) is the allocator declared above.

#include "../../../Apt/EAStringC.h"

// Retail empty singleton at VA 0x00DDC020: the eight-byte StringDataC header
// is { refCount=0x0101, size=0, maxSize=0, hash=0 } in game.dat. Callers use
// this object as the immortal empty-string sentinel.
EAStringC::StringDataC g_eaEmptyStringData = { 0x0101, 0, 0, 0 };

// ?FreeData@EAStringC@@SAXPAVStringDataC@1@@Z
void EAStringC::FreeData(StringDataC *current)
{
	if (!(current->m_uRefCount >= 1)) {
		g_bfmeAptAssertAtE17734("pData->m_uRefCount >= 1", ".\\string\\EAString.inl", 0xF9);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();}
	}
	if (--current->m_uRefCount != 0)
		return;
	if (current == &g_eaEmptyStringData) {
		g_bfmeAptAssertAtE17734("(char *)pData != s_EmptyInternalData", ".\\string\\EAString.inl", 0xFD);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();}
	}
	g_pChainBlockAllocator->freeBlock(current, (int)(current->m_uMaxSize + 9));
}

// ??1EAStringC@@QAE@XZ, retail 0x006D3010 (10B). Scalar destructor: releases
// the shared data through FreeData. Retail is the bare 10-byte
// load-push-call-cleanup shape with no vtable work (EAStringC is a
// value class); the release call resolves via the FreeData row.
inline EAStringC::~EAStringC()
{
	FreeData(data);
}

// ??0EAStringC@@QAE@ABV0@@Z, retail 0x006D2FC0 (70B). Copy constructor:
// shares the source data after validating its refcount, then takes its
// own reference. The empty singleton skips validation but still AddRefs.
__declspec(noinline) inline EAStringC::EAStringC(const EAStringC &other)
{
	StringDataC *otherData = other.data;
	data = otherData;
	if (otherData != &g_eaEmptyStringData) {
		if (!(otherData->m_uRefCount <= 0xFFFE)) {
			g_bfmeAptAssertAtE17734("m_pData->m_uRefCount <= 0xfffe", ".\\string\\EAString.inl", 0xE1);
			if (g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();}
		}
	}
	data->m_uRefCount++;
}

// ??4EAStringC@@QAEAAV0@ABV0@@Z, retail 0x006D3030 (85B). Assignment:
// validates and AddRefs the new data first (the source pointer survives
// in edi across the release call), then releases the old data and
// stores. Keeping the source object (not just its data pointer) in a
// named local is what pins retail's edi/esi allocation.
EAStringC &EAStringC::operator=(const EAStringC &other)
{
	const EAStringC *src = &other;
	if (src->data != &g_eaEmptyStringData) {
		if (!(src->data->m_uRefCount <= 0xFFFE)) {
			g_bfmeAptAssertAtE17734("m_pData->m_uRefCount <= 0xfffe", ".\\string\\EAString.inl", 0xE1);
			if (g_bfmeAptBreakOnAssertAtDDC01C) {__asm int 3}
		}
	}
	src->data->m_uRefCount++;
	FreeData(data);
	data = src->data;
	return *this;
}

// ?clear@EAStringC@@QAEAAV1@XZ, retail 0x006D2F90 (16B). Resets to the
// empty singleton with its own reference; chained (returns *this), which
// is what keeps the opening mov eax,ecx in retail's shape. Name is a
// semantic pick: the body takes no arguments and only re-roots m_pData.
EAStringC &EAStringC::clear()
{
	EAStringC *self = this;
	self->data = &g_eaEmptyStringData;
	g_eaEmptyStringData.m_uRefCount++;
	return *self;
}

// ?Reserve@EAStringC@@QAEXH@Z, retail 0x006D3760 (127B). Buffer
// allocator: validates the request, rounds it to a 4-byte pitch over
// the 8-byte header, and installs a fresh refcount-1 block from the
// global pool. Both bound checks are unsigned (ja/jb). The re-read of
// m_pData before the max-size store is load-bearing: without it the
// compiler forwards the freshly stored pointer and the tail rotates.
__declspec(noinline) inline void EAStringC::Reserve(int size)
{
	EAStringC *self = this;
	if (!((unsigned)size > 0u)) {
		g_bfmeAptAssertAtE17734("uSize > 0", ".\\string\\EAString.inl", 0x4CB);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();}
	}
	int rounded = (size + 12) & ~3;
	if (!((unsigned)rounded < 0xFFFFu)) {
		g_bfmeAptAssertAtE17734("uAllocateSize < 0xffff", ".\\string\\EAString.inl", 0x4D2);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();}
	}
	StringDataC *current = (StringDataC *)(*(Rva006DB160 * *)&g_pChainBlockAllocator)->allocBlock(rounded);
	self->data = current;
	current->m_uRefCount = 1;
	current = self->data;
	current->m_uMaxSize = (unsigned short)(rounded - 9);
}

// ??0EAStringC@@QAE@PBD@Z, retail 0x006D4C80 (25B). C-string constructor:
// roots a null data pointer, then delegates the whole build to Assign
// (rowed separately; pinned here until that row lands). Returning this
// in eax is the standard ctor epilogue.
inline EAStringC::EAStringC(const char *text)
{
	data = 0;
	Assign(text);
}

// ??0EAStringC@@QAE@I@Z, retail 0x006D45F0 (71B). Reserve constructor:
// roots null, empty size re-roots the immortal singleton, otherwise
// Reserve plus SetSize(0) plus hash-zero plus terminator. Donor is
// open-bfme-1 Code/Libraries/Source/EA/Apt/AptString/EAStringCReserveCtor.cpp
// (EAStringC(unsigned int), same empty-vs-reserve split); retail routes the
// allocate path through rowed Reserve 0x006D3760 and SetSize 0x006D3BC0.
// Callers at 0x006D4744/0x006D48F7/0x006D4FFA/0x006D51F8/0x006D75C5;
// neighbours rva006D4190 and ChangeBuffer share /O2 /DNDEBUG /MD.
__declspec(noinline) inline EAStringC::EAStringC(unsigned int nSize)
{
	data = 0;
	if (nSize) {
		Reserve(nSize);
		SetSize(0);
		data->m_uHash = 0;
		reinterpret_cast<char *>(data)[sizeof(StringDataC)] = 0;
	} else {
		data = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
	}
}

// ??0EAStringC@@QAE@II@Z, retail 0x006D4640 (114B). Fill constructor:
// reserve nSize bytes, repeat the low byte of fillChar, then set the logical
// size, clear the cached hash, and append the terminator. Target calls the
// rowed Reserve and SetSize methods; its two-argument ctor pin proves identity.
EAStringC::EAStringC(unsigned int fillChar, unsigned int nSize)
{
	data = 0;
	if (nSize) {
		Reserve(nSize);
		memset(reinterpret_cast<char *>(data) + sizeof(StringDataC),
			(int)fillChar, nSize);
		SetSize((int)nSize);
		data->m_uHash = 0;
		reinterpret_cast<char *>(data)[sizeof(StringDataC) + nSize] = 0;
	} else {
		data = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
	}
}

// ?GetAt@EAStringC@@QBEHH@Z, retail 0x006D3020 (13B). Sign-extending
// character fetch from the internal buffer (the movsx proves an int
// result, not a char one). No calls or data references.
int EAStringC::GetAt(int index) const
{
	return reinterpret_cast<char *>(data)[sizeof(StringDataC) + index];
}

// ?IsEmpty@EAStringC@@QBE_NXZ, retail 0x006D2F30 (14B). Tests whether
// the string is the shared empty singleton by pointer comparison; the
// xor-then-sete shape is the canonical bool return.
bool EAStringC::IsEmpty() const
{
	return data == &g_eaEmptyStringData;
}

// ?IsEqualTo@EAStringC@@QBE_NPBV1@@Z, retail 0x006D3090 (54B). Compares
// two refcounted strings by handle: size mismatch is false, shared data
// is true, otherwise an intrinsic memcmp over the text. Name is a
// semantic pick: the body takes a string pointer and returns a bool with
// no side effects; the 23 Apt callers all pass string objects.
bool EAStringC::IsEqualTo(const EAStringC *other) const
{
	unsigned int otherSize = other->data->m_uSize;
	unsigned int ownSize = data->m_uSize;
	if (ownSize != otherSize)
		return false;
	StringDataC *ownData = data;
	StringDataC *otherData = other->data;
	if (ownData == otherData)
		return true;
	return memcmp(ownData + 1, otherData + 1, ownSize) == 0;
}

// ?Assign@EAStringC@@QAEXPBD@Z, retail 0x006D4BF0 (144B, abuts the 25B
// PBD ctor at 0x006D4C80). C-string assignment: null text trips the
// EAString.cpp assert, empty text re-roots the immortal singleton, and
// anything else is measured with intrinsic strlen, reserved, sized and
// copied with its terminator (length + 1) via intrinsic memcpy.
void EAStringC::Assign(const char *text)
{
	if (text == 0) {
		g_bfmeAptAssertAtE17734("pStrText != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x82F);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();}
	}
	if (*text == 0) {
		data = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
		return;
	}
	unsigned int length = strlen(text);
	Reserve(length);
	SetSize(length);
	data->m_uHash = 0;
	memcpy((char *)data + sizeof(StringDataC), text, length + 1);
}

// ?Rva006D4F00Append@EAStringC@@QAEAAV1@ABV1@@Z, retail 0x006D4F00 (105B).
// String append: an empty target delegates to assignment, an empty source
// is a no-op, otherwise the buffer grows through ChangeBuffer and the
// source text (terminator included) lands via intrinsic memcpy.
EAStringC &EAStringC::Rva006D4F00Append(const EAStringC &other)
{
	unsigned int oldSize = data->m_uSize;
	if (oldSize == 0) {
		operator=(other);
		return *this;
	}
	unsigned int otherSize = other.data->m_uSize;
	if (otherSize == 0)
		return *this;
	unsigned int newSize = oldSize + otherSize;
	ChangeBuffer(newSize, 0, oldSize, CB_NO_PUSH_ZERO, newSize);
	memcpy((char *)data + sizeof(StringDataC) + oldSize,
		(char *)other.data + sizeof(StringDataC), otherSize + 1);
	return *this;
}

// ?rva006D2F40@EAStringC@@QBEGXZ, retail 0x006D2F40, 70 bytes. Ghidra's
// 62-byte range stops exactly at the target's short-branch landing at +0x3E;
// that landing contains the remaining hash-read return path through +0x45.
// The next Ghidra function starts at +0x50.
// EAStringC hash accessor: returns the cached m_uHash word at +6, asserting
// it is non-zero via the EAString.inl 0x184 "m_pData->m_uHash != 0" check.
// Donor BFME1 EAStringCAssign.cpp proves StringDataC carries unsigned short
// m_uHash; callers at 0x0070ACD4/0x0070AFC5/0x0070DC1A/0x0070DC86/0x0070DDCC
// /0x0070DE8C plus 0x006D3708/0x006D3712 consume the hash; neighbours
// IsEmpty 0x006D2F30 and clear 0x006D2F90 live in this TU.
// The compiler memory barrier at the debugger trap keeps the reload
// after the breakpoint like retail; intrinsic hoists the load above int3
// (SetSize 0x006D3BC0 precedent, proven blocker).
unsigned short EAStringC::rva006D2F40() const
{
	if (!(data->m_uHash != 0)) {
		g_bfmeAptAssertAtE17734("m_pData->m_uHash != 0", ".\\string\\EAString.inl", 0x184);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			_ReadWriteBarrier(); __debugbreak(); _ReadWriteBarrier();
		}
	}
	return data->m_uHash;
}

// ?rva006D30D0@EAStringC@@QBE_NPBV1@@Z, retail 0x006D30D0, 83 bytes.
// EAStringC inequality: logical negation of IsEqualTo in this TU; the 83B
// verbose bool shape (xor/test/sete/mov per return) is the inlined !IsEqualTo
// (56B IsEqualTo at 0x006D3090 plus outer !), not a hand-rolled compare.
// Callers at 0x006CC682/0x006EC123/0x006EE7F0/0x006EE808/0x006EEA9D/0x006EEB7E
// pass string objects; neighbours IsEqualTo 0x006D3090 and compare family
// at 0x006D3130 live in this cluster. Honest address name; identity is
// class plus sibling pattern.
bool EAStringC::rva006D30D0(const EAStringC *other) const
{
	return !IsEqualTo(other);
}

// ?rva006D3470@EAStringC@@QAEXXZ, retail 0x006D3470, 29 bytes.
// EAStringC release-to-empty: frees the shared data through FreeData
// (rowed 0x006D2EB0 in this TU), then re-roots to the empty singleton
// at 0x00DDC020 with its own reference. Callers at 0x006CFC68/0x006DA115
// /0x006DD6EE/0x006FD712/0x006FD71B/0x007016A2/0x0070B2FA/0x0070DB90 plus
// jmp 0x006D6CB2; neighbours IsEqualTo 0x006D3090 and rva006D30D0 live
// in this TU. Honest address name; void return proves it is not clear.
void EAStringC::rva006D3470()
{
	FreeData(data);
	data = &g_eaEmptyStringData;
	g_eaEmptyStringData.m_uRefCount++;
}

// ?rva006D3490@EAStringC@@QBE_NPBD@Z, retail 0x006D3490, 125 bytes.
// EAStringC C-string equality: asserts pStrText non-null via EAString.inl
// 0x3A6, then compares the internal buffer (+8) with the C-string through
// intrinsic strcmp inlined as a 2-byte unrolled loop with sbb -1/0/1 tail
// plus outer ! for bool. Callers at 0x006DE21C/0x006DE24C/0x006E95A5
// /0x006E9607/0x006EAB54/0x006EAB90/0x006EABCC/0x0070DC2B; neighbours
// rva006D3470 and compare family live in this cluster. Honest address
// name; PBD signature proves C-string overload.
bool EAStringC::rva006D3490(const char *text) const
{
	if (!(text != 0)) {
		g_bfmeAptAssertAtE17734("pStrText != NULL", ".\\string\\EAString.inl", 0x3A6);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();}
	}
	const char *a = (const char *)data + 8;
	return strcmp(a, text) == 0;
}

// ?rva006D3C20@EAStringC@@QAEXXZ, retail 0x006D3C20 (61B). EAStringC
// release-to-null: asserts IsValid() when null (EAString.inl 0x517) via the
// shared Apt triple, then frees through rowed FreeData and nulls m_pData.
// Callers at 0x0070A883/0x0070A978/0x0070AA18; neighbours SetSize and
// utf8EncodedLength share /O2 /DNDEBUG /MD. Honest address name.
void EAStringC::rva006D3C20()
{
	if (data == 0) {
		g_bfmeAptAssertAtE17734("IsValid()", ".\\string\\EAString.inl", 0x517);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			__debugbreak();
		}
	}
	FreeData(data);
	data = 0;
}

// ?rva006D3C60@EAStringC@@QAEXXZ, retail 0x006D3C60 (57B). EAStringC
// null-expecting re-root to empty: asserts IsValid()==false when non-null
// (EAString.inl 0x52E), then installs the immortal singleton with its own
// reference. Callers at 0x006CF2CB/0x0070B69D; same flags and TU.
// Honest address name.
void EAStringC::rva006D3C60()
{
	if (data != 0) {
		g_bfmeAptAssertAtE17734("IsValid() == false", ".\\string\\EAString.inl", 0x52E);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			_ReadWriteBarrier(); __debugbreak(); _ReadWriteBarrier();
		}
	}
	data = &g_eaEmptyStringData;
	++g_eaEmptyStringData.m_uRefCount;
}

// ?rva006D3CA0@EAStringC@@QAEXPBV1@@Z, retail 0x006D3CA0 (107B). EAStringC
// null-expecting share: asserts IsValid()==false when this is non-null
// (EAString.inl 0x545), takes the source data, validates its refcount
// (EAString.inl 0xE1, empty singleton skips) and AddRefs. Callers at
// 0x0070AE98/0x0070AEED/0x0070AF2F in one Apt string worker; neighbours
// rva006D3C60 and utf8EncodedLength share /O2 /DNDEBUG /MD. Honest
// address name; void plus const-string-pointer from ret-4 plus data flow.
void EAStringC::rva006D3CA0(const EAStringC *other)
{
	if (data != 0) {
		g_bfmeAptAssertAtE17734("IsValid() == false", ".\\string\\EAString.inl", 0x545);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			_ReadWriteBarrier(); __debugbreak(); _ReadWriteBarrier();
		}
	}
	StringDataC *src = other->data;
	data = src;
	if (src != &g_eaEmptyStringData) {
		if (!(src->m_uRefCount <= 0xFFFE)) {
			g_bfmeAptAssertAtE17734("m_pData->m_uRefCount <= 0xfffe", ".\\string\\EAString.inl", 0xE1);
			if (g_bfmeAptBreakOnAssertAtDDC01C) {
				_ReadWriteBarrier(); __debugbreak(); _ReadWriteBarrier();
			}
		}
	}
	++data->m_uRefCount;
}

// ?GetInternalRefCount@EAStringC@@QBEIXZ, retail 0x006D2E10 (6B). EAStringC
// internal refcount accessor: returns m_pData->m_uRefCount zero-extended.
// Caller at 0x0070DB62 proves the name via assert
// "saConstant[i].GetInternalRefCount() == 1" in StringPool.cpp;
// sibling GetInternalMaxSize pattern proves unsigned-int const accessor;
// neighbours FreeData 0x006D2EB0 and rva006D2F40 share /O2 /DNDEBUG /MD.
unsigned int EAStringC::GetInternalRefCount() const
{
	return data->m_uRefCount;
}

// ?SetInternalRefCount@EAStringC@@QAEXI@Z, retail 0x006D2E20 (80B). Gap body
// right after GetInternalRefCount: asserts "uRefCount <= 0xffff"
// (EAString.inl 0xB1, retail strings) and stores the low word as the data
// refcount; retail triplicates the store tail (the native debugger memory barrier keeps
// the store after the breakpoint, as in rva006D2F40). The setter spelling mirrors the
// proven GetInternalRefCount and the assert's parameter name (inference).
void EAStringC::SetInternalRefCount(unsigned int uRefCount)
{
	if (!(uRefCount <= 0xFFFF)) {
		g_bfmeAptAssertAtE17734("uRefCount <= 0xffff", ".\\string\\EAString.inl", 0xB1);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			_ReadWriteBarrier(); __debugbreak(); _ReadWriteBarrier();
		}
	}
	data->m_uRefCount = (unsigned short)uRefCount;
}

// ?rva006D3510@EAStringC@@QBE_NPBD@Z, retail 0x006D3510, 71 bytes.
// EAStringC C-string case-insensitive equality: asserts pStrText non-null
// via EAString.inl 0x3D1, then compares the internal buffer (+8) with the
// C-string through _strcmpi (rowed thunk 0x00629A2A) plus ==0 bool tail.
// Callers at 0x006D8361/0x006D8375/0x006D8389/0x006D839D/0x006D83B1/0x006D83C5
// in one Apt string worker; neighbours rva006D3490 (strcmp 125B) and
// rva006D3560 share /O2 /DNDEBUG /MD. Honest address name; PBD proves
// C-string overload and _strcmpi proves case-insensitive.
bool EAStringC::rva006D3510(const char *text) const
{
	if (!(text != 0)) {
		g_bfmeAptAssertAtE17734("pStrText != NULL", ".\\string\\EAString.inl", 0x3D1);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();}
	}
	const char *a = (const char *)data + 8;
	return _strcmpi(a, text) == 0;
}

// ?rva006D3560@EAStringC@@QBE_NPBV1@@Z, retail 0x006D3560, 57 bytes.
// EAStringC case-insensitive equality: size mismatch is false, shared data
// is true, otherwise _strcmpi over the text (+8) plus ==0 bool tail.
// Callers at 0x006DDE93/0x006DDEA9/0x0070024D/0x00700263/0x00704606;
// neighbours rva006D3490 and rva006D3510 share /O2 /DNDEBUG /MD.
// Honest address name; PBV1 proves string-pointer overload.
bool EAStringC::rva006D3560(const EAStringC *other) const
{
	StringDataC *otherData = other->data;
	StringDataC *ownData = data;
	if (ownData->m_uSize != otherData->m_uSize)
		return false;
	if (ownData == otherData)
		return true;
	// Preserve the byte-sized result used by retail's AL boolean tail.
	unsigned char same = _strcmpi((const char *)ownData + 8, (const char *)otherData + 8) == 0;
	return same;
}

// ?Rva006D50A0Append@EAStringC@@QAEAAV1@PBD@Z, retail 0x006D50A0 (191B).
// EAStringC C-string append: empty target delegates to PBD assign via a
// temp plus operator=, empty source is a no-op, otherwise the buffer grows
// through ChangeBuffer and the text (terminator included) lands via
// intrinsic memcpy. Callers at 0x006D9737/0x006DDED2/0x006DDEEE plus Apt
// workers; neighbours Rva006D4F00Append 0x006D4F00 and bfmeAppendVKG
// 0x006D52A0 share /O2 /DNDEBUG /MD. Honest address name; PBD proves
// C-string overload, sibling Rva006D4F00Append proves Append identity.
EAStringC &EAStringC::Rva006D50A0Append(const char *text)
{
	unsigned int oldSize = data->m_uSize;
	if (oldSize == 0) {
		EAStringC tmp(text);
		operator=(tmp);
		return *this;
	}
	unsigned int len = strlen(text);
	if (len == 0)
		return *this;
	unsigned int newSize = oldSize + len;
	ChangeBuffer(newSize, 0, oldSize, CB_NO_PUSH_ZERO, newSize);
	memcpy((char *)data + sizeof(StringDataC) + oldSize, text, len + 1);
	return *this;
}

// ?rva006D3D10@EAStringC@@QBEGXZ, retail 0x006D3D10 (152B).
// EAStringC hash refresh: recomputes m_uHash via rowed hashLower 0x006D3800
// over the text (+8) and stores it; empty hash asserts non-zero on return
// (EAString.inl 0x59D), non-empty asserts stability against the entry old
// hash (EAString.inl 0x5A4). Callers at 0x0070A7CC/0x0070A802/0x0070B2DB
// /0x0070B38B/0x0070B43D; neighbours rva006D3CA0 0x006D3CA0 and
// utf8EncodedLength 0x006D3DB0 share /O2 /DNDEBUG /MD. Honest address name;
// const ushort return plus hashLower call prove hash accessor.
unsigned short EAStringC::rva006D3D10() const
{
	StringDataC *current = data;
	unsigned short oldHash = current->m_uHash;
	if (oldHash == 0) {
		current->m_uHash = hashLower((const char *)current + 8);
		if (!(data->m_uHash != 0)) {
			g_bfmeAptAssertAtE17734("m_pData->m_uHash != 0", ".\\string\\EAString.inl", 0x59D);
			if (g_bfmeAptBreakOnAssertAtDDC01C) {
				__debugbreak(); _ReadWriteBarrier();
			}
		}
	} else {
		current->m_uHash = hashLower((const char *)current + 8);
		if (!(data->m_uHash == oldHash)) {
			g_bfmeAptAssertAtE17734("m_pData->m_uHash == uOldHash", ".\\string\\EAString.inl", 0x5A4);
			if (g_bfmeAptBreakOnAssertAtDDC01C) {
				__debugbreak();
			}
		}
	}
	return data->m_uHash;
}

// ?rva006D3750@EAStringC@@QBEIXZ, retail 0x006D3750 (7B). EAStringC
// internal size accessor: returns m_pData->m_uSize zero-extended.
// 40+ callers; sibling GetInternalRefCount 0x006D2E10 proves unsigned-int
// const accessor pattern (movzx); neighbours compare 0x006D36C0 and
// Reserve 0x006D3760 share /O2 /DNDEBUG /MD. Honest address name.
unsigned int EAStringC::rva006D3750() const
{
	return data->m_uSize;
}

// ?rva006D3BA0@EAStringC@@QBEXXZ, retail 0x006D3BA0 (21B). EAStringC
// hash store: recomputes m_uHash via rowed hashLower 0x006D3800 over
// the text (+8) and stores it unconditionally. Caller at 0x0070DC7F;
// neighbours Find 0x006D38E0 and SetSize 0x006D3BC0 share /O2 /DNDEBUG
// /MD. Honest address name; const since only pointee is modified.
void EAStringC::rva006D3BA0() const
{
	StringDataC *current = data;
	current->m_uHash = hashLower((const char *)current + 8);
}

// ?rva006D36F0@EAStringC@@QBE_NPBV1@@Z, retail 0x006D36F0 (82B). EAStringC
// case-insensitive equality with hash short-circuit: shared data is true
// then rowed hash accessor 0x006D2F40 on both sides must match then
// _strcmpi over the text (+8) plus ==0 bool tail. Callers at 0x0070AD14
// /0x0070ADFF/0x0070AE64/0x0070AFFF/0x0070B0EF/0x0070B143; neighbours
// compare 0x006D36C0 and Reserve 0x006D3760 share /O2 /DNDEBUG /MD.
// Honest address name; PBV1 proves string-pointer overload.
bool EAStringC::rva006D36F0(const EAStringC *other) const
{
	if (data == other->data)
		return true;
	if (rva006D2F40() != other->rva006D2F40())
		return false;
	return _strcmpi((const char *)data + 8, (const char *)other->data + 8) == 0;
}


// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1S4Mem005864A0@@QAE@XZ=??1EAStringC@@QAE@XZ")
#pragma comment(linker, "/alternatename:??1S4Mem005879C0@@QAE@XZ=??1EAStringC@@QAE@XZ")

// Inline empty construction is shared by the native Left return path.
inline EAStringC::EAStringC()
{
	data = &g_eaEmptyStringData;
	++data->m_uRefCount;
}

// ?Left@EAStringC@@QBE?AV1@H@Z
// EAString.cpp donor Left semantics; native 0x006D55B0 independently proves
// signed count, hidden value-result argument, shared copies and ChangeBuffer.
// The donor name is supported by that complete operation and sibling usage.
EAStringC EAStringC::Left(int count) const
{
	if (count <= 0) return EAStringC();
	if ((unsigned)count >= data->m_uSize) return *this;
	EAStringC text(*this);
	text.ChangeBuffer(count, 0, count, CB_PUSH_ZERO, count);
	return text;
}

// BF1 9cbfb551fe EAStringCUtf8Suffix.cpp supplies the empty-initialization
// semantics. Complete native 6D2FA0..6D2FB2 is INT3-bounded and initializes
// the same pointer and real singleton as adjacent rowed EAStringC::clear.
// The original constructor/method spelling and unused argument type remain
// unresolved; this address-named initializer models its 32-bit ignored slot
// and receiver return, without a guessed constructor identity or new class.
EAStringC *EAStringC::initializeEmpty_Rva006D2FA0(unsigned int)
{
    data = &g_eaEmptyStringData;
    ++g_eaEmptyStringData.m_uRefCount;
    return this;
}

// ?rva006D59F0@EAStringC@@QAEAAV1@PBD@Z, retail 0x006D59F0 (348B).
// EAString donor semantics and retail call graph: trim leading characters
// found in the supplied set (the scan counts the prefix whose characters
// strchr finds, then keeps Mid(count)); callers at 0x006D5CC1 and 0x00708A77.
// Several remaining assertion sites use an opaque inline-assembly barrier:
// plain __debugbreak can change reloads or temporary frame slots in callers.
// Intrinsic repairs are retained individually only after every body in this
// unit verifies; the FreeData repair preserves these callers byte for byte.
EAStringC &EAStringC::rva006D59F0(const char *text)
{
	if (!text) {
		g_bfmeAptAssertAtE17734("pStrText != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x56E);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();}
	}
	unsigned i, size = data->m_uSize;
	const char *buffer = (const char *)(data + 1);
	for (i = 0; i < size; ++i) {
		char c = *buffer++;
		if (strchr(text, c) == 0) break;
	}
	EAStringC result;
	result = Mid(i);
	*this = result;
	return *this;
}

// ?TrimRight@EAStringC@@QAEAAV1@PBD@Z, retail 0x006D5B50 (352B). Mirror of
// rva006D59F0 from the end: counts the trailing characters found in the set
// (backward strchr scan) and keeps Left(size - count) through a result temp;
// EAString.cpp assert 0x59A (target strings). Name from the EAString donor
// family (TrimLeft/TrimRight pair); the body is the right-hand trim.
EAStringC &EAStringC::TrimRight(const char *text)
{
	if (!text) {
		g_bfmeAptAssertAtE17734("pStrText != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp", 0x59A);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {__debugbreak();}
	}
	unsigned i, size = data->m_uSize;
	const char *buffer = (const char *)(data + 1) + size - 1;
	for (i = 0; i < size; ++i) {
		char c = *buffer--;
		if (strchr(text, c) == 0) break;
	}
	EAStringC result;
	result = Left(size - i);
	*this = result;
	return *this;
}
