// cl: /MD /Oi-
// ?rva00381D02@Rva00381D02@@QAEXPAX@Z, retail 0x00381D02, 24 bytes.
// memcpy 0x10 bytes from src arg into this+0xCC. Evidence: unlock lane; callee
// memcpy via _memcpy pin at 0x006291A8 (ji_006291A8 row); callers at 0x003838D9
// 0x0043E88D 0x00581AFB 0x00581C2B 0x0058235D 0x005AF599; sibling 0x00381CED.
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);

struct Rva00381D02
{
	char m_pad[0xCC];
	char m_buf[0x10];
	void rva00381D02(void *src);
};

void Rva00381D02::rva00381D02(void *src)
{
	memcpy(m_buf, src, 0x10);
}
