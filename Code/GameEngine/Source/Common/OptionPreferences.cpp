// cl: /GX /Ireference/shims/bfme2_ascii /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?setSetting@OptionPreferences@@QAEXHH@Z @0x002E553D 155B.
// WB 0x00DCD180 names OptionPreferences::setSetting in this file; assertion
// line 605 identifies the value-range check against s_CustomLODSettings.
// Retail 0x002E553D..0x002E55D8 has thiscall/ret 8 and two integer-width
// arguments. The original enum spelling for the setting index is unproven;
// this view preserves its signed 32-bit ABI without inventing an enum name.
// Target table layout comes independently from existing enum-dispatch/erase
// siblings: VA 0x00DBD120, stride 12, key +0, values +4, count +8. Reuse their
// owned BfmeEnumTable symbol and the same map base at this+4.
// A value outside the range erases the key; otherwise retain the selected
// text across map::operator[] before calling BFME2's StringBase::set(text).
#include "ascii_string.h"
#include <map>

// Retail's tree frees nodes through a direct _free; the dllimport+forceinline
// specialization takes __malloc_alloc<0>::deallocate inline so this TU emits
// no copy of its own (retail's is the unoptimized import entry, 0x00023A70).
namespace _STL {
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

bool operator<(const AsciiString &left, const AsciiString &right);
namespace _STL
{
template <> struct less<AsciiString>
{
    bool operator()(const AsciiString &left, const AsciiString &right) const
    {
        return left < right;
    }
};
template <> AsciiString &map<AsciiString, AsciiString, less<AsciiString>,
    allocator<pair<const AsciiString, AsciiString> > >::operator[](const AsciiString &key);
}

typedef _STL::map<AsciiString, AsciiString> PreferenceMap;
struct BfmeEnumTableEntry
{
public:
	const char *m_key; // +0x00
	const void *m_subtable; // +0x04
	int m_count; // +0x08
};
extern BfmeEnumTableEntry BfmeEnumTable[];

class OptionPreferences : public PreferenceMap
{
public:
    virtual ~OptionPreferences();
    void setSetting(int setting, int value);
};

void OptionPreferences::setSetting(int setting, int value)
{
    if (value < 0 || value >= BfmeEnumTable[setting].m_count)
    {
        AsciiString key(BfmeEnumTable[setting].m_key);
        erase(key);
    }
    else
    {
        AsciiString key(BfmeEnumTable[setting].m_key);
        const char *selected = ((const char **)BfmeEnumTable[setting].m_subtable)[value];
        AsciiString &entry = (*this)[key];
        ((StringBase<char> *)&entry)->set(selected);
    }
}
