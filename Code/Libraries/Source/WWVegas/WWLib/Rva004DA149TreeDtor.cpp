// cl: /O1 /EHs /MD
// Ghidra [4DA149,4DA181),56B RET0. This clears nodes via the full41B
// tree-clear4D9FF2 then releases the header at receiver+0 through full17B
// GameMemory_free30830 if nonnull. Clear's native node/header accesses prove
// red-black tree teardown; the queued Pod340 fill-insert label is refuted.
// STLport4.5.3 tree destructor and existing56B tree-dtor siblings guide the
// base-storage split. Pointer0 and count4 come from target clear evidence;
// original application tree and payload identities remain unknown.
// EHs retains retail's unwind-state transition before freeing the header.
void free(void*);
class Rva004D9B4B {public:void rva004D9FF2();};
class Rva004DA149Storage {
protected:void *head;unsigned int count;
public:__forceinline ~Rva004DA149Storage(){if(head) free(head);}
};
class Rva004DA149Tree:public Rva004DA149Storage {public:~Rva004DA149Tree();};
Rva004DA149Tree::~Rva004DA149Tree(){reinterpret_cast<Rva004D9B4B*>(this)->rva004D9FF2();}
#pragma comment(linker, "/alternatename:?free@@YAXPAX@Z=_free")
