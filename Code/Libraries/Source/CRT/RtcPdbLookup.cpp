// cl: /O1 /G6 /Oi /Ob1 /MD /GX- /GS- /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// Complete native pdblkup.obj member (GetImageInfo, GetPdbDll, _RTC_GetSrcLine),
// independently authored from retail bytes, native COFF identities, CodeView
// records and call relationships, against public SDK declarations only.
// No Microsoft implementation source read. Prior evidence:
// reverse/attempt_support/0x0075b177-pdb-source-lookup/ and pdb-*-2026102x/.
#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <malloc.h>
struct PDB;struct DBI;struct Mod;
struct ImageInfo {
 unsigned long sig,BaseAddress,BaseSize;HMODULE hndl;
 IMAGE_NT_HEADERS *img;IMAGE_SECTION_HEADER *sectHdr;char *imgName;ImageInfo *next;
};
extern "C" {
static HMODULE mspdb=0,psapi=0,imghlp=0,kernel=0;
static int (__cdecl *PDBOpenValidate3)(const char *,const char *,long *,char *,char *,unsigned long *,unsigned long *,PDB **)=0;
static int (__cdecl *PDBOpenDBI)(PDB *,const char *,const char *,DBI **)=0;
static int (__cdecl *DBIQueryModFromAddr)(DBI *,unsigned short,long,Mod **,unsigned short *,long *,long *)=0;
static int (__cdecl *ModQueryLines)(Mod *,unsigned char *,long *)=0;
static int (__cdecl *ModClose)(Mod *)=0;
static int (__cdecl *DBIClose)(DBI *)=0;
static int (__cdecl *PDBClose)(PDB *)=0;
static IMAGE_NT_HEADERS *(WINAPI *ImageNtHeader)(void *)=0;
static BOOL (WINAPI *pGetModuleInformation)(HANDLE,HMODULE,MODULEINFO *,DWORD)=0;
static BOOL (WINAPI *pEnumProcessModules)(HANDLE,HMODULE *,DWORD,DWORD *)=0;
static HANDLE (WINAPI *CreateToolhelp32SnapshotW9x)(DWORD,DWORD)=0;
static BOOL (WINAPI *Module32FirstW9x)(HANDLE,MODULEENTRY32 *)=0;
static BOOL (WINAPI *Module32NextW9x)(HANDLE,MODULEENTRY32 *)=0;
static ImageInfo *lImages=0;
static const char *mspdbName="MSPDB71.DLL";
}
static ImageInfo *GetImageInfo(unsigned long address) {
 ImageInfo *cur;
 for(cur=lImages;cur;cur=cur->next)
  if(cur->BaseAddress<=address && address-cur->BaseAddress<=cur->BaseSize)return cur;
 while(lImages) {ImageInfo *next=lImages->next;HeapFree(GetProcessHeap(),0,lImages);lImages=next;}
 if(!imghlp) {
  kernel=LoadLibraryA("KERNEL32.DLL");imghlp=LoadLibraryA("IMAGEHLP.DLL");
  if(!kernel||!imghlp)return 0;
  ImageNtHeader=(IMAGE_NT_HEADERS *(WINAPI *)(void *))GetProcAddress(imghlp,"ImageNtHeader");if(!ImageNtHeader)return 0;
  CreateToolhelp32SnapshotW9x=(HANDLE(WINAPI *)(DWORD,DWORD))GetProcAddress(kernel,"CreateToolhelp32Snapshot");
  if(!CreateToolhelp32SnapshotW9x) {
   psapi=LoadLibraryA("PSAPI.DLL");if(!psapi)return 0;
   pEnumProcessModules=(BOOL(WINAPI *)(HANDLE,HMODULE *,DWORD,DWORD *))GetProcAddress(psapi,"EnumProcessModules");if(!pEnumProcessModules)return 0;
   pGetModuleInformation=(BOOL(WINAPI *)(HANDLE,HMODULE,MODULEINFO *,DWORD))GetProcAddress(psapi,"GetModuleInformation");if(!pGetModuleInformation)return 0;
  } else {
   Module32FirstW9x=(BOOL(WINAPI *)(HANDLE,MODULEENTRY32 *))GetProcAddress(kernel,"Module32First");if(!Module32FirstW9x)return 0;
   Module32NextW9x=(BOOL(WINAPI *)(HANDLE,MODULEENTRY32 *))GetProcAddress(kernel,"Module32Next");if(!Module32NextW9x)return 0;
  }
 }
 if(!CreateToolhelp32SnapshotW9x) {
  HANDLE hProcess=GetCurrentProcess();HMODULE hModules[512];DWORD imageCount;MODULEINFO info;
  if(!pEnumProcessModules(hProcess,hModules,sizeof(hModules),&imageCount))return 0;
  imageCount/=sizeof(HMODULE);
  for(unsigned i=0;i<imageCount;++i) {
   if(!pGetModuleInformation(hProcess,hModules[i],&info,sizeof(info)))return 0;
   ImageInfo *node=(ImageInfo *)HeapAlloc(GetProcessHeap(),0,sizeof(ImageInfo));if(!node)goto error;
   node->hndl=hModules[i];node->BaseAddress=(DWORD)info.lpBaseOfDll;node->BaseSize=info.SizeOfImage;
   node->imgName=0;node->next=lImages;lImages=node;
  }
 } else {
  HANDLE snap=CreateToolhelp32SnapshotW9x(TH32CS_SNAPMODULE,0);if(snap==INVALID_HANDLE_VALUE)return 0;
  MODULEENTRY32 *entry=(MODULEENTRY32 *)_alloca(sizeof(MODULEENTRY32));entry->dwSize=sizeof(MODULEENTRY32);
  BOOL exists=Module32FirstW9x(snap,entry);
  while(exists) {
   ImageInfo *node=(ImageInfo *)HeapAlloc(GetProcessHeap(),0,sizeof(ImageInfo));
   if(!node){CloseHandle(snap);goto error;}
   node->hndl=entry->hModule;node->BaseAddress=(DWORD)entry->modBaseAddr;node->BaseSize=entry->modBaseSize;
   node->imgName=0;node->next=lImages;lImages=node;
   exists=Module32NextW9x(snap,entry);
  }
  CloseHandle(snap);
 }
 for(cur=lImages;cur;cur=cur->next) {
  cur->img=ImageNtHeader((void *)cur->BaseAddress);
  cur->sectHdr=(IMAGE_SECTION_HEADER *)((char *)cur->img+sizeof(DWORD)+sizeof(IMAGE_FILE_HEADER)+cur->img->FileHeader.SizeOfOptionalHeader);
  char *buf=(char *)_alloca(513);buf[512]=0;
  if(!GetModuleFileNameA(cur->hndl,buf,512))goto error;
  int len=0;while(buf[len])++len;
  cur->imgName=(char *)HeapAlloc(GetProcessHeap(),0,len+1);if(!cur->imgName)goto error;
  int i=0;do{cur->imgName[i]=buf[i];}while(buf[i++]);
 }
 for(cur=lImages;cur;cur=cur->next)
  if(cur->BaseAddress<=address && address-cur->BaseAddress<=cur->BaseSize)return cur;
error:
 while(lImages) {
  ImageInfo *next=lImages->next;
  if(lImages->imgName)HeapFree(GetProcessHeap(),0,lImages->imgName);
  HeapFree(GetProcessHeap(),0,lImages);lImages=next;
 }
 return 0;
}
static HMODULE GetPdbDll() {
 static int alreadyTried=0;
 if(alreadyTried)return 0;
 alreadyTried=1;
 HMODULE result=LoadLibraryA(mspdbName);if(result)return result;
 HMODULE advapi=LoadLibraryA("ADVAPI32.DLL");if(!advapi)return 0;
 LONG (WINAPI *RegOpenKeyExA)(HKEY,LPCSTR,DWORD,REGSAM,PHKEY)=(LONG(WINAPI *)(HKEY,LPCSTR,DWORD,REGSAM,PHKEY))GetProcAddress(advapi,"RegOpenKeyExA");if(!RegOpenKeyExA)return 0;
 LONG (WINAPI *RegQueryValueExA)(HKEY,LPCSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD)=(LONG(WINAPI *)(HKEY,LPCSTR,LPDWORD,LPDWORD,LPBYTE,LPDWORD))GetProcAddress(advapi,"RegQueryValueExA");if(!RegQueryValueExA)return 0;
 LONG (WINAPI *RegCloseKey)(HKEY)=(LONG(WINAPI *)(HKEY))GetProcAddress(advapi,"RegCloseKey");if(!RegCloseKey)return 0;
 HKEY key1;DWORD len,type;
 if(RegOpenKeyExA(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\VisualStudio\\7.1\\Setup\\VS",0,KEY_QUERY_VALUE,&key1)) {FreeLibrary(advapi);return 0;}
 if(RegQueryValueExA(key1,"EnvironmentDirectory",0,&type,0,&len))return 0;
 len+=13;
 char *buf=(char *)_alloca(len);
 LONG status=RegQueryValueExA(key1,"EnvironmentDirectory",0,&type,(BYTE *)buf,&len);
 RegCloseKey(key1);FreeLibrary(advapi);if(status)return 0;
 if(buf[len-2]!='\\')buf[len-1]='\\';else --len;
 for(int i=0;i<12;++i)buf[len+i]=mspdbName[i];
 return LoadLibraryA(buf);
}
int _RTC_GetSrcLine(unsigned long address,char *source,int sourcelen,int *pline,char **moduleName) {
 struct SSrcModuleHdr {unsigned short cFile,cSeg;};
 struct SStartEnd {unsigned long start,end;};
 char *errname=(char *)_alloca(1024);
 int res=0;ImageInfo *info;long imageAddr,secAddr;WORD sectionIndex;
 PDB *ppdb;DBI *pdbi;Mod *pmod;long err,offsetRes,size;DWORD fo,cb;char *pdbname;WORD sectionIndexRes;static int PDBOK=0;
 *pline=0;source[0]=0;*moduleName=0;
 info=GetImageInfo(address);if(!info)goto done;
 imageAddr=address-info->BaseAddress;*moduleName=info->imgName;res=1;
 if(!PDBOK) {
  if(mspdb)goto done;
  mspdb=GetPdbDll();if(!mspdb)goto done;
  PDBOpenValidate3=(int(__cdecl *)(const char *,const char *,long *,char *,char *,DWORD *,DWORD *,PDB **))GetProcAddress(mspdb,"PDBOpenValidate3");if(!PDBOpenValidate3)return 0;
  PDBOpenDBI=(int(__cdecl *)(PDB *,const char *,const char *,DBI **))GetProcAddress(mspdb,"PDBOpenDBI");if(!PDBOpenDBI)return 0;
  DBIQueryModFromAddr=(int(__cdecl *)(DBI *,WORD,long,Mod **,WORD *,long *,long *))GetProcAddress(mspdb,"DBIQueryModFromAddr");if(!DBIQueryModFromAddr)return 0;
  ModQueryLines=(int(__cdecl *)(Mod *,BYTE *,long *))GetProcAddress(mspdb,"ModQueryLines");if(!ModQueryLines)return 0;
  ModClose=(int(__cdecl *)(Mod *))GetProcAddress(mspdb,"ModClose");if(!ModClose)return 0;
  DBIClose=(int(__cdecl *)(DBI *))GetProcAddress(mspdb,"DBIClose");if(!DBIClose)return 0;
  PDBClose=(int(__cdecl *)(PDB *))GetProcAddress(mspdb,"PDBClose");if(!PDBClose)return 0;
  PDBOK=1;
 }
 for(sectionIndex=0;sectionIndex<info->img->FileHeader.NumberOfSections;++sectionIndex) {
  if(info->sectHdr[sectionIndex].VirtualAddress<(DWORD)imageAddr && (DWORD)(imageAddr-info->sectHdr[sectionIndex].VirtualAddress)<info->sectHdr[sectionIndex].SizeOfRawData)goto sectionFound;
 }
 goto done;
sectionFound:
 secAddr=imageAddr-info->sectHdr[sectionIndex].VirtualAddress;if(secAddr==-1)goto done;
 pdbname=(char *)_alloca(260);
 if(!PDBOpenValidate3(info->imgName,"",&err,errname,pdbname,&fo,&cb,&ppdb))goto done;
 if(!PDBOpenDBI(ppdb,"r",0,&pdbi))goto closePdb;
 if(!DBIQueryModFromAddr(pdbi,++sectionIndex,secAddr,&pmod,&sectionIndexRes,&offsetRes,&size))goto closeDbi;
 if(!ModQueryLines(pmod,0,&size)||!size)goto closeMod;
 {
 BYTE *lineBuffer=(BYTE *)HeapAlloc(GetProcessHeap(),0,size);
 if(!ModQueryLines(pmod,lineBuffer,&size))goto closeMod;
 int i;
 SSrcModuleHdr *module=(SSrcModuleHdr *)lineBuffer;
 long *fileOffsets=(long *)(module+1);
 for(i=0;i<module->cFile;++i) {
  WORD *file=(WORD *)(lineBuffer+fileOffsets[i]);
  int segments=file[0];
  long *lineOffsets=(long *)(file+2);
  SStartEnd *ranges=(SStartEnd *)(lineOffsets+segments);
  char *srcName=(char *)(ranges+segments);
  int seg;
  for(seg=0;seg<segments;++seg)
   if(ranges[seg].start<=(DWORD)secAddr && (DWORD)secAddr<=ranges[seg].end)goto segmentFound;
  continue;
segmentFound:
  WORD *lines=(WORD *)(lineBuffer+lineOffsets[seg]);
  int count=lines[1];long *offsets=(long *)(lines+2);WORD *lineNums=(WORD *)(offsets+count);
  int best=-1;DWORD delta=0xffffffff;
  for(int j=0;j<count;++j) {DWORD dist=secAddr-offsets[j];if(dist<delta){best=j;delta=dist;}}
  if(best>=0) {
   *pline=lineNums[best];
   int copied=0;while(srcName[copied] && copied<sourcelen){source[copied]=srcName[copied];++copied;}
   source[copied<sourcelen?copied:sourcelen-1]=0;
  }
  break;
 }
 HeapFree(GetProcessHeap(),0,lineBuffer);
 }
closeMod:ModClose(pmod);
closeDbi:DBIClose(pdbi);
closePdb:PDBClose(ppdb);
done:
 return res;
}
