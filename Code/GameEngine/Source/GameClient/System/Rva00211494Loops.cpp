// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?rva00211494@Rva00211494@@QAEXXZ, RVA 0x00211494, 113 bytes.
// Two back-to-back vectors of object pointers at +0x234/+0x240; each element
// virtual slot 3 (+0x0C) called in index order. Evidence: caller 0x002123BE
// calls this first with same this (its +0x218 hashtable pins WindowVideoManager).
struct Rva00211494_Item
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
};

struct Rva00211494
{
	unsigned char m_pad[0x234];
	Rva00211494_Item **m_vec1Begin; // +0x234
	Rva00211494_Item **m_vec1End; // +0x238
	void *m_vec1Cap; // +0x23C
	Rva00211494_Item **m_vec2Begin; // +0x240
	Rva00211494_Item **m_vec2End; // +0x244
	void *m_vec2Cap; // +0x248
	void rva00211494();
};

void Rva00211494::rva00211494()
{
	unsigned int i;
	for (i = 0; i < (unsigned int)(m_vec2End - m_vec2Begin); ++i)
		m_vec2Begin[i]->v3();
	for (i = 0; i < (unsigned int)(m_vec1End - m_vec1Begin); ++i)
		m_vec1Begin[i]->v3();
}

// Caller and terminal cleanup use one shared partial receiver view below.
// Native 002141D1..00214243, 114B, terminal jump to 002118C2.
// 16-byte vector at +2A8, existing null particle-system factory and two
// rowed particle calls establish the handle semantics. Receiver identity
// and record tails remain unknown; preserve the range-erase element view.
class ParticleSystem
{
public:
    void destroy();
};
ParticleSystem *Make001FCBD7();
class Rva001F3852ByteOneSetter
{
public:
    void enable();
};
class BfmeParticleSystemPtr
{
public:
    operator ParticleSystem *() const { return target; }
    ParticleSystem *operator->() const
    {
        ParticleSystem *value = target;
        if (!value) value = Make001FCBD7();
        return value;
    }
private:
    ParticleSystem *volatile target;
};
struct Rva00213949Element
{
    BfmeParticleSystemPtr system;
    char unknown04[12];
};
namespace _STL
{
template<class T> class allocator {};
template<class T, class A=allocator<T> > class vector
{
public:
    unsigned int size() const { return last - first; }
    T *begin() { return first; }
    T *end() { return last; }
    T &operator[](unsigned int n) { return *(begin() + n); }
    T *erase(T *a, T *b);
    void clear() { erase(begin(), end()); }
private:
    T *first, *last, *limit;
};
}
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Rva003FC7FC { public: void rva003FC7FC(); };
class Rva002141D1
{
public:
    void rva002141D1();
    void rva002118C2();
private:
    char unknown00[0x234];
    Rva003FC7FC **first234, **last238, **limit23C;
    Rva003FC7FC **first240, **last244, **limit248;
    char unknown24C[0x2A8 - 0x24C];
    _STL::vector<Rva00213949Element> systems;
};
void Rva002141D1::rva002141D1()
{
    for (unsigned int i=0; i<systems.size(); ++i)
    {
        if (systems[i].system)
        {
            reinterpret_cast<Rva001F3852ByteOneSetter *>(systems[i].system.operator->())->enable();
            systems[i].system->destroy();
        }
    }
    systems.clear();
    rva002118C2();
}

// Native 002118C2..0021193B: this unit's rowed cleanup ends by calling
// this function on the same receiver. Compiler barriers preserve the native
// bound-load order, as in the matched Rva00211589 loop. Both ranges and the element
// clear target are independently visible in the complete native body.
void Rva002141D1::rva002118C2()
{
    unsigned int i;
    for (i=0; i<(unsigned int)(last238-first234); ++i) {
        _ReadWriteBarrier();
        Rva003FC7FC *item=first234[i];
        if (item) item->rva003FC7FC();
    }
    for (i=0; i<(unsigned int)(last244-first240); ++i) {
        _ReadWriteBarrier();
        Rva003FC7FC *item=first240[i];
        if (item) item->rva003FC7FC();
    }
}
