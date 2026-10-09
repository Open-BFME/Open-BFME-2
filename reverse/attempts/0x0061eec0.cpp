// ?bfmeBumpURB@BfmeThingURB@@QAEXXZ
// partial score=1.0 date=2026-10-09
// cl: /O2 /Ob2 /G6 /DNDEBUG /MD
class Q1Receiver0134FAAC { public: char pad[0x30]; int seq; __forceinline int &counter(){return seq;} };
extern Q1Receiver0134FAAC *TheQ1Receiver;
class BfmeThingURB {public: char pad[0x10]; int id; void bfmeBumpURB();};
void BfmeThingURB::bfmeBumpURB(){ if(TheQ1Receiver) { int &value=TheQ1Receiver->seq; id=++value; } }
