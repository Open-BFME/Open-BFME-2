// cl: /DNDEBUG /MD /EHsc /Ob2
// ??1Rva005F566A@@UAE@XZ @0x005F566A 14B: dtor sets vptr then tail-jmps to rowed clear 0x005F55FA; caller deleting dtor 0x005F5678
void *__cdecl operator new(unsigned int size) throw();

class Rva005F566A;
class Rva0057C394;

// Native 5F53E6 stores owner/provider/callback at 0/4/8 and builds two
// army handlers. WB independently names ArmyUnitSwapperDialog::Impl.
// The other forwarded input identities remain opaque.
class Rva005F54DA {
public:
    Rva005F54DA(Rva005F566A *owner, Rva0057C394 *provider,
        void *firstA, void *firstB, void *secondA, void *secondB, void *callback);
private:
    char storage[0x1C];
};

class Rva005F55FA {
public:
    void clear();
    __forceinline void setNew(Rva005F54DA *value) { pointer = value; }
private:
    Rva005F54DA *pointer;
};

class Rva005F566A {
public:
    Rva005F566A(Rva0057C394 *provider, void *firstA, void *firstB,
        void *secondA, void *secondB, void *callback);
    virtual ~Rva005F566A();
    Rva005F55FA m_holder;
};

// Native 5F5614..5F566A forwards owner plus six arguments to new 1C Impl.
Rva005F566A::Rva005F566A(Rva0057C394 *provider, void *firstA, void *firstB,
    void *secondA, void *secondB, void *callback)
{
    m_holder.setNew(new Rva005F54DA(this, provider, firstA, firstB,
        secondA, secondB, callback));
}

Rva005F566A::~Rva005F566A()
{
    m_holder.clear();
}
