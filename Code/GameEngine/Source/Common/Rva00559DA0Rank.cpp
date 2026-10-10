// ?rva00559DA0@Rva00559D0CRankWeights@@QBEHPBVRva00553E47StatsCore@@H@Z
// Native559DA0..559E48 RET8; WB13FA600 and owned rank sibling prove
// weights2C/30, nonzero-stat150 and byte-key ushort maps04/10.
// The second argument occupies the native four-byte stack slot. Only its low
// byte selects a key; the signed carrier then holds the truncated win score.
// A saved pointer preserves the original stats address while its dead parameter
// representation transports the byte key at offset3, as native does. This is
// byte access to a parameter object, not an application pointer/layout claim.
// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
class Rva005B8053
{
	void *m_header;
public:
	__declspec(nothrow) void *rva005B8053(unsigned char const *key);
};


// Keep the proven reference selection TU-local; no standalone STLport max COMDAT.
static __forceinline const int& rankMax(const int&a,const int&b){return a<b?b:a;}
class Rva00553E47StatsCore;
class Rva00559D0CRankWeights{
 char opaque[0x2c];float winWeight,lossWeight;
public:int rva00559DA0(const Rva00553E47StatsCore*,int)const;
};
int Rva00559D0CRankWeights::rva00559DA0(const Rva00553E47StatsCore*stats,int key)const{
 if(*(const int*)((const char*)stats+0x150)==0)return 0;
 const Rva00553E47StatsCore*copy=stats;
 int wins=0;unsigned char k=(unsigned char)key;
 ((unsigned char*)&stats)[3]=k;
 Rva005B8053*map=(Rva005B8053*)((char*)copy+4);
 void*node=map->rva005B8053((const unsigned char*)&stats+3);
 if(node!=*(void**)map)wins=*(unsigned short*)((char*)node+0x12);
 key=(int)((float)wins*winWeight);
 wins=0;unsigned char k2=k;
 ((unsigned char*)&stats)[3]=k2;
 map=(Rva005B8053*)((char*)copy+0x10);
 node=map->rva005B8053((const unsigned char*)&stats+3);
 if(node!=*(void**)map)wins=*(unsigned short*)((char*)node+0x12);
 int rank=(int)((float)wins*lossWeight+(float)key);
 return rankMax(rank,0);
}
