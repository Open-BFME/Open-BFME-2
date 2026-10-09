// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Donor: Open-BFME-1 874e38488c7dcf8cf3343452e8e5371bb3a0e64c,
// game/Libraries/Source/STLport/Rva0084AF80Open.cpp, b1 RVA 0x0084AF80.
// Target [0x0001E2D0,0x0001E321): RET 8 followed by INT3 padding.
// Native evidence: file buffer at receiver+0x0c; _Filebuf_base at buffer+0x24;
// filename, mode and protection 0x80 reach the rowed _M_open at 0x0001D390.
// Failure updates the virtual-base ios state and reaches _M_throw_failure
// at 0x0001BC50 when the exception mask requires it.
// The donor has folded identities. This STLport specialization is a verified
// layout and emission view, not proof of native character type or owner name.
#include <fstream>

struct Rva0001E2D0 : _STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >
{
    void open(const char *name, int mode);
};

void Rva0001E2D0::open(const char *name, int mode)
{
    if (!rdbuf()->open(name, (_STL::ios_base::openmode)mode, 0x80))
        setstate(_STL::ios_base::failbit);
}
