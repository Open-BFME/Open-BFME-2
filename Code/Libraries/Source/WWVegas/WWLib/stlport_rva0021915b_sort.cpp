// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
//
// STLport's sort over 8-byte Rva0021915B records with the comparator object
// Rva0021B753: sort (0x0021F13C, 67B) and its family 0x0021BA88 .. 0x0021F065.
// Target evidence: every comparing body calls the rowed
// Rva0021B753::operator() (0x0021B753, Rva0021915BAssign.cpp) and assigns
// through the rowed Rva0021915B::operator= (0x0021915B); the partition is rowed
// as this instantiation (stlport_unguarded_partition_rva0021915B.cpp). The
// median, swap, inserts and heap helpers are rowed by hand, and this
// instantiation reproduces them.
//
// The record is declared as Rva0021915BAssign.cpp declares it: an AsciiString
// (shared header) and a flag, assigned out of line, copied and destroyed by the
// implicit members.

#include "ascii_string.h"
#include <algorithm>

#include "../../../../GameEngine/Include/Common/Rva0021915B.h"

struct Rva0021B753
{
	bool operator()(const Rva0021915B &a, const Rva0021915B &b) const;
};

// The separately rowed partition owns its swap and unwind graph.
namespace _STL {
template <> Rva0021915B *__unguarded_partition<Rva0021915B *, Rva0021915B, Rva0021B753>(Rva0021915B *, Rva0021915B *, Rva0021915B, Rva0021B753);
}

template void _STL::sort<Rva0021915B *, Rva0021B753>(Rva0021915B *, Rva0021915B *, Rva0021B753);
