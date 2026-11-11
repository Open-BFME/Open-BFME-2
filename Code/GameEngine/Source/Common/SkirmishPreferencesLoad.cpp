// cl: /O1 /Oy- /MD /EHs /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport46
#include "../../Include/GameClient/SkirmishPreferencesClass.h"
#include "../../Include/Common/UserPreferences.h"
// Target43BC0A..43BD36 (300B): complete independent EH prologue/epilogue.
// Existing SkirmishPreferences key builder and vtable+20 getAsciiString prove
// owner; HeroIndexes/GameInfo literals establish the preference import role.
// BF1 Skirmish preferences and ZH GameInfo parser are semantic guides; this
// BFME2-only hero extension uses rowed getSlot3FF29F/set3FF0E7 (+5C) for8 slots
// then ParseAsciiStringToGameInfo40116B. Both globals are existing named owners.
// Canonical narrow string header; full300 hot/import/string/EH verification.
// Canonical preference layouts supply the inherited getAsciiString slot.
#include "ascii_string.h"
#include <stdlib.h>
#include <string.h>
class UnicodeString;

class GameSlot;
#include "../../Include/GameNetwork/GameInfo.h"
class SkirmishGameInfo; extern SkirmishGameInfo *TheSkirmishGameInfo;
#include "../../Include/GameNetwork/Rva003FF0E7DwordSlot.h"
bool ParseAsciiStringToGameInfo(GameInfo*,AsciiString,bool);
struct SkirmishStringDataView{char header[8];char text[1];};
__forceinline const char *skirmishText(const AsciiString&asciiString){
 const SkirmishStringDataView *data=*(const SkirmishStringDataView *const*)&asciiString;return data?data->text:"";
}
bool SkirmishPreferences::getGameInfo(){
 if(!(*(GameInfo * *)&TheSkirmishGameInfo))return false;
 AsciiString value=getAsciiString(buildProfileKey("HeroIndexes"),AsciiString::TheEmptyString);
 const char *p=skirmishText(value);
 for(unsigned i=0;i<8;++i){
 if(!p)break;
  ++p;
  GameSlot *slot=(*(GameInfo * *)&TheSkirmishGameInfo)->getSlot(i);
  if(!slot)break;
  ((Rva003FF0E7DwordSlot*)slot)->set(atoi(p));
  p=strchr(p,':');

 }
 value=getAsciiString(buildProfileKey("GameInfo"),AsciiString::TheEmptyString);
 return ParseAsciiStringToGameInfo((*(GameInfo * *)&TheSkirmishGameInfo),value,true);
}
