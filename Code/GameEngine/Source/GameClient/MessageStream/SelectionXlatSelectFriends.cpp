// ?selectFriends@SelectionTranslator@@QAE_NPAVDrawable@@PAVGameMessage@@_N@Z
// partial score=0.98 date=2026-10-13
// ?selectFriends@SelectionTranslator@@QAE_NPAVDrawable@@PAVGameMessage@@_N@Z
// partial score=0.98 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /Os /DNDEBUG /MD /EHsc
// stlport
// ?selectFriends@SelectionTranslator@@QAE_NPAVDrawable@@PAVGameMessage@@_N@Z @0x0042FE7F 321B: CanSelect gate plus max-limit warning plus selectCountMap inc plus append plus selectDrawable. Evidence: pin, LINK BONUS 29B from selectFriendsWrapper, donor SelectionTranslator_selectFriends, rowed CanSelectDrawable 0x0042FA63, retail slots 0x11c/0x118/0x40/0x108 plus fetch 0x3c plus UnicodeString plus ImageSubscriptMap 0x002077D6 plus append 0x0030F979.
#include "ascii_string.h"
#include "unicode_string.h"
typedef int Int;
typedef bool Bool;
enum ObjectID

{
 OBJECTID_NONE = 0
 
}
;
class Drawable;
class GameMessage;
class ThingTemplate;
class Object

{
 public:
 unsigned char m_pad00[0x74];
 ObjectID m_id;
 
}
;
#include "../../../Include/GameClient/Drawable.h"
#include "../../../Include/Common/MessageStream.h"
#include "../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
#include "../../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;
class Image;
#include "../../../Include/GameClient/ImageSubscriptMap.h"
Bool CanSelectDrawable(const Drawable *draw, Bool dragSelecting);
class SelectionTranslator

{
 public:
 Bool selectFriends(Drawable *draw, GameMessage *createTeamMsg, Bool dragSelecting);
 private:
 unsigned char m_pad00[0x20];
 Bool m_displayedMaxWarning;
 unsigned char m_pad21[0x28 - 0x21];
 ImageSubscriptMap m_selectCountMap;
 
}
;
Bool SelectionTranslator::selectFriends(Drawable *draw, GameMessage *createTeamMsg, Bool dragSelecting)

{
 if (CanSelectDrawable(draw, dragSelecting))
 
 {
  if (TheInGameUI->getMaxSelectCount() > 0)
  
  {
   Int maxLimit = TheInGameUI->getMaxSelectCount();
   Int curCount = TheInGameUI->getSelectCount();
   if (curCount >= maxLimit)
   
   {
    if (!m_displayedMaxWarning)
    
    {
     m_displayedMaxWarning = true;
     UnicodeString maxSelectionWarning;
     maxSelectionWarning.format(TheGameText->fetch("GUI:MaxSelectionSize").str(), TheInGameUI->getMaxSelectCount());
     TheInGameUI->rva0029E846(maxSelectionWarning);
     
    }
    return false;
    
   }
   
  }
  ++(int &)m_selectCountMap[(unsigned int)draw->m_template];
  if (draw->m_object && createTeamMsg)
  createTeamMsg->appendObjectIDArgument(draw->m_object->m_id);
 if (0) { UnicodeString t1_dead; }
  TheInGameUI->selectDrawable(draw);
  return true;
  
 }
 return false;
 
}
