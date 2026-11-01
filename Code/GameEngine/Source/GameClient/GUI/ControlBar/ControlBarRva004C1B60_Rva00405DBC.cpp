// cl: -DNDEBUG -DWIN32 -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/ControlBar
// Retail 0x00405DBC /129 (BFME 1 0x004C1B60). Named UI callers establish the ControlBar
// receiver (the BfmeConv1022 caller loads VA012F33F8/TheControlBar); the method keeps an address-derived name.
#include "../../../../Include/GameClient/Bfme2GameWindow.h"
void *GadgetButtonGetData(GameWindow *);
struct BfmeMsgDN;
// The temporary is an OldSchoolHelpBoxContentSource: its constructor
// 0x00405A25 installs table 0x00838970, whose slot 3 is the WorldBuilder-named
// OldSchoolHelpBoxContentSource::createContent 0x00405E3D. Slots 1, 2 and 4
// are its clone 0x00405D7C, getter 0x004059BE and comparator 0x004059CF; slot
// 5 is inherited from the middle class whose table 0x00838958 (installed by
// ctor 0x00405A45) supplies the id getter 0x004059F6. The root table
// 0x007E5838 is the destructor and five pure virtuals. Method names other
// than createContent stay placeholders; only the slot owners are proven.
// The middle class's default constructor is import-inline: every use here
// inlines, and the object emits no copy beside the strong
// ??0Rva00405A45@@QAE@XZ (0x004059ED) in Rva00405A45Ctor.cpp
// (docs/linking_obstacles.md LINK-087).
namespace _STL { template <class T> struct auto_ptr; }
class BfmeThingGX {
public:
 virtual ~BfmeThingGX() {}
 virtual _STL::auto_ptr<BfmeThingGX> clone() = 0;
 virtual int get() = 0;
 virtual struct TreeHintRef00217D4C createContent() = 0;
 virtual int bfmeEquals(const BfmeThingGX *other) const = 0;
 virtual int rva004059F6() = 0;
};
class Rva00405A45:public BfmeThingGX {
public:
 __declspec(dllimport) __forceinline Rva00405A45() {}
 virtual int rva004059F6();
};
class ControlBar;
class OldSchoolHelpBoxContentSource:public Rva00405A45 {
public:
 OldSchoolHelpBoxContentSource(ControlBar *owner,GameWindow *window,void *data)
  :m_owner(owner),m_window(window),m_data(data) {}
 virtual ~OldSchoolHelpBoxContentSource() {}
 virtual _STL::auto_ptr<BfmeThingGX> clone();
 virtual int get();
 virtual struct TreeHintRef00217D4C createContent();
 virtual int bfmeEquals(const BfmeThingGX *other) const;
 ControlBar *m_owner;GameWindow *m_window;void *m_data;
};
#include "../../../../Include/GameClient/ControlBar.h"
extern ControlBar *TheControlBar;
class WinInstanceData;
void commandButtonTooltip(GameWindow *window, WinInstanceData *, unsigned int)
{
 TheControlBar->rva004C1B60(window, 0);
}
void ControlBar::rva004C1B60(GameWindow *window,void *data)
{
 if(!data) {
  if(!window) return;
  if(window->winGetStyle()&1) {
   data=GadgetButtonGetData(window);
   if(!data) return;
  } else if(!(window->winGetStyle()&0x200) && !(window->winGetStyle()&0x80)) return;
 }
 OldSchoolHelpBoxContentSource adapter(this,window,data);
 bfmeShowDN((BfmeMsgDN *)&adapter);
}
