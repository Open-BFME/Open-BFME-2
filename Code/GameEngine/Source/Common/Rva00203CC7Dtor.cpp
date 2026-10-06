// cl: /O1
// ??1Rva00203CC7@@QAE@XZ @0x00203CC7 15B. Dtor stores vtable g_00BE39EC then links.
// Evidence: mov eax,[ecx+8]; mov [ecx],vtable; mov ecx,[ecx+4]; mov [eax],ecx; no calls.
extern const void *const g_00BE39EC[];
class Rva00203CC7
{
public:
	~Rva00203CC7();
	void *m00;
	void *m04;
	void *m08;
};
Rva00203CC7::~Rva00203CC7()
{
	void *next = m08;
	m00 = (void *)g_00BE39EC;
	*(void **)next = m04;
}
