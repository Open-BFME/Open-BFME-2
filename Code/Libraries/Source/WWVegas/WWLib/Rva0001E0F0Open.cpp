// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Donor: Open-BFME-1 10af19f44a89ab7ecc23195bb9a842ceafbc02c9,
// game/Libraries/Source/STLport/Rva0084ADA0Open.cpp, b1 0x0084ADA0.
// Target [0x0001E0F0,0x0001E141): RET 8 followed by INT3 padding.
// It passes filename, mode and protection 0x80 to the verified file-opening
// routine at 0x0001D390, using the file buffer at receiver+0x0c and its
// base at +0x54. On failure it updates virtual-base ios state and calls
// verified ios_base::_M_throw_failure at 0x0001BC50 when masked.
// The donor has folded identities. This shared STLport header specialization
// supplies a layout/emission view, not an assertion of native character type,
// original owner class, method name or logging purpose.

#include <fstream>

struct Rva0001E0F0Owner : _STL::basic_fstream<char, _STL::char_traits<char> >
{
    void open(const char *filename, int mode);
};

void Rva0001E0F0Owner::open(const char *filename, int mode)
{
    if (!rdbuf()->open(filename, (_STL::ios_base::openmode)mode, 0x80))
        setstate(_STL::ios_base::failbit);
}

