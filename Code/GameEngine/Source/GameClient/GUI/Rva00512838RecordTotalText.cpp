// cl: /O1 /MD
// BFME1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/BfmeConv1025.cpp. Whole donor /O1 /Os /O2
// compilation found this 44-byte formatting callback; its list-sum lead was
// adapted separately to native +F0 in Rva002B4DE2.cpp.
// Native512BB8 installs this exact entry in a four-word callback binding.
// The preceding function ends with RET4 at512835; this entry ends RET12.
// The first word is unused; the second is sprintf's char-buffer destination,
// and the low byte of the third suppresses the update. Original API name and
// the unused argument's type remain unknown.
class Rva002BA8F1Logic;
extern Rva002BA8F1Logic *g_009FEF10;

// External call-site ABI view only: no owner layout or implementation.
// Native512849 calls the separately matched thiscall2B5C1D/65 and consumes
// its 32-bit result as sprintf's "%d" argument. Bind that existing provider.
class Rva00512838SumView
{
public:
    int sum();
};
#pragma comment(linker, "/alternatename:?sum@Rva00512838SumView@@QAEHXZ=?rva002B5C1D@Rva002B4DE2@@QAEHXZ")

extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);

void __stdcall rva00512838(unsigned int opaque0, char *destination,
    unsigned char skip)
{
    if (skip != 0)
        return;
    if (g_009FEF10 == 0)
        return;
    sprintf(destination, "%d", reinterpret_cast<Rva00512838SumView *>(g_009FEF10)->sum());
}
