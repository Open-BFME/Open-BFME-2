// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva00153565Register@@YAXPBDPAX@Z, retail 0x00153565, 154 bytes.
// Unique-register helper over global vector<BfmePod68> pointer at 0x00DF6F20:
// validates name and obj non-null plus strlen<=0x40 via strlen thunk 0x629170,
// lazily creates the vector via rowed operator new 0x2FDA0 plus Vector_base
// 0x211E58, copies name via strcpy thunk 0x629176 into a 68-byte {char[64],
// void*} slot with obj at +0x40, dedups via _strcmpi IAT 0xBBA518 over the
// 0x44-stride entries, and push_backs via rowed 0x1534D3 when absent.
// Called from ctors with "WaterDraw" 0x7EBFB, "Vegetation" 0xE6350,
// "WW3D" 0x18BEC7 and "Sas" 0x1510C2. Flags match prev TU
// stlport_pod_vector_bodies.cpp.
#define _strcmpi _stlport_hides_strcmpi
#include <vector>
#undef _strcmpi
struct BfmePod68 { int a[17]; };
extern _STL::vector<BfmePod68> *g_Rva00153565Vec;
// g_Rva00153565Vec: VA 0xdf6f20 (zero-filled .bss).
_STL::vector<BfmePod68> * g_Rva00153565Vec;
extern "C" {
unsigned __cdecl strlen(const char *s);
extern "C" char *__cdecl _mbscpy(char *d, const char *s);
__declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
}
void *__cdecl operator new(unsigned int s);
void __cdecl Rva00153565Register(const char *name, void *obj)
{
	if (!name)
		return;
	if (!obj)
		return;
	if (strlen(name) > 0x40)
		return;
	if (!g_Rva00153565Vec)
		g_Rva00153565Vec = new _STL::vector<BfmePod68>;
	BfmePod68 tmp;
	_mbscpy((char *)&tmp, name);
	tmp.a[16] = (int)obj;
	for (BfmePod68 *it = g_Rva00153565Vec->begin(); it != g_Rva00153565Vec->end(); ++it) {
		if (!_strcmpi((char *)it, name))
			return;
	}
	g_Rva00153565Vec->push_back(tmp);
}
