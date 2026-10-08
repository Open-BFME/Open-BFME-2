// cl: /O2 /MD
// AptValueVector family: named Apt value containers from
// AptValue/AptValueVector.h. Retail assertion strings name that header
// and its mCurrentNum member. Element entries pair a shared EAStringC
// name with an integer value; the vector adds the element pointer array.
// EAStringC here is the minimal TU-local view the original needs: the
// copy, assign and clear operations resolve via ledger rows while the
// default constructor re-roots to the shared empty singleton (retail
// 0x006D2F90, ICF-shared with clear) so this unit stops emitting a stray
// empty copy.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern "C" void *__cdecl memmove(void *, const void *, unsigned int);
void __debugbreak();
#pragma intrinsic(__debugbreak)

class Rva006DB160
{
public:
	void *allocBlock(int blockSize);
};

// Pool allocator instance at 0x00E176E8 (same global the string
// Reserve path uses; DIR32 sites auto-patch from retail at verify).
extern class Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8

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

	StringDataC *m_pData;

public:
	EAStringC();
	EAStringC(const EAStringC &other);
	EAStringC &operator=(const EAStringC &other);
	EAStringC &clear();
};

extern EAStringC::StringDataC g_eaEmptyStringData;

__declspec(noinline) inline EAStringC::EAStringC()
{
	m_pData = &g_eaEmptyStringData;
	++g_eaEmptyStringData.m_uRefCount;
}

class AptValue;

class AptValueNameEntry
{
public:
	AptValueNameEntry();
	AptValueNameEntry(const EAStringC &name, int value);

	EAStringC m_name;
	int m_value;
};

class AptValueVector
{
public:
	static void *Allocate(int size);
	AptValue ***GetData();
	void rva006CC0A0(int iPos);

	EAStringC m_name;
	int mCurrentNum;
	AptValue **m_data;
};

// ??0AptValueNameEntry@@QAE@ABVEAStringC@@H@Z, retail 0x006CBFE0 (26B).
// Named-value entry constructor: shares the name string through the
// rowed EAStringC copy constructor, then stores the integer value.
// The array pointer lives in the owning vector, so this body touches
// only the 8 bytes it owns.
AptValueNameEntry::AptValueNameEntry(const EAStringC &name, int value) :
	m_name(name),
	m_value(value)
{
}

// ??0AptValueNameEntry@@QAE@XZ, retail 0x006CC000 (19B). Default entry
// constructor: the implicit EAStringC default (empty re-root at 0x006D2F90,
// ICF-shared with clear) initializes the name, then zeroes the value.
// Retail leaves the owning vector's array pointer to the caller; array
// construction drives this body per element through the 0x00629512 helper.
inline AptValueNameEntry::AptValueNameEntry()
{
	m_value = 0;
}

// ?GetData@AptValueVector@@QAEPAPAPAVAptValue@@XZ, retail 0x006CBFD0 (4B).
// Returns the address of the element pointer array so callers can reseat
// it; the bare lea eax,[ecx+8] shape carries no call or data references.
AptValue ***AptValueVector::GetData()
{
	return &m_data;
}

// ?Allocate@AptValueVector@@SAPAXH@Z, retail 0x006CC020 (17B). Pool
// allocation entry: forwards the byte size to the global Apt pool
// allocator instance. Static (no this use); the global load and the
// allocator call both resolve as relocs at verify time.
void *AptValueVector::Allocate(int size)
{
	return (*(Rva006DB160 **)&g_pChainBlockAllocator)->allocBlock(size);
}

// ?rva006CC0A0@AptValueVector@@QAEXH@Z, retail 0x006CC0A0 (104B). Erase at
// iPos: assert iPos bounds via the AptVector.h line 0x45 check, decrement
// mCurrentNum, memmove the tail left unless the last slot was removed,
// then null the freed slot. Caller at 0x006CE27D passes one int;
// strings name AptValueVector.h and mCurrentNum.
void AptValueVector::rva006CC0A0(int iPos)
{
	if (!(iPos >= 0 && iPos < mCurrentNum)) {
		g_bfmeAptAssertAtE17734("iPos >= 0 && iPos < mCurrentNum", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValueVector.h", 0x45);
		if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
	}
	--mCurrentNum;
	if (mCurrentNum != 0 && iPos != mCurrentNum) {
		memmove(&m_data[iPos], &m_data[iPos + 1], (mCurrentNum - iPos) * sizeof(*m_data));
	}
	m_data[mCurrentNum] = 0;
}

// ??0AptValueNameEntry@@QAE@XZ is a header inline in retail: other units emit
// select-any copies of it, so a strong definition here was a duplicate symbol
// in the linked build. This anchor only makes this unit emit its copy for the
// ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitAptValueVector@@YAXPAVAptValueNameEntry@@@Z present-unmatched
void bfmeEmitAptValueVector(AptValueNameEntry *p)
{
	p->AptValueNameEntry::AptValueNameEntry();
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Rva00892640Item@@QAE@XZ=??0AptValueNameEntry@@QAE@XZ")
