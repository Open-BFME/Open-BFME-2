// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Native0031D64F..0031D85D (526B; RET0); WB00C2EDC0 has the same
// full call graph and fields but no recovered original method name. The
// existing ControlBar pin and GameLogic caller establish the receiver.
// Clean BF1 f989 ControlBar.cpp CommandSet traversal and postProcessCommands
// guide the cache workflow; they do not establish these target-specific
// filter offsets or the five radial image lookups. Native supplies the
// +108 bit1 and +6C side test, template next+484 and command set+70, local
// player side+58 and PlayerTemplate command set+138. Adjacent known methods
// and WB independently agree with these members and repeated resolver calls.
//
// Native0031D61E..0031D64F (49B; RET4) preloads the non-null buttons returned
// by the rowed 32-slot CommandSet accessor. Existing table lookup31D5F8 and
// cache helper35B3E7 are used under their established names; the latter's
// original member name remains unknown. Both complete bodies match on the
// first trial; the receiver and method names retain the existing uncertainty.
#include "ascii_string.h"
class Rva0035B456Owner {public:void rva0035B3E7();};
class CommandButton;
class CommandSet {public:const CommandButton *getCommandButton(int)const;};
class Rva0031D5F8 {public:void *rva0031D5F8(const AsciiString *);};
class Image {public:void rva002D937E();};
class ImageCollection {public:const Image *findImageByName(const AsciiString&);};
extern ImageCollection *TheMappedImageCollection;
class ThingTemplate {
public:
 const Image *getButtonImage();const Image *rva0033BA46();
 char pad00[0x6C];AsciiString side;AsciiString commandSet;
 char pad74[0x108-0x74];unsigned kindOf;
 char pad10C[0x484-0x10C];ThingTemplate *next;
};
class ThingFactory {public:char pad00[12];ThingTemplate *first;};
extern ThingFactory *TheThingFactory;
class PlayerTemplate {public:char pad00[0x138];AsciiString commandSet;};
class Player {public:char pad00[0x34];PlayerTemplate *base;char pad38[0x58-0x38];AsciiString side;};
class PlayerList {public:char pad00[16];Player *local;};
extern PlayerList *ThePlayerList;
class ControlBar {public:void rva0031D61E(const AsciiString *);void rva0031D64F();};
void ControlBar::rva0031D61E(const AsciiString *name) {
 CommandSet *set=(CommandSet*)((Rva0031D5F8*)this)->rva0031D5F8(name);
 if(set) {
  for(int i=0;i<32;++i) {
   const CommandButton *button=set->getCommandButton(i);
   if(button)((Rva0035B456Owner*)button)->rva0035B3E7();
  }
 }
}
void ControlBar::rva0031D64F() {
 if(!ThePlayerList||!TheThingFactory)return;
 Player *player=ThePlayerList->local;
 if(!player)return;
 AsciiString side=player->side;
 for(ThingTemplate *t=TheThingFactory->first;t;t=t->next) {
  if((t->kindOf&2)&&t->side.compare(side)==0) {
   rva0031D61E(&t->commandSet);
   if(t->getButtonImage()) const_cast<Image*>(t->getButtonImage())->rva002D937E();
   if(t->rva0033BA46()) const_cast<Image*>(t->rva0033BA46())->rva002D937E();
  }
 }
 PlayerTemplate *base=player->base;
 if(base)rva0031D61E(&base->commandSet);
 if(!TheMappedImageCollection)return;
 const Image *push=TheMappedImageCollection->findImageByName(AsciiString("RadialPush"));
 const Image *over=TheMappedImageCollection->findImageByName(AsciiString("RadialOver"));
 const Image *border=TheMappedImageCollection->findImageByName(AsciiString("RadialBorder"));
 const Image *clock1=TheMappedImageCollection->findImageByName(AsciiString("RadialClockOverlay1"));
 const Image *clock2=TheMappedImageCollection->findImageByName(AsciiString("RadialClockOverlay2"));
 if(push)const_cast<Image*>(push)->rva002D937E();
 if(over)const_cast<Image*>(over)->rva002D937E();
 if(border)const_cast<Image*>(border)->rva002D937E();
 if(clock1)const_cast<Image*>(clock1)->rva002D937E();
 if(clock2)const_cast<Image*>(clock2)->rva002D937E();
}
