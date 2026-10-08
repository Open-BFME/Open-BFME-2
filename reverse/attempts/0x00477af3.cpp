// ?rva00477AF3@Rva00477AF3UpdateReceiver@@QAEXXZ
// partial score=0.99 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHsc
// BFME1 ba7ddda7 HordeContain/HordeTransportContain.cpp supplies update semantics.
// Target ctor/Xfer prove outer+120 count and outer+124 latch; receiver is +10.
// Primary maintenance members are banked, not recovered providers.
int GetGameLogicRandomValue(int,int,char *,int);
class HordeTransportContain {public:void rva004779F9();void rva0047748E();};
class Rva047E59E {public:void rva00468749();};
class Rva00477AF3UpdateReceiver {
public:void rva00477AF3();
private:char head[0x110];int frames;unsigned char enabled;
};
void Rva00477AF3UpdateReceiver::rva00477AF3()
{
    if(enabled==1) {
        if(frames==-1000) {
            frames=GetGameLogicRandomValue(3,5,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeTransportContain.cpp",0x35A);
            ((HordeTransportContain*)((char*)this-0x10))->rva004779F9();
        }
        if(frames<=0) {
            ((HordeTransportContain*)((char*)this-0x10))->rva0047748E();
            frames=GetGameLogicRandomValue(0,4,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeTransportContain.cpp",0x367);
        }
        --frames;
    }
    ((Rva047E59E*)this)->rva00468749();
}
