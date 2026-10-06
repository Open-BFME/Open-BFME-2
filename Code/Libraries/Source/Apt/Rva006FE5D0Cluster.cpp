// cl: /MD
// ?rva006FE5D0@AptBasePtrStack@@QAEPAVBfmeAptValue006DCD20@@XZ @0x006FE5D0 55B.
// Checked single-element pop from the Apt base pointer stack: asserts
// GetSize() >= 1 (_AptBasePtrStack.h line 0x110), then pre-decrements
// m_nElements and returns the old top element. Evidence: its own assert
// strings in reverse/string_xrefs.tsv (expr "GetSize() >= 1", file
// _AptBasePtrStack.h); layout/flags/assert triple shared with the rowed
// neighbors At 0x006FE580 and rva006FE920 in AptActionInterpreterBitwise.cpp
// and AptBasePtrStackPopAndPush.cpp.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class BfmeAptValue006DCD20;

class AptBasePtrStack
{
public:
	BfmeAptValue006DCD20 *rva006FE5D0();

	int m_nElements;
	int m_nCapacity;
	BfmeAptValue006DCD20 **m_aElements;
};

BfmeAptValue006DCD20 *AptBasePtrStack::rva006FE5D0()
{
	if (!(m_nElements >= 1)) {
		g_bfmeAptAssertAtE17734("GetSize() >= 1", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x110);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return m_aElements[--m_nElements];
}
