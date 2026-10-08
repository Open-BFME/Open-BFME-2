// ?Rva00448423@@YA_NPAVLANGameInfo@@PADH@Z
// partial score=0.96967 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /O1 /EHsc /G7
//
// GenerateGameOptionsString, retail 0x00447C46 (99 bytes): the host's game
// options string, empty unless TheLAN has a current game that this machine
// hosts. Ported from Open-BFME-1's GenerateGameOptionsString.cpp (BFME 1
// retail 0x0068DFF0), itself Zero Hour's LANGameInfo.cpp body with the
// include-slots argument.
// Target evidence: the body asks TheLAN (0x009FE958) for its game through
// LANAPI vslot 56 three times, tests it with the rowed amIHost body
// 0x004477C7 (in-game, then slot 0 is the local player), and returns either
// AsciiString::TheEmptyString or 0x00400AF8's string; 0x00400AF8 formats
// "M=%3.3x%s;MC=%X;MS=%d;SD=%d;GSID=%X;GT=%..." and the "H"/"C"/"O:" slot
// records, which is Zero Hour's GameInfoToAsciiString.
// BFME 2 difference: amIHost stays out of line.

typedef bool Bool;

#include "ascii_string.h"
#include "unicode_string.h"
#include <cstring>

template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap( char (*)[N] ) = 0;
};
template <> class VSlots<0>
{
};

enum SlotState { SLOT_OPEN, SLOT_CLOSED, SLOT_EASY_AI, SLOT_MED_AI, SLOT_BRUTAL_AI, SLOT_AI_5, SLOT_PLAYER };
struct GameSlotConnectInfo { GameSlotConnectInfo():ip(0),port(0){} unsigned int ip; unsigned short port; };
class GameSlot {
public:
    GameSlot();
    GameSlot(const GameSlot&);
    virtual ~GameSlot();
    void setState(SlotState,UnicodeString,const GameSlotConnectInfo*);
    void unAccept();
    void setMapAvailability(bool);
    void setPlayerTemplate(int);
    bool decodeHero(unsigned char);
    bool isHuman() const;
    bool isAI() const;
    unsigned char encodeHero() const;
    int get_color() const { return color; }
    int get_playerTemplate() const { return playerTemplate; }
    int get_startPos() const { return startPos; }
    int get_team() const { return team; }
    int get_field20() const { return field20; }
    int get_field40() const { return field40; }
    int get_state() const { return state; }
    bool isAccepted() const { return accepted; }
    bool hasMapData() const { return hasMap; }
    int state;
    bool accepted, hasMap, muted;
    int color, startPos, field14, playerTemplate, team, field20;
    int original[3];
    UnicodeString name;
    AsciiString field34;
    unsigned int ip;
    unsigned short port;
    int field40;
    char pad44[0x18];
    int field5c;
    char pad60[0x1ac-0x60];
};
class GameInfo
{
public:
    GameSlot *getSlot(int);
    void setSlot(int,GameSlot);
    void setMap(AsciiString);
    void setMapCRC(unsigned int);
    void setMapSize(unsigned int);
    void rva0033F898(int);
    void setSeed(int);
    void rva003FF1A7(int);
    AsciiString getMap() const;
    const GameSlot *getConstSlot(int) const;
    unsigned int get_mapMask() const { return mapMask; }
    unsigned int get_mapCRC() const { return mapCRC; }
    unsigned int get_mapSize() const { return mapSize; }
    unsigned int get_seed() const { return seed; }
    unsigned int get_field88() const { return field88; }
    unsigned int get_field5c() const { return field5c; }
    unsigned int get_field58() const { return field58; }
    unsigned int get_rule(unsigned int i) const { return rules[i]; }
    char pad0[0x44];
    unsigned int mapCRC, mapSize, mapMask, seed;
    int field54, field58, field5c;
    unsigned int rules[10];
    unsigned int field88;
};

class LANGameInfo : public GameInfo
{
public:
	Bool amIHost( void ) const;
};

class LANAPI : public VSlots<56>
{
public:
	virtual LANGameInfo *GetMyGame( void ) = 0;
};

extern LANAPI *TheLAN;

AsciiString GameInfoToAsciiString( const GameInfo *game, Bool includeSlots );

AsciiString GenerateGameOptionsString( void )
{
	if( !TheLAN->GetMyGame() || !TheLAN->GetMyGame()->amIHost() )
		return AsciiString::TheEmptyString;

	return GameInfoToAsciiString( TheLAN->GetMyGame(), true );
}

