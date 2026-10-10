// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
//
// ?rva005E5BF7@Rva005CDA3D@@QAEHPAVGameMessage@@@Z, retail 0x005e5bf7, 30 bytes. Banked partial (score 0.83) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
class GameMessage;
class Rva005E5A8B { public:int rva005E5B82(GameMessage*); };
class Rva005DAA6C { public:int rva005DAA6C(int); };
class Rva005CDA3D { public:int rva005E5BF7(GameMessage*);private:char prefix[8];Rva005E5A8B* delegate; };
int Rva005CDA3D::rva005E5BF7(GameMessage*msg){
 int result=((Rva005DAA6C*)this)->rva005DAA6C((int)msg);
 if(result==1)return result;
 return (delegate?delegate:delegate)->rva005E5B82(msg);
}
