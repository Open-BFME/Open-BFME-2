// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?Rva004BD7AEGet@@YGMPAU_Rva004BD7AE@@@Z @0x004BD7AE 38B
// No callers; stdcall float(struct*) with int at +0xC gating float at +0x1C.
// Honest address name.

struct _Rva004BD7AE
{
	char m_pad[0xC];
	int m_kind;
	char m_pad10[12];
	float m_value;
};

float __stdcall Rva004BD7AEGet(struct _Rva004BD7AE *p)
{
	float f = 0.0f;
	if (p->m_kind == 8)
		f = p->m_value;
	return f;
}
