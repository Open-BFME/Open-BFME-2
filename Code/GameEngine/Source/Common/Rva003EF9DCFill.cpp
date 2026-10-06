// cl: /DNDEBUG /MD /EHsc
// stlport
// ?Rva003EF9DCFill@@YGXPAURva003EF9DCNode@@PAV?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@@Z, retail 0x003EF9DC, 46 bytes.
// Free __stdcall drain of a +0x28-linked list into a vector<ObjectID> by
// inserting each node's +0 word at the vector's start. Callee is the rowed
// vector<ObjectID>::insert at 0x003EF85F. Callers 0x003EFB16 0x003EFBFD
// unblock 0x003EFA0A. Honest address name; node head and value role unproven.
enum ObjectID
{
    INVALID_ID = 0
};
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector
{
public:
    T *_M_start;
    T *_M_finish;
    T *_M_end_of_storage;
    T *insert(T *, const T &);
};
}
struct Rva003EF9DCNode
{
    ObjectID id00;
    char pad04[0x24];
    Rva003EF9DCNode *next28;
};

void __stdcall Rva003EF9DCFill(Rva003EF9DCNode *head, _STL::vector<ObjectID, _STL::allocator<ObjectID> > *vec)
{
    if (!head)
        return;
    for (Rva003EF9DCNode *p = head; p; p = p->next28) {
        ObjectID value = p->id00;
        vec->insert(vec->_M_start, value);
    }
}
