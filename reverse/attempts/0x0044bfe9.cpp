// ?MessageBoxYesNo@@YAXVUnicodeString@@0P6AXXZ1@Z
// partial score=0.87 date=2026-10-09
// cl: /O1 /arch:SSE /G7 /EHsc /MD /Ireference/shims/bfme2_ascii
#include "unicode_string.h"
struct TargetRef00217D4C { void *m_vtbl; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva0044BC76 {
public:
    Rva0044BC76(const int *);
    TargetRef00217D4C *m_ptr;
};
typedef void(*GameWinMsgBoxFunc)();
struct Rva004F6986Member : Rva0044BC76 {
    __forceinline Rva004F6986Member(GameWinMsgBoxFunc fn) : Rva0044BC76((const int*)&fn) {}
    __forceinline Rva004F6986Member(const Rva004F6986Member &other) : Rva0044BC76(other) {
        if (m_ptr) ++m_ptr->references;
    }
    __forceinline ~Rva004F6986Member() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
struct Rva004C5DD0Ref { int m_00, m_refs; };
struct Rva004C5DD0Pair { Rva004C5DD0Ref *a, *b; };
class Rva004C5DD0 {
    Rva004C5DD0Ref *m_00,*m_04;
public: Rva004C5DD0 &set(const Rva004C5DD0Pair *);
};
struct Rva0044BA4E {
    Rva0044BA4E(Rva004F6986Member,Rva004F6986Member);
    ~Rva0044BA4E();
    __forceinline Rva0044BA4E(const Rva0044BA4E &other) {
        ((Rva004C5DD0 *)this)->set((const Rva004C5DD0Pair *)&other);
    }
    TargetRef00217D4C *m_00,*m_04;
};
struct Rva0051732A {
    TargetRef00217D4C *m_ptr;
    Rva0051732A *rva0051732A(TargetRef00217D4C *);
    __forceinline Rva0051732A(const Rva0051732A &other) : m_ptr(other.m_ptr) {
        if(m_ptr) ++m_ptr->references;
    }
    __forceinline ~Rva0051732A() { if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
    __forceinline Rva0051732A(const int *fn) { rva0051732A(Rva0044BC76(fn).m_ptr); }
};
struct Rva0044BF40 { void *m_ptr; Rva0044BF40 *rva0044BF40(Rva0044BA4E); };
struct Rva0044BFB2 { void *m_ptr; Rva0044BFB2 *rva0044BFB2(Rva0044BA4E); };
struct Rva0044BF77 { void *m_ptr; Rva0044BF77 *rva0044BF77(Rva0051732A); };
class Rva0023E8D8 {
    TargetRef00217D4C *m_ptr;
public:
    __forceinline Rva0023E8D8(const Rva0044BA4E &pair,int kind) {
        if(kind==1) ((Rva0044BFB2*)this)->rva0044BFB2(pair);
        else ((Rva0044BF40*)this)->rva0044BF40(pair);
    }
    __forceinline Rva0023E8D8(const Rva0051732A &single) {
        ((Rva0044BF77*)this)->rva0044BF77(single);
    }
    __forceinline Rva0023E8D8(const Rva0023E8D8 &other):m_ptr(other.m_ptr) {
        if(m_ptr) ++m_ptr->references;
    }
    __forceinline ~Rva0023E8D8(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
};
extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0023E8D8);
typedef void(*GameWinMsgBoxFunc)();
__declspec(noinline) void MessageBoxNullCallback() {}
void MessageBoxYesNo(UnicodeString title,UnicodeString message,GameWinMsgBoxFunc yes,GameWinMsgBoxFunc no) {
    Rva00437F61(2,title,message,Rva0023E8D8(Rva0044BA4E(yes?yes:MessageBoxNullCallback,no?no:MessageBoxNullCallback),2));
}
void MessageBoxOkCancel(UnicodeString title,UnicodeString message,GameWinMsgBoxFunc ok,GameWinMsgBoxFunc cancel) {
    Rva00437F61(1,title,message,Rva0023E8D8(Rva0044BA4E(ok?ok:MessageBoxNullCallback,cancel?cancel:MessageBoxNullCallback),1));
}
void MessageBoxOk(UnicodeString title,UnicodeString message,GameWinMsgBoxFunc ok) {
    ok=ok?ok:MessageBoxNullCallback;
    Rva0051732A single((const int*)&ok);
    Rva00437F61(0,title,message,Rva0023E8D8(single));
}
