// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00357A03@ScriptEngine@@QAEXHW4ScienceType@@@Z, retail 0x00357A03, 51 bytes.
// Removes one ScienceType from ScriptEngine per-player vector at +0x1A3A8[index].
// Target evidence: same +0x1A3A8 index*12 array as Science push_back at 0x00357F43 (rowed vector<ScienceType>::push_back 0x002E01C6);
// caller at 0x002AC694 passes Player+0x54 index plus ScienceVec +0x2F0 element; callee erase at 0x0025BF5D is ICF-shared with Science single-erase (its body calls Science copy helper).
// Donor shape: BFME1 isScienceAcquired erase branch (reference/open-bfme-1/.../ScriptEngineIsScienceAcquired.cpp) without bounds check or remove flag.

enum ScienceType
{
    SCIENCE_INVALID = -1
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
    T *erase(T *pos);

    T *m_start;
    T *m_finish;
    T *m_end;
};
}

class ScriptEngine
{
public:
    void rva00357A03(int playerIndex, ScienceType science);
private:
    char m_pad[0x1A3A8];
    _STL::vector<ScienceType> m_playerVectors[20];
};

void ScriptEngine::rva00357A03(int playerIndex, ScienceType science)
{
    _STL::vector<ScienceType> *vec = &m_playerVectors[playerIndex];
    ScienceType *end = vec->m_finish;
    for (ScienceType *it = vec->m_start; it != end; ++it) {
        if (*it == science) {
            vec->erase(it);
            break;
        }
    }
}
