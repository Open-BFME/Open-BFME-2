// ?Thread_Function@PSThreadClass@@MAEXXZ
// partial score=0.999027 date=2026-10-09
// Focused body bank for PersistentStorageThread.cpp at7761282bfc.
// Required TU declaration updates (all87 old bodies were verified exact):
// basic_string: declare basic_string(const basic_string &); inline c_str returns start.
// PSPlayerAllStats: inline Int getID() const { return m_id; }.
// Queue interface: after addResponse add slot1c then trackPlayerStats(PSPlayerAllStats).
// Concrete GameSpyPSMessageQueue: inline setLocalPlayerID(Int id) writes m_localPlayerID.
// Replace the TU opaque UserPreferences view with the full declaration below.
#include <cstdio>
class UnicodeString;
namespace _STL {
template<> struct less<AsciiString> { bool operator()(const AsciiString &, const AsciiString &) const; };
}
typedef _STL::map<AsciiString, AsciiString> StoragePreferenceMap;
template<> AsciiString &StoragePreferenceMap::operator[](const AsciiString &);
class UserPreferences : public StoragePreferenceMap
{
public:
    UserPreferences();
    virtual ~UserPreferences();
    virtual bool load(const AsciiString &);
    virtual bool load(const UnicodeString &);
    virtual bool write();
    virtual bool getBool(const AsciiString &, bool) const;
    virtual float getReal(const AsciiString &, float) const;
    virtual int getInt(const AsciiString &, int) const;
    virtual int getEnumIndex(const char *, const char **, int, int) const;
    virtual AsciiString getAsciiString(const AsciiString &,const AsciiString &) const;
    virtual void setBool(const AsciiString &,bool);
    virtual void setReal(const AsciiString &,float);
    virtual void setInt(const AsciiString &,int);
    virtual void setAsciiString(const AsciiString &,const AsciiString &);
private:
    void *m_filename;
};

