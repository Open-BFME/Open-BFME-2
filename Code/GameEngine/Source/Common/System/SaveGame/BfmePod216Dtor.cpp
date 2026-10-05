// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1BfmePod216@@QAE@XZ 0x0021E50F 164B via Rva0021E85A layout with set54; evidence pin BfmePod216 callers 0x0021E77A 0x0021F188 trees 0x0021D61F 0x0021B775 0x0021E0FC free 0x00030830 releaseBuffer 0x00036410
#include <vector>
#include <map>
#include <set>
#include "ascii_string.h"

enum ScienceType
{
    SCIENCE_INVALID = 0
};

struct BfmeStringRecord0021A940
{
    int m_a;
    int m_b;
};

typedef _STL::map<int, _STL::vector<unsigned int> > IntegerVectorMap;
typedef _STL::map<int, int> IntegerMap;
typedef _STL::set<BfmeStringRecord0021A940> BfmeStringSet;

class BfmePod216
{
    AsciiString m_00;
    AsciiString m_04;
    AsciiString m_08;
    AsciiString m_0c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    AsciiString m_20;
    IntegerVectorMap m_24;
    _STL::vector<ScienceType> m_30;
    _STL::vector<ScienceType> m_3c;
    IntegerMap m_48;
    BfmeStringSet m_54;
public:
    ~BfmePod216();
};

BfmePod216::~BfmePod216()
{
}
