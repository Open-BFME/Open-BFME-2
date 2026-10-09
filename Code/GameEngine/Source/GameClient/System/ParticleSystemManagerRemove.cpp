// stlport
// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// Native manager removal 001F8109..001F8152 (73B). Identity and ABI:
// ParticleSystem destructor 001FBD17 passes an intrusive 12B handle;
// manager insertion 001F88B4 uses the same list at +4C and count at +58.
// ZH ParticleSys.cpp friend_removeParticleSystem guides search/erase/count.
// BFME2 nodes contain the 12B handle at +8; only its first pointer word
// participates in find. The pointer-list view is limited to traversal.
// The explicit erase member reproduces all 44 bytes and relocation targets
// of existing stdcall owner 001F63C9: unlink, handle destruction at 4CCFF,
// free and hidden iterator result; ECX is unused by that native body.
// Donor revision f98983a7d; field widths independently follow native access.
#include <list>
#include <algorithm>
class RvaSmartPtr12 {public:void *ptr,*prev,*next;};
class Rva0004CCFF {public:void *destroyDelete(unsigned);void *ptr,*prev,*next;};
struct Rva001F63C9Node {void *next,*prev;Rva0004CCFF handle;};
extern "C" void __cdecl free(void*);
class Rva001F63C9List {public:_STL::list<void*>::iterator erase(_STL::list<void*>::iterator);};
_STL::list<void*>::iterator Rva001F63C9List::erase(_STL::list<void*>::iterator position) {
 Rva001F63C9Node *p=(Rva001F63C9Node*)position._M_node;
 void *next=p->next,*prev=p->prev;*(void**)prev=next;*(void**)((char*)next+4)=prev;
 p->handle.destroyDelete(0);free(p);
 return _STL::list<void*>::iterator((_STL::_List_node<void*>*)next);
}
class Rva001F8109 {
public:void rva001F8109(const RvaSmartPtr12&);
 unsigned char unknown00[0x4c];_STL::list<void *> systems;
 unsigned char unknown50[8];int count;
};
void Rva001F8109::rva001F8109(const RvaSmartPtr12 &handle)
{
 typedef _STL::list<void *>::iterator Iterator;
 Iterator it=_STL::find(systems.begin(),systems.end(),handle.ptr);
 if(it==systems.end())return;
 ((Rva001F63C9List*)&systems)->erase(it);
 --count;
}
