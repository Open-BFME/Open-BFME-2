// ??0Rva005E4F6D@@QAE@PAU_Rva005E4AE2In@@H@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native constructor 5E4F6D..5E5018 has two interfaces at 0 and 8,
// shared virtual counted base at 14 and owned child at 10. The hidden
// most-derived flag controls both vbtables and the counted-base initialization.
struct RvaSmallVtableZeroBase { void *m_04; RvaSmallVtableZeroBase() : m_04(0) {} };
class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
    Rva0007DF07() {}
    virtual ~Rva0007DF07() {}
};
class Rva005CC5E5 : public virtual Rva0007DF07
{
public:
    Rva005CC5E5();
    virtual void slot0();
    virtual ~Rva005CC5E5() {}
};
class Rva005E3AE1 : public virtual Rva0007DF07
{
public:
    Rva005E3AE1();
    virtual void slot0() = 0;
    virtual ~Rva005E3AE1();
};
struct _Rva005E4AE2In;
class Rva005E4AE2
{
public:
    Rva005E4AE2(void *, _Rva005E4AE2In *, int);
private:
    char storage[0x30];
};
class Rva005E4B9D
{
public:
    Rva005E4B9D(Rva005E4AE2 *v) : value(v) {}
    ~Rva005E4B9D() { clear(); }
    void clear();
    Rva005E4AE2 *value;
};
class Rva005E4F6D : public Rva005CC5E5, public Rva005E3AE1
{
public:
    Rva005E4F6D(_Rva005E4AE2In *, int);
    virtual ~Rva005E4F6D();
    virtual void slot0();
    virtual void slot1();
private:
    Rva005E4B9D child;
};
Rva005E4F6D::Rva005E4F6D(_Rva005E4AE2In *info, int count)
    : child(new Rva005E4AE2(this, info, count)) {}
Rva005E4F6D::~Rva005E4F6D() {}
