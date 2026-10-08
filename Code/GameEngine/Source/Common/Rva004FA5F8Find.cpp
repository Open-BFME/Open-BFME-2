// ?getOwningPlayer@LivingWorldBuildingNuggetSpawnArmy@@QAEPAVRva002E2903Player@@XZ @0x004FA5F8 32B.
// Chain from the LivingWorld id find at 0x002B51F8: follows this+4 then +0x24
// and returns null when the inner pointer is null else the find result for id at +0x13C.
// Callers in 0x004FA83E and 0x004FA9B1 families. TU-local honest-address views.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002E2903Player;
class Rva002BA8F1Logic { public: Rva002E2903Player *find(int, unsigned int *); };

#define TheRva00DFEF10 (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)
struct Rva004FA5F8B { char pad[0x13C]; int id; };
struct Rva004FA5F8A { char pad[0x24]; Rva004FA5F8B *b; };
struct LivingWorldBuildingNuggetSpawnArmy { char pad0[4]; Rva004FA5F8A *a; Rva002E2903Player *getOwningPlayer(); };
Rva002E2903Player *LivingWorldBuildingNuggetSpawnArmy::getOwningPlayer()
{
    Rva004FA5F8A *aa = *(Rva004FA5F8A **)((char *)this + 4);
    Rva004FA5F8B *bb = *(Rva004FA5F8B **)((char *)aa + 0x24);
    if (!bb)
        return 0;
    int id = bb->id;
    return TheRva00DFEF10->find(id, 0);
}
