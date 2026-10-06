// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// ?rva00222F0A@Rva00222F0A@@QAEHXZ @0x00222F0A 75B
// Scan 14-entry table at +0xD8 for -1 slots and return first index absent from map at +0x84.
// Evidence: _M_find row 0x00357180 plus 0xE loop plus caller 0x00224754 using +0xD8 +0xCC +0x5C.
#include <map>
typedef _STL::map<unsigned int, void *> Map84_t;
enum { Map84Size = sizeof(Map84_t) };
class Rva00222F0A
{
public:
    int rva00222F0A();
private:
    char m_pad00[0x84];
    Map84_t m_map84;
    char m_pad01[0xD8 - 0x84 - Map84Size];
    struct Entry00222F0A {
        int m_v00;
        char m_pad[0x28 - 4];
    };
    Entry00222F0A m_entries[14];
};
int Rva00222F0A::rva00222F0A()
{
    int i = 0;
    Entry00222F0A *p = m_entries;
    for (; i < 14; i++) {
        if (p->m_v00 == -1) {
            unsigned int key = (unsigned int)i;
            if (m_map84.find(key) == m_map84.end())
                return i;
        }
        p++;
    }
    return -1;
}
