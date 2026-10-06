// cl: /MD
// ?rva006CE630@Rva006CE630@@QAEPAXI@Z @0x006CE630 35B evidence chain via 0x006DB270 freeBlock plus detach row 0x006CD530 plus pool 0x00A176E8 size 8 plus ret-4 flag free
class Rva006CD530 {
public:
    void detach();
};
class Rva006DB270 {
public:
    void freeBlock(void *p, int size);
};
extern Rva006DB270 *g_pChainBlockAllocator;
struct Rva006CE630 {
    void *m00;
    void *rva006CE630(unsigned int flags);
};
void *Rva006CE630::rva006CE630(unsigned int flags)
{
    ((Rva006CD530 *)this)->detach();
    if ((flags & 1) != 0)
        g_pChainBlockAllocator->freeBlock(this, 8);
    return this;
}
