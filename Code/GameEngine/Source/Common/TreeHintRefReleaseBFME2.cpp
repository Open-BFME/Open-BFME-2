// stlport
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// Retail0x7DEEF decrements the reference count at+4; on <=0 it invokes
// virtual slot0 with flag0 and deletes the returned allocation at0x2FD60.
// This release is called by the mapped value in pair destructor0x2175CE.
// The original application object type remains unknown.
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void operator delete(void *p);
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p) { if (--p->references <= 0) ::operator delete(p->destroy(0)); }
