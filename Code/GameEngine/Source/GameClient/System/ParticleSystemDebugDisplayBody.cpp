// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_MALLOC
// stlport
// ParticleSystemDebugDisplay (0x001FA04B, 1013 bytes): the particle statistics
// debug page. Identity and layout from the BF1 readonly9cbfb551 semantic donor
// plus the target's literals, vtable slots and offsets (see the banked attempt's
// record); the STL helper instantiations it calls are verified in
// ParticleSystemDebugDisplay.cpp. Closed from the 0.9977 banked partial: the
// "Avg per system" average is one in-flight x87 expression inside the print call
// (a float local with a compound divide put the display vtable in EAX, not ECX).
#include "ascii_string.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_USE_STATIC_LIB
#include <map>
bool operator<(const AsciiString &,const AsciiString &);
namespace _STL { template<> struct less<AsciiString> { bool operator()(const AsciiString &a,const AsciiString &b) const { return a<b; } }; }

class DebugDisplayInterface;
struct _iobuf;
class ParticleSystemManager;
class GlobalData;
extern ParticleSystemManager *TheParticleSystemManager;
extern GlobalData *TheWritableGlobalData;

// Address-derived views: only slots/offsets used by this retail body are asserted.
struct Rva001FA04BDisplay {
 virtual void slot00();
 virtual void print(const char *, ...);
 virtual void slot08();
 virtual void cursor(int, int);
 virtual void slot10(); virtual void slot14(); virtual void slot18();
 virtual void slot1c();
 virtual void margin(int);
};
struct Rva001FA04BManager {
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1c(); virtual void slot20();
 virtual void slot24();virtual void slot28();virtual void slot2c();virtual void slot30();virtual void slot34();
 virtual int onScreen();
};
namespace FXParticleSystem { class ParticleSystemTemplate { public: AsciiString getName() const; }; }
struct Rva001FA04BParticleModule {
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();
 virtual void slot4();virtual void slot5();virtual void slot6();virtual int getCount();
};
#include "../../../Include/GameClient/ParticleSystemClass.h"
static inline FXParticleSystem::ParticleSystemTemplate *getTemplate(const ParticleSystem *system) { return (FXParticleSystem::ParticleSystemTemplate *)system->m_template; }
static inline int getParticleCount(const ParticleSystem *system) { return ((Rva001FA04BParticleModule *)system->m_A4)->getCount(); }
static inline float getCost(const ParticleSystem *system) { return system->m_AC; }
#include "../../../Include/Common/RvaSmartPtr12.h"
class Rva0004CCFF {public:void *destroyDelete(unsigned int);};
namespace _STL {static __forceinline void _Destroy(RvaSmartPtr12 *p){((Rva0004CCFF *)p)->destroyDelete(0);}}
#include <list>
// Compare typed nodes locally; retail inlines these comparisons.
namespace _STL {
template <class T, class L, class R>
static inline bool operator!=(const _Rb_tree_iterator<T, L>& a, const _Rb_tree_iterator<T, R>& b)
{ return a._M_node != b._M_node; }
template <class T, class L, class R>
static inline bool operator!=(const _List_iterator<T, L>& a, const _List_iterator<T, R>& b)
{ return a._M_node != b._M_node; }
}

template<> _STL::list<RvaSmartPtr12>::list(const _STL::list<RvaSmartPtr12>&);
typedef _STL::list<RvaSmartPtr12> ParticleDebugList;
static bool timing() { return *((char *)TheWritableGlobalData+0x9c2)!=0; }
static float managerFloat(unsigned off) { return *(float *)((char *)TheParticleSystemManager+off); }
static int managerInt(unsigned off) { return *(int *)((char *)TheParticleSystemManager+off); }

void ParticleSystemDebugDisplay(DebugDisplayInterface *display, void *, _iobuf *) {
 Rva001FA04BDisplay *dd=(Rva001FA04BDisplay *)display;
 if(!dd) return;
 dd->cursor(0,0);
 dd->margin(2);
 dd->print("Total Particles: %d\n",managerInt(0x50));
 dd->print("Total Particles (On Screen): %d\n",((Rva001FA04BManager *)TheParticleSystemManager)->onScreen());
 dd->print("Total Particle\tSystems: %d\n",managerInt(0x58));
 if(timing()) dd->print("Total Particle\tSystems Cost: %.2f msec\n",managerFloat(0x60));
 ParticleDebugList list(*reinterpret_cast<const _STL::list<RvaSmartPtr12> *>((char *)TheParticleSystemManager+0x4c));
 _STL::map<AsciiString,int> templateMap;
 _STL::map<AsciiString,int> templateMapParticleCount;
 _STL::map<AsciiString,float> templateMapCost;
 _STL::map<AsciiString,float>::iterator costIt;
 _STL::map<AsciiString,int>::iterator mapIt;
 _STL::map<AsciiString,int>::iterator countIt;

 for(ParticleDebugList::iterator it=list.begin();it!=list.end();++it) {
  AsciiString templateName=getTemplate((*it).operator->())->getName();
  mapIt=templateMap.find(templateName);
  if(mapIt==templateMap.end()) {
   templateMap.insert(_STL::make_pair(templateName,1));
   templateMapParticleCount.insert(_STL::make_pair(templateName,getParticleCount((*it).operator->())));
   if(timing()) templateMapCost.insert(_STL::make_pair(templateName,getCost((*it).operator->())));
  } else {
   ++mapIt->second;
   countIt=templateMapParticleCount.find(templateName);
   if(countIt!=templateMapParticleCount.end()) countIt->second+=getParticleCount((*it).operator->());
   if(timing()) {
    costIt=templateMapCost.find(templateName);
    if(costIt!=templateMapCost.end()) costIt->second+=getCost((*it).operator->());
   }
  }
 }
 for(mapIt=templateMap.begin();mapIt!=templateMap.end();++mapIt) {
  countIt=templateMapParticleCount.find(mapIt->first);
  if(timing()) costIt=templateMapCost.find(mapIt->first);
  dd->print("  %s: %d instances",mapIt->first.str(),mapIt->second);
  if(countIt!=templateMapParticleCount.end() && mapIt->second>0) {
   // Parenthesised cast: retail builds the divide as one in-flight x87 expression.
   dd->print("    (Avg per system %.2f) ",((float)countIt->second)/mapIt->second);
  }
  if(timing() && costIt!=templateMapCost.end() && mapIt->second>0)
   dd->print("   (Avg cost per system %.2f msec)",costIt->second/(float)mapIt->second);
  dd->print("\n");
 }
}

