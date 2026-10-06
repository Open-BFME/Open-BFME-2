// cl: /MD
// ?rva000F0803@Rva000F26DC@@QAEXH@Z 0x000F0803 47B frees slot idx: delete[] ptr at +0x4180 then zeroes word at +0x4400; callers 0x000F16B4 0x000F26DC dtor loop 160
void operator delete[](void *block);
class Rva000F26DC {
public:
    void rva000F0803(int idx);
private:
    char _pad0[0x4180];
    char *m_ptrs[160];
    unsigned short m_words[160];
};
void Rva000F26DC::rva000F0803(int idx)
{
    if (m_ptrs[idx] != 0)
        delete[] m_ptrs[idx];
    m_words[idx] = 0;
    m_ptrs[idx] = 0;
}
