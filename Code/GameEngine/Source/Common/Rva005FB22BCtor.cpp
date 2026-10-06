// cl: /MD
// ??0Rva005FB22B@@QAE@PBX@Z @ 0x005FB22B 24B
// Honest address-name ctor beside Rva005FA393Dtor. Target evidence: 24B
// retail stores vtable VA 0x879F04 at [this], zeroes +4, copies *arg to +8,
// 1 caller 0x5FB2B3, ret 4. Prev dtor shares /O1 /MD shape.
class __declspec(novtable) Rva005FB22B
{
public:
    Rva005FB22B(const void *arg);
    virtual ~Rva005FB22B();
private:
    int m_04;
    void *m_08;
};
extern const void *const g_00879F04[];
Rva005FB22B::Rva005FB22B(const void *arg)
{
    m_04 = 0;
    *(const void **)this = g_00879F04;
    m_08 = *(void *const *)arg;
}
