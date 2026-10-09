// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <fstream>

// Native 0x0001E2D0..0x0001E321, RET 8, surrounded by CC padding.
// BFME1 donor 874e38488c7dcf8cf3343452e8e5371bb3a0e64c:
// game/Libraries/Source/STLport/Rva0084AF80Open.cpp, 0x0084AF80, 81 bytes.
// Target evidence: filebuf at +0xc, _Filebuf_base at +0x30; forwards the
// name, mode and protection 0x80 to verified _Filebuf_base::_M_open at
// 0x0001D390; failure sets failbit through virtual-base ios state and calls
// verified ios_base::_M_throw_failure at 0x0001BC50 when required.
// A wide-fstream layout reproduces these accesses. No target caller proves
// the original owner or character identity; this is a target-address layout
// view, not a claim to the donor's ICF-folded name or a native template name.
struct Rva0001E2D0Owner
    : _STL::basic_fstream<wchar_t, _STL::char_traits<wchar_t> >
{
    void open(const char *name, int mode);
};

void Rva0001E2D0Owner::open(const char *name, int mode)
{
    if (!rdbuf()->open(name, (_STL::ios_base::openmode)mode, 0x80))
        setstate(_STL::ios_base::failbit);
}
