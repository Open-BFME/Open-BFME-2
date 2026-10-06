// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?Rva001532E1Erase@@YAXPBD@Z, retail 0x001532E1 63B.
// Erase first BfmePod68 entry whose leading name matches case-insensitively.
// Evidence: caller at 0x001F4B24 passes "Particle"; global vector at
// 0x00DF6F20 with begin at +0 end at +4 and stride 0x44; rowed vector
// erase at 0x00153223; direct IAT _strcmpi call proves dllimport; no donor.
// string.h (via the STL headers below) declares _strcmpi without dllimport
// because this TU builds with /D_CRTIMP=; rename that decl away so the real
// import decl after the includes is the only _strcmpi the TU sees.
#define _strcmpi _stlport_hides_strcmpi
#include <vector>
#undef _strcmpi

struct BfmePod68
{
	char m_name[0x44];
};

extern _STL::vector<BfmePod68> *g_Rva00153565Vec;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);

void __cdecl Rva001532E1Erase(const char *name)
{
	if (name == 0)
		return;
	for (_STL::vector<BfmePod68>::iterator it = g_Rva00153565Vec->begin(); it != g_Rva00153565Vec->end(); ++it)
	{
		if (_strcmpi((const char *)&*it, name) == 0)
		{
			g_Rva00153565Vec->erase(it);
			return;
		}
	}
}
