// cl: /O1 /arch:SSE /G7 /MD
// Native 0x00555D74..0x00555DDC, ret 4: merge an object's trailing
// fields after its prefix merge at 0x00555845. That 323B callee traverses
// the source's maps at +0x154..+0x184 and cleans one pointer argument.
// Copy the two words unconditionally, retain only positive integer inputs,
// and assign the nonempty narrow string through rowed 0x000120C0.
// The original owner/method names remain unknown. Layout and conditions
// come from target bytes; the narrow-string identity follows its owned callee.

namespace _STL
{
template<class T> class char_traits {};
template<class T> class allocator {};
template<class C, class T, class A> class basic_string
{
public:
    basic_string &assign(const basic_string &source);
    unsigned size() const { return finish - start; }
private:
    C *start;
    C *finish;
    C *storageEnd;
};
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > Rva00555D74String;

class Rva00555D74
{
public:
    void rva00555D74(const Rva00555D74 *source);
    void rva00555845(const Rva00555D74 *source);
private:
    unsigned char pad00[0x190];
    unsigned short word190;
    unsigned short word192;
    int value194;
    int value198;
    Rva00555D74String text19C;
};

void Rva00555D74::rva00555D74(const Rva00555D74 *source)
{
    rva00555845(source);
    word190 = source->word190;
    word192 = source->word192;
    if (source->value194 > 0)
        value194 = source->value194;
    if (source->value198 > 0)
        value198 = source->value198;
    if (source->text19C.size() != 0)
        text19C.assign(source->text19C);
}
