// ?checkValid@BfmeItemE63@@QAE_NXZ
// partial score=0.97 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// Native 397B89..397BD9; callers use this+14 pending ObjectID. The BFME1
// CastleBehaviorIsPendingObjectUnavailable.cpp at donor874e38488 supplies
// the unavailable-object purpose. Native BFME2 condition words and shifts
// differ; the original owning class name remains unproven, so preserve the
// existing address-derived donor view used by the independently matched caller.
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class Object
{
public:
 char pad00[0x110];
 unsigned int m_110;
 unsigned int m_114;
 char pad118[0x124-0x118];
 unsigned int m_124;
 char pad128[0x438-0x128];
 unsigned char m_438;
};
class BfmeItemE63
{
public:
 char pad00[0x14];
 ObjectID m_pendingID;
 bool checkValid();
};
bool BfmeItemE63::checkValid()
{
 Object *object = TheGameLogic->findObjectByID(m_pendingID);
 if (!object || (object->m_438 & 1)) return true;
 if (((unsigned char)(object->m_124 >> 27) & 1) ||
     ((unsigned char)(object->m_124 >> 26) & 1) ||
     ((unsigned char)(object->m_114 >> 5) & 1)) return true;
 return ((unsigned char)(object->m_110 >> 30) & 1) != 0;
}
