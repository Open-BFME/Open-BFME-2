// ?rva0059A8D7@Rva0059AC4D@@QAEXPAVTeam@@PAH@Z
// partial score=0.75 date=2026-10-08
// cl: /ICode/Libraries/Include/Lib /O1 /arch:SSE /MD /EHs /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include <stdlib.h>
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#undef free
#include "../../../Common/GameLogicObjectLookupView.h"
struct Coord3D;
class Player;
class TeamPrototype;
class Team { public: char pad[0x30]; TeamPrototype *prototype; };
class ThingTemplate { public: char pad[0x108]; unsigned char kind0; char gap[0xA]; unsigned char kind1; };
class Object { public: char pad[4]; ThingTemplate *m_template; void setTeam(Team *); };
class Rva0039D7C1ByteField { public: unsigned char get() const; };
class Rva0039D7C8LeaGetter { public: void *get() const; };
class Rva005C4AD1LeaField { public: void *get() const; };
class Rva002A8F24 { public: void *rva002A8F24(Player *); void *rva002A8B73(void *, int); };
struct RecruitmentTemplate { char pad[0x198]; int targetType; int pad19c; int mode; unsigned limit; };
extern Rva002A8F24 *g_00DFEEF8;
extern GameLogic *TheGameLogic;
typedef _STL::vector<unsigned> IDVector;
class AITeamBuilder { public: void distanceSortUnits(void *, const void *, const Coord3D *); };
class Rva0059A01C { public: bool test(Object *, RecruitmentTemplate *, void *); };
class Rva0059AC4D {
public:
 void rva0059A8D7(Team *, int *);
 void distanceSortUnits(void *, const void *, const Coord3D *);
 bool eligible(Object *, RecruitmentTemplate *, void *);
private: char pad[0x14]; Player *owner; public: Player *getOwner() { return owner; }
};
void Rva0059AC4D::rva0059A8D7(Team *team, int *count)
{
 void *stats = g_00DFEEF8->rva002A8F24(getOwner());
 Rva005C4AD1LeaField *units = *(Rva005C4AD1LeaField **)stats;
 TeamPrototype *prototype = team->prototype;
 RecruitmentTemplate *templ = (RecruitmentTemplate *)((char *)prototype + 0x12c);
 void *target = g_00DFEEF8->rva002A8B73(getOwner(), templ->targetType);
 IDVector *original = (IDVector *)units->get();
 IDVector *list = original;
 IDVector sorted;
 if (((Rva0039D7C1ByteField *)prototype)->get()) {
  ((AITeamBuilder *)this)->distanceSortUnits(&sorted, original, (const Coord3D *)((Rva0039D7C8LeaGetter *)prototype)->get());
  list = &sorted;
 }
 unsigned *end = list->end();
 for (unsigned *it = list->begin(); it != end && (unsigned)*count < templ->limit; ++it) {
  Object *object = TheGameLogic->findObjectByID((ObjectID)*it);
  if ((object->m_template->kind0 & 8) && ((Rva0059A01C *)this)->test(object, templ, target)) {
   object->setTeam(team);
   ++*count;
  }
 }
 int mode = templ->mode;
 if (mode == 0 || mode == 1) {
  for (unsigned *it = list->begin(); it != end; ++it) {
   Object *object = TheGameLogic->findObjectByID((ObjectID)*it);
   if ((object->m_template->kind1 & 4) && ((Rva0059A01C *)this)->test(object, templ, target)) {
    object->setTeam(team);
    ++*count;
   }
  }
 }
}
