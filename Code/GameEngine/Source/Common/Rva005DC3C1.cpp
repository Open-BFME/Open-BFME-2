// cl: /DNDEBUG /MD
// ?rva005DC3C1@Rva005DC3C1@@QAEXGGHH@Z @0x005DC3C1 71B unlock: two int[64] arrays at +0x18 and +0x118 plus list at +0x04 with forEach 0x005DBE6A and notify 0x001FF3A9, callers 0x005A68F8 and 0x005A8F41, neighbours forEach 0x005DBE6A and vector overflow 0x005DC499
class Rva005DBE6AListener
{
public:
    virtual void notify(void *, int, int);
};

class Rva005DBE6AList
{
public:
    void forEach(void (Rva005DBE6AListener::*notify)(void *, int, int), void *arg, int value, int extra);
private:
    Rva005DBE6AListener **m_begin; // +0x00
    Rva005DBE6AListener **m_end; // +0x04
    Rva005DBE6AListener **m_capacity; // +0x08
    unsigned int m_index; // +0x0C
};

class Rva001FF3A9Notify
{
public:
    virtual void rva001FF3A9();
};

class Rva005DC3C1
{
public:
    void rva005DC3C1(unsigned short a, unsigned short b, int expected, int newVal);
private:
    char m_pad00[4];
    Rva005DBE6AList m_list; // +0x04
    char m_pad14[0x18 - 0x14];
    int m_arr18[64]; // +0x18
    int m_arr118[64]; // +0x118
};

void Rva005DC3C1::rva005DC3C1(unsigned short a, unsigned short b, int expected, int newVal)
{
    if (a >= 8)
        return;
    if (b >= 8)
        return;
    int idx = b + a * 8;
    if (expected != m_arr118[idx])
        return;
    m_arr18[idx] = newVal;
    m_list.forEach((void (Rva005DBE6AListener::*)(void *, int, int))&Rva001FF3A9Notify::rva001FF3A9, this, a, b);
}
