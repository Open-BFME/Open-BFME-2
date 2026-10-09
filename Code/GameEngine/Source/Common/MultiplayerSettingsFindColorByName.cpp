// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ZH donor MultiplayerSettings.cpp:findMultiplayerColorDefinitionByName,
// at BF1 575ba2b04 inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/
// GameEngine/Source/Common/MultiplayerSettings.cpp. Native380E34..380EB1
// 125B and WB00BF47C0 independently prove the string scan and returned
// mapped-value address; constructor3811D8 proves map34/observer44/random84
// in the C4-byte receiver. Color copy380D30 establishes its full40-byte value.
// The opaque prefix preserves those offsets without claiming base behavior.
// The existing24B getTooltipName provider remains out of line; the direct
// iterator-node comparison keeps donor semantics while avoiding wrapper code.
// No new pins, globals or shared-header changes.
#include "ascii_string.h"
#include <map>
struct RGBColor {float red,green,blue;};
class MultiplayerColorDefinition {
public: AsciiString getTooltipName() const;
private:
 AsciiString name; RGBColor rgb;int color;RGBColor nightRgb;int nightColor;
 RGBColor extra1,extra2;bool extraFlag;
};
typedef _STL::map<int,MultiplayerColorDefinition> MultiplayerColorList;
class MultiplayerSettings {
 char prefix[0x34]; MultiplayerColorList m_colorList;
 int count; MultiplayerColorDefinition observer,random;
public: MultiplayerColorDefinition *findMultiplayerColorDefinitionByName(AsciiString name);
};
MultiplayerColorDefinition *MultiplayerSettings::findMultiplayerColorDefinitionByName(AsciiString name){
 MultiplayerColorList::iterator iter=m_colorList.begin();
 while(iter._M_node!=m_colorList.end()._M_node) {
  if(iter->second.getTooltipName()==name)return &iter->second;
  ++iter;
 }
 return 0;
}
