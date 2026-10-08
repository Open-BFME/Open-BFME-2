// flags: region default (reverse/retail_inventory/flag_regions.csv)

// Keep the shared one-pointer string layout. The retail emptiness test reads
// the canonical header's 16-bit length at offset 4.
#include "../../../../../reference/shims/bfme2_ascii/string_base.h"

template <class CHAR>
bool StringBase<CHAR>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}

template bool StringBase<char>::isEmpty() const;

// Clean BF1 9cbfb551fe System/SaveGame/GameStateRealMapPathToPortableMapPathThunk.cpp
// stringLength supplies null-safe length semantics. Native052C4..052D2 follows
// the rowed RGB-color debug body's RET052C3, tests the cdecl pointer, returns
// full EAX0 for null and otherwise tail-calls the actual strlen import thunk
// at629170 (IAT BBA6D4). Original helper/template name and return signedness
// remain unknown; this address-named unsigned view preserves the result bits.
#include <string.h>
unsigned int Rva000052C4LengthOrZero(const char *text)
{
    return text ? (unsigned int)strlen(text) : 0u;
}

// Native 3B180F..3B1820 forwards this and one string reference to the rowed
// StringBase<char>::compareNoCase at 6A00, then returns whether its result is
// zero. BF1 9cbfb551fe20 TerrainRoads_find.cpp supplies a semantic lead; its
// equality spelling does not establish the original target class or name.
class Rva003B180FStringQuery
{
public:
    bool equalsNoCase(const StringBase<char> &other) const;
};

bool Rva003B180FStringQuery::equalsNoCase(const StringBase<char> &other) const
{
    return reinterpret_cast<const StringBase<char> *>(this)->compareNoCase(other) == 0;
}
