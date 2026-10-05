// cl: /O2 /Ob0 /O1
// ?rva003888F9@Rva003888F9@@QAEHH@Z @0x003888F9 27B unlock lane bounds getter.
// Evidence: same 27B shape as rowed get 0x003888C3; cmp index 0 and 8 then array +0x21C else 0; callers 0x0038DDBC 0x0038DDD1.
class Rva003888F9
{
    char m_pad[0x21C];
    int m_slots[8];

public:
    int rva003888F9(int index);
};

int Rva003888F9::rva003888F9(int index)
{
    if (index < 0 || index >= 8)
        return 0;
    return m_slots[index];
}
