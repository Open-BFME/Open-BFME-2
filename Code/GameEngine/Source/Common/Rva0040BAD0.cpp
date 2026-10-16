// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
// Award-statistic lookup and insertion on the same manager. Retail and the
// WorldBuilder lookup at VA 0x01084A80 establish the vector at +0x18, its
// 0x68-byte elements, and the name key in each element's first word.
// Keep the existing address-derived names; original method names are unknown.
#include <vector>
#include <algorithm>
#include "ascii_string.h"

enum NameKeyType
{
    NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
    const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

// Read-only layout view of the existing statistic type. The matched copy
// constructor at 0x0040AF66 and vector push_back at 0x0040BA6A establish the
// extent. Lookup reads only the key; it neither copies nor destroys records.
class Rva0040AF66
{
public:
    int m_00;
private:
    char m_rest[0x64];
};

inline bool operator==(const Rva0040AF66 &record, const int &key)
{
    return record.m_00 == key;
}

// The existing provider owns push_back. Keep the insertion member's real
// call to it instead of instantiating another copy in this unit.
namespace _STL
{
template <> void vector<Rva0040AF66>::push_back(const Rva0040AF66 &);
}

class Rva0040BAD0
{
public:
    bool rva0040BAD0(Rva0040AF66 *arg);
    int rva0040AAF8(int key);
private:
    char m_pad00[0x18];
    _STL::vector<Rva0040AF66> m_vec18;
};

// ?rva0040AAF8@Rva0040BAD0@@QAEHH@Z @0x0040AAF8 173B.
// Return the matching statistic, or materialize the diagnostic names and
// return null. The name lifetimes remain observable through StringBase's
// refcount operations even though no diagnostic output survives in retail.
int Rva0040BAD0::rva0040AAF8(int key)
{
    Rva0040AF66 *begin = m_vec18.begin();
    Rva0040AF66 *end = m_vec18.end();
    Rva0040AF66 *found = _STL::find(begin, end, key);
    if (found != end)
        return (int)found;

    AsciiString name = TheNameKeyGenerator->keyToName((NameKeyType)key);
    for (unsigned int i = 0; i < m_vec18.size(); ++i)
    {
        Rva0040AF66 *record = &m_vec18[i];
        AsciiString current(TheNameKeyGenerator->keyToName((NameKeyType)record->m_00));
        // Codegen workaround: both retail VA 0x0080AB69 and WorldBuilder
        // VA 0x01084B7F retain this NOP between the copy and destruction.
        // MSVC 7.1 omits it for the recovered C++ lifetime alone. All control
        // flow, storage, calls and EH data are still generated from C++.
        __asm nop
    }
    return 0;
}

// ?rva0040BAD0@Rva0040BAD0@@QAE_NPAVRva0040AF66@@@Z @0x0040BAD0 39B.
// Insert the whole argument record only when its name key is not present.
bool Rva0040BAD0::rva0040BAD0(Rva0040AF66 *arg)
{
    if (rva0040AAF8(arg->m_00) == 0)
    {
        m_vec18.push_back(*arg);
        return true;
    }
    return false;
}
