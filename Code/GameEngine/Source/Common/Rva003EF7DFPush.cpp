// cl: /DNDEBUG /MD /EHsc
// ?rva003EF7DF@Rva003EF7DF@@QAEXPAURva003EF7DFDest@@H@Z, retail 0x003EF7DF, 48 bytes.
// __thiscall lookup-and-collect: indexes this record-pointer span via the
// just-landed 0x003EF648 and push_backs the hit into the dest vector at +4.
// Caller 0x0020F64A unblocks 0x0020F5B3. Honest address names; dest head and
// record type beyond the compared id word are unproven.
class ModuleData;
struct Rva003EF648Item
{
    int id;
};
struct Rva003EF648Span
{
    Rva003EF648Item **begin;
    Rva003EF648Item **end;
};
int __stdcall Rva003EF648Index(Rva003EF648Span *span, int value);
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector
{
public:
    void push_back(T const &);
};
}
struct Rva003EF7DFDest
{
    int unknown00;
    _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > vec04;
};
class Rva003EF7DF
{
    Rva003EF648Item **begin00;
    Rva003EF648Item **end04;
public:
    void rva003EF7DF(Rva003EF7DFDest *dest, int value);
};

void Rva003EF7DF::rva003EF7DF(Rva003EF7DFDest *dest, int value)
{
    int index = Rva003EF648Index((Rva003EF648Span *)this, value);
    if (index != -1)
        dest->vec04.push_back((const ModuleData *)begin00[index]);
}
