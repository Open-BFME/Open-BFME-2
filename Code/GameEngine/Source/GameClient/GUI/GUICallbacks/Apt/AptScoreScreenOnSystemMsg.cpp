// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// AptScoreScreen::OnSystemMsg (WB 0x145F4D0) at 0x0051C452: the template lookup is the rowed ThingFactory::findTemplate (0x002D06CA) on the real TheThingFactory global, reached as in WB 0x145F4D0 through an inline forwarder; with it the register allocation keeps the template in ebx (add ebx,0x30; push ebx) and the equal-arm ternaries, barrier and goto are gone.
//
// BFME2's score screen Apt callbacks, 0x0051BF75 onward, bound by these
// names ("AptScoreScreen::OnInitialized" ...) as member pointers by the
// screen's registration; that binding is their only reference. The class
// is named for the strings' prefix. +0x27C is the screen's state.
#include "../../../../../Include/GameClient/GameText.h"
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
#include <string.h>
#include <stdio.h>
// The objectives summary at +0x288: a count at +4 and up to eight
// checked flags at +0x28.
struct AptScoreObjectives

{
 unsigned char m_pad00[4];
 int m_count;
// +0x04
 unsigned char m_pad08[0x28 - 0x08];
 bool m_checked[8];
// +0x28
 
}
;
class BfmeKeyLC;
// The list box user data byte +0x12 the score screen sets.
struct AptScoreListData

{
 unsigned char m_pad[0x12];
 bool m_12;
// +0x12
 
}
;
#include "../../../../../Include/GameClient/Bfme2GameWindow.h"
void GadgetTextEntrySetText(GameWindow *textEntry, UnicodeString text);
void *GadgetListBoxGetItemData(GameWindow *listbox, int row, int column);
int GadgetListBoxGetEntryBasedOnXY(GameWindow *listbox, int x, int y, int &row, int &column);
void GadgetTextEntrySetMaxChars(BfmeKeyLC *textEntry, unsigned short maxLength);
#include "../../../../../Include/GameClient/GameWindowManager.h"
extern GameWindowManager *TheWindowManager;
// The Apt player's rowed call 0x00222A8B on a movie's level.
#include "../../../../../Include/Common/Rva00222A8BTarget.h"
extern class Rva00222A8BTarget *TheRva00222A8BTarget;
// TheMouse's rowed tooltip setter 0x001EEA6D (MouseRva001EEA6D.cpp).
#include "../../../../../../Libraries/Include/Lib/RGBColor.h"
#include "../../../../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
// TheThingFactory's rowed template lookup 0x002D06CA; the template's
// display name at +0x30 and its flag byte +0x113, whose bit 2 marks a hero.
struct Rva002D06CATemplate

{
 unsigned char m_pad000[0x30];
 UnicodeString m_displayName;
// +0x30
 unsigned char m_pad034[0x113 - 0x34];
 unsigned char m_113;
// +0x113
 
}
;
class ThingTemplate;
class ThingFactory
{
public:
 const ThingTemplate *findTemplate(const AsciiString &name);
 // WB 0x145F4D0 reaches the lookup through an inline forwarder (WB names the
 // out-of-line body findTemplateInternal; the ledger rows it findTemplate).
 const ThingTemplate *findTemplateInline(const AsciiString &name) { return findTemplate(name); }
};
extern ThingFactory *TheThingFactory;
// A persistent unit's list box item data: its template name at +4 and the
// player's name for it at +0xA0.
struct AptScorePersistentUnit

{
 unsigned char m_pad00[4];
 AsciiString m_templateName;
// +0x04
 unsigned char m_pad08[0xA0 - 0x08];
 UnicodeString m_customName;
// +0xA0
 
}
;
// The Apt screen base's rowed window message handler 0x0051274F.
#include "../../../../../Include/GameClient/_bfme_AptGameWindow.h"
// TheLivingWorldLogic (VA 0x00DFEF10); its
// unrowed 0x002B3740 returns a byte of its current entry, pinned by
// address.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class AptScoreScreen

{
 public:
 void OnInitialized(const char *unused);
 void Timeline(const char *unused);
 void RestartGame(const char *unused);
 void Continue(const char *unused);
 void InitGadgets(const char *name, void *argument, GameWindow *window);
 void RenameCancel(const char *unused);
 void objectiveChecked(int index, char *result, bool skip);
 void heroVetUpgrade(int index, char *result, bool skip);
 void OnButtonRenameAccept(int unused);
 int OnSystemMsg(int message, unsigned int wParam, unsigned int lParam);
 private:
 unsigned char m_pad000[0x274];
 void *m_movie;
// +0x274
 unsigned char m_pad278[0x27C - 0x278];
 int m_state;
// +0x27C
 unsigned char m_pad280[0x288 - 0x280];
 AptScoreObjectives *m_objectives;
// +0x288
 _STL::vector<bool> m_heroUpgrades;
// +0x28C
 GameWindow *m_units;
// +0x2A0
 GameWindow *m_rename;
// +0x2A4
 AptScorePersistentUnit *m_renaming;
// +0x2A8
 int m_renameIndex;
// +0x2AC
 unsigned char m_pad2b0[0x2B4 - 0x2B0];
 int m_lastX;
// +0x2B4
 int m_lastY;
// +0x2B8
 int m_hoverFrames;
// +0x2BC
 AsciiString m_tooltip;
// +0x2C0
 
}
;
// Retail 0x0051C452, 890 bytes: the score screen's window messages (its
// vftable slot at 0x00C663B4) ahead of the Apt screen base 0x0051274F.
// Resting the mouse on a persistent unit for ten frames shows whether it
// may be renamed (heroes may not) and keeps that tooltip up after eight;
// selecting one opens the rename entry on its current name, and the
// entry's GEM_EDIT_DONE accepts it.
int AptScoreScreen::OnSystemMsg(int message, unsigned int wParam, unsigned int lParam)

