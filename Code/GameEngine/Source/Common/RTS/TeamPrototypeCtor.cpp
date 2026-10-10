// ??0TeamPrototype@@QAE@PAVTeamFactory@@ABVAsciiString@@1PAVPlayer@@_NPAVDict@@H@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii /ICode/Libraries/Include /DBFME_ASCII_DTOR_DECL
// ZH Team.cpp (BFME1 reference575ba2b04743f190) supplies semantic structure.
// Native offsets and WB identity are target evidence; opaque field labels and
// the source-only flag wrapper do not assert recovered native type names.
// Native3A3299..3A33A1264B; WB EF1480 and C1AE94 name getter establish
// identity. Target owner/name strings10/14; flags18; script namesAC[32];
// template12C size1EC; frame320; coordinate328 and instance head334.
#include "ascii_string.h"
#include "Common/Snapshot.h"
#include "Lib/Coord3D.h"
#include <string.h>
class Dict;class TeamFactory;class Player;class Team;class Script;
class TeamTemplateInfo { public:TeamTemplateInfo(Dict*);virtual ~TeamTemplateInfo();private:char body[0x1ec-4]; };
#include "../GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
struct TeamInitialCoordinate:Coord3D {TeamInitialCoordinate(){x=0.0f;y=0.0f;z=0.0f;}};
// A one-byte subobject retains the native initialization ordering at +0x324.
struct TeamFlag324
{
 bool value;
 __forceinline TeamFlag324(bool v=false) throw():value(v){}
};
typedef char TeamFlagSizeCheck[sizeof(TeamFlag324)==1?1:-1];
class TeamPrototype:public Snapshot {
public:
 TeamPrototype(TeamFactory*,const AsciiString&,const AsciiString&,Player*,bool,Dict*,int);
 void addToLists();
protected:
 virtual ~TeamPrototype();virtual void crc(Xfer*);virtual void xfer(Xfer*);virtual void loadPostProcess();
private:
 TeamFactory *m_factory;Player*m_owningPlayer;int m_id;
 AsciiString m_ownerName,m_name;int m_flags;bool m_productionConditionAlwaysFalse;
 AsciiString m_conditionName;Script*m_productionConditionScript;bool m_retrievedGenericScripts;
 Script*m_genericScriptsToRun[32];AsciiString m_genericScriptNames[32];
 TeamTemplateInfo m_teamTemplate;AsciiString m_attackPriorityName;
 bool m_byte31C,m_byte31D,m_byte31E;unsigned m_frame320;TeamFlag324 m_byte324;
 TeamInitialCoordinate m_coordinate328;Team *m_teamInstanceList;
};
typedef char TeamPrototypeSizeCheck[sizeof(TeamPrototype)==0x338?1:-1];
TeamPrototype::TeamPrototype(TeamFactory*tf,const AsciiString&owner,const AsciiString&name,Player*player,bool singleton,Dict*d,int id):
 m_factory(tf),m_owningPlayer(player),m_id(id),m_ownerName(owner),m_name(name),m_flags(singleton?1:0),
 m_productionConditionAlwaysFalse(false),m_productionConditionScript(0),m_retrievedGenericScripts(false),
 m_teamTemplate(d),m_byte31C(false),m_byte31D(false),m_byte31E(false),m_frame320(TheGameLogic->getFrame()),
 m_byte324(false),m_coordinate328(),m_teamInstanceList(0)
{
 memset(m_genericScriptsToRun,0,sizeof(m_genericScriptsToRun));
 addToLists();
}
