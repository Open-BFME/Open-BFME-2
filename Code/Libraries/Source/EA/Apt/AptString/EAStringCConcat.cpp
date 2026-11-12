// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??HEAStringC@@QBE?AV0@ABV0@@Z
// Retail 0x006D46C0..0x006D47EC (300 bytes).
// EAStringC concatenation returning a new string: an empty receiver returns
// a copy of the other string and an empty other string returns a copy of the
// receiver; otherwise a string reserved for the summed size (rowed
// EAStringC(unsigned) 0x006D45F0) receives both texts with intrinsic memcpy
// and a terminator and its logical size is set (rowed SetSize 0x006D3BC0)
// before it is copied out (rowed copy ctor 0x006D2FC0) and released (rowed
// FreeData 0x006D2EB0 through the inline destructor as in EAStringCMid.cpp).
// Target fact kept as found: the cached hash word (+6) that is cleared is the
// receiver's (the saved this pointer is reloaded for it) not the result's.
// The operator name is a semantic pick from the body (receiver-left
// concatenation by value; ret 8 = hidden result + other); flags follow the
// EAStringCMid.cpp sibling.
#define _CRTIMP // retail calls the linked CRT bodies directly
#include <string.h>
#undef _CRTIMP
#pragma intrinsic(memcpy)

// Use the real CRT declarations; retain the existing intrinsic selections.


#pragma intrinsic(strlen)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DB270;
extern Rva006DB270 *g_pChainBlockAllocator;
#include "../../../../../GameEngine/Include/Common/Rva006DB160.h"

#include "../../../Apt/EAStringC.h"

// The four existing native helpers must be visible together: the sized
// constructor follows Reserve and SetSize; the return copy reads that result.
// This proves the local string does not escape and lets cl preserve its data
// pointer across the copy. Each helper independently retains its whole retail
// body and relocations. SetSize keeps its original assertion barrier.
extern char g_eaEmptyStringData[16];

// Retail inlines these members in this unit; the header keeps them out of line.
inline EAStringC::EAStringC(const char *text) : data(0)
{
	Assign(text);
}

inline EAStringC::~EAStringC()
{
	FreeData(data);
}

inline unsigned int EAStringC::GetInternalMaxSize() const
{
	return data->m_uMaxSize;
}

