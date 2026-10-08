// ?_bfme_setAptScreenRef@@YAXABVAsciiString@@V?$AptRef@VAptScreenInitGadgets@@@@@Z
// partial score=1.0 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
#include "ascii_string.h"
struct TargetRef00217D4C {virtual void *destroy(unsigned int); int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
struct TreeHintRef00217D4C {
    TargetRef00217D4C *m_ptr;
    TreeHintRef00217D4C():m_ptr(0){}
    TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &);
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

class AptScreenInitGadgets;
template<class T>class AptRef {
public:
 ~AptRef(){if(m_ptr)ReleaseTreeHintRef00217D4C(m_ptr);}
 TargetRef00217D4C *m_ptr;
};
extern Rva000427195 g_aptScreenReferences;
void _bfme_setAptScreenRef(const AsciiString &name,AptRef<AptScreenInitGadgets> incoming) {
 TreeHintRef00217D4C *slot=(TreeHintRef00217D4C *)g_aptScreenReferences.rva0041112B(&name);
 *slot=*(const TreeHintRef00217D4C *)&incoming;
}