{
 switch (message)
 
 {
  case 0x18: // GWM_MOUSE_POS
  
  {
   if ((GameWindow *)wParam != m_units)
   break;
   int mouseX = lParam & 0xFFFF;
   int mouseY = lParam >> 16;
   if (mouseX == m_lastX && mouseY == m_lastY)
   ++m_hoverFrames;
   else
   m_hoverFrames = 0;
   int row;
   int column;
   GadgetListBoxGetEntryBasedOnXY((GameWindow *)wParam, mouseX, mouseY, row, column);
   if (m_hoverFrames == 10)
   
   {
    if (column != 0)
    
    {
     AsciiString label("APT:NULL");
     TheMouse->rva001EEA6D(TheGameText->fetch(label), -1, 0, 1.0f);
     m_tooltip = label;
     
    }
    if (column == 0)
    
    {
     AsciiString label;
     m_renaming = (AptScorePersistentUnit *)GadgetListBoxGetItemData(m_units, row, 0);
     if (m_renaming)
     
     {
      Rva002D06CATemplate *unitTemplate = 0;
      if (TheThingFactory)
       unitTemplate = (Rva002D06CATemplate *)TheThingFactory->findTemplateInline(m_renaming->m_templateName);
      if (unitTemplate && (unitTemplate->m_113 & 4))
      {
       label = "TOOLTIP:YouMayNotRenameAHero";
       TheMouse->rva001EEA6D(TheGameText->fetch(label), -1, 0, 1.0f);
      }
      else
      {
       label = "TOOLTIP:ClickToRenameThisUnit";
       TheMouse->rva001EEA6D(TheGameText->fetch(label), -1, 0, 1.0f);
      }
     }
     m_tooltip = label;
     
    }
    
   }
   else if (m_hoverFrames > 7 && column == 0)
   
   {
    TheMouse->rva001EEA6D(TheGameText->fetch(m_tooltip), -1, 0, 1.0f);
    
   }
   m_lastX = mouseX;
   m_lastY = mouseY;
   break;
   
  }
  case 0x4014: // GLM_SELECTED
  
  {
   if ((GameWindow *)wParam != m_units || !m_units || !m_rename || (int)lParam < 0)
   break;
   m_renaming = (AptScorePersistentUnit *)GadgetListBoxGetItemData(m_units, lParam, 0);
   if (!m_renaming)
   break;
   m_renameIndex = lParam;
   Rva002D06CATemplate *unitTemplate = 0;
   if (TheThingFactory)
   
   {
    unitTemplate = (Rva002D06CATemplate *)TheThingFactory->findTemplateInline(m_renaming->m_templateName);
   }
   if (unitTemplate && (unitTemplate->m_113 & 4))
   {
    m_renaming = 0;
    m_renameIndex = -1;
    break;
   }
   UnicodeString name;
   AptScorePersistentUnit *renaming = m_renaming;
   UnicodeString &customName = renaming->m_customName;
   if (!customName.isEmpty())
    name = customName;
   else if (unitTemplate)
   {
    name = unitTemplate->m_displayName;
   }
   GadgetTextEntrySetText(m_rename, name);
   TheWindowManager->winSetFocus(m_rename);
   m_units->winEnable(false);
   void *movie = m_movie;
   TheRva00222A8BTarget->invoke(movie, "openRenamePersistentUnit", 0, 0, 0, 0, 0, 0);
   break;
   
  }
  case 0x4031: // GEM_EDIT_DONE
  if ((GameWindow *)wParam == m_rename && lParam == 0 && m_renaming)
  
  {
   OnButtonRenameAccept(0);
   TheRva00222A8BTarget->invoke(m_movie, "closeRenamePersistentUnit", 0, 0, 0, 0, 0, 0);
   
  }
  break;
  default:
  return ((_bfme_AptGameWindow *)this)->rva0051274F(message, wParam, lParam);
  
 }
 return 1;
 
}

// OnInitialized, Timeline, RestartGame, Continue, InitGadgets, RenameCancel,
// objectiveChecked and heroVetUpgrade are defined with their rows in
// AptScoreScreenCallbacks.cpp.
