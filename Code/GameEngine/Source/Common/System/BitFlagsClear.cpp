// cl: /O2 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <bitset>
// Rehomes the existing clear row at 0x00666E80, not a newly identified function.
// Zero Hour's Common/BitFlags.h (a donor) stores a bitset and delegates clear
// to reset; here clear() zeroes the shared header's word array, which gives
// retail's 14 bytes. <bitset> stays included because dropping it changes the
// STLport symbols this object carries. Its prior
// owner had only this verified row plus unrelated naked assembly; the full
// prior source is preserved under reverse/attempt_support/bitflags-clear-owner-20261023/.
// Original reference is GPL-3.0-or-later; this repository retains its license.
#include "../../../Include/Common/BitFlagsTemplate.h"

template <int NUMBITS> void BitFlags<NUMBITS>::clear()
{
    for (unsigned int i = 0; i < NUMWORDS; i++)
        m_bits[i] = 0;
}
template void BitFlags<116>::clear();
