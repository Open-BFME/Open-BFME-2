// cl: /MD
// ?rva000EFDA0@Rva000EFDA0@@QAEXXZ 0x000EFDA0 27B free array at +0x24 via delete[] then zero +0x24 +0x28; callers 0x000F11C0 0x000F2963
void operator delete[](void *block);
class Rva000EFDA0 {
public:
    void rva000EFDA0();
private:
    char _pad0[0x24];
    char *m_24;
    int m_28;
};
void Rva000EFDA0::rva000EFDA0()
{
    if (m_24 != 0) {
        ::operator delete[](m_24);
        m_24 = 0;
        m_28 = 0;
    }
}
