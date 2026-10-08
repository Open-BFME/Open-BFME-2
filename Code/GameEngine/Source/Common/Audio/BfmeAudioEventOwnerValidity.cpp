// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /MD
#include "Common/BfmeAudioEventPrefix136.h"
#include "../GameLogicObjectLookupView.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
// Native2DA318..2DA398; same owner tags/ID fields and providers as the
// rowed owner-position worker. WorldBuilder BD63A0 corroborates the lookup
// operation, but its object/drawable tag mapping differs from this target.
class Drawable;
class Object;
class GameClient {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual Drawable *findDrawableByID(int);
};
class Rva002BFDAE {public: void *rva002BFDAE(void *);};
struct Rva002B488EResult;
struct Rva002B2579Result;
class Rva002BA8F1Logic {public: Rva002B488EResult *rva002B488E(int);Rva002B2579Result *rva002B2579(int);};
extern GameLogic *TheGameLogic;
class ClientFrameSubsystem;
extern ClientFrameSubsystem *TheGameClient;
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;

class Rva002DA318 {
 char m_pad00[0x34];
 int m_id34;
 int m_tag38;
public:
 bool rva002DA318();
};
bool Rva002DA318::rva002DA318() {
 switch(m_tag38) {
 case 1: return ((GameClient *)TheGameClient)->findDrawableByID(m_id34) == 0;
 case 2: return TheGameLogic->findObjectByID((ObjectID)m_id34) == 0;
 case 3: return g_00DFEF18 && ((Rva002BFDAE *)g_00DFEF18)->rva002BFDAE((void*)m_id34) ? 0 : 1;
 case 4: return TheLivingWorldLogic && ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B488E(m_id34) ? 0 : 1;
 case 5: return TheLivingWorldLogic && ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B2579(m_id34) ? 0 : 1;
 }
 return false;
}
