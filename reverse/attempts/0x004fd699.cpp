// ?rva004FD699@Rva004FD699@@QAEXPBVModuleData@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z
// partial score=0.94 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD
// ?rva004FD699@Rva004FD699@@QAEXPBVModuleData@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z @0x004FD699 96B
// Evidence: unlock lane unblocks 0x0057D709 0x002B7582; rowed erase 0x0031BD55 push_back 0x004DFCB0 Contains 0x0059E31F Collect 0x0059E32F; this+0x98/0x9c begin/end like siblings.
class ModuleData;

namespace _STL {
template <typename T> class allocator {};
template <typename T, typename A> class vector
{
public:
    T *erase(T *, T *);
    void push_back(const T &);
    void *_M_start;
    void *_M_finish;
    void *_M_end;
};
}

class Rva0059E2FD
{
public:
    bool rva0059E31F(const Rva0059E2FD &o);
};

class Rva0059E32F : public Rva0059E2FD
{
public:
    void rva0059E32F(_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *out);
};

class ModuleData : public Rva0059E32F
{
};

class Rva004FD699
{
public:
    void rva004FD699(const ModuleData *p, _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *out);
private:
    unsigned char m_pad[0x98];
    ModuleData **m_begin;
    ModuleData **m_end;
};

void Rva004FD699::rva004FD699(const ModuleData *p, _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *out)
{
    ((_STL::vector<void *, _STL::allocator<void *> > *)out)->erase((void **)out->_M_start, (void **)out->_M_finish);
    ModuleData **end = m_end;
    for (ModuleData **pp = m_begin; pp != end; ++pp) {
        ModuleData *cur = *pp;
        if (cur->rva0059E31F(*p)) {
            cur->rva0059E32F(out);
            return;
        }
    }
    out->push_back(p);
}
