// ?rva002B2A0A@LivingWorldLogic@@QAEXXZ
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /EHsc /MD
class Rva0020F27EHost {public:bool rva0020F27E(int,int);};
struct RvaFloatPair {
 float x,y;
 RvaFloatPair(){}
 RvaFloatPair(const RvaFloatPair&a){x=a.x;y=a.y;}
 ~RvaFloatPair(){}
};
class Rva002BECCD {public:void rva002BECCD(RvaFloatPair,float);};
class Rva002D3627Host {public: char pad[0x1c];unsigned x,y; union Bits{float f;unsigned u;};void setX(float a){Bits b;b.f=a;x=b.u;}void setY(float a){Bits b;b.f=a;y=b.u;}};
extern Rva002D3627Host*g_00DFEF18;

class LivingWorldLogic {public:void rva002B2A0A();private:char pad[0xb0];Rva0020F27EHost*host;char padB4[4];int index;};
void LivingWorldLogic::rva002B2A0A(){
 RvaFloatPair pos;pos.x=0.0f;pos.y=0.0f;
 host->rva0020F27E(index,(int)&pos);
 if(g_00DFEF18){((Rva002BECCD*)g_00DFEF18)->rva002BECCD(pos,0.0f);Rva002D3627Host::Bits a,b;a.f=pos.x;b.f=pos.y;g_00DFEF18->x=a.u;g_00DFEF18->y=b.u;}
}
