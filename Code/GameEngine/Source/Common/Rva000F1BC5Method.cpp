// cl: /MD /EHsc
// ?rva000F1BC5@Rva000F1BC5@@QAEXPBD@Z 0x000F1BC5 72B new Rva000F1B8F from arg plus Add to table at +4; caller none; callees new plus ctor 0x000F1B37 plus Add
class HashableClass {
};
class HashTableClass {
public:
    void Add(HashableClass *obj);
};
class Rva000F1B8F {
public:
    Rva000F1B8F(const char *s);
private:
    char _s[0xC];
};
class Rva000F1BC5 {
public:
    void rva000F1BC5(const char *s);
private:
    int _p0;
    HashTableClass *m_4;
};
void Rva000F1BC5::rva000F1BC5(const char *s)
{
    Rva000F1B8F *p = new Rva000F1B8F(s);
    m_4->Add(reinterpret_cast<HashableClass *>(p));
}
