// cl: /MD
// ?rva005CB91E@Rva005CB91E@@QAEHH@Z @0x005CB91E 179B: priority encoder returning 0..6 via three flag-gated lookups plus virtual bool checks. Evidence: pinned Lookup 0x003FE245 plus rowed Lookups 0x0052B225 0x0059E0F7 plus callers 0x005CB9E1 0x005CBBB9 plus unlock lane.
extern "C" void *Rva003FE245Lookup(int key);
unsigned __cdecl Rva0052B225(unsigned key);
unsigned __cdecl Rva0059E0F7(unsigned key);
struct LookupRes { char m_pad[0x38]; void *m_38; };
struct Rva005CB91EIface
{
    virtual bool v00(void *p);
    virtual bool v04(void *p);
    virtual bool v08(void *p);
    virtual bool v0C(void *p);
    virtual bool v10(void *p);
    virtual bool v14(void *p);
    virtual bool v18(void *p);
};
class Rva005CB91E
{
    Rva005CB91EIface *m_00;
    bool m_04;
    bool m_05;
    bool m_06;
public:
    int rva005CB91E(int key);
};
int Rva005CB91E::rva005CB91E(int key)
{
    if (m_04)
    {
        if (void *p = Rva003FE245Lookup(key))
        {
            void *v = ((LookupRes *)p)->m_38;
            if (v)
            {
                if (m_00->v18(v))
                    return 0;
            }
            else
            {
                if (m_00->v0C(p))
                    return 1;
            }
        }
    }
    if (m_05)
    {
        if (unsigned q = Rva0052B225((unsigned)key))
        {
            void *v = ((LookupRes *)(unsigned)q)->m_38;
            if (v)
            {
                if (m_00->v14(v))
                    return 2;
            }
            else
            {
                if (m_00->v08((void *)q))
                    return 3;
            }
        }
    }
    if (m_06)
    {
        if (int r = Rva0059E0F7((unsigned)key))
        {
            void *v = ((LookupRes *)r)->m_38;
            if (v)
            {
                if (m_00->v10(v))
                    return 4;
            }
            else
            {
                if (m_00->v04((void *)r))
                    return 5;
            }
        }
    }
    return 6;
}
