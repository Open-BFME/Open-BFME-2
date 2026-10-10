// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// ?rva004F92E3@Rva004F92E3@@QAEXPAX@Z, retail 0x004f92e3, 149 bytes. Banked partial (score 0.92) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
#include <vector>

struct TargetRef00217D4C
{
    virtual void *destroy(unsigned int flags);
    int m_references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
    TargetRef00217D4C *m_ptr;
    TreeHintRef00217D4C(const TreeHintRef00217D4C &o) : m_ptr(o.m_ptr)
    {
        if (m_ptr)
            ++m_ptr->m_references;
    }
    ~TreeHintRef00217D4C()
    {
        if (m_ptr)
            ReleaseTreeHintRef00217D4C(m_ptr);
    }
};

struct Rva004F8D92Element
{
    TargetRef00217D4C *m_ptr;
};

class Rva004F830BVector
{
    void *m_start;
    void *m_finish;
    void *m_end;
public:
    void reserve(unsigned int n);
};

class Rva004F92E3
{
    char m_pad[12];
    void *m_src0_start;
    void *m_src0_finish;
    void *m_src0_end;
    void *m_src1_start;
    void *m_src1_finish;
    void *m_src1_end;
public:
    void rva004F92E3(void *out);
};

void Rva004F92E3::rva004F92E3(void *out)
{
    typedef _STL::vector<TreeHintRef00217D4C> SrcVec;
    typedef _STL::vector<TreeHintRef00217D4C> DestEraseVec;
    typedef _STL::vector<Rva004F8D92Element> DestPushVec;

    DestEraseVec *dest = (DestEraseVec *)out;
    SrcVec *src = (SrcVec *)((char *)this + 12);

    int n = 2;
    do {
        // Codegen: same-valued PHI on the destination pointer closes the native register roles.
        DestEraseVec &destErase = *(dest?dest:dest);
        SrcVec &srcVec = *src;
        DestPushVec &destPush = *(DestPushVec *)dest;

        destErase.erase(destErase.begin(), destErase.end());
        ((Rva004F830BVector &)destErase).reserve(srcVec.size());

        TreeHintRef00217D4C *end = srcVec.end();
        for (TreeHintRef00217D4C *p = srcVec.begin(); p != end; ++p) {
            TreeHintRef00217D4C tmp = *p;
            destPush.push_back((Rva004F8D92Element &)tmp);
        }

        ++dest;
        ++src;
    } while (--n != 0);
}
