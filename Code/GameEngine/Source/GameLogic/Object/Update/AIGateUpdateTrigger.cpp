// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native callback4B09E7 is embedded in loadTrigger4B0AAA at4B0BBC;
// complete entry through4B0A24 is61B. It classifies the entering/leaving
// object relative to owner+8 and adjusts counters28/2C; names unresolved.
enum Relationship { RELATION_0,RELATION_1,RELATION_2 };
class Object {public:Relationship getRelationship(const Object *) const;};
class AIGateUpdate {public:
 static void rva004B09E7(Object *,AIGateUpdate *,bool);
 char pad[8];Object *object;char pad0C[0x1C];int count28,count2C;
};
void AIGateUpdate::rva004B09E7(Object *o,AIGateUpdate *gate,bool entered) {
 Relationship r=o->getRelationship(gate->object);
 if(entered) {
  switch(r) {case RELATION_0:++gate->count2C;break;case RELATION_2:++gate->count28;break;}
 } else {
  switch(r) {case RELATION_0:--gate->count2C;break;case RELATION_2:--gate->count28;break;}
 }
}
