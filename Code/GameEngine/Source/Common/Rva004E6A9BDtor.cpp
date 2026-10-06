// cl: /O1 /MD /EHsc
// ??1Rva004E6A9B@@QAE@XZ @0x004E6A9B 157B
// Non-virtual dtor of Rva004E6A9B. Notifies via globals then clears holders.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
class Rva00224B7DTarget
{
public:
    bool method(int v);
};
class DisplayStringManager
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(int v);
};
extern DisplayStringManager *TheDisplayStringManager;
class Rva004E6A1D
{
public:
    ~Rva004E6A1D() { clear(); }
    void clear();
    void *m_ptr;
};
class Rva0052413E
{
public:
    ~Rva0052413E();
    char m_pad[12];
};
class Rva005241B0
{
public:
    ~Rva005241B0();
    char m_pad[12];
};
class Rva00524265
{
public:
    ~Rva00524265();
    char m_pad[12];
};
class Rva005242D7
{
public:
    ~Rva005242D7();
    char m_pad[16];
};
class Rva004E6A9BBase
{
public:
    virtual void b0();
    ~Rva004E6A9BBase() {}
};
class Rva004E6A9B : public Rva004E6A9BBase
{
public:
    ~Rva004E6A9B();
    int m04;
    char m_pad08[4];
    Rva0052413E m0C;
    Rva005241B0 m18;
    Rva00524265 m24;
    Rva005242D7 m30;
    Rva004E6A1D m40;
    Rva004E6A1D m44;
    int m48;
    int m4C;
};
Rva004E6A9B::~Rva004E6A9B()
{
    if (TheRva00222A8BTarget)
        ((Rva00224B7DTarget *)TheRva00222A8BTarget)->method(m04);
    if (TheDisplayStringManager)
        TheDisplayStringManager->v15(m4C);
}