// Native complete447CA9..447FD5, 812B; WB14A7FD0 names GameInfoToByteBuffer
// in LANGameInfo.cpp. ZH GameInfoToAsciiString guides semantic field roles;
// packet byte sequence, offsets, branch letters and helper calls are native.
// Original existing entry symbol retained pending independent name admission.
AsciiString Rva00400783Get(const AsciiString&,bool);
char *Rva004478A9Copy(char*,const char*,char*);
char *Rva0044780FCopy(char*,void*,unsigned int,char*) throw();
char *Rva00447845WriteU16(char*,unsigned short,char*);
char *Rva0044786BWriteU32(char*,unsigned int,char*);
char *Rva00447891Write1(char*,char,char*);
char *Rva00447891Write1(char*,unsigned char,char*);
unsigned char Rva0056BD91Pack(unsigned char,unsigned char,char,char);

static inline const unsigned short *lanWideText(const UnicodeString &s) {
    const unsigned short *data=*reinterpret_cast<const unsigned short *const*>(&s);
    return data ? data+4 : reinterpret_cast<const unsigned short*>(L"");
}

void Rva00447CA9(LANGameInfo *game,char *data,int size)
{
    if (!data) return;
    memset(data,0,size);
    if (!game) return;
    char *cursor=data;
    char *limit=data+size;
    AsciiString map;
    map=Rva00400783Get(game->getMap(),true);
    cursor=Rva004478A9Copy(cursor,map.str(),limit);
    cursor=Rva00447845WriteU16(cursor,game->get_mapMask(),limit);
    cursor=Rva0044786BWriteU32(cursor,game->get_mapCRC(),limit);
    cursor=Rva0044786BWriteU32(cursor,game->get_mapSize(),limit);
    cursor=Rva0044786BWriteU32(cursor,game->get_seed(),limit);
    for (unsigned int j=0;j<10;++j) cursor=Rva0044786BWriteU32(cursor,game->get_rule(j),limit);
    cursor=Rva0044786BWriteU32(cursor,game->get_field88(),limit);
    cursor=Rva0044786BWriteU32(cursor,game->get_field5c(),limit);
    cursor=Rva00447891Write1(cursor,static_cast<char>(game->get_field58()),limit);
    for (unsigned int i=0;i<8;++i) {
        const GameSlot *slot=game->getConstSlot(i);
        if (slot && slot->isHuman()) {
            cursor=Rva00447891Write1(cursor,'P',limit);
            { UnicodeString name(lanWideText(slot->name),10);
              cursor=Rva0044780FCopy(cursor,const_cast<unsigned short*>(lanWideText(name)),22,limit); }
            cursor=Rva0044786BWriteU32(cursor,slot->ip,limit);
            cursor=Rva00447845WriteU16(cursor,slot->port,limit);
            char flags=0;
            flags |= slot->isAccepted()?1:0;
            flags |= (slot->hasMapData()?1:0)<<1;
            cursor=Rva00447891Write1(cursor,flags,limit);
            unsigned char packed=Rva0056BD91Pack(slot->get_color(),slot->get_playerTemplate(),-1,-2);
            cursor=Rva00447891Write1(cursor,packed,limit);
            cursor=Rva00447891Write1(cursor,static_cast<unsigned char>(slot->get_startPos()),limit);
            cursor=Rva00447891Write1(cursor,static_cast<unsigned char>(slot->get_team()),limit);
            cursor=Rva00447891Write1(cursor,static_cast<unsigned char>(slot->get_field20()),limit);
            cursor=Rva00447891Write1(cursor,static_cast<unsigned char>(slot->get_field40()),limit);
            unsigned char hero=slot->encodeHero();
            cursor=Rva00447891Write1(cursor,hero,limit);
        } else if (slot && slot->isAI()) {
            char state;
            if(slot->get_state()==2) state='E';
            else if(slot->get_state()==3) state='M';
            else if(slot->get_state()==4) state='H';
            else state='B';
            cursor=Rva00447891Write1(cursor,state,limit);
            unsigned char packed=Rva0056BD91Pack(slot->get_color(),slot->get_playerTemplate(),-1,-2);
            cursor=Rva00447891Write1(cursor,packed,limit);
            cursor=Rva00447891Write1(cursor,static_cast<unsigned char>(slot->get_startPos()),limit);
            cursor=Rva00447891Write1(cursor,static_cast<unsigned char>(slot->get_team()),limit);
            cursor=Rva00447891Write1(cursor,static_cast<unsigned char>(slot->get_field20()),limit);
            unsigned char hero=slot->encodeHero();
            cursor=Rva00447891Write1(cursor,hero,limit);
        } else if(slot && slot->get_state()==0) cursor=Rva00447891Write1(cursor,'O',limit);
        else if(slot && slot->get_state()==1) cursor=Rva00447891Write1(cursor,'C',limit);
        else cursor=Rva00447891Write1(cursor,'X',limit);
    }
}

