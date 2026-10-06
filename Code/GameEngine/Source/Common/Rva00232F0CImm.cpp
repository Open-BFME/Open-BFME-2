// cl: /MD
// ?rva00232F0C@Rva00232F0C@@QAEXXZ @0x00232F0C 67B unlock lane.
// Evidence: callee ImmGetCompositionStringW thunk 0x0065561C rowed; caller 0x00233C97; buffer +0x1024 len 0x800 index GCS_RESULTSTR 0x800.
long __stdcall ji_0065561c(void *himc, unsigned long idx, void *buf, unsigned long len);
#pragma comment(linker, "/alternatename:?ji_0065561c@@YGJPAXK0K@Z=?ji_0065561c@@YAXXZ")

class Rva00232F0C {
	char m_pad[0x14];
public:
	void *m_14;
	char m_pad2[0x1024 - 0x18];
	unsigned short m_buf[0x400];
	char m_pad3[0x800];
	unsigned short m_2024;
	void rva00232F0C();
};

void Rva00232F0C::rva00232F0C()
{
	void *himc = m_14;
	int idx = 0;
	unsigned short *buf = m_buf;
	buf[0] = 0;
	if (himc != 0) {
		long ret = ji_0065561c(himc, 0x800, buf, 0x800);
		if (ret >= 0)
			idx = ret / 2;
	}
	m_buf[idx] = 0;
	m_2024 = 0;
}
