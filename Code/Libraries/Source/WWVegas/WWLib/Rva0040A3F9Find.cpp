// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?findIndex@Rva0040A3F9@@QBEHPAVCreateAHeroData@@@Z @0x0040A3F9 43B
// Evidence: unlock lane; vector-like +0/+4 of CreateAHeroData* searched via
// rowed _STL::find 0x20E873; null returns count else index of value (count if
// absent); callers 0x441599 0x522067 0x5220AD unclaimed; LINK BONUS none.
#include <vector>
#include <algorithm>

class CreateAHeroData;

class Rva0040A3F9
{
public:
    int findIndex(CreateAHeroData *value) const;
    bool rva0040A441(CreateAHeroData *value);
    CreateAHeroData *rva0040A32F(int index);
private:
    CreateAHeroData **m_begin;
    CreateAHeroData **m_end;
};

int Rva0040A3F9::findIndex(CreateAHeroData *value) const
{
    if (value == 0)
        return m_end - m_begin;
    return _STL::find(m_begin, m_end, value) - m_begin;
}

// ?rva0040A441@Rva0040A3F9@@QAE_NPAVCreateAHeroData@@@Z @0x0040A441 46B
// Evidence: unlock lane; same +0/+4 CreateAHeroData* vector as findIndex above;
// find via rowed 0x20E873 then rowed vector<void*> erase 0x1FF51F; false if
// absent else erase and true; caller 0x5B6A1E unclaimed; LINK BONUS none.
bool Rva0040A3F9::rva0040A441(CreateAHeroData *value)
{
    CreateAHeroData **found = _STL::find(m_begin, m_end, value);
    bool ok;
    if (found == m_end)
        ok = false;
    else {
        (( _STL::vector<void *, _STL::allocator<void *> > *)this)->erase((void **)found);
        ok = true;
    }
    return ok;
}

// ?rva0040A32F@Rva0040A3F9@@QAEPAVCreateAHeroData@@H@Z @0x0040A32F 28B
// Evidence: same +0/+4 CreateAHeroData* vector; bounds-checked index read
// (unsigned compare against the element count, null past the end); six
// matched callers reach it under this name.
CreateAHeroData *Rva0040A3F9::rva0040A32F(int index)
{
    if ((unsigned int)index >= (unsigned int)(m_end - m_begin))
        return 0;
    return m_begin[index];
}
