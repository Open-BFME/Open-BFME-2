// cl: /Ireference/shims/bfme2_ascii /MD /O1 /G7 /arch:SSE /EHsc
// ?openFile@@YAPAVFile@@PBVAsciiString@@@Z @0x000A9F48 61B
// Free file-open helper: AsciiString m_data ? m_data+8 : empty, then loop
// TheFileSystem->openFile(s,1,0) stripping leading path via strchr(s,'\\').
// Evidence: callers 0x000AA557 (AsciiString+".apt") and 0x000AB96D pass string
// object in eax (mov eax,[eax]; lea esi,[eax+8]); empty global
// g_Rva0107301CEmptyString; IAT strchr; rowed openFile 0x00600C34.
#include "ascii_string.h"

// File virtual slot34 is readEntireAndClose: the matched RAMFile provider
// at605682 independently proves the char* result and slot13. NativeAA557
// saves that entire-file buffer at owner+4.
class File {public:
 virtual void v0();virtual void v1();virtual void close();virtual void v3();virtual void v4();virtual void v5();virtual void nextLine(char *,int);virtual void v7();virtual void v8();virtual void v9();virtual void v10();virtual void v11();virtual void v12();
 virtual char *readEntireAndClose();
 bool eof();
};
class FileSystem
{
public:
	File *openFile(const char *filename, int access, int unk);
};
extern FileSystem *TheFileSystem;
extern "C" __declspec(dllimport) char *__cdecl strchr(const char *, int);

// Native DAT temporary is destroyed without an extra unwind state; the
// already-owned render-data parser also carries this helper exception contract.
static __declspec(noinline) __declspec(nothrow) File *openFile(const AsciiString *fname)
{
	char *t = *(char * const *)fname;
	const char *s = t ? t + 8 : "";
	for (;;) {
		File *f = TheFileSystem->openFile(s, 1, 0);
		if (f)
			return f;
		s = strchr(s, '\\');
		if (!s)
			return 0;
		++s;
	}
}


// NativeAA557..AA5B2 RET0: construct name+".apt", open with the private
// EAX-argument61B helper, read the entire buffer through virtual34 and store at owner+4.
// Owned AB910 ctor independently proves the AsciiString0/word4 prefix;
// the rest of the owner (including its two hash maps) is not accessed here.
class Rva000AB910 {public:
 AsciiString name; char *data;
 void rva000AA557();
 void rva000AB193();
 void rva000AB956();
};
void Rva000AB910::rva000AA557(){
 AsciiString path(name);path.concat(".apt");
 File *input=openFile(&path);
 data=input?input->readEntireAndClose():0;
}

#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/BFME2ParticleTextureHandles.h"
extern BFME2ParticleTextureHandle BFME2LoadParticleTexture(const char*,int,int);
class TextureAsset {public:void SetQualityLevel(int);};
class ShroudFilter; // The already-owned10B setter at13ED10 writes word+8. Its ledger spelling
// is an ABI carrier here; this is not a claim that a filter is an iostream.
namespace _STL {class ios_base {protected:void _M_clear_nothrow(int);friend class ::ShroudFilter;friend class ::Rva000AB910;};}
class ShroudFilter {public:int words[5]; void setMode(int mode){reinterpret_cast<_STL::ios_base*>(this)->_M_clear_nothrow(mode);}};
class ShroudTexture {public:ShroudFilter *getFilter();};
class AssetReference {public:unsigned pointer;AssetReference(const AssetReference &);};
class Rva00785140Handle {// Native new-expression carries no delete-on-throw state for this27B
// pointer-copy constructor; carry that observed caller contract.
public:__declspec(nothrow) Rva00785140Handle(const AssetReference &);private:unsigned vptr;AssetReference ref;};
class Object;
class ObjectLookupMap {public:Object **findSlot(int *);};
class WW3D {public:static void Get_Device_Resolution(int&,int&,int&,bool&);};
class GlobalData; extern GlobalData *TheWritableGlobalData;
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *,const char *,...);
// Target AB193..AB3E2 full591B: .dat lines map texture IDs to asset holders.
// Buffer-end NUL, renderer outputs, DD1 flag, filter words, allocation8 and
// hash-table+8 calls are native facts; WB8AA510 independently supplies the
// same filename/texture pipeline. Original resolution-local type is unknown.
struct Rva000AB193Resolution {int x,y;};
void Rva000AB910::rva000AB193(){
 AsciiString path(name);path.concat(".dat");
 File *input=openFile(&AsciiString(path.str()));
 if(!input)return;
 char line[1024]; line[1023]=0;
 Rva000AB193Resolution resolution;int bits; bool windowed;
 bool mode;
 WW3D::Get_Device_Resolution(resolution.x,resolution.y,bits,windowed);
 mode=*(bool*)((char*)TheWritableGlobalData+0xdd1);
 if(resolution.x==1024)mode=!mode;
 while(!input->eof()){
  input->nextLine(line,1023);
  if(line[0]==';')continue;
  AsciiString filename;
  int id,index;
  if(sscanf(line,"%d->%d",&id,&index)==2)filename.format("apt_%s_%d.tga",name.str(),index);
  else if(sscanf(line,"%d",&id)==1)filename.format("apt_%s_%d.tga",name.str(),id);
  else continue;
  BFME2ParticleTextureHandle texture=BFME2LoadParticleTexture(filename.str(),1,0);
  ((TextureAsset*)&texture)->SetQualityLevel(2);
  ShroudTexture *view=(ShroudTexture*)&texture;
  if(mode){view->getFilter()->words[1]=1;view->getFilter()->words[0]=1;reinterpret_cast<_STL::ios_base*>(view->getFilter())->_M_clear_nothrow(1);}
  else{view->getFilter()->words[1]=3;view->getFilter()->words[0]=3;reinterpret_cast<_STL::ios_base*>(view->getFilter())->_M_clear_nothrow(3);}
  view->getFilter()->words[3]=1;view->getFilter()->words[4]=1;
  Rva00785140Handle *handle=new Rva00785140Handle((const AssetReference&)texture);
  *reinterpret_cast<ObjectLookupMap*>((char*)this+8)->findSlot(&id)=(Object*)handle;
 }
 input->close();
}

class AptAnimData {public:void rva000AB83B();};
// Native AB956..AB96D23B retains this between the two loaders then
// tail-calls the owned AptAnimData geometry loader with no receiver adjustment.
void Rva000AB910::rva000AB956(){rva000AA557();rva000AB193();reinterpret_cast<AptAnimData*>(this)->rva000AB83B();}
