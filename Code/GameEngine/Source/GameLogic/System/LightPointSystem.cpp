// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// stlport
// BFME1 9cbfb55 INILightPointLevel.cpp supplies the semantic class guide.
// WB 0x010EE1D0 and retail 0x004212E4..0x00421312 prove initialization of
// the 36-byte light-point level: override link/flag/index, narrow/wide strings
// and vector<unsigned int>. Preserve Rva004211CA, the existing vtable and
// destructor owner. The actual STLport vector base constructor supplies the
// witnessed stack allocator temporary and all three zeroed pointers.
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
class Rva004211CA;
class LightPointOverrideFields
{
public:
    LightPointOverrideFields() : m_next(0), m_override(false), m_index(-1) {}
    Rva004211CA *m_next;
    bool m_override;
    int m_index;
};
class Rva004211CA : public LightPointOverrideFields
{
public:
    Rva004211CA();
    virtual ~Rva004211CA();
    AsciiString m_name;
    UnicodeString m_label;
    _STL::vector<unsigned int> m_values;
};
Rva004211CA::Rva004211CA() : m_name(), m_label(), m_values() {}