// Reference: ZH PSThreadClass::Thread_Function, donor9cbfb551fe20.
// Target5580FB..558D07 adds request categories5..12 and two persistent streams.
// Native lock+4 is MutexClass::LockClass::Failed; mutex at thread+68 gates exit.
class Rva00555EB4Setter { public: void set(Rva00385333String); };
class Rva00555EEFSetter { public: void set(Rva00385333String); };
class Rva00555F2ASetter { public: void set(Rva00385333String); };
class GameSpyGame { public: char prefix[0x101c]; void *match; };
extern GameSpyGame *TheGameSpyGame;
extern "C" void *NewGame(int);
extern "C" void FreeGame(void *);
extern "C" void CloseStatsConnection();
extern "C" int SendGameSnapShotA(void *, const char *, int);
typedef void (*StorageReadFn)(int,int,persisttype_t,int,int,time_t,char*,int,void*);
typedef void (*StorageWriteFn)(int,int,persisttype_t,int,int,time_t,void*);
extern "C" void GetPersistDataValuesA(int,int,persisttype_t,int,const char*,StorageReadFn,void*);
extern "C" void GetPersistData(int,int,persisttype_t,int,StorageReadFn,void*);
extern "C" void SetPersistDataValuesA(int,int,persisttype_t,int,const char*,StorageWriteFn,void*);
extern "C" void SetPersistData(int,int,persisttype_t,int,const char*,int,StorageWriteFn,void*);
extern "C" void PreAuthenticatePlayerCDA(int,const char*,const char*,const char*,PersAuthCallbackFn,void*);
extern "C" void ghttpRequestThink(int);
struct MiscPrefOwner;
void resetOnlineMiscPref(int,int,int,int,int,int,MiscPrefOwner*);
template<class T> inline const T &storageMin(const T &a,const T &b) { return a<b?a:b; }
// ?Thread_Function@PSThreadClass@@MAEXXZ present-unmatched
void PSThreadClass::Thread_Function() {
 int len;
 try {
  BfmeOpaqueOwnedRecord1432 req;
  for (;;) {
   MutexClass::LockClass lock(*(MutexClass *)m_owner,1);
   bool gotRequest=TheGameSpyPSMessageQueue->getRequest(req);
   if(!lock.Failed() && !gotRequest) break;
   if(gotRequest) switch(req.requestType) {
   case 5:
    if(tryConnect() && TheGameSpyGame) { ++m_opCount; TheGameSpyGame->match=NewGame(0); }
    break;
   case 6:
    if(!IsStatsConnected()) {
     if(TheGameSpyGame) {
      if(TheGameSpyGame->match) { FreeGame(TheGameSpyGame->match);TheGameSpyGame->match=0; }
     }
    } else if(TheGameSpyGame) {
     len=req.results.size();int count=0;
     while(len>0) { count+=storageMin(len,511);len-=storageMin(len,511); }
     SendGameSnapShotA(0,req.results.c_str(),1);
     if(TheGameSpyGame->match) { FreeGame(TheGameSpyGame->match);TheGameSpyGame->match=0; }
     --m_opCount;
    }
    break;
   case 7:
    if(!IsStatsConnected()) {
     if(TheGameSpyGame) {
      if(TheGameSpyGame->match) { FreeGame(TheGameSpyGame->match);TheGameSpyGame->match=0; }
     }
    } else if(TheGameSpyGame) {
     if(TheGameSpyGame->match) { SendGameSnapShotA(0,"",1); FreeGame(TheGameSpyGame->match);TheGameSpyGame->match=0; }
     --m_opCount;
    }
    break;
   case 0:
    if(!MESSAGE_QUEUE->getLocalPlayerID()) {
     MESSAGE_QUEUE->setLocalPlayerID(req.player.getID());
     ((Rva00555EB4Setter *)MESSAGE_QUEUE)->set(req.email);
     ((Rva00555EEFSetter *)MESSAGE_QUEUE)->set(req.nick);
     ((Rva00555F2ASetter *)MESSAGE_QUEUE)->set(req.password);
    }
    if(tryConnect()) {
     if(req.m_04) {
      if(req.m_04>0) {
       if(req.m_04>2) {
        if(req.m_04==3) {
         ++m_opCount;GetPersistDataValuesA(0,req.player.getID(),pd_public_ro,0,"\\preorder",getPreorderCallback,this);
         ++m_opCount;GetPersistData(0,req.player.getID(),pd_public_rw,1,getPersistentDataCallback,this);
         ++m_opCount;GetPersistData(0,req.player.getID(),pd_public_rw,2,getPersistentDataCallback,this);
        }
       } else { ++m_opCount;GetPersistData(0,req.player.getID(),pd_public_rw,req.m_04,getPersistentDataCallback,this); }
      }
     } else { ++m_opCount;GetPersistDataValuesA(0,req.player.getID(),pd_public_ro,0,"\\preorder",getPreorderCallback,this); }

    }
    ((Rva00557996 *)this)->rva00557A33(req.player.getID());
    if(MESSAGE_QUEUE->getLocalPlayerID()==req.player.getID()) { ((Rva00557996 *)this)->rva00557996(1);((Rva00557996 *)this)->rva00557996(2); }
    break;
   case 2:
    if(tryConnect() && tryLogin(req.player.getID(),req.nick,req.password,req.email)) {
     char kvbuf[256];sprintf(kvbuf,"\\locale\\%d",req.player.getLocale());
     ++m_opCount;SetPersistDataValuesA(0,req.player.getID(),pd_public_rw,0,kvbuf,setPersistentDataLocaleCallback,this);
    }
    break;
   case 1: {
    UserPreferences pref;
    AsciiString userPrefFilename;
    userPrefFilename.format("%s\\MiscPref%d.ini","Online Files",MESSAGE_QUEUE->getLocalPlayerID());
    pref.UserPreferences::load(userPrefFilename);
    Int addedInDesyncs2=pref.UserPreferences::getInt("0",0);if(addedInDesyncs2<0)addedInDesyncs2=10;
    Int addedInDesyncs3=pref.UserPreferences::getInt("1",0);if(addedInDesyncs3<0)addedInDesyncs3=10;
    Int addedInDesyncs4=pref.UserPreferences::getInt("2",0);if(addedInDesyncs4<0)addedInDesyncs4=10;
    Int addedInDiscons2=pref.UserPreferences::getInt("3",0);if(addedInDiscons2<0)addedInDiscons2=10;
    Int addedInDiscons3=pref.UserPreferences::getInt("4",0);if(addedInDiscons3<0)addedInDiscons3=10;
    Int addedInDiscons4=pref.UserPreferences::getInt("5",0);if(addedInDiscons4<0)addedInDiscons4=10;
    if(req.addDesync || req.addDiscon) {
     AsciiString val;
     if(req.lastHouse==2) {
      val.format("%d",addedInDesyncs2+req.addDesync);pref["0"]=val;
      val.format("%d",addedInDiscons2+req.addDiscon);pref["3"]=val;
     } else if(req.lastHouse==3) {
      val.format("%d",addedInDesyncs3+req.addDesync);pref["1"]=val;
      val.format("%d",addedInDiscons3+req.addDiscon);pref["4"]=val;
     } else {
      val.format("%d",addedInDesyncs4+req.addDesync);pref["2"]=val;
      val.format("%d",addedInDiscons4+req.addDiscon);pref["5"]=val;
     }
     pref.UserPreferences::write();
     if(req.password.size()==0)return;
    }
    if(!req.player.getID())return;
    if(tryConnect() && tryLogin(req.player.getID(),req.nick,req.password,req.email)) {
     if(TheGameSpyPSMessageQueue)TheGameSpyPSMessageQueue->trackPlayerStats(req.player);
     switch(req.m_04) {
     case 3: {
      ++m_opCount;char *data=rva0055686A(&req.player,&len);
      SetPersistData(0,req.player.getID(),pd_public_rw,1,data,len,(StorageWriteFn)resetOnlineMiscPref,this);
      Rva00030830FreeAllocation(data);
     }
     case 2: {
      ++m_opCount;char *data=rva00556B3C(&req.player,&len);
      SetPersistData(0,req.player.getID(),pd_public_rw,2,data,len,(StorageWriteFn)resetOnlineMiscPref,this);Rva00030830FreeAllocation(data);break;
     }
     case 1: {
      ++m_opCount;char *data=rva0055686A(&req.player,&len);
      SetPersistData(0,req.player.getID(),pd_public_rw,1,data,len,(StorageWriteFn)resetOnlineMiscPref,this);Rva00030830FreeAllocation(data);break;
     }
     }
    }
    break;
   }
   case 11:
    if(tryConnect() && tryLogin(req.player.getID(),req.nick,req.password,req.email)) {
     ++m_opCount;char kvbuf[128];
     if(req.player.rva00556508().m_194>0)sprintf(kvbuf,"\\best1v1LadderRank\\%d",req.player.rva00556508().m_194);
     if(req.player.rva00556508().m_198>0)sprintf(kvbuf+strlen(kvbuf),"\\best2v2LadderRank\\%d",req.player.rva00556508().m_198);
     SetPersistDataValuesA(0,req.player.getID(),pd_public_rw,0,kvbuf,(StorageWriteFn)resetOnlineMiscPref,this);
    }
    break;
   case 3:
    if(tryConnect()) {
     ++m_opCount;
     CDAuthInfo cdAuthInfo;
     cdAuthInfo.done=false;cdAuthInfo.success=false;cdAuthInfo.id=0;
     char cdkeyHash[33]="",validationToken[33]="";
     char *munkeeHack=strdup(req.cdkey.c_str());
     GenerateAuthA(GetChallenge(0),munkeeHack,validationToken);GenerateAuthA("",munkeeHack,cdkeyHash);Rva00030830FreeAllocation(munkeeHack);
     PreAuthenticatePlayerCDA(0,"preorder",cdkeyHash,validationToken,preAuthCDCallback,&cdAuthInfo);
     for(;;) {
      MutexClass::LockClass inner(*(MutexClass *)m_owner,1);
      if(!inner.Failed() || !IsStatsConnected() || cdAuthInfo.done)break;
      PersistThink();
     }
     if(cdAuthInfo.done && cdAuthInfo.success)GetPersistDataValuesA(0,cdAuthInfo.id,pd_public_ro,0,"\\preorder",getPreorderCallback,this);
     else --m_opCount;
    }
    break;
   case 10: ((Rva00557996 *)this)->rva00557AC2();break;
   case 12: ((Rva00557996 *)this)->rva00557B04();break;
   }
   if(IsStatsConnected()) { PersistThink();if(m_opCount<=0) { CloseStatsConnection();m_opCount=0; } }
   for(_STL::map<int,Rva00557996Request*>::iterator it=m_requests.begin();it._M_node!=m_requests.end()._M_node;) {
    _STL::map<int,Rva00557996Request*>::iterator next=it;
    ++next;ghttpRequestThink(it->first);it=next;
   }
  }
  if(IsStatsConnected())CloseStatsConnection();
 } catch(...) {}
}
