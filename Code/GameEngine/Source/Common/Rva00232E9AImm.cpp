// cl: /MD
// ?rva00232E9A@Rva00232E9A@@QAEXXZ @0x00232E9A 114B unlock lane.
// Evidence: next Rva00232F0C same ImmGetCompositionStringW thunk 0x0065561C rowed; caller 0x00233CDF; GCS_COMPSTR 8 plus GCS_CURSORPOS 0x80.
long __stdcall ji_0065561c(void *himc, unsigned long idx, void *buf, unsigned long len);
#pragma comment(linker, "/alternatename:?ji_0065561c@@YGJPAXK0K@Z=?ji_0065561c@@YAXXZ")
class Rva00232E9A {
	char m_pad00[0x14];
public:
	void *m_14;
	char m_pad18[0xA];
	unsigned short m_buf22[0x400];
	char m_pad822[0x800];
	unsigned short m_1022;
	char m_pad1024[0x1002];
	unsigned short m_2026;
	char m_pad2028[0x1000];
	int m_3028;
	int m_302c;
	void rva00232E9A();
};
void Rva00232E9A::rva00232E9A()
{
	m_3028 = 0;
	m_buf22[0] = 0;
	m_2026 = 0;
	m_302c = 0;
	if (m_14 != 0) {
		long ret = ji_0065561c(m_14, 8, m_buf22, 0x800);
		if (ret >= 0) {
			m_302c = ret / 2;
			m_3028 = ji_0065561c(m_14, 0x80, 0, 0) & 0xffff;
		}
	}
	m_buf22[m_302c] = 0;
	m_1022 = 0;
}
