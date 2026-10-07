// cl: /O1 /MD /EHsc
// Target wait-set storage helpers, native 0x0004123B/83B and 0x0004128E/72B.
// Identity: constructors 0x000412D6 and 0x00041389 call both on the same
// owner as the independently matched wait 0x00041078 and refresh 0x00041118.
// Layout: native accesses establish count +0xC, eight inline handles +0x10,
// objects +0x30, done bytes +0x50, and three four-byte owners +0x58/5C/60.
// Array ownership is the rowed setter 0x00041168 and new[] 0x0002FDE0.
// Original class and helper names remain unknown.
void *__cdecl operator new[](unsigned int);

class Rva00041168 {
public:
    void rva00041168(void *p);
    void *m_p;
};

class Rva00041118Obj {
public:
    virtual void vf0();
    virtual unsigned char vf1();
    void *m_handle;
};

class Rva00041078 {
public:
    void rva0004123B(int count);
    void rva0004128E();
private:
    void **m_handles;
    Rva00041118Obj **m_objs;
    unsigned char *m_done;
    int m_count;
    void *m_inlineHandles[8];
    Rva00041118Obj *m_inlineObjs[8];
    unsigned char m_inlineDone[8];
    Rva00041168 m_handleOwner;
    Rva00041168 m_objectOwner;
    Rva00041168 m_doneOwner;
};

void Rva00041078::rva0004123B(int count)
{
    m_count = count;
    if (count <= 8) {
        m_objs = m_inlineObjs;
        m_done = m_inlineDone;
    } else {
        void *objects = ::operator new[](count * sizeof(Rva00041118Obj *));
        m_objectOwner.rva00041168(objects);
        m_objs = (Rva00041118Obj **)m_objectOwner.m_p;
        void *done = ::operator new[](m_count);
        m_doneOwner.rva00041168(done);
        m_done = (unsigned char *)m_doneOwner.m_p;
    }
}

void Rva00041078::rva0004128E()
{
    if (m_count <= 8) {
        m_handles = m_inlineHandles;
    } else {
        void *handles = ::operator new[](m_count * sizeof(void *));
        m_handleOwner.rva00041168(handles);
        m_handles = (void **)m_handleOwner.m_p;
    }
    for (int i = 0; i < m_count; ++i)
        m_handles[i] = m_objs[i]->m_handle;
}
