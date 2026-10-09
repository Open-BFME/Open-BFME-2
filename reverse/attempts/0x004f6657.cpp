// ??$__lower_bound@PAUTreeHintRef00217D4C@@U1@URva004F9185Cmp@@H@_STL@@YAPAUTreeHintRef00217D4C@@PAU1@0ABU1@URva004F9185Cmp@@PAH@Z
// partial score=0.86 date=2026-10-09
// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport4.5.3 bounds search; caller-owned comparison temporaries use
// the same target-supported handle conversion as the matched sort family.
#include <algorithm>
struct Key004F9185 { int _00[3]; int m_key; };
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; Key004F9185 *m_08; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {TargetRef00217D4C *m_ptr;};
struct ConstTreeHintRef00217D4C {
 TargetRef00217D4C *m_ptr;
 ConstTreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr) {if(m_ptr)++m_ptr->references;}
 __forceinline ~ConstTreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
};
struct Rva004F9185Cmp {
 __forceinline bool operator()(const ConstTreeHintRef00217D4C &a,const ConstTreeHintRef00217D4C &b) const {int ka=a.m_ptr->m_08->m_key;int kb=b.m_ptr->m_08->m_key;return ka>kb;}
};
template TreeHintRef00217D4C *_STL::__lower_bound(TreeHintRef00217D4C *,TreeHintRef00217D4C *,const TreeHintRef00217D4C &,Rva004F9185Cmp,int *);
template TreeHintRef00217D4C *_STL::__upper_bound(TreeHintRef00217D4C *,TreeHintRef00217D4C *,const TreeHintRef00217D4C &,Rva004F9185Cmp,int *);
