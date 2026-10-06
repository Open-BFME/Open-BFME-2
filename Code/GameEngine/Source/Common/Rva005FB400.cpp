// cl: /MD
// ??0Rva005FB400@@QAE@PBX@Z @0x005FB400 24B: honest ctor storing vtable VA 0x00C79F24 at [this] plus zeroes +4 plus copies *arg to +8. Evidence: caller new 0xc at 0x005FB46F plus ret 4 plus precedent Rva005FB22BCtor same 24B shape.
class __declspec(novtable) Rva005FB400
{
public:
    Rva005FB400(const void *arg);
    virtual ~Rva005FB400();
private:
    int m_04;
    void *m_08;
};
extern const void *const g_00C79F24[];
Rva005FB400::Rva005FB400(const void *arg)
{
    m_04 = 0;
    *(const void **)this = g_00C79F24;
    m_08 = *(void *const *)arg;
}
