// BfmeItemKAVector: a named layout matching STLport's vector<BfmeItemKA *> (begin, finish, end of storage), not the
// real vector type. It has no constructor or destructor on purpose: retail constructs the one instance
// (g_bfmeBegKA, retail RVA 0x009FEA44) in the initializer 0x007ADE2F (vector allocator ctor 0x004F710A) and destroys
// it in the atexit thunk 0x007B77B9, both rowed as explicit calls on its address. A real vector type would make the
// defining unit construct and destroy it a second time. Retail's push_back 0x004DFCB0, called on it from
// SubTitleWindow's constructor, reads +4 and compares it with +8.
#ifndef BFME2_BFMEITEMKAVECTOR_H
#define BFME2_BFMEITEMKAVECTOR_H

class BfmeItemKA;

struct BfmeItemKAVector
{
	BfmeItemKA **_M_start;           // +0x0
	BfmeItemKA **_M_finish;          // +0x4
	BfmeItemKA **_M_end_of_storage;  // +0x8
};

typedef char BfmeItemKAVectorSize[sizeof(BfmeItemKAVector) == 12 ? 1 : -1];

extern BfmeItemKAVector g_bfmeBegKA;

#endif
