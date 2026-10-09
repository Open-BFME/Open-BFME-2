#ifndef BFME2_REGION_ICON_SLOT_RESIZE_VIEW_H
#define BFME2_REGION_ICON_SLOT_RESIZE_VIEW_H
#include "RegionIconSlotReferenceView.h"
// Existing resize005EFDE9 owns its four-byte fill argument by value. The
// target one-argument wrapper005EFE6E transfers a null temporary to it.
// This shared specialization records that observed ABI; the primary STLport
// header in this checkout instead declares a const-reference fill argument.
struct Rva005EFDE9Element {
 Rva005EFD53Target *m_ptr;
 Rva005EFDE9Element():m_ptr(0) {}
 Rva005EFDE9Element(const Rva005EFDE9Element &x):m_ptr(x.m_ptr) { if(m_ptr)++m_ptr->m_refCount; }
 ~Rva005EFDE9Element() { if(m_ptr)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(reinterpret_cast<char *>(m_ptr)+4)); }
};
namespace _STL {
 template<class T> class allocator;
 template<class T,class A> class vector;
 template<> class vector<Rva005EFDE9Element,allocator<Rva005EFDE9Element> > {
 public:
 typedef unsigned int size_type;
 void _M_fill_insert(Rva005EFDE9Element *,size_type,const Rva005EFDE9Element &);
 Rva005EFDE9Element *erase(Rva005EFDE9Element *,Rva005EFDE9Element *);
 void resize(size_type,Rva005EFDE9Element);
 void resize(size_type);
 private: Rva005EFDE9Element *_M_start,*_M_finish,*_M_end_of_storage;
 };
}
#endif
