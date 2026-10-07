// ?rva002B2CE7@@YA_NPAVGameMessage@@PAPAVRva0020E89C@@H@Z
// partial score=0.93 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /MD
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
union GameMessageArgumentType {int integer;};
class GameMessage {public:const GameMessageArgumentType*getArgument(int)const;};
class Rva0020E89C;
class Rva0020EAF6View {public:Rva0020E89C*rva0020EAF6(int);};
class Rva002BA8F1Logic {public:char pad[0xb0];Rva0020EAF6View*manager;};
extern Rva002BA8F1Logic*g_009FEF10;
static __declspec(noinline) bool rva002B2CE7(GameMessage*message,Rva0020E89C**out,int index){
 const GameMessageArgumentType *arg=message->getArgument(index);
 int key=((const volatile GameMessageArgumentType*)arg)->integer;
 _ReadWriteBarrier();
 Rva0020E89C*result=g_009FEF10->manager->rva0020EAF6(key);
 *out=result;return result!=0;
}
// ?rva002B2CE7Caller absent-from-retail
bool rva002B2CE7Caller(GameMessage*message,Rva0020E89C**out,int index){return rva002B2CE7(message,out,index);}
