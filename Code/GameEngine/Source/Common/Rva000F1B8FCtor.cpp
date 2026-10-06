// cl: /MD /EHsc
// ??0Rva000F1B8F@@QAE@PBD@Z 0x000F1B37 60B ctor vtable g_00BCEFD4 plus m_04 zero plus String m_08 from arg plus false; caller 0x000F1BEC new 0xC plus Add
class StringClass {
    void *m_data;
    void Free_String();
public:
    StringClass(const char *name, bool flag);
    ~StringClass(void);
};
struct Rva000F1B8FBase {
    int m_04;
    Rva000F1B8FBase() : m_04(0) {}
    virtual ~Rva000F1B8FBase() {}
};
struct Rva000F1B8F : Rva000F1B8FBase {
    StringClass m_08;
    Rva000F1B8F(const char *s);
    virtual ~Rva000F1B8F();
};
Rva000F1B8F::Rva000F1B8F(const char *s) : m_08(s, false)
{
}

// Native public teardown and Free_String share0x00610A40 (DX8Wrapper call proof).
#pragma comment(linker, "/alternatename:??1StringClass@@QAE@XZ=?Free_String@StringClass@@AAEXXZ")
