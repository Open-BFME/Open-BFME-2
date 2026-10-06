// cl: /MD /EHsc
// ??0Rva000F0AF7@@QAE@XZ 0x000F0AF7 110B ctor of 8-byte holder of two HashTableClass(0x800); caller 0x000F1A32 does new 8 + this ctor
class HashTableClass {
public:
    HashTableClass(int size);
private:
    int m_size;
    void *m_table;
};
class Rva000F0AF7 {
public:
    Rva000F0AF7();
private:
    HashTableClass *m_a;
    HashTableClass *m_b;
};
Rva000F0AF7::Rva000F0AF7()
{
    m_a = new HashTableClass(0x800);
    m_b = new HashTableClass(0x800);
}
