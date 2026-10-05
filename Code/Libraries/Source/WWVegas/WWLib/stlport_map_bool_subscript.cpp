// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// _STL::map<int, bool>::operator[] @0x00470353 69B, /O1.
// BFME 1 donor FileExistCacheIntKey.cpp (Open-BFME-1 6583b3c1ff) recompiled
// /O1 places uniquely here with every non-relocation byte equal
// (tools/donor_sweep.py); retail's two key compares are signed (jl/jge),
// so the key is int. Target facts: the lower_bound and insert calls read
// from retail land on the pinned map<int,bool> callees 0x00382A92 and
// 0x0046F0A5. The explicit instantiation emits only the operator and its
// callees, no scaffold function.
#include <map>

template bool &_STL::map<int, bool>::operator[](const int &);
