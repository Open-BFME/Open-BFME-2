// ?rva006E9A40@Rva006E0DE0@@QAEXPAVAptValue@@@Z
// partial score=0.8957 date=2026-10-05
// ?rva006E9A40@Rva006E0DE0@@QAEXPAVAptValue@@@Z
// cl: /O2 /MD
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptValue {
public:
	virtual void AddRef();
	virtual void Release();
};

class Rva006E0DE0 {
	union {
		struct {
			unsigned short m_nElements;
			unsigned short m_nMaxElements;
		};
		int m_0;
	};
	AptValue **m_ppElements;
	int m_8;
	int m_C;
public:
	void rva006E9A40(AptValue *p);
};

void Rva006E0DE0::rva006E9A40(AptValue *p)
{
	AptValue **tab;
	if (m_nElements >= m_nMaxElements) {
		g_bfmeAptAssertAtE17734("mnElements < mnMaxElements", "c:\projects\bfme2patch103\bfme2\code\libraries\source\apt\_AptSet.h", 0x27);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	for (int i = 0; i < m_nMaxElements; ++i) {
		if (m_ppElements[i] == p) {
			g_bfmeAptAssertAtE17734("maElements[i] != element", "c:\projects\bfme2patch103\bfme2\code\libraries\source\apt\_AptSet.h", 0x2D);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
	}
	tab = m_ppElements;
	++m_nElements;
	int idx = m_nElements;
	if (tab[idx] != 0) {
		while (1) {
			if (idx >= m_nMaxElements)
				idx = 0;
			idx++;
			if (tab[idx - 1] == 0)
				break;
			idx--;
		}
	}
	tab[idx] = p;
	p->AddRef();
}
