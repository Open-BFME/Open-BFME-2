// ?Rva006D1520@@YAXVRva006D07E0Key@@@Z
// partial score=0.96 date=2026-10-10
// cl: /MD /EHsc
// Native006D1520..006D15B0 RET0 consumes established four-byte counted argument.
// Existing rowed caller006D1680 proves argument ownership; copied handle owns
// one reference and is released by lookup006D1450 RET4. Its receiver is the
// existing AptLinker global E176F8; semantic lookup name remains unknown.
// Playback cell E176EC has existing canonical g_aptPlaybackCheckpoints owner.
// Callee006D0930 RET10 iterates (EAStringC + state) records: EAStringC::IsEqualTo
// 006D3090 proves const-EAStringC-pointer first arg; state1 to3, absent-state2.
// Native instructions at006D1570 place LEA before PUSH1; default compiler
// produces the same144B with the five-byte LEA/PUSH ordering swapped.
// No new pins retained. G7 default146 and O1/G7 99 are poorer shapes.
class EAStringC {void *data;public:const char*rva00620090()const;};
class Rva006E3E20Object {public:void rva006E3E20(void*,void*);};
class Rva006D0280 {public:int m_useCount;int unused4;EAStringC name8;int typeC;int argument10;void*object14;void*buffer18;~Rva006D0280();};
class Rva006DB270 {public:void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006D07E0Key {public:
 Rva006D07E0Key(Rva006D0280*p=0):m_object(p){if(p)++p->m_useCount;}
 Rva006D07E0Key(const Rva006D07E0Key&o):m_object(o.m_object){if(m_object)++m_object->m_useCount;}
 ~Rva006D07E0Key(){Rva006D0280*p=m_object;if(p&&--p->m_useCount==0){p->~Rva006D0280();g_pChainBlockAllocator->freeBlock(p,0x1c);}}
 Rva006D0280*m_object;
};

class AptLinker {public:void *rva006D1450(Rva006D07E0Key);};
extern AptLinker *g_bfmeAptLinkerAtE176F8;
extern int g_bfmeAptFlagAtE176D4;
class Rva006CEB10Playback {public:void rva006D0930(const EAStringC &,int,int,int);};
extern Rva006CEB10Playback *g_aptPlaybackCheckpoints;
void Rva006D1520(Rva006D07E0Key key){
 g_bfmeAptLinkerAtE176F8->rva006D1450(key);
 if(g_bfmeAptFlagAtE176D4)g_aptPlaybackCheckpoints->rva006D0930(key.m_object->name8,1,3,2);
}
