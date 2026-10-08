// cl: /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfme2_ascii
// stlport
#include <vector>
// Native2AA857..2AA8BF104B and WB C1CA30/239B prove Player this+34,
// two one-word AsciiString lists at18C/198 and unsigned index bounds.
// The operation name and the original identities of both lists are unknown.
// ControlBar::populateCommand uses this selector for its revival template pass.
#include "ascii_string.h"
class ThingTemplate;
class ThingFactory;
extern ThingFactory *TheThingFactory;
class Rva002D06CA { public: void *rva002D06CA(const AsciiString *); };
struct PlayerTemplateStringList { AsciiString *begin,*end,*capacity;
 unsigned int size() const {return end-begin;} };
struct RevivalPlayerTemplateView {
 char unknown00[0x18C]; _STL::vector<AsciiString> secondary,primary;
};
class Player {
public:
 const ThingTemplate *rva002AA857(int index);
private:
 char unknown00[0x34]; RevivalPlayerTemplateView *playerTemplate;
};
// ?rva002AA857@Player@@QAEPBVThingTemplate@@H@Z
const ThingTemplate *Player::rva002AA857(int index)
{
 if(index<playerTemplate->primary.size())
  return (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&playerTemplate->primary[index]);
 int secondIndex=index-playerTemplate->primary.size();
 if(secondIndex<playerTemplate->secondary.size())
  return (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&playerTemplate->secondary[secondIndex]);
 return 0;
}