// Banked C++ near miss: native448423..448D06 2275B and WB14A8BF0
// ByteBufferToGameInfo LANGameInfo.cpp lines758..1060 establish identity.
// ZH text parser guides semantic field roles. This reproduces the native
// instruction sequence and branch targets but not local stack displacements.
// The helper type and map-mask alias repairs are separately verified commits.
// field40 is NAT behavior from WB line944; unresolved field names stay neutral.
char *Rva00447FD5Append(char*,StringBase<char>*,char*);
char *Rva00447909Copy(char*,void*,unsigned int,char*);
char *Rva0044799ACopy1(char*,void*,char*);
char *Rva0044793FReadU32(char*,unsigned int*,char*);
char *Rva0044796CReadU16(char*,unsigned short*,char*);
void Rva0056BDA5Split(unsigned char,char,char,unsigned char*,unsigned char*);
AsciiString _Rva00621350GameInfoMapPath(const AsciiString&,bool);
class Rva003FF0E7DwordSlot { public: void set(int); };
// The admitted GameInfo address-named setter reproduces native map-mask +4C.

class MultiplayerSettings {
    char pad[0x38]; int colorCount, field3c, numColors;
public: int getNumColors(){ if(numColors==0) numColors=colorCount; return numColors; }
};
extern MultiplayerSettings *TheMultiplayerSettings;
struct PlayerTemplateBody { char bytes[0x1dc]; };
class PlayerTemplateStore {
    char pad[0xc]; PlayerTemplateBody *start,*finish;
public: int getPlayerTemplateCount(){return finish-start;}
};
extern PlayerTemplateStore *ThePlayerTemplateStore;

