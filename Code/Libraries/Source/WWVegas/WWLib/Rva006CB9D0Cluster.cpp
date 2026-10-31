// cl: /Ireference/shims/bfme2_ascii
// ?Rva006CB9D0@@YAPAXPBD@Z @ 0x006CB9D0 (51B). Assert-guarded wrapper from
// AptValueFactory.cpp: it validates a string argument then hands it to the
// unnamed creational helper at 0x006D7090 and returns that helper's value.
//
// The single argument string and file literal come from the retail assert
// site (VA 0x00CE8AE8 / 0x00CE8AF8), read off the PE image directly; the
// assertion mechanism matches the already-matched AptValueGCRootBFME2.cpp
// (call through the global pointer at VA 0x00E17734, then break on the flag
// at VA 0x00DDC01C).
//
// Structural inference, NOT proven identity: the caller of 0x006D7090 reads
// it as a pool-allocate-and-initialise that returns the new value, so this
// body is a null-checked thin forwarder. The address-derived name is used
// because no ledger row names this function.
//
// 0x006D7090 is declared and pinned address-derived; it has its own body
// elsewhere and only the call is reproduced here.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

// Unnamed AptValueFactory helper at 0x006D7090.
void *__cdecl rva006D7090(const char *szValue);

void *Rva006CB9D0(const char *szValue)
{
	if (szValue == 0) {
		g_bfmeAptAssertAtE17734("szValue != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValueFactory.cpp", 52);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return rva006D7090(szValue);
}

// ?Rva006CBAD0Format@@YAPAXPBDZZ @ 0x006CBAD0 (80B). Ghidra-unlisted sibling
// from the same AptValueFactory.cpp: asserts szFormat (line 0xCB, retail
// strings), creates an empty value through the same 0x006D7090 helper and
// formats the variadic arguments into its +8 EAStringC through the rowed
// va_list formatter 0x006D53F0. Address-derived name, as above.
class EAStringC
{
public:
	void rva006D53F0(const char *szFormat, char *args);
};

void *Rva006CBAD0Format(const char *szFormat, ...)
{
	if (szFormat == 0) {
		g_bfmeAptAssertAtE17734("szFormat != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValueFactory.cpp", 0xCB);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	void *value = rva006D7090("");
	((EAStringC *)((char *)value + 8))->rva006D53F0(szFormat, (char *)(&szFormat + 1));
	return value;
}

// 0x006CBA10 / 0x006CBA20 / 0x006CBA30 (5B each, between the two above):
// the same factory's integer, float and boolean creators, each a tail jump
// into the rowed pooled factory (AptInteger::Create 0x006D8520, the float
// factory 0x006D8700, AptBoolean::Create 0x006D88C0). Address-derived names.
class AptValue;
class AptInteger
{
public:
	static AptValue *Create(int value);
};
class AptBoolean
{
public:
	static AptValue *Create(bool value);
};
AptValue *Rva008A4EA0MakeFloat(float value);

AptValue *createInteger(int value)
{
	return AptInteger::Create(value);
}

AptValue *createFloat(float value)
{
	return Rva008A4EA0MakeFloat(value);
}

AptValue *createBoolean(bool value)
{
	return AptBoolean::Create(value);
}

// 0x006CBA40 (140B): the factory's array creator: asserts its value list
// (retail "pAptValue != NULL", line 0xAC), then builds the rowed array-family
// object 0x006DA4D0 in a 0x2C-byte block of the value allocator at VA
// 0x00E176F4 (rowed allocBlock 0x006D29E0; freeBlock 0x006D2A60 on unwind).
class BfmeAptValue006DCD20;
class Rva006D2A60
{
public:
	void *allocBlock(int size);
	void freeBlock(void *block, int size);
};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class Rva006DA4D0
{
public:
	Rva006DA4D0(int count, BfmeAptValue006DCD20 **pValues);
	static void *operator new(unsigned int size)
	{
		return g_pChainBlockAllocatorF4->allocBlock((int)size);
	}
	static void operator delete(void *block, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(block, (int)size);
	}
private:
	char m_storage[0x2C];
};

AptValue *createArray(int count, BfmeAptValue006DCD20 **pAptValue)
{
	if (pAptValue == 0) {
		g_bfmeAptAssertAtE17734("pAptValue != NULL",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValueFactory.cpp", 0xAC);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return (AptValue *)new Rva006DA4D0(count, pAptValue);
}

// 0x006CB9B0 (17B, just before 0x006CB9D0): a raw block of the given size
// from the same value allocator (rowed allocBlock 0x006D29E0).
void *allocValueBlock(int size)
{
	return g_pChainBlockAllocatorF4->allocBlock(size);
}
