// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva0007ECA3@Rva0007F944Item@@QAE_NPBURva0007F944Vec@@@Z 0x0007ECA3 281B
// ?rva0007FA2B@Rva0007F944Host@@QAEHMM@Z 0x0007FA2B 127B
// One unit: retail's 0x0007FA2B keeps the item pointer in ECX across its
// call to 0x0007ECA3 which MSVC only does for a callee compiled earlier in
// the same TU (it knows the callee leaves ECX alone).
// 0x0007ECA3: winding-number point-in-polygon over the item's 12-byte point
// vector (+0x14/+0x18); WorldBuilder twin 0x0073E200 calls an isLeft helper
// (0x0073E390) that retail inlines; the vector size is re-derived through
// (end-begin)/12 each time it is read.
// 0x0007FA2B: walks the host's item pointers (+0x108/+0x10C) holding a
// counted reference to each (+4 count; release through the rowed fastcall
// 0x0007DEEF) and returns the +0x40 id of the item whose polygon contains
// (x y) with the highest first-point z.

#include <vector>

struct Rva0007F944Vec
{
    float x;
    float y;
    float z;
};

class Rva0007F944Item
{
public:
    static int isLeft(const Rva0007F944Vec *a, const Rva0007F944Vec *b, const Rva0007F944Vec *p)
    {
        return (int)((b->x - a->x) * (p->y - a->y) - (p->x - a->x) * (b->y - a->y));
    }

    bool rva0007ECA3(const Rva0007F944Vec *pt);

    unsigned char m_pad00[4];
    int m_refCount;                 // +0x04
    unsigned char m_pad08[0x14 - 0x08];
    _STL::vector<Rva0007F944Vec> m_points;  // +0x14
    unsigned char m_pad20[0x40 - 0x20];
    int m_id;                       // +0x40
};

bool Rva0007F944Item::rva0007ECA3(const Rva0007F944Vec *pt)
{
    int wn = 0;
    for (unsigned int i = 0; i < m_points.size(); i++) {
        unsigned int next = (i + 1 < m_points.size()) ? i + 1 : 0;
        if (m_points[i].y <= pt->y) {
            if (m_points[next].y > pt->y) {
                if (isLeft(&m_points[i], &m_points[next], pt) > 0)
                    ++wn;
            }
        } else {
            if (m_points[next].y <= pt->y) {
                if (isLeft(&m_points[i], &m_points[next], pt) < 0)
                    --wn;
            }
        }
    }
    return wn != 0;
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// Counted reference to an item: +4 is its reference count.
class Rva0007F944ItemRef
{
public:
    Rva0007F944ItemRef(const Rva0007F944ItemRef &that) : m_item(that.m_item)
    {
        if (m_item)
            ++m_item->m_refCount;
    }
    ~Rva0007F944ItemRef()
    {
        if (m_item)
            ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(m_item));
    }
    Rva0007F944Item *operator->() const { return m_item; }

    Rva0007F944Item *m_item;
};

class Rva0007F944Host
{
public:
    float rva0007F944(float x, float y);
    Rva0007F944Item *rva0007F9AD(float x, float y);
    int rva0007FA2B(float x, float y);

    unsigned char m_pad000[0x108];
    _STL::vector<Rva0007F944ItemRef> m_items;   // +0x108
};

float Rva0007F944Host::rva0007F944(float x, float y)
{
    Rva0007F944Vec pt;
    pt.x = x;
    pt.y = y;
    pt.z = 0.0f;
    float best = 0.0f;
    _STL::vector<Rva0007F944ItemRef>::iterator end = m_items.end();
    for (_STL::vector<Rva0007F944ItemRef>::iterator it = m_items.begin(); it != end; ++it) {
        Rva0007F944Item *item = it->m_item;
        float h = item->m_points[0].z;
        if (h > best && item->rva0007ECA3(&pt))
            best = h;
    }
    return best;
}

Rva0007F944Item *Rva0007F944Host::rva0007F9AD(float x, float y)
{
    Rva0007F944Vec pt;
    pt.x = x;
    pt.y = y;
    pt.z = 0.0f;
    Rva0007F944Item *result = 0;
    float best = 0.0f;
    for (_STL::vector<Rva0007F944ItemRef>::iterator it = m_items.begin(); it != m_items.end(); ++it) {
        Rva0007F944ItemRef item = *it;
        if (item->rva0007ECA3(&pt)) {
            float h = item->m_points[0].z;
            if (h >= best) {
                best = h;
                result = item.m_item;
            }
        }
    }
    return result;
}

int Rva0007F944Host::rva0007FA2B(float x, float y)
{
    Rva0007F944Vec pt;
    pt.x = x;
    pt.y = y;
    pt.z = 0.0f;
    int result = 0;
    float best = 0.0f;
    for (_STL::vector<Rva0007F944ItemRef>::iterator it = m_items.begin(); it != m_items.end(); ++it) {
        Rva0007F944ItemRef item = *it;
        if (item->rva0007ECA3(&pt)) {
            float h = item->m_points[0].z;
            if (h >= best) {
                result = item->m_id;
                best = h;
            }
        }
    }
    return result;
}
