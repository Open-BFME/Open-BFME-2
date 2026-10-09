// ?LoadPCAFile@StandingWaterArea@@QAEXXZ
// partial score=0.6655433844008063 date=2026-10-09
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Op /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Target 3093F6..309CF8; WB BDE250 names StandingWaterArea::LoadPCAFile.
// Neutral record type: native proves 16 bytes and four float components, not original type name.
extern "C" __declspec(dllimport) double __cdecl atof(const char*);
extern "C" __declspec(dllimport) int __cdecl atoi(const char*);
#include <new>
#include <string>
#include <vector>

#include "ascii_string.h"
struct StandingWaterPCARecord { StandingWaterPCARecord(); float X,Y,Z,W; };
class Rva00308DF0Ref;
class Rva00308DF0 {public:Rva00308DF0Ref *rva00308DF0();};
struct Rva00199FCCRec { AsciiString key;char pad[32]; };
class Rva00199FCC {public:void *rva00199FCC(const AsciiString &name);private:Rva00199FCCRec *begin,*end;};
void *Rva00199FCC::rva00199FCC(const AsciiString &name){Rva00199FCCRec *p=begin;for(;p!=end;++p){if(p->key.compareNoCase(name)==0)break;}return p!=end?p:0;}
struct StandingWaterPCAProperty {AsciiString key; unsigned pad; AsciiString value;};
class File { public:virtual ~File();virtual bool open(const char *,int);virtual void close();virtual int read(void*,int)=0;virtual int write(const void*,int)=0;enum seekMode{START,CURRENT,END};virtual int seek(int,seekMode)=0;virtual void nextLine(char*,int)=0;};
class FileSystem {public:File *openFile(const char *,int,int);};
extern FileSystem *TheFileSystem;
void Rva00309358Tokenize(const std::string&,std::vector<std::string>&,const std::string&);
class StandingWaterArea
{
 unsigned char prefix[0xa0]; unsigned count;float scale;
 StandingWaterPCARecord *mean;StandingWaterPCARecord *channels[9];bool needsLoad;
public:void rva003080CE();void LoadPCAFile();
};
void StandingWaterArea::LoadPCAFile()
{
 if(!needsLoad)return;
 needsLoad=false;rva003080CE();
 Rva00308DF0Ref *material=reinterpret_cast<Rva00308DF0*>(this)->rva00308DF0();
 if(!material)return;
 StandingWaterPCAProperty *entry=static_cast<StandingWaterPCAProperty*>(reinterpret_cast<Rva00199FCC*>(reinterpret_cast<char*>(material)+12)->rva00199FCC(AsciiString("WaterPCATexture1")));
 if(!entry)return;
 AsciiString filename(entry->value);
 for(int k=0;k<3;++k)filename.removeLastChar();
 filename.concat("basis");
 AsciiString path("Art\\Textures\\");path.concat(filename);
 File *file=TheFileSystem->openFile(path.str(),0x21,0);
 if(!file)return;
 std::string header,scaleText,meanText,basisText[12];
 std::vector<std::string> headerTokens;
 char headerBuffer[128];file->nextLine(headerBuffer,128);header=headerBuffer;
 Rva00309358Tokenize(header,headerTokens,std::string(" "));
 count=atoi(headerTokens[1].c_str());
 int bufSize=count*60;char *buffer=new char[bufSize];
 file->nextLine(buffer,bufSize);scaleText=buffer;
 file->nextLine(buffer,bufSize);meanText=buffer;
 for(int j=0;j<3;++j){
  file->nextLine(buffer,bufSize);basisText[j*4]=buffer;
  file->nextLine(buffer,bufSize);basisText[j*4+1]=buffer;
  file->nextLine(buffer,bufSize);basisText[j*4+2]=buffer;
  file->nextLine(buffer,bufSize);basisText[j*4+3]=buffer;
 }
 delete[]buffer;file->close();
 std::vector<std::string> scaleTokens,meanTokens,basisTokens[12];
 Rva00309358Tokenize(scaleText,scaleTokens,std::string(" "));
 Rva00309358Tokenize(meanText,meanTokens,std::string(" "));
 for(int j=0;j<3;++j){
  Rva00309358Tokenize(basisText[j*4],basisTokens[j*4],std::string(" "));
  Rva00309358Tokenize(basisText[j*4+1],basisTokens[j*4+1],std::string(" "));
  Rva00309358Tokenize(basisText[j*4+2],basisTokens[j*4+2],std::string(" "));
  Rva00309358Tokenize(basisText[j*4+3],basisTokens[j*4+3],std::string(" "));
 }
 scale=(float)atof(scaleTokens[1].c_str());
 mean=new StandingWaterPCARecord[count];
 for(int j=0;j<3;++j){channels[j]=new StandingWaterPCARecord[count];channels[j+3]=new StandingWaterPCARecord[count];channels[j+6]=new StandingWaterPCARecord[count];}
 for(unsigned i=1;i<=count;++i){
  mean[i-1].X=(atof(meanTokens[i].c_str())*(1.0/255.0));
  for(int j=0;j<3;++j){
   channels[j][i-1].X=(atof(basisTokens[j*4][i].c_str())*(1.0/255.0));
   channels[j][i-1].Y=(atof(basisTokens[j*4+1][i].c_str())*(1.0/255.0));
   channels[j][i-1].Z=(atof(basisTokens[j*4+2][i].c_str())*(1.0/255.0));
   channels[j][i-1].W=(atof(basisTokens[j*4+3][i].c_str())*(1.0/255.0));
  }
  mean[i-1].Z=(atof(meanTokens[count+i].c_str())*(1.0/255.0));
  for(int j=0;j<3;++j){
   channels[j+6][i-1].X=(atof(basisTokens[j*4][count+i].c_str())*(1.0/255.0));
   channels[j+6][i-1].Y=(atof(basisTokens[j*4+1][count+i].c_str())*(1.0/255.0));
   channels[j+6][i-1].Z=(atof(basisTokens[j*4+2][count+i].c_str())*(1.0/255.0));
   channels[j+6][i-1].W=(atof(basisTokens[j*4+3][count+i].c_str())*(1.0/255.0));
  }
  mean[i-1].Y=(atof(meanTokens[2*count+i].c_str())*(1.0/255.0));
  for(int j=0;j<3;++j){
   channels[j+3][i-1].X=(atof(basisTokens[j*4][2*count+i].c_str())*(1.0/255.0));
   channels[j+3][i-1].Y=(atof(basisTokens[j*4+1][2*count+i].c_str())*(1.0/255.0));
   channels[j+3][i-1].Z=(atof(basisTokens[j*4+2][2*count+i].c_str())*(1.0/255.0));
   channels[j+3][i-1].W=(atof(basisTokens[j*4+3][2*count+i].c_str())*(1.0/255.0));
  }
 }
}
