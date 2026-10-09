// cl: /O1 /G7 /arch:SSE /MD /EHsc
void __cdecl operator delete(void *);
namespace _STL { template<class T> class allocator {}; template<class T,class A=allocator<T> > class vector { public: T *erase(T *,T *); T *begin,*end,*capacity; }; }
class EconomyFarmDestroyView { public: virtual void *destroy(int); };
class Player;
class CreateAHeroData;
class Rva002A8F24 { public: void *rva002A8F24(Player *); };
class Rva004DFB55 { public: void rva004DFB55(CreateAHeroData *); };
extern Rva002A8F24 *g_00DFEEF8;
#include "AIEconomyBuilderFarmLibrary.h"
class BaseA { public: virtual void a0(); virtual void a1(); virtual ~BaseA(); int a4,a8; };
class Rva00506B1B { public: virtual ~Rva00506B1B(); virtual void b1(); virtual void rva004EA33A(); bool flag; };
class Rva004EA3B8 : public BaseA,public Rva00506B1B {
public: virtual void rva004EA33A(); void *m_owner14; int m_18,m_1C,m_20; _STL::vector<void *> pending;
};
// WB13816D0 names AIEconomyBuilder::shutdown. Native4EA33A..4EA3A4
// RET0 proves deletion of the farm library and unregistering this owner.
// Keep the existing neutral owner and pin used by the matched destructor.
// Its two-base hierarchy makes this override receive the +0C subobject;
// compiler adjustment supplies the primary owner for the final callback.
void Rva004EA3B8::rva004EA33A()
{
 if (AIEconomyBuilder::m_farmList.first != AIEconomyBuilder::m_farmList.finish) {
  Rva00596F18 **it = AIEconomyBuilder::m_farmList.first;
  Rva00596F18 **end = AIEconomyBuilder::m_farmList.finish;
  for (; it != end; ++it) {
   EconomyFarmDestroyView *farm = reinterpret_cast<EconomyFarmDestroyView *>(*it);
   void *allocation = farm ? farm->destroy(0) : 0;
   ::operator delete(allocation);
  }
  reinterpret_cast<_STL::vector<void *> &>(AIEconomyBuilder::m_farmList).erase(
   reinterpret_cast<void **>(AIEconomyBuilder::m_farmList.first),
   reinterpret_cast<void **>(AIEconomyBuilder::m_farmList.finish));
 }
 m_18 = 0;
 void *stats = g_00DFEEF8->rva002A8F24(static_cast<Player *>(m_owner14));
 reinterpret_cast<Rva004DFB55 *>(stats)->rva004DFB55(reinterpret_cast<CreateAHeroData *>(this));
}
