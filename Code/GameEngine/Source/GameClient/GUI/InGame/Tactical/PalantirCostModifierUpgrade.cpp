// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Native52914B..529315 RET4 / WB13C9D90 prove16B cost state, object
// template bit7, module flag128 and both independently owned cost getters.
// Names remain address-derived. Native BB9270 static-label cleanup tail-jumps
// to48BA39; local string cleanup calls36410. The owning label's out-of-line
// destructor is a verified5B relocation twin of the canonical AsciiString
// destructor at48BA39; its contained AsciiString has the same lifetime.
// Existing address-named static guard ownership remains census debt.
#include "ascii_string.h"
#include "unicode_string.h"
enum NameKeyType { NAMEKEY_INVALID=0 };
#include "../../../../../Include/Common/NameKeyGenerator.h"
extern NameKeyGenerator *TheNameKeyGenerator;
class Player;class Module;class Rva0052914B;
struct ObjectCostTemplate {char unknown[0x108];unsigned char kindOf[0x14];};
class Object {public: Player *getControllingPlayer() const;ObjectCostTemplate *getTemplate() const {return data;}protected:friend class Rva0052914B;Module *findModule(NameKeyType) const;void *vtable;ObjectCostTemplate *data;};
class PlayerList;extern PlayerList *ThePlayerList;
class Rva002A7DDEArg;
#include "../../../../../Include/Common/Rva002A7DDE.h"
class Rva00528C65 {public:AsciiString rva00528C65() const;int rva00528C85(Player*);void *vtable;struct Data {char unknown[0x128];bool percentage;};Data *data;};
class Rva00528BDD {public:void rva00528BDD();};
#include "../../../../../Include/Common/Rva00222A8BTarget.h"
#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;
// Keep the persistent label's cleanup out of line, as witnessed by BB9270.
// Ordinary member ownership preserves the canonical4B string representation.
class Rva0052914BStaticLabel {public:
 __forceinline Rva0052914BStaticLabel(const char*s):value(s) {}
 ~Rva0052914BStaticLabel();
 __forceinline const AsciiString &asString() const {return value;}
private: AsciiString value;
};
class Rva0052914B {public:void rva0052914B(Object*);void *level;bool visible,cached,percentage,unknown7;int oldValue,amount;};
void Rva0052914B::rva0052914B(Object *object) {
 if(!(object->getTemplate()->kindOf[0]&0x80)) {if(visible)((Rva00528BDD*)this)->rva00528BDD();return;}
 static NameKeyType key=TheNameKeyGenerator->nameToKey("CostModifierUpgrade");
 Rva00528C65 *module=(Rva00528C65*)object->findModule(key);
 Player *player=object->getControllingPlayer();
 if(module && player && ((Rva002A7DDE*)ThePlayerList)->rva002A7DDE((Rva002A7DDEArg*)object)) {
  if(!visible) {
   ((Rva00222A8BTarget*)g_bfmeAptWindowManager)->invoke(level,"ShowCostModifierUpgradeInterface",0,0,0,0,0,0);
   visible=true;cached=false;
  }
  bool percent=module->data->percentage;
  AsciiString name=module->rva00528C65();
  int value=module->rva00528C85(player);
  if(cached) {
   if(percent!=percentage || (!percent && oldValue!=0) || value!=amount)cached=false;
  }
  if(!cached) {
   UnicodeString text;text.format(TheGameText->fetchPtr(name,0),value);
   static Rva0052914BStaticLabel textField("APT:CostModifierUpgrade");
   g_bfmeAptWindowManager->bfmeSetText(textField.asString(),text,false);
   percentage=percent;cached=true;oldValue=0;amount=value;
  }
 } else if(visible)((Rva00528BDD*)this)->rva00528BDD();
}

Rva0052914BStaticLabel::~Rva0052914BStaticLabel() {}
