// cl: /O1 /G7 /GX /MD /arch:SSE /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// WorldBuilder AptPlayer.cpp:713-729 names AddOverButtonHandler and its level map.
// Retail 224584..2245FF proves +0xDC map, 0x28 stride, retained input handle,
// copied key, lookup-before-assignment, and both teardown calls.
// Isolated /G7 retains retail IMUL without changing neighboring callback COMDATs.
#include "ascii_string.h"
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class AptRefCounted {public:void *m_vtbl;int m_refCount;};
class AptOverButtonHandler : public AptRefCounted {};
template<class T> class AptRef {
public:
 T *m_ptr;
 AptRef(const AptRef &other):m_ptr(other.m_ptr){if(m_ptr)++m_ptr->m_refCount;}
 ~AptRef(){if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}
 __declspec(noinline) AptRef &operator=(const AptRef &other);
};
template<class T> AptRef<T> &AptRef<T>::operator=(const AptRef &other){
 if(this!=&other){
  if(other.m_ptr)++other.m_ptr->m_refCount;
  if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);
  m_ptr=other.m_ptr;
 }
 return *this;
}
class Rva00056F61 {public:void *rva00056F61(const AsciiString *);};
struct TreeHintRef00222C5A;
class Rva00223F4B {public:TreeHintRef00222C5A &rva00223F4B(const AsciiString &);};
// Only the map extent and level stride are established; the remaining fields
// and retail level count remain opaque.
struct AptOverButtonLevelView {unsigned char map[20];unsigned char unknown[20];};
class AptPlayer {public:void AddOverButtonHandler(unsigned,const AsciiString &,AptRef<AptOverButtonHandler>);};
void AptPlayer::AddOverButtonHandler(unsigned level,const AsciiString &name,AptRef<AptOverButtonHandler> handler){
 if(!handler.m_ptr)return;
 AsciiString buttonName(name);
 void *table=reinterpret_cast<AptOverButtonLevelView *>(reinterpret_cast<char *>(this)+0xdc)[level].map;
 reinterpret_cast<Rva00056F61 *>(table)->rva00056F61(&buttonName);
 AptRef<AptOverButtonHandler> &entry=reinterpret_cast<AptRef<AptOverButtonHandler> &>(reinterpret_cast<Rva00223F4B *>(table)->rva00223F4B(buttonName));
 entry=handler;
}
