// cl: /MD
// ??0Rva005753D1@@QAE@XZ @0x005753D1 12B. Trivial derived ctor delegating to
// rowed base ctor 0x005CC61E. Evidence: same this passed through; returns this.
class Rva005CC61E {
public:
    Rva005CC61E();
    int *m_ptr00;
};
class Rva005753D1 : public Rva005CC61E {
public:
    Rva005753D1();
};
Rva005753D1::Rva005753D1()
{
}
