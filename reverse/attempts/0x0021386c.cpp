// ?rva0021386C@Rva00056F61@@QAEAAPAXPBVAsciiString@@@Z
// partial score=0.97 date=2026-10-08
// cl: /O1 /G7 /Oy- /Ob2 /EHsc /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
struct Rva00212A16Record;
namespace _STL {
template<class A,class B> struct pair;
template<class T> struct hash;
template<class T> struct _Select1st;
template<class T> struct equal_to;
template<class T> class allocator;
template<class V,class K,class H,class S,class E,class A> class hashtable {
public: V &_M_insert(const V&);
};
}
typedef _STL::pair<const Rva00212A16Record,Rva00212A16Record> InsertPair;
typedef _STL::hashtable<InsertPair,Rva00212A16Record,_STL::hash<Rva00212A16Record>,_STL::_Select1st<InsertPair>,_STL::equal_to<Rva00212A16Record>,_STL::allocator<InsertPair> > InsertTable;
class Rva00056F61;
struct Rva0041534BIter {
 void *m_node;
 Rva00056F61 *m_table;
 Rva0041534BIter(void*n,Rva00056F61*t):m_node(n),m_table(t){}
};
struct SoundPair21386C {
 AsciiString name;
 void *sound;
 SoundPair21386C(const AsciiString &n,void*s):name(n),sound(s){}
};
class Rva00056F61 {
public:
 Rva0041534BIter rva0041534B(const AsciiString*);
 void *&rva0021386C(const AsciiString*);
};
void *&Rva00056F61::rva0021386C(const AsciiString *key)
{
 void *node;
 {
  Rva0041534BIter found=rva0041534B(key);
  node=found.m_node;
 }
 return !node
  ? *(void**)((char*)&((InsertTable*)this)->_M_insert(
    *(const InsertPair*)&static_cast<const SoundPair21386C&>(SoundPair21386C(*key,0)))+4)
  : *(void**)((char*)node+8);
}

