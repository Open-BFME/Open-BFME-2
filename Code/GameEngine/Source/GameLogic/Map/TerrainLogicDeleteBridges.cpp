// cl: /O1 /DNDEBUG /MD /arch:SSE
// Semantic source: ZH TerrainLogic.cpp::deleteBridges at the BFME1 reference
// revision ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f (inputs/reference).
// Target facts from existing BFME2 TerrainLogicBridges.cpp: getFirstBridge
// vslot40/A0; Bridge next4; TerrainLogic bridge head40. Native extent
// 27D5AD..27D5E0; ::delete calls virtual destructor flags0 then global delete.
// BFME1's game/ replacement only deletes orphaned bridges and is inapplicable.
// Keep cleanup independent of the older bridge unit's unresolved providers.
class Bridge {public:virtual ~Bridge();Bridge *next;};
template<int N> class TerrainLogicCleanupSlots:public TerrainLogicCleanupSlots<N-1> {
public:virtual void gap(char (*)[N]);
};
template<> class TerrainLogicCleanupSlots<0> {};
class TerrainLogic:public TerrainLogicCleanupSlots<40> {
public:virtual Bridge *getFirstBridge() const;
protected:void deleteBridges();
private:char opaque04[0x40-4];Bridge *m_bridgeListHead;
};
void TerrainLogic::deleteBridges() {
 Bridge *next=0;
 for(Bridge *bridge=getFirstBridge();bridge;bridge=next) {
  next=bridge->next;
  bridge->next=0;
  ::delete bridge;
 }
 m_bridgeListHead=0;
}
