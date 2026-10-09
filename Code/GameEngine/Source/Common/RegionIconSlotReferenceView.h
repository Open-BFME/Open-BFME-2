#ifndef BFME2_REGION_ICON_SLOT_REFERENCE_VIEW_H
#define BFME2_REGION_ICON_SLOT_REFERENCE_VIEW_H
// Borrowed twelve-byte prefix: primary word00 and reference base04/count08.
// _Construct005F09FF retains count08; resize005EFDE9 releases base04.
// Factory005EFE87 supplies the64-byte Rva005EEF2F slot. This prefix does
// not assert the remaining pointee layout or the original handle spelling.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct Rva005EFD53Target { int m_head00; void *m_vtable04; int m_refCount; };
struct Rva005EFD53Element {
 Rva005EFD53Target *m_ptr;
 Rva005EFD53Element(Rva005EFD53Target *p=0):m_ptr(p) { if(m_ptr)++m_ptr->m_refCount; }
 Rva005EFD53Element(const Rva005EFD53Element &x):m_ptr(x.m_ptr) { if(m_ptr)++m_ptr->m_refCount; }
 ~Rva005EFD53Element() { if(m_ptr)ReleaseTreeHintRef00217D4C(reinterpret_cast<TargetRef00217D4C *>(reinterpret_cast<char *>(m_ptr)+4)); }
};
#endif
