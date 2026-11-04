// cl: /DNDEBUG /MD /EHsc
// ?Rva00895050@Gen_uw_00893e70@@QAEXPAV1@@Z @0x006D0040 301B evidence donor Rva00895050InlineContainerSwap plus callers 0x006D03E8 plus Rva006CD5A0Copy row plus AptValueNameEntry ctor row
#include "../../../Libraries/Source/Apt/EAStringC.h"
class AptValueNameEntry
{
public:
    AptValueNameEntry() throw() { m_value = 0; }
    EAStringC m_name;
    int m_value;
};
class Rva006CD5A0Elem
{
public:
    EAStringC m_name;
    int m_value;
};
extern Rva006CD5A0Elem *__cdecl Rva006CD5A0Copy(Rva006CD5A0Elem *first, Rva006CD5A0Elem *last, Rva006CD5A0Elem *dest);
class Gen_uw_00893e70
{
public:
    void Rva00895050(Gen_uw_00893e70 *other);
    unsigned int m_count;
    unsigned int m_capacity;
    Rva006CD5A0Elem *m_data;
    Rva006CD5A0Elem m_inline[2];
};
void Gen_uw_00893e70::Rva00895050(Gen_uw_00893e70 *other)
{
    unsigned int count = other->m_count;
    other->m_count = m_count;
    m_count = count;
    unsigned int capacity = other->m_capacity;
    other->m_capacity = m_capacity;
    Rva006CD5A0Elem *data = m_data;
    bool this_inline = data == m_inline;
    m_capacity = capacity;
    bool other_inline = other->m_data == other->m_inline;
    if (other_inline)
        m_data = m_inline;
    else
        m_data = other->m_data;
    if (this_inline)
        other->m_data = other->m_inline;
    else
        other->m_data = data;
    if (!other_inline && !this_inline)
        return;
    AptValueNameEntry temporary[2];
    temporary[1] = AptValueNameEntry();
    Rva006CD5A0Copy(m_inline, m_inline + 2, (Rva006CD5A0Elem *)temporary);
    Rva006CD5A0Copy(other->m_inline, other->m_inline + 2, m_inline);
    Rva006CD5A0Copy((Rva006CD5A0Elem *)temporary, (Rva006CD5A0Elem *)temporary + 2, other->m_inline);
}