// Each helper returns the old cursor on failure and the advanced cursor on success.
#define LAN_READ(call) { next=(call); if(next<=cursor) return false; if(next>limit) return false; cursor=next; }
bool Rva00448423(LANGameInfo *game,char *data,int size)
{
    if(!game || !data) return false;
    char *cursor=data; char *next=0; char *limit=data+size;
    AsciiString map;
    LAN_READ(Rva00447FD5Append(cursor,reinterpret_cast<StringBase<char>*>(&map),limit));
    map=_Rva00621350GameInfoMapPath(map,true);
    if(!map.getLength()) return false;
    short mask; unsigned int crc, mapSize, seed;
    LAN_READ(Rva0044796CReadU16(cursor,reinterpret_cast<unsigned short*>(&mask),limit));
    LAN_READ(Rva0044793FReadU32(cursor,&crc,limit));
    LAN_READ(Rva0044793FReadU32(cursor,&mapSize,limit));
    LAN_READ(Rva0044793FReadU32(cursor,&seed,limit));
    int rules[10]={-1};
    for(int i=0;i<10;++i) {
        LAN_READ(Rva0044793FReadU32(cursor,reinterpret_cast<unsigned int*>(&rules[i]),limit));
    }
    unsigned int field88=0;
    LAN_READ(Rva0044793FReadU32(cursor,&field88,limit));
    unsigned int field5c=0;
    LAN_READ(Rva0044793FReadU32(cursor,&field5c,limit));
    char field58=-1;
    LAN_READ(Rva0044799ACopy1(cursor,&field58,limit));
    GameSlot slots[8];
    for(unsigned int i=0;i<8;++i) {
        GameSlot *slot=&slots[i];
        char state;
        LAN_READ(Rva0044799ACopy1(cursor,&state,limit));
        if(state=='P') {
            {
                UnicodeString name;
                unsigned short text[11];
                LAN_READ(Rva00447909Copy(cursor,text,22,limit));
                name+=text;
                if(!name.getLength()) return false;
                unsigned int ip; unsigned short port;
                LAN_READ(Rva0044793FReadU32(cursor,&ip,limit));
                LAN_READ(Rva0044796CReadU16(cursor,&port,limit));
                GameSlotConnectInfo connect;
                connect.ip=ip; connect.port=port;
                slot->setState(SLOT_PLAYER,name,&connect);
            }
            char flags;
            LAN_READ(Rva0044799ACopy1(cursor,&flags,limit));
            bool accept=(flags&1)!=0, hasMap=((flags>>1)&1)!=0;
            if(accept) slot->accepted=true; else slot->unAccept();
            if(hasMap) slot->setMapAvailability(true); else slot->setMapAvailability(false);
            unsigned char packed; char color, player;
            LAN_READ(Rva0044799ACopy1(cursor,&packed,limit));
            Rva0056BDA5Split(packed,-1,-2,reinterpret_cast<unsigned char*>(&color),reinterpret_cast<unsigned char*>(&player));
            if(color<-1 || color>=TheMultiplayerSettings->getNumColors()) return false;
            slot->color=color;
            if(player<-2 || player>=ThePlayerTemplateStore->getPlayerTemplateCount()) return false;
            slot->setPlayerTemplate(player);
            char start,team,field20,field40;
            LAN_READ(Rva0044799ACopy1(cursor,&start,limit));
            if(start<-1) return false;
            slot->startPos=start;
            LAN_READ(Rva0044799ACopy1(cursor,&team,limit));
            if(team<-1 || team>=4) return false;
            slot->team=team;
            LAN_READ(Rva0044799ACopy1(cursor,&field20,limit));
            if(field20<-100 || field20>0 || field20%5!=0) return false;
            slot->field20=field20;
            LAN_READ(Rva0044799ACopy1(cursor,&field40,limit));
            int natBehavior=field40;
            if(natBehavior<0 || natBehavior>256) return false;
            slot->field40=natBehavior;
            unsigned char hero;
            LAN_READ(Rva0044799ACopy1(cursor,&hero,limit));
            reinterpret_cast<Rva003FF0E7DwordSlot*>(slot)->set(game->getSlot(i)->field5c);
            if(!slot->decodeHero(hero)) return false;
        } else if(state=='E' || state=='M' || state=='H' || state=='B') {
            switch(state) {
            case 'E': {GameSlotConnectInfo connect; slot->setState(SLOT_EASY_AI,UnicodeString::TheEmptyString,&connect); break;}
            case 'M': {GameSlotConnectInfo connect; slot->setState(SLOT_MED_AI,UnicodeString::TheEmptyString,&connect); break;}
            case 'H': {GameSlotConnectInfo connect; slot->setState(SLOT_BRUTAL_AI,UnicodeString::TheEmptyString,&connect); break;}
            case 'B': {GameSlotConnectInfo connect; slot->setState(SLOT_AI_5,UnicodeString::TheEmptyString,&connect); break;}
            default: return false;
            }
            unsigned char packed; char color,player;
            LAN_READ(Rva0044799ACopy1(cursor,&packed,limit));
            Rva0056BDA5Split(packed,-1,-2,reinterpret_cast<unsigned char*>(&color),reinterpret_cast<unsigned char*>(&player));
            if(color<-1 || color>=TheMultiplayerSettings->getNumColors()) return false;
            slot->color=color;
            if(player<-2 || player>=ThePlayerTemplateStore->getPlayerTemplateCount()) return false;
            slot->setPlayerTemplate(player);
            char start,team,field20;
            LAN_READ(Rva0044799ACopy1(cursor,&start,limit)); slot->startPos=start;
            LAN_READ(Rva0044799ACopy1(cursor,&team,limit)); slot->team=team;
            LAN_READ(Rva0044799ACopy1(cursor,&field20,limit));
            if(field20<-100 || field20>0 || field20%5!=0) return false;
            slot->field20=field20;
            unsigned char hero;
            LAN_READ(Rva0044799ACopy1(cursor,&hero,limit));
            reinterpret_cast<Rva003FF0E7DwordSlot*>(slot)->set(game->getSlot(i)->field5c);
            if(!slot->decodeHero(hero)) return false;
        } else if(state=='O') {GameSlotConnectInfo connect; slot->setState(SLOT_OPEN,UnicodeString::TheEmptyString,&connect);}
        else if(state=='C') {GameSlotConnectInfo connect; slot->setState(SLOT_CLOSED,UnicodeString::TheEmptyString,&connect);}
        else return false;
    }
    for(unsigned int i=0;i<8;++i) game->setSlot(i,slots[i]);
    game->setMap(map);
    game->setMapCRC(crc); game->setMapSize(mapSize);
    game->rva0033F898(mask);
    game->setSeed(seed); memcpy(game->rules,rules,sizeof(rules));
    game->field88=field88; game->rva003FF1A7(field5c); game->field58=field58;
    return true;
}
#undef LAN_READ
