// Target facts (code addresses are RVAs; tables are VAs): ImageSubscriptMap is this project's nonvirtual unsigned-key pointer-map call view, with no virtual functions or observed base subobject. Its only ledger member is operator[] 0x002077D6: lower_bound call 0x002077E3 targets 0x004FF3B6, unsigned comparison 0x002077EE reads node+0x10, insert call 0x0020780B targets 0x00358211, and 0x00207813 returns the mapped four-byte lvalue at node+0x14. ImageCollection::addImage calls it on collection+0x0C at 0x002D947A.
// Allocation size 0x0C at 0x0035834E, constructor call 0x00358363 to 0x0033C432 and subscript call 0x0035838D share one allocation; ScriptEngine::setObjectCount independently indexes maps with stride 0x0C at 0x00207E0D. Constructor chain 0x0033C432 -> 0x001F068F -> 0x001F0534 stores the allocated header pointer at map+0 (0x001F054E) and zero at map+4 (0x001F069F). Clear 0x002D9186 tests and clears map+4; destructor 0x002D922A clears the tree and frees map+0. Neither lifetime installs a vptr; bytes +8..+0x0B retain neutral storage names.
// ImageCollection constructor 0x002D932B calls SubsystemInterface 0x001B4E63, installs table VA 0x00C03878 at collection+0 (0x002D9348), then constructs the map at collection+0x0C (0x002D934E). Destructor 0x002D9283 restores that collection table, destroys the map through 0x002D922A and calls base destructor 0x001B4E74, which restores VA 0x00BD77A0. Both 14-slot tables belong to the enclosing collection/base lifetime, not the map. No ImageSubscriptMap constructor, destructor, copy or assignment ledger row establishes another out-of-line method name.

#pragma once
#ifndef __BFME2_IMAGESUBSCRIPTMAP_H_
#define __BFME2_IMAGESUBSCRIPTMAP_H_

class Image;

class ImageSubscriptMap
{
public:
    Image *&operator[](const unsigned int &key);

private:
    void *m_storage00;
    unsigned int m_storage04;
    unsigned char m_storage08[4];
};

typedef char ImageSubscriptMapSizeCheck[sizeof(ImageSubscriptMap) == 0x0C ? 1 : -1];

#endif
