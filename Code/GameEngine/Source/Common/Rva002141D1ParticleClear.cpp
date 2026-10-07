// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
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
class Rva002141D1
{
public:
    void rva002141D1();
    void rva002118C2();
private:
    char unknown00[0x2A8];
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
