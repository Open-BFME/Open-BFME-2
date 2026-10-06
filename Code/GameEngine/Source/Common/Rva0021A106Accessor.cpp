// cl: /MD
// CreateAHeroManager::GetBlingBinder, retail 0x0021A106 46B (WorldBuilder
// name; its assert reads blingBinderIndex < m_blingBinderList.size(), the
// 20-byte element vector at +0x168/+0x16C).
// Count via signed idiv by 0x14, element via imul 0x14; null on miss.
// Proven by callers 0x0021CC49/0x005B1BD1 on the 0x009FE344 global which also
// calls CreateAHeroManager methods 0x0021A097/0x0021A1B6. Same idiv recipe as 0x00219B9E;
// /G7 carries the imul 0x14 (IMUL law: /O1 alone strength-reduces i*20 to lea).
struct Elem20 { char m_00[20]; };
struct Vec20 {
    Elem20 *m_start;
    Elem20 *m_finish;
    Elem20 *m_end;
};
static __forceinline unsigned Vec20Size(const Vec20 *v) { return v->m_finish - v->m_start; }
static __forceinline Elem20 &Vec20At(Vec20 *v, unsigned i) { return v->m_start[i]; }
class CreateAHeroManager {
    char m_pad[0x168];
    Vec20 m_blingBinderList;
public:
    void *GetBlingBinder(unsigned int blingBinderIndex);
};
void *CreateAHeroManager::GetBlingBinder(unsigned int blingBinderIndex)
{
    unsigned int count = Vec20Size(&m_blingBinderList);
    if (blingBinderIndex < count)
        return &Vec20At(&m_blingBinderList, blingBinderIndex);
    return 0;
}
