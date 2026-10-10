// cl: /O1 /MD
// Native38-byte RET4 cleanup wrapper on the sameB4 allocation as6E6060.
// Constructor/dtor field evidence establish a nonvirtual pool-data object;
// preserve the wrapper under an address-derived method without asserting a vtable.
class Rva006DB270{public:void freeBlock(void*,int);};extern Rva006DB270*g_pChainBlockAllocator;
class Rva006E6060Root{char data[0xB4];public:~Rva006E6060Root();void*rva006CC320(unsigned);};
void*Rva006E6060Root::rva006CC320(unsigned flags){this->~Rva006E6060Root();if(flags&1)g_pChainBlockAllocator->freeBlock(this,sizeof(*this));return this;}
