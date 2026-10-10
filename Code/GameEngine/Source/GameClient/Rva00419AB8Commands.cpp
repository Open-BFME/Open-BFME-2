// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native [419AB8,419B68), RET20. WB1329F00 corroborates the command
// strings and dispatch. Original callback/receiver names remain unknown.
// Console virtual +38 writes help text; engine virtual +50 requests exit.
// Writable global-data byte1100 is set from atoi's nonzero result.
extern "C" int __cdecl strcmp(const char *,const char *);
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
class Rva00419AB8Console { public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
#undef V
 virtual void write(const char *);
};
class Rva00419AB8EngineView { public:
#define V(n) virtual void slot##n();
 V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19)
#undef V
 virtual void requestExit(bool);
};
class GameEngine;extern GameEngine *TheGameEngine;
class GlobalData;extern GlobalData *TheWritableGlobalData;
struct Rva00419AB8DataView { unsigned char unknown[0x1100];bool fastGameplay; };
bool __stdcall Rva00419AB8(void *receiver,const char *command,int mode,
 unsigned count,const char **args)
{
 if(strcmp(command,"help")==0) {
  if(mode!=0)return true;
  if(count==0)reinterpret_cast<Rva00419AB8Console *>(receiver)->write("game group help:\n  die\n");
  else if(strcmp(args[0],"die")==0)reinterpret_cast<Rva00419AB8Console *>(receiver)->write("die\n\nQuits to desktop NOW!\n");
  else return false;
 } else if(strcmp(command,"die")==0) {
  reinterpret_cast<Rva00419AB8EngineView *>(TheGameEngine)->requestExit(true);
 } else if(strcmp(command,"fastgameplay")==0 && count>0) {
  reinterpret_cast<Rva00419AB8DataView *>(TheWritableGlobalData)->fastGameplay=atoi(args[0])!=0;
 } else return false;
 return true;
}
