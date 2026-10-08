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

class GameSlot {
public:
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
    char pad0[4];
    int state;
    bool accepted, hasMap, muted;
    int color, startPos, field14, playerTemplate, team, field20;
    int original[3];
    UnicodeString name;
    AsciiString field34;
    unsigned int ip;
    unsigned short port;
    int field40;
};
class GameInfo
{
public:
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
