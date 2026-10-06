// cl: /MD
// ?rva000F07C3@Rva000F26DC@@QAE_NHH@Z 0x000F07C3 64B alloc slot idx: new unsigned short[count*5] into +0x4180, zero +0x4400, store count at +0x4540; caller 0x000F16B4
void *__cdecl operator new[](unsigned int size);
class Rva000F26DC {
public:
    bool rva000F07C3(int idx, int count);
private:
    char _pad0[0x4180];
    unsigned short *m_ptrs[160];
    unsigned short m_zero[160];
    unsigned short m_counts[160];
};
bool Rva000F26DC::rva000F07C3(int idx, int count)
{
    int n = count * 5;
    unsigned short *p = new unsigned short[n];
    m_ptrs[idx] = p;
    if (p == 0)
        return false;
    m_zero[idx] = 0;
    m_counts[idx] = (unsigned short)n;
    return true;
}
