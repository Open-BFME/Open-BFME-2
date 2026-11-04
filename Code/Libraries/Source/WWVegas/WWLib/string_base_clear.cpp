// flags: region default (reverse/retail_inventory/flag_regions.csv)
// BFME1 StringBase cleanup entry points transferred to BFME2.  The wrappers
// tail-jump to the existing BFME2 releaseBuffer workers, so this mirror keeps
// the shared header and the worker implementations untouched.  The nulling
// default constructor and the no-op leak hook ride in the same mirror for the
// same reason: each folds onto an existing retail body by bytes alone.

typedef unsigned short wchar_t;

// Reuse the shared declaration so this donor composes with string users.
#include "../../../../../reference/shims/bfme2_ascii/string_base.h"

template <typename T>
void StringBase<T>::debugIgnoreLeaks()
{
}

template void StringBase<char>::clear();
template void StringBase<wchar_t>::clear();
template void StringBase<char>::debugIgnoreLeaks();
template void StringBase<wchar_t>::debugIgnoreLeaks();
template void StringBase<char>::validate() const;
template void StringBase<wchar_t>::validate() const;
template StringBase<char>::StringBase();
template StringBase<wchar_t>::StringBase();
template StringBase<char>::~StringBase();
template StringBase<wchar_t>::~StringBase();
