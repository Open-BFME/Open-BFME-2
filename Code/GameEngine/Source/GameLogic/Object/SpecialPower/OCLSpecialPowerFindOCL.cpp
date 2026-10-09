// cl: /O1 /MD
// ZH OCLSpecialPower.cpp findOCL supplies the semantic body and method name.
// Target WB125D170 has the same two callees and first-owned science/OCL
// selection. Rowed OCL constructor4C30D8 proves data4/Object8; data ctor
// 4C32BC and parse table prove UpgradeOCL7C/defaultOCL88 independently.
// This TU uses bounded target views; no complete class extent is claimed.
class ObjectCreationList;
enum ScienceType { SCIENCE_INVALID = -1 };
class Player { public: bool hasScience(ScienceType)const; };
class Object { public: Player *getControllingPlayer()const; };
struct OCLScienceEntry { ScienceType science; const ObjectCreationList *value; };
struct OCLSpecialPowerDataView {
 char prefix[0x7C];
 OCLScienceEntry *begin,*end,*capacity;
 const ObjectCreationList *fallback;
};
class OCLSpecialPower {
 char prefix[4];
 OCLSpecialPowerDataView *m_data;
 Object *m_object;
protected: const ObjectCreationList *findOCL()const;
};
const ObjectCreationList *OCLSpecialPower::findOCL()const
{
 const OCLSpecialPowerDataView *data=m_data;
 Player *player=m_object->getControllingPlayer();
 if(player) {
  for(const OCLScienceEntry *entry=data->begin;entry!=data->end;++entry)
   if(player->hasScience(entry->science)) return entry->value;
 }
 return data->fallback;
}
