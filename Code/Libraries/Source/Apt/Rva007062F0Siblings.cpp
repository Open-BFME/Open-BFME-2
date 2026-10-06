// cl: /MD
// ?rva007062F0@AptBasePtrStack@@QAEPAVBfmeAptValue006DCD20@@XZ @0x007062F0 53B.
// Recovers the base-class spelling of the Apt value ptr stack top getter from
// the ?rva006DE160@AptValuePtrStack@@ recipe at 0x006DE160. Same operand-masked
// shape: assert m_nElements - nPos > 0 at the shared Apt assert triple, then
// return m_aElements[m_nElements-1]. Only the header literal (retail path
// _AptBasePtrStack.h) and the asserted line 0x10A differ; both are pushed
// immediately, while the two globals are DIR32 memory operands. Layout mirrors
// the template (m_nElements +0, m_nCapacity +4, m_aElements +8).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class BfmeAptValue006DCD20;

class AptBasePtrStack
{
public:
	int m_nElements;
	int m_nCapacity;
	BfmeAptValue006DCD20 **m_aElements;
	BfmeAptValue006DCD20 *rva007062F0();
};

BfmeAptValue006DCD20 *AptBasePtrStack::rva007062F0()
{
	if (!(m_nElements > 0)) {
		g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x10a);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return m_aElements[m_nElements - 1];
}
