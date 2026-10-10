// cl: /MD /EHs-c-
//
// ?Rva00102215Get@@YAPAVRva001021F7@@XZ @0x00102215 38B: chain singleton getter
// for Rva001021F7 (0x20) via global g_00DEC268; new + ctor 0x001021F7.
// Evidence: packet disassembly; calls landed ctor; 8 callers.

class ObjectCreationList
{
public:
    ObjectCreationList();
private:
    char m_pad[12];
};

class Rva001021F7
{
public:
    Rva001021F7();
    void *m_a;
    ObjectCreationList m_list1;
    void *m_b;
    ObjectCreationList m_list2;
};

// Singleton pointer (data_ledger RVA 0x9EC268, zero .data, unowned);
// defined here, nothing else defines it.
Rva001021F7 *g_00DEC268 = 0;

Rva001021F7 *Rva00102215Get()
{
    if (g_00DEC268)
        return g_00DEC268;
    Rva001021F7 *p = new Rva001021F7;
    g_00DEC268 = p;
    return p;
}
