// ?rva0041112B@Rva000427195@@QAEPAXPBVAsciiString@@@Z
// partial score=0.96529 date=2026-10-08
// Trial only: pair destructor uses read-only proposed binding 0x00410688.
// Production pair<TreeHintRef00217D4C> destructor owns 0x002175CE;
// do not add a second pin. Reconcile the actual screen-map value type first.
// Direct-pair trial: full156B, stack frame24 vs native20, offsets -1C/-24
// vs native -18/-20. Existing Rva00410688 composition stays159B at .90597.
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
#include "ascii_string.h"
struct TargetRef00217D4C {virtual void *destroy(unsigned int); int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
    TargetRef00217D4C *m_ptr;
    TreeHintRef00217D4C():m_ptr(0){}
    ~TreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
};
struct TreeHintPayload00410A86 {unsigned char m_body[4];};
namespace _STL {
 template<class A,class B>struct pair {
     pair(const A &,const B &);
     ~pair();
     A first; B second;
 };
}
typedef _STL::pair<const AsciiString, TreeHintRef00217D4C> ScreenRefPair;
class Rva00410688 {
public:
    __forceinline Rva00410688(const AsciiString &key,const TreeHintRef00217D4C &value):m_value(key,value){}
    ~Rva00410688();
    ScreenRefPair m_value;
};
class Rva00056F61;
struct Rva0041534BIter {
 void *m_node; Rva00056F61 *m_table;
 Rva0041534BIter(void *n,Rva00056F61 *t):m_node(n),m_table(t){}
};
class Rva00056F61 {public:Rva0041534BIter rva0041534B(const AsciiString *);};
class Rva000427195 {
public:
 _STL::pair<const AsciiString,TreeHintPayload00410A86> *rva00410DDF(const _STL::pair<const AsciiString,TreeHintPayload00410A86> *);
 void *rva0041112B(const AsciiString *);
};
void *Rva000427195::rva0041112B(const AsciiString *name) {
 Rva0041534BIter found=((Rva00056F61 *)this)->rva0041534B(name);
 return !found.m_node ? (char *)rva00410DDF((const _STL::pair<const AsciiString,TreeHintPayload00410A86> *)&ScreenRefPair(*name,TreeHintRef00217D4C()))+4 : (char *)found.m_node+8;
}
