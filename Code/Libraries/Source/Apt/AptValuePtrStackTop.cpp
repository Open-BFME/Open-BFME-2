// cl: /MD
// ?rva006DE160@AptValuePtrStack@@QAEPAVBfmeAptValue006DCD20@@XZ @0x006DE160 53B.
// Returns the top element m_aElements[m_nElements-1] of the Apt value ptr
// stack from _AptValuePtrStack.h, asserting m_nElements - nPos > 0 at line
// 0x89 via the shared Apt assert triple. Layout mirrors AptBasePtrStack
// (m_nElements at +0, m_nCapacity at +4, m_aElements at +8). Callers at
// 0x6DF9F4 and 0x70846C consume the top. No donor; retail-shaped.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class BfmeAptValue006DCD20;

class AptValuePtrStack
{
public:
	int m_nElements;
	int m_nCapacity;
	BfmeAptValue006DCD20 **m_aElements;
	BfmeAptValue006DCD20 *rva006DE160();
	BfmeAptValue006DCD20 *rva006DCC10(int nPos);
};

BfmeAptValue006DCD20 *AptValuePtrStack::rva006DE160()
{
	if (!(m_nElements > 0)) {
		g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x89);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return m_aElements[m_nElements - 1];
}

BfmeAptValue006DCD20 *AptValuePtrStack::rva006DCC10(int nPos)
{
	if (!(m_nElements - nPos > 0)) {
		g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x89);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return m_aElements[m_nElements - nPos - 1];
}
