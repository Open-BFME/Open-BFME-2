// Retail RVA006C83B0: 958B Windows profiling-command launcher.
// Target WB1746230 establishes command strings and Debug slot38; retail
// establishes buffer boundaries and align8 stack frame. ZH profile_cmd
// has related command plumbing but no VSPerf80 runner. Original name unknown.
// Use existing hook globals, matching FrameStart/FrameEnd providers.
// cl: /O2 /Oi /MD /Ireference/shims/sweep 
#include <windows.h>
#include "../debug/debug.h"
#include "internal_funclevel.h"
#include <stdio.h>
#include <string.h>
extern "C" __declspec(dllimport) UINT __stdcall GetSystemDirectoryA(char*,UINT);

// Retail .bss VA 0x00E0C764 is initially null.
static HMODULE profilePerfLibrary;

void rva006C83B0(Debug &dbg,unsigned argc,const char *const *argv)
{
 if(argc<1){dbg << "Please specify mode\n";return;}
 __declspec(align(8)) char systemPath[260]="";
 GetSystemDirectoryA(systemPath,260);
 strcat(systemPath,"\\cmd.exe");
 __declspec(align(8)) char scriptPath[260];
 GetModuleFileNameA(0,scriptPath,260);
 char *end=strrchr(scriptPath,'\\');
 if(!end)end=scriptPath;
 strcpy(end,"\\profile.cmd");
 __declspec(align(8)) char command[512];
 strcpy(command,"/c \"");
 strcat(command,scriptPath);
 strcat(command,"\"");
 bool start=false;
 int next;
 if(argv[0][0]=='+'){
  const char *output; if(argc>=2)output=argv[1];else output="profileOut";
  __declspec(align(8)) char format[256];
  sprintf(format," /start %s %lu",output,GetCurrentProcessId());
  strcat(command,format);
  next=2;
  start=true;
 }else if(argv[0][0]=='-'){
  strcat(command," /stop");
  next=1;
 }else{dbg << "Invalid mode\n";return;}
 for(;next<(int)argc;++next){strcat(command," ");strcat(command,argv[next]);}
 dbg << "Executing profile command: " << systemPath << " " << command << "\n";
 __declspec(align(8)) STARTUPINFOA startup;
 __declspec(align(8)) PROCESS_INFORMATION process;
 memset(&startup,0,sizeof(startup));
 startup.cb=sizeof(startup);
 startup.dwFlags=STARTF_USESHOWWINDOW;
 startup.wShowWindow=SW_HIDE;
 if(!CreateProcessA(systemPath,command,0,0,FALSE,0x08000000,0,0,&startup,&process)){
  dbg << "Launching profiler proccess failed. Make sure 'profile.cmd' exists in the current working directory.\n";return;
 }
 if(WaitForSingleObject(process.hProcess,30000)==258){dbg << "Timed out waiting for profiler process to end.\n";return;}
 if(start){
  if(!profilePerfLibrary){
   profilePerfLibrary=LoadLibraryA("VSPerf80.dll");
   if(!profilePerfLibrary){dbg << "Could not load profiler API dll\n";return;}
   ProfileFuncLevelTracer::frameStartHook=(void (__stdcall *)(int,int))GetProcAddress(profilePerfLibrary,"StartProfile");
   ProfileFuncLevelTracer::frameEndHook=(void (__stdcall *)(int,int))GetProcAddress(profilePerfLibrary,"StopProfile");
  }
 }else{
  ProfileFuncLevelTracer::frameStartHook=0;
  ProfileFuncLevelTracer::frameEndHook=0;
  if(profilePerfLibrary)FreeLibrary(profilePerfLibrary);
 }
}
