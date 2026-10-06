// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva0040334B@Rva0040334B@@QAEXPAVObject@@@Z @0x0040334B 55B unlock lane loop via Object pin.
// Evidence: cmp stack arg null then loop +0x20 to +0x24 step 0x10 calling pinned Object rva0028EA91 0x0028EA91 with string +4 and int +8 minus TheGameLogic+0x40; caller 0x00470A38.
#include "ascii_string.h"

class Object
{
public:
    bool rva0028EA91(const AsciiString &s, int v);
};
class GameLogic;
extern GameLogic *TheGameLogic;

struct Rva0040334BElem
{
    int m_00;
    AsciiString m_04;
    int m_08;
    int m_0C;
};

class Rva0040334B
{
public:
    void rva0040334B(Object *obj);
private:
    char m_pad[0x20];
    Rva0040334BElem *m_begin;
    Rva0040334BElem *m_end;
};

void Rva0040334B::rva0040334B(Object *obj)
{
    if (!obj)
        return;
    for (Rva0040334BElem *e = m_begin; e != m_end; ++e)
        obj->rva0028EA91(e->m_04, e->m_08 - *(int *)((char *)TheGameLogic + 0x40));
}
