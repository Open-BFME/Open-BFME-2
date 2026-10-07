// ?rva001EC859@Rva001EC859@@QAEPAXHH@Z
// partial score=0.88 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native Ghidra 001EC859..001EC8C0, 103B, RET8.
// Preserve the existing address-derived caller pin's word ABI (void*, int, int).
// Search 001EB023 proves a 172-byte record range at +A4/+A8; its key input
// is a Rva00376A62 reference. The native result reads ObjectID +74 and sets
// the +438 byte's bit 10; the record quantity is signed at +90.
class Object;
class Rva00376A62;
struct Rva001EB023Elem
{
    char unknown00[0x90];
    int quantity;
    char unknown94[0xAC - 0x94];
};
class Rva001EB023
{
public:
    Rva001EB023Elem *rva001EB023(Rva00376A62 &key);
};
class Rva0037DCE8
{
public:
    Object *rva0037DCE8(int argument);
};
struct Rva001EC859ObjectView
{
    char unknown00[0x74];
    unsigned int id;
    char unknown78[0x438 - 0x78];
    unsigned char flags;
};
struct BfmePod172 { int a[43]; };
namespace _STL
{
template<class T> class allocator {};
template<class T, class A=allocator<T> > class vector
{
public:
    void push_back(const T &value);
private:
    T *first, *last, *limit;
};
}
class Rva001EBCD8
{
public:
    void *rva001EBCD8(void *record);
};
class Rva001EC859
{
public:
    void *rva001EC859(int key, int argument);
private:
    char unknown00[0xA4];
    Rva001EB023Elem *first, *last, *limit;
    int unknownB0;
    _STL::vector<BfmePod172> used;
};
void *Rva001EC859::rva001EC859(int key, int argument)
{
    unsigned int id = 0;
    Rva001EB023Elem *record = reinterpret_cast<Rva001EB023 *>(this)
        ->rva001EB023(*reinterpret_cast<Rva00376A62 *>(key));
    if (record != last)
    {
        Object *object = reinterpret_cast<Rva0037DCE8 *>(record)->rva0037DCE8(argument);
        if (object)
        {
            Rva001EC859ObjectView *view = reinterpret_cast<Rva001EC859ObjectView *>(object);
            id = view->id;
            view->flags |= 0x10;
        }
        used.push_back(*reinterpret_cast<const BfmePod172 *>(record));
        int quantity = record->quantity;
        if (quantity <= 1)
            reinterpret_cast<Rva001EBCD8 *>(reinterpret_cast<char *>(this) + 0xA4)
                ->rva001EBCD8(record);
        else
            record->quantity = quantity - 1;
    }
    return reinterpret_cast<void *>(id);
}
