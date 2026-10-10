// ?rva005E5BF7@Rva005CDA3D@@QAEHPAVGameMessage@@@Z
// partial score=0.83 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
class GameMessage;
class Rva005E5A8B { public:int rva005E5B82(GameMessage*); };
class Rva005DAA6C { public:int rva005DAA6C(int); };
class Rva005CDA3D { public:int rva005E5BF7(GameMessage*);private:char prefix[8];Rva005E5A8B* delegate; };
int Rva005CDA3D::rva005E5BF7(GameMessage*msg){
 int result=((Rva005DAA6C*)this)->rva005DAA6C((int)msg);
 if(result==1)return result;
 return delegate->rva005E5B82(msg);
}
