#pragma once
// Target-owned 24-byte pool view; original template/application names unknown.
// Native grow [2E8548,2E85AD) establishes six fields and a 24-byte node stride.
// DB9440 and DBD4C8 both initialize to {128,0,0,42FFC0,42FFE0,0}.
// Native ScienceStore release accesses DB9440+8, this owner's free-node head.
class Rva002E8548
{
public:
    void *rva002EB448();
private:
    friend class Rva002EB448;
    friend class Rva001FF36A;
    bool rva002E8548(int arena, int size);
public:
    int m_00; // default node count
    void *m_04; // allocated-block list
    void *m_head; // free-node list
    void *(__cdecl *m_alloc)(int size, int context);
    void (__cdecl *m_free)(void *block, int context);
    int m_14; // callback context
};

extern Rva002E8548 g_Va00DB9440;
extern Rva002E8548 g_Va00DBD4C8;
