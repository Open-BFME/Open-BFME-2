// cl: /O1 /Oy- /Oi- /MD /GX- /Ireference/shims/bfme2_ascii
// Target: GameFileClass::Set_Name at 0x0007846F, 712 bytes, RET4.
// Identity: the named constructor at 0x00078737 calls this body; retail
// GameFileClass vtable 0x00BC6788 places Set_Name at slot 2, Is_Open at 6,
// and Close at 14. Verified siblings establish file +4, presence +8,
// path +9 and original filename +0x10D, each path buffer 260 bytes.
// Semantic guide: GeneralsMD W3DFileSystem.cpp in Open-BFME-1 reference
// checkout dae380faa5f6fa536eec8d6ebbe877321d4cb51d. Retail establishes
// the five extensions, two-letter directories, apt_ exception, user map
// previews, editor molds, lookup order and all literal strings below.
// The user-directory getter returns an owned AsciiString at 0x2360DE.
// Keep imported declarations for string comparisons, strncpy and sprintf;
// retail strcpy/strlen instead call the verified direct CRT thunks. Hide
// only their unused imported header declarations before declaring those
// real names. No renamed CRT helper is defined or used by this body.
#define strcpy GameFileUnusedHeaderCopy
#define strlen GameFileUnusedHeaderLength
#include "ascii_string.h"
#undef strcpy
#undef strlen
extern "C" char *__cdecl strcpy(char *,const char *);
extern "C" unsigned int __cdecl strlen(const char *);
extern "C" char *__cdecl _mbscat(char *,const char *);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *,const char *,...);
class FileSystem { public: bool doesFileExist(const char *) const; };
extern FileSystem *TheFileSystem;
class GlobalData { public: AsciiString rva002360DE() const; };
extern GlobalData *TheWritableGlobalData;
class GameFileClass {
public:
 virtual ~GameFileClass();
 virtual const char *File_Name() const;
 virtual const char *Set_Name(const char *);
 virtual int Create(); virtual int Delete(); virtual bool Is_Available(int);
 virtual bool Is_Open() const; virtual int Open(int); virtual int Open(const char *,int);
 virtual int Read(void *,int); virtual int Seek(int,int); virtual int Tell();
 virtual int Size(); virtual int Write(const void *,int); virtual void Close();
private:
 void *m_theFile; bool m_fileExists; char m_filePath[260],m_filename[260];
};
const char *GameFileClass::Set_Name(const char *filename) {
 if(Is_Open()) Close();
 strncpy(m_filename,filename,260);
 char name[260];char extension[32];extension[0]=0;
 strcpy(name,filename);
 int i=strlen(name);--i;int extLen=1;
 while(i>0 && extLen<32) {
  if(name[i]=='.') {strcpy(extension,name+i);name[i]=0;break;}
  --i;++extLen;
 }
 int j=0;
 for(i=0;name[i];++i) if(name[i]!=' ') name[j++]=name[i];
 name[j]=0;
 int fileType=0;
 if(_strcmpi(extension,".w3d")==0) fileType=1;
 else if(_strcmpi(extension,".tga")==0) fileType=2;
 else if(_strcmpi(extension,".png")==0) fileType=5;
 else if(_strcmpi(extension,".dds")==0) fileType=3;
 else if(_strcmpi(extension,".jpg")==0) fileType=4;
 if(fileType==1) {
  strcpy(m_filePath,"Art/W3D/");
  if(strlen(name)>=2) {
   char *end=m_filePath+strlen(m_filePath);
   *end++=filename[0];*end++=filename[1];*end++='\\';strcpy(end,filename);
  } else _mbscat(m_filePath,filename);
 } else if(fileType>=2 && fileType<=5) {
  if(strlen(name)>=2 && strncmp(filename,"apt_",4)!=0) {
   strcpy(m_filePath,"Art/CompiledTextures/");
   char *end=m_filePath+strlen(m_filePath);
   *end++=filename[0];*end++=filename[1];*end++='\\';strcpy(end,filename);
  } else {strcpy(m_filePath,"Art/Textures/");_mbscat(m_filePath,filename);}
 } else strcpy(m_filePath,filename);
 m_fileExists=TheFileSystem->doesFileExist(m_filePath);
 if(!m_fileExists && TheWritableGlobalData) {
  if(fileType==2) {sprintf(m_filePath,"%sMapPreviews/",TheWritableGlobalData->rva002360DE().str());_mbscat(m_filePath,filename);}
  m_fileExists=TheFileSystem->doesFileExist(m_filePath);
 }
 if(!m_fileExists && fileType==1) {
  sprintf(m_filePath,"data/editor/molds/%s",filename);
  m_fileExists=TheFileSystem->doesFileExist(m_filePath);
 }
 return m_filename;
}
