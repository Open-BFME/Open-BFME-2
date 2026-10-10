// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii_common /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/ini /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// stable_sort machinery over AsciiString* with less<AsciiString>.
//
// Open-BFME-1's Win32BIGFileSystem_loadBigFiles.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76) stable_sorts a vector of archive
// names. Compiled with the donor's flags plus /O1, four of the STLport bodies
// that sort emits place uniquely on unclaimed game.dat .text by masked
// whole-.text search, and ./build.sh reproduces them byte for byte. The
// BFME 2 caller is not recovered, so this unit carries no caller: an explicit
// instantiation of stable_sort emits the same instantiation chain.
#include "Common/AsciiString.h"
#include <vector>
#include <algorithm>

template void _STL::stable_sort<AsciiString *>(AsciiString *, AsciiString *);
