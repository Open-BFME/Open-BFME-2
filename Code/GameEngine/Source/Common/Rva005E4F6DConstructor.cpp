// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native destructor 5E5018..5E508F has two interfaces at 0 and 8,
// shared virtual counted base at 14 and owned child at 10. The hidden
// native teardown adjusts the virtual-base this bias and clears the child.
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
Rva005E4F6D::~Rva005E4F6D() {}

// The constructor 5E6ED6 calls the 12-byte polymorphic base at 0 and
// Rva005E4F6D at C. Its shared counted base moves to24; the second owned
// pointer at20 is independently cleared in the native102-byte teardown.
class Rva005F64F5
{
public:
    virtual ~Rva005F64F5();
private:
    void *data4;
    void *owned8;
};
class Rva005E6D90
{
public:
    ~Rva005E6D90() { clear(); }
    void clear();
private:
    void *value;
};
class Rva005E6F9D : public Rva005F64F5, public Rva005E4F6D
{
public:
    virtual ~Rva005E6F9D();
private:
    Rva005E6D90 child20;
};
Rva005E6F9D::~Rva005E6F9D() {}
