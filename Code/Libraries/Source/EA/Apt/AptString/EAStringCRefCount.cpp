// cl: /O2 /DNDEBUG /MD
// ?FreeData@EAStringC@@SAXPAVStringDataC@1@@Z, retail 0x006D2EB0 (118B).
// EA refcounted-string release worker: asserts the data refcount is live,
// drops it, and returns while shared; the last release frees the block
// through the sized deallocator at 0x006DB270 unless it is the immortal
// empty singleton at 0x00DDC020 (which trips the empty assertion).
// Assertion strings name .\string\EAString.inl; the empty-singleton
// evidence is the retail "(char *)pData != s_EmptyInternalData" message.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#pragma intrinsic(memcmp)

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);
extern "C" void *__cdecl memcpy(void *dst, const void *src, unsigned int count);
extern "C" unsigned int __cdecl strlen(const char *str);
#pragma intrinsic(memcpy)
#pragma intrinsic(strlen)

class Rva006DB270
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

class Rva006DB160
{
public:
	void *allocBlock(int blockSize);
};

// Same pool instance, allocation side (companion pin to the freeBlock
// pin above; per-TU extern names each patch from retail independently).
extern Rva006DB160 *g_aptPoolAllocator; // 0x00E176E8

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

public:
	EAStringC(const EAStringC &other);
	EAStringC(const char *text);
	EAStringC &operator=(const EAStringC &other);
	~EAStringC();
	EAStringC &clear();
	void Reserve(int size);
	void SetSize(int size);
	void Assign(const char *text);
	int GetAt(int index) const;
	bool IsEmpty() const;
	bool IsEqualTo(const EAStringC *other) const;
};

// Retail empty singleton at 0x00DDC020. The linker never sees this TU's
// reloc target; DIR32 sites auto-patch from retail at verify time, the
// same idiom as g_pChainBlockAllocator above.
extern EAStringC::StringDataC g_eaEmptyStringData; // 0x00DDC020

