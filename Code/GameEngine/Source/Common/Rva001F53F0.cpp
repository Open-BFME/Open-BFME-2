// cl: /MD
// ?rva001F53F0@Rva001F53F0@@QAEHXZ @0x001F53F0 14B
// Null-checked ptr at +0x1c8 returning dword at +0x20 else 0. Caller at 0x003A5A89.
// Honest Rva names; /O1 for je shape like sibling Rva001F53BCGet.
struct Inner001F53F0 {
    char m_pad[0x20];
    int m_val;
};
class Rva001F53F0 {
public:
    int rva001F53F0();
private:
    char m_pad[0x1c8];
    Inner001F53F0 *m_ptr;
};
int Rva001F53F0::rva001F53F0()
{
    Inner001F53F0 *p = m_ptr;
    if (p)
        return p->m_val;
    return 0;
}
