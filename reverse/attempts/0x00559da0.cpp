// ?rva00559DA0@Rva00559D0CRankWeights@@QBEHPBVRva00553E47StatsCore@@E@Z
// partial score=0.9504761904761905 date=2026-10-10
// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs
class Rva005B8053
{
	void *m_header;
public:
	__declspec(nothrow) void *rva005B8053(unsigned char const *key);
};


#include <algorithm>
class Rva00553E47StatsCore;
class Rva00559D0CRankWeights{
 char opaque[0x2c];float winWeight,lossWeight;
public:int rva00559DA0(const Rva00553E47StatsCore*,unsigned char)const;
};
int Rva00559D0CRankWeights::rva00559DA0(const Rva00553E47StatsCore*stats,unsigned char key)const{
 if(*(const int*)((const char*)stats+0x150)==0)return 0;
 int wins=0;unsigned char k=key;
 Rva005B8053*map=(Rva005B8053*)((char*)stats+4);
 void*node=map->rva005B8053(&k);
 if(node!=*(void**)map)wins=*(unsigned short*)((char*)node+0x12);
 int winPoints=(int)((float)wins*winWeight);
 wins=0;unsigned char k2=key;
 map=(Rva005B8053*)((char*)stats+0x10);
 node=map->rva005B8053(&k2);
 if(node!=*(void**)map)wins=*(unsigned short*)((char*)node+0x12);
 int rank=(int)((float)wins*lossWeight+(float)winPoints);
 return std::max(rank,0);
}