// ?FreeData@EAStringC@@SAXPAVStringDataC@1@@Z
void EAStringC::FreeData(StringDataC *data)
{
	if (!(data->m_uRefCount >= 1)) {
		g_bfmeAptAssertAtE17734("pData->m_uRefCount >= 1", ".\\string\\EAString.inl", 0xF9);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (--data->m_uRefCount != 0)
		return;
	if (data == &g_eaEmptyStringData) {
		g_bfmeAptAssertAtE17734("(char *)pData != s_EmptyInternalData", ".\\string\\EAString.inl", 0xFD);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	g_pChainBlockAllocator->freeBlock(data, (int)(data->m_uMaxSize + 9));
}

// ??1EAStringC@@QAE@XZ, retail 0x006D3010 (10B). Scalar destructor: releases
// the shared data through FreeData. Retail is the bare 10-byte
// load-push-call-cleanup shape with no vtable work (EAStringC is a
// value class); the release call resolves via the FreeData row.
EAStringC::~EAStringC()
{
	FreeData(m_pData);
}

// ??0EAStringC@@QAE@ABV0@@Z, retail 0x006D2FC0 (70B). Copy constructor:
// shares the source data after validating its refcount, then takes its
// own reference. The empty singleton skips validation but still AddRefs.
EAStringC::EAStringC(const EAStringC &other)
{
	StringDataC *otherData = other.m_pData;
	m_pData = otherData;
	if (otherData != &g_eaEmptyStringData) {
		if (!(otherData->m_uRefCount <= 0xFFFE)) {
			g_bfmeAptAssertAtE17734("m_pData->m_uRefCount <= 0xfffe", ".\\string\\EAString.inl", 0xE1);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
	}
	m_pData->m_uRefCount++;
}

// ??4EAStringC@@QAEAAV0@ABV0@@Z, retail 0x006D3030 (85B). Assignment:
// validates and AddRefs the new data first (the source pointer survives
// in edi across the release call), then releases the old data and
// stores. Keeping the source object (not just its data pointer) in a
// named local is what pins retail's edi/esi allocation.
EAStringC &EAStringC::operator=(const EAStringC &other)
{
	const EAStringC *src = &other;
	if (src->m_pData != &g_eaEmptyStringData) {
		if (!(src->m_pData->m_uRefCount <= 0xFFFE)) {
			g_bfmeAptAssertAtE17734("m_pData->m_uRefCount <= 0xfffe", ".\\string\\EAString.inl", 0xE1);
			if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
		}
	}
	src->m_pData->m_uRefCount++;
	FreeData(m_pData);
	m_pData = src->m_pData;
	return *this;
}

// ?clear@EAStringC@@QAEAAV1@XZ, retail 0x006D2F90 (16B). Resets to the
// empty singleton with its own reference; chained (returns *this), which
// is what keeps the opening mov eax,ecx in retail's shape. Name is a
// semantic pick: the body takes no arguments and only re-roots m_pData.
EAStringC &EAStringC::clear()
{
	EAStringC *self = this;
	self->m_pData = (StringDataC *)0x00DDC020;
	g_eaEmptyStringData.m_uRefCount++;
	return *self;
}

// ?Reserve@EAStringC@@QAEXH@Z, retail 0x006D3760 (127B). Buffer
// allocator: validates the request, rounds it to a 4-byte pitch over
// the 8-byte header, and installs a fresh refcount-1 block from the
// global pool. Both bound checks are unsigned (ja/jb). The re-read of
// m_pData before the max-size store is load-bearing: without it the
// compiler forwards the freshly stored pointer and the tail rotates.
void EAStringC::Reserve(int size)
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
	StringDataC *data = (StringDataC *)g_aptPoolAllocator->allocBlock(rounded);
	self->m_pData = data;
	data->m_uRefCount = 1;
	data = self->m_pData;
	data->m_uMaxSize = (unsigned short)(rounded - 9);
}

// ??0EAStringC@@QAE@PBD@Z, retail 0x006D4C80 (25B). C-string constructor:
// roots a null data pointer, then delegates the whole build to Assign
// (rowed separately; pinned here until that row lands). Returning this
// in eax is the standard ctor epilogue.
EAStringC::EAStringC(const char *text)
{
	m_pData = 0;
	Assign(text);
}

// ?GetAt@EAStringC@@QBEHH@Z, retail 0x006D3020 (13B). Sign-extending
// character fetch from the internal buffer (the movsx proves an int
// result, not a char one). No calls or data references.
int EAStringC::GetAt(int index) const
{
	return reinterpret_cast<char *>(m_pData)[sizeof(StringDataC) + index];
}

// ?IsEmpty@EAStringC@@QBE_NXZ, retail 0x006D2F30 (14B). Tests whether
// the string is the shared empty singleton by pointer comparison; the
// xor-then-sete shape is the canonical bool return.
bool EAStringC::IsEmpty() const
{
	return m_pData == &g_eaEmptyStringData;
}

// ?IsEqualTo@EAStringC@@QBE_NPBV1@@Z, retail 0x006D3090 (54B). Compares
// two refcounted strings by handle: size mismatch is false, shared data
// is true, otherwise an intrinsic memcmp over the text. Name is a
// semantic pick: the body takes a string pointer and returns a bool with
// no side effects; the 23 Apt callers all pass string objects.
bool EAStringC::IsEqualTo(const EAStringC *other) const
{
	unsigned int otherSize = other->m_pData->m_uSize;
	unsigned int ownSize = m_pData->m_uSize;
	if (ownSize != otherSize)
		return false;
	StringDataC *ownData = m_pData;
	StringDataC *otherData = other->m_pData;
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
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	if (*text == 0) {
		m_pData = &g_eaEmptyStringData;
		++g_eaEmptyStringData.m_uRefCount;
		return;
	}
	unsigned int length = strlen(text);
	Reserve(length);
	SetSize(length);
	m_pData->m_uHash = 0;
	memcpy((char *)m_pData + sizeof(StringDataC), text, length + 1);
}
