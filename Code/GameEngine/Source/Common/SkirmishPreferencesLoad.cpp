// cl: /O1 /Oy- /MD /EHs /Ireference/shims/bfme2_ascii
// Target43BC0A..43BD36 (300B): complete independent EH prologue/epilogue.
// Existing SkirmishPreferences key builder and vtable+20 getAsciiString prove
// owner; HeroIndexes/GameInfo literals establish the preference import role.
// BF1 Skirmish preferences and ZH GameInfo parser are semantic guides; this
// BFME2-only hero extension uses rowed getSlot3FF29F/set3FF0E7 (+5C) for8 slots
// then ParseAsciiStringToGameInfo40116B. Both globals are existing named owners.
// Canonical narrow string header; full300 hot/import/string/EH verification.
// UserPreferences/SkirmishPreferences declarations below are callable views,
// not complete allocating class layouts; this body uses no private members.
#include "ascii_string.h"
#include <stdlib.h>
#include <string.h>
class UnicodeString;
class UserPreferences {
public:
 virtual ~UserPreferences();
 virtual bool load(const AsciiString&);virtual bool load(const UnicodeString&);virtual bool write();
 virtual bool getBool(const AsciiString&,bool)const;
 virtual float getReal(const AsciiString&,float)const;
 virtual int getInt(const AsciiString&,int)const;
 virtual int getEnumIndex(const char*,const char**,int,int)const;
 virtual AsciiString getAsciiString(const AsciiString&,const AsciiString&)const;
 virtual void setBool(const AsciiString&,bool);virtual void setReal(const AsciiString&,float);
 virtual void setInt(const AsciiString&,int);virtual void setAsciiString(const AsciiString&,const AsciiString&);
};
class SkirmishPreferences:public UserPreferences {
public:AsciiString buildProfileKey(const char*);bool rva0043BC0A();
};
class GameSlot;
class GameInfo {public:GameSlot *getSlot(int);};
extern GameInfo *TheSkirmishGameInfo;
class Rva003FF0E7DwordSlot {public:void set(int);};
bool ParseAsciiStringToGameInfo(GameInfo*,AsciiString,bool);
struct SkirmishStringDataView{char header[8];char text[1];};
__forceinline const char *skirmishText(const AsciiString&s){
 const SkirmishStringDataView *data=*(const SkirmishStringDataView *const*)&s;return data?data->text:"";
}
bool SkirmishPreferences::rva0043BC0A(){
 if(!TheSkirmishGameInfo)return false;
 AsciiString value=getAsciiString(buildProfileKey("HeroIndexes"),AsciiString::TheEmptyString);
 const char *p=skirmishText(value);
 for(unsigned i=0;i<8;++i){
 if(!p)break;
  ++p;
  GameSlot *slot=TheSkirmishGameInfo->getSlot(i);
  if(!slot)break;
  ((Rva003FF0E7DwordSlot*)slot)->set(atoi(p));
  p=strchr(p,':');

 }
 value=getAsciiString(buildProfileKey("GameInfo"),AsciiString::TheEmptyString);
 return ParseAsciiStringToGameInfo(TheSkirmishGameInfo,value,true);
}
