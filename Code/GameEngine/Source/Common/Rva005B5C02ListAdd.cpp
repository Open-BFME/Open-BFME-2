// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?Add@Rva005B5C02List@@QAE_NPAURva005B5C02Entry@@@Z @0x0040A384 45B
// Evidence: leaf lane; caller 0x005B5C62 Run passes Entry* and ignores return;
// vector-like +0/+4 searched via rowed _STL::find 0x0020E873 then (*found)->Use
// via pinned 0x00409359; true/false in al proves bool return (pin says void).
#include <vector>
#include <algorithm>

class CreateAHeroData;

struct Rva005B5C02Entry
{
    void Use(void *s);
};

struct Rva005B5C02List
{
    Rva005B5C02Entry **m_begin;
    Rva005B5C02Entry **m_end;
    bool Add(Rva005B5C02Entry *e);
};

bool Rva005B5C02List::Add(Rva005B5C02Entry *e)
{
    CreateAHeroData **begin = (CreateAHeroData **)m_begin;
    CreateAHeroData **end = (CreateAHeroData **)m_end;
    CreateAHeroData * const &val = (CreateAHeroData * const &)e;
    CreateAHeroData **found = _STL::find(begin, end, val);
    if (found == end)
        return false;
    ((Rva005B5C02Entry *)*found)->Use(e);
    return true;
}
