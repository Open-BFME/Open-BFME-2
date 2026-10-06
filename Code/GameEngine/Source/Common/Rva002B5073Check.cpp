// ?rva002B5073@Rva002B5073@@QAE_NH@Z @0x002B5073 74B.
// Vector at +0xCC searched for an element whose virtual slot 0x18 result overlaps the mask.
// Returns true on first overlap else false. Callees are all rowed. Unblocks 2 functions.
// TU-local honest-address views; element virtuals prove slot only not original names.
// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
struct Rva002B5073Elem {
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05(); virtual int slot06();
};
struct Rva002B5073 {
    char pad[0xCC];
    _STL::vector<Rva002B5073Elem *> vec;
    bool rva002B5073(int mask);
};
bool Rva002B5073::rva002B5073(int mask)
{
    for (unsigned int i = 0; i < vec.size(); ++i) {
        if (vec[i]->slot06() & mask)
            return true;
    }
    return false;
}
