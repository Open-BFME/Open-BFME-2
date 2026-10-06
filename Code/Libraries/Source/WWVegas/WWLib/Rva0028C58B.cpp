// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// ?rva0028C58B@Rva0028C58B@@QAEPAV1@XZ @0x0028C58B 20B: memset this 0x14 to 0 and return this. Evidence: retail pushes 0x14 0 this to rowed memset thunk 0x006291AE then mov eax esi; caller at 0x0029915A; neighbours share same cl flags.
void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class Rva0028C58B
{
public:
	Rva0028C58B *rva0028C58B();
private:
	char m_pad[0x14];
};

Rva0028C58B *Rva0028C58B::rva0028C58B()
{
	ji_006291ae(this, 0, 0x14);
	return this;
}
