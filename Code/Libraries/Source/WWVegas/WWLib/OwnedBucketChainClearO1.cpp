// cl: /O1 /MD
// Native 00216AF6..00216B3F and 002A1D02..002A1D4B are hashtable clear
// loops: bucket vector at +4/+8, next pointer at node+0, count at +10.
// Structural guide: STLport 4.5.3 hashtable::clear and verified siblings
// Rva002A8FE0Finish.cpp / Rva0041EA88Clear.cpp. Node deletion is already
// recovered at 00216787 and 002A14FA. The native caller sets ECX to the table;
// the deleting bodies ignore it, so the member spellings alias their existing
// stdcall definitions. Original table and value identities remain unknown.
struct Rva00216787Node;
class Rva00216AF6
{
public:
    void clear();
private:
    void freeNode(Rva00216787Node *);
    int m_functors;
    Rva00216787Node **m_begin;
    Rva00216787Node **m_end;
    Rva00216787Node **m_capacity;
    unsigned m_count;
};
#pragma comment(linker, "/alternatename:?freeNode@Rva00216AF6@@AAEXPAURva00216787Node@@@Z=?Rva00216787Free@@YGXPAURva00216787Node@@@Z")
void Rva00216AF6::clear()
{
    for (unsigned i = 0; i < (unsigned)(m_end - m_begin); ++i) {
        Rva00216787Node *cur = m_begin[i];
        while (cur) {
            Rva00216787Node *next = *(Rva00216787Node **)cur;
            freeNode(cur);
            cur = next;
        }
        m_begin[i] = 0;
    }
    m_count = 0;
}

class Rva002A1D02
{
public:
    void clear();
private:
    void freeNode(void *);
    int m_functors;
    void **m_begin;
    void **m_end;
    void **m_capacity;
    unsigned m_count;
};
#pragma comment(linker, "/alternatename:?freeNode@Rva002A1D02@@AAEXPAX@Z=?Rva002A14FAFree@@YGXPAX@Z")
void Rva002A1D02::clear()
{
    for (unsigned i = 0; i < (unsigned)(m_end - m_begin); ++i) {
        void *cur = m_begin[i];
        while (cur) {
            void *next = *(void **)cur;
            freeNode(cur);
            cur = next;
        }
        m_begin[i] = 0;
    }
    m_count = 0;
}