__declspec(noinline) inline EAStringC::EAStringC(const EAStringC &other)
{
	StringDataC *otherData = other.data;
	data = otherData;
	if (otherData != (EAStringC::StringDataC *)g_eaEmptyStringData) {
		if (!(otherData->m_uRefCount <= 0xFFFE)) {
			g_bfmeAptAssertAtE17734("m_pData->m_uRefCount <= 0xfffe", ".\\string\\EAString.inl", 0xE1);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
	}
	data->m_uRefCount++;
}
__declspec(noinline) inline EAStringC::EAStringC(unsigned int nSize)
{
	data = 0;
	if (nSize) {
		Reserve(nSize);
		SetSize(0);
		data->m_uHash = 0;
		reinterpret_cast<char *>(data)[sizeof(StringDataC)] = 0;
	} else {
		data = (EAStringC::StringDataC *)g_eaEmptyStringData;
		++((EAStringC::StringDataC *)g_eaEmptyStringData)->m_uRefCount;
	}
}
__declspec(noinline) inline void EAStringC::Reserve(int size)
{
	EAStringC *self = this;
	if (!((unsigned)size > 0u)) {
		g_bfmeAptAssertAtE17734("uSize > 0", ".\\string\\EAString.inl", 0x4CB);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	int rounded = (size + 12) & ~3;
	if (!((unsigned)rounded < 0xFFFFu)) {
		g_bfmeAptAssertAtE17734("uAllocateSize < 0xffff", ".\\string\\EAString.inl", 0x4D2);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	StringDataC *current = (StringDataC *)(*(Rva006DB160 * *)&g_pChainBlockAllocator)->allocBlock(rounded);
	self->data = current;
	current->m_uRefCount = 1;
	current = self->data;
	current->m_uMaxSize = (unsigned short)(rounded - 9);
}
__declspec(noinline) inline void EAStringC::SetSize(int uSize)
{
	if (!(uSize <= GetInternalMaxSize())) {
		g_bfmeAptAssertAtE17734("uSize <= GetInternalMaxSize()", ".\\string\\EAString.inl", 0x5C);
		if (g_bfmeAptBreakOnAssertAtDDC01C) {
			__asm int 3
		}
	}
	data->m_uSize = (unsigned short)uSize;
}
void EAStringC::setCapacityWord_Rva006D2E00(unsigned int value)
{
    data->m_uMaxSize = (unsigned short)value;
}

EAStringC EAStringC::operator+(const EAStringC &other) const
{
	unsigned int size = data->m_uSize;
	if (size == 0)
		return other;
	unsigned int otherSize = other.data->m_uSize;
	if (otherSize == 0)
		return *this;
	unsigned int total = size + otherSize;
	EAStringC result(total);
	const char *source = (char *)data + sizeof(StringDataC);
	char *text = (char *)result.data + sizeof(StringDataC);
	memcpy(text, source, size);
	memcpy(text + size, (char *)other.data + sizeof(StringDataC), otherSize);
	text[size + otherSize] = 0;
	result.SetSize(total);
	data->m_uHash = 0;
	return result;
}

// Native 6D4F70..6D509D: right C-string concatenation. Same layout and
// ownership as the verified 300-byte overload; no volatile pointer workaround.
EAStringC EAStringC::operator+(const char *other) const
{
	unsigned int size = data->m_uSize;
	if (size == 0)
		return other;
	unsigned int otherSize = strlen(other);
	if (otherSize == 0)
		return *this;
	unsigned int total = size + otherSize;
	EAStringC result(total);
	char *text = (char *)(result.data + 1);
	memcpy(text, (char *)data + sizeof(StringDataC), size);
	memcpy(text + size, other, otherSize);
	text[size + otherSize] = 0;
	result.SetSize(total);
	data->m_uHash = 0;
	return result;
}

// Native 6D5160..6D5292: left C-string concatenation. The caller at 6FF980
// supports the argument order and return ABI; the original name is unknown.
EAStringC rva006D5160(const char *left, const EAStringC &right)
{
	unsigned int size = right.data->m_uSize;
	if (size == 0)
		return EAStringC(left);
	unsigned int otherSize = strlen(left);
	if (otherSize == 0)
		return right;
	unsigned int total = otherSize + size;
	EAStringC result(total);
	char *text = (char *)result.data + sizeof(EAStringC::StringDataC);
	memcpy(text, left, otherSize);
	memcpy(text + otherSize, (char *)right.data + sizeof(EAStringC::StringDataC), size);
	text[otherSize + size] = 0;
	EAStringC *presult = &result;
	presult->SetSize(total);
	presult->data->m_uHash = 0;
	return *presult;
}

// Native 6D47F0..6D4A9C (685 bytes incl. RET 8): non-overlapping substring
// replacement returning the replacement count. Target evidence: the
// "pStrOld != NULL" / "pStrNew != NULL" / "pStrOccurence != NULL" asserts
// at EAString.cpp lines 0x3B4, 0x3B5 and 0x3E7, the only caller 0x006D5580
// (Replace("<char>", "") on a one-character string), and the rowed sized
// constructor 0x006D45F0 and FreeData 0x006D2EB0 calls. The EAString.inl
// size install (line 0x5C, clearing the hash) and copy assignment (line
// 0xE1) are inlined in retail. WB 0x01775230 guides the shape; the original
// member name is not proven, so the address-derived name stays.
#define STRING_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\string\\EAString.cpp"
#define STRING_INL ".\\string\\EAString.inl"
static __forceinline void aptAssert(const char *test, const char *file, int line)
{
	g_bfmeAptAssertAtE17734(test, file, line);
	if (g_bfmeAptBreakOnAssertAtDDC01C) {
		__asm int 3
	}
}
static __forceinline void setSizeAndClearHash(EAStringC &eAStringC, unsigned int n)
{
	EAStringC::StringDataC *p = eAStringC.data;
	if (n > p->m_uMaxSize)
		aptAssert("uSize <= GetInternalMaxSize()", STRING_INL, 0x5C);
	p->m_uSize = (unsigned short)n;
	p->m_uHash = 0;
}
// Keep the native inlined assignment (EAString.inl line 0xE1) without
// emitting a competing external copy of the separately recovered 0x006D3030
// operator= in EAStringCRefCount.
static __forceinline void assignShared(EAStringC &self, const EAStringC &s)
{
	if (s.data != (EAStringC::StringDataC *)g_eaEmptyStringData && s.data->m_uRefCount > 0xFFFE)
		aptAssert("m_pData->m_uRefCount <= 0xfffe", STRING_INL, 0xE1);
	++s.data->m_uRefCount;
	EAStringC::FreeData(self.data);
	self.data = s.data;
}
int EAStringC::rva006D47F0(const char *oldString, const char *newString)
{
	if (!oldString)
		aptAssert("pStrOld != NULL", STRING_FILE, 0x3B4);
	if (!newString)
		aptAssert("pStrNew != NULL", STRING_FILE, 0x3B5);
	unsigned int oldLength = strlen(oldString);
	if (!oldLength)
		return 0;
	unsigned int newLength = strlen(newString);
	int count = 0;
	const char *src = (reinterpret_cast<char *>(data) + sizeof(StringDataC));
	const char *occurrence;
	while ((occurrence = strstr(src, oldString)) != 0) {
		++count;
		src = occurrence + oldLength;
	}
	if (!count)
		return 0;
	int resultSize = data->m_uSize + (newLength - oldLength) * count;
	EAStringC result(resultSize);
	src = (reinterpret_cast<char *>(data) + sizeof(StringDataC));
	char *start;
	char *dest = start = (reinterpret_cast<char *>(result.data) + sizeof(StringDataC));
	for (int i = 0; i < count; ++i) {
		occurrence = strstr(src, oldString);
		if (!occurrence)
			aptAssert("pStrOccurence != NULL", STRING_FILE, 0x3E7);
		unsigned int prefix = occurrence - src;
		if (prefix) {
			memcpy(dest, src, prefix);
			dest += prefix;
		}
		src = occurrence + oldLength;
		memcpy(dest, newString, newLength);
		dest += newLength;
	}
	unsigned int remaining = resultSize - (dest - start);
	if (remaining) {
		memcpy(dest, src, remaining);
		dest += remaining;
	}
	*dest = 0;
	setSizeAndClearHash(result, resultSize);
	assignShared(*this, result);
	return count;
}
