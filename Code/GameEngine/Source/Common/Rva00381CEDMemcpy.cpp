// cl: /MD /Oi-
// ?rva00381CED@Rva00381CED@@QAEXPAX@Z, retail 0x00381CED, 21 bytes.
// memcpy 0x28 bytes from src arg into this+0x60. Evidence: unlock lane; callee
// memcpy via _memcpy pin at 0x006291A8 (ji_006291A8 row); callers at 0x00383997
// 0x0043E87A 0x0043FC9D; prev stlport_vector_stringrecord next DispDwordFieldGetters.
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);

struct Rva00381CED
{
	char m_pad[0x60];
	char m_buf[0x28];
	void rva00381CED(void *src);
};

void Rva00381CED::rva00381CED(void *src)
{
	memcpy(m_buf, src, 0x28);
}
