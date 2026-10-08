// cl: /GX /Ireference/shims/bfme2_ascii /MD /D_STLP_USE_STATIC_LIB
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
    const char *m_key;
    const void *m_subtable;
    int m_count;
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
