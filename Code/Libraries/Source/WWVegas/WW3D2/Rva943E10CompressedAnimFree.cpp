// cl: /DNDEBUG /MD /EHsc
// Without an explicit declaration MSVC reaches for the scalar ??3 here; retail
// frees the block through operator delete[] (??_V) at 0x00881EF0.
#include <new>

// The array element is retail's 0x1C-byte scene-list element: its destructor
// is 0x00141CA0 and its vector-deleting destructor 0x00141D00, both rowed in
// Rva00141D00VectorDeletingDtor.cpp (vtable + 0x14-byte head at +4).
class BfmeNonRefSceneList
{
public:
    virtual ~BfmeNonRefSceneList();

private:
    char m_pad[0x14];
};

class Rva00141D00
{
public:
    ~Rva00141D00();

private:
    int m_pad;
    BfmeNonRefSceneList m_list;
};

class Rva943E10CompressedAnim
{
public:
    void free();

private:
    unsigned char data[24];
    Rva00141D00 *node_motion;
};

// ?d_00943e10@@YAXXZ
// ?Rva943E10CompressedAnim::free present-unmatched
void Rva943E10CompressedAnim::free()
{
    if (node_motion != 0) {
        delete[] node_motion;
    }
}
