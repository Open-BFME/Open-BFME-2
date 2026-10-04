// cl: /O1
// ?Rva002E6E9FGet@@YAPAXPAX@Z @0x002E6E9F 43B
// Evidence: unlock lane; free scan over pointer table at +0x244 calling slot
// 0x68 on subobject at +0xC and tail-calling slot 0 on success; callers
// 0x002F1946 0x002F1997 in 0x002F18D4.
class Sub68
{
public:
    virtual void *v00();
    virtual void *v01();
    virtual void *v02();
    virtual void *v03();
    virtual void *v04();
    virtual void *v05();
    virtual void *v06();
    virtual void *v07();
    virtual void *v08();
    virtual void *v09();
    virtual void *v10();
    virtual void *v11();
    virtual void *v12();
    virtual void *v13();
    virtual void *v14();
    virtual void *v15();
    virtual void *v16();
    virtual void *v17();
    virtual void *v18();
    virtual void *v19();
    virtual void *v20();
    virtual void *v21();
    virtual void *v22();
    virtual void *v23();
    virtual void *v24();
    virtual void *v25();
    virtual void *v26();
};

class Res0
{
public:
    virtual void *first();
};

struct Elem
{
    char m_pad[12];
    Sub68 m_sub;
};

void *__cdecl Rva002E6E9FGet(void *arg)
{
    struct Table
    {
        char m_pad[0x244];
        Elem **m_ptr;
    };
    Elem **pp = ((Table *)arg)->m_ptr;
    for (;;) {
        Elem *e = *pp;
        if (e == 0)
            return 0;
        void *w = e->m_sub.v26();
        if (w != 0)
            return ((Res0 *)w)->first();
        ++pp;
    }
}
