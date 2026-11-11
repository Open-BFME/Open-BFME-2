// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// Clean reference: Open-BFME-1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d
// game/GameEngine/Source/GameClient/MapPreviewImage.cpp; ZH MapUtil purpose.
// Target-specific evidence: WB C5EF20 preserves _art.tga UV inversion and
// C5F770 names copyFromBigToDir. Native main300EB4..30127A includes catch
// continuation301149..301159 and common cleanup301220..30127A (967B).
// The211-byte helper3007A8..30087A is followed by nextbody30087B; its private
// EAX/stack-reference ABI is produced by ordinary static C++ beside caller.
// Target FileSystem open carries third32-bit arg0; Image is34B with names4/8,
// UV14 and texture2C. Those facts come from native bodies and existing rows;
// BF1 donor supplies semantics and control structure only.
#include "ascii_string.h"
#include <string.h>
template<class T> __forceinline void StringBase<T>::concat(T c) {concat(&c,1);}
#include "../../Include/Common/File.h"
#include "../../Include/Common/FileSystem.h"
extern FileSystem *TheFileSystem;
// Native300F6E passes TheGameState and3010A4 uses TheWritableGlobalData's
// existing narrow path getter. These declaration-only views preserve their
// established ABI; no donor global address or additional pin is carried over.
#include "../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;
#include "../../Include/Common/GameState.h"
extern GameState *TheGameState;
class TextureClass {public: void Release_Ref();};
class BfmeMapPictureTexture {
public:
 BfmeMapPictureTexture(const char *);
 ~BfmeMapPictureTexture() { if(ptr) ptr->Release_Ref(); }
private: TextureClass *ptr;
};
#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../Libraries/Include/Lib/Region2D.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../Include/GameClient/ImageClass.h"
#include "../../Include/GameClient/Image.h"
#include "../../Include/Common/XferException.h"
// Native3007F1/300854 use the existing game array allocation operators.
#include <new>
#include "../../Include/GameClient/Rva003006C4.h"
static void copyFromBigToDir(const AsciiString &infile,const AsciiString &outfile) {
 File *file=TheFileSystem->openFile(infile.str(),0x41);
 if(!file) throw XferException(5,0);
 int fileSize=file->seek(0, File::END);
 file->seek(0, File::START);
 char *buffer=new char[fileSize];
 if(!buffer) throw XferException(5,0);
 if(file->read(buffer,fileSize)<fileSize) throw XferException(5,0);
 file->close();
 File *filenew=TheFileSystem->openFile(outfile.str(),0x4a);
 if(!filenew || filenew->write(buffer,fileSize)<fileSize) throw XferException(5,0);
 filenew->close();
 delete [] buffer;
}
Image *getMapPreviewImage(AsciiString mapName) {
 if(!TheWritableGlobalData) return 0;
 if(!strstr(mapName.str(),".map")) return 0;
 AsciiString tgaName=mapName;
 AsciiString name;
 AsciiString tempName;
 AsciiString filename;
 tgaName.removeLastChar();tgaName.removeLastChar();tgaName.removeLastChar();tgaName.removeLastChar();
 name=tgaName;
 filename=reinterpret_cast<const StringBase<char> *>(&tgaName)->reverseFind('\\')+1;
 reinterpret_cast<StringBase<char> *>(&filename)->concat(".tga");reinterpret_cast<StringBase<char> *>(&tgaName)->concat(".tga");
 AsciiString portableName=TheGameState->realMapPathToPortableMapPath(name);
 reinterpret_cast<StringBase<char> *>(&tempName)->set(*reinterpret_cast<const StringBase<char> *>(&AsciiString::TheEmptyString));
 for(int i=0;i<portableName.getLength();++i) {
  // Canonical StringBase stores its buffer pointer at0 and text atbuffer+8.
  // Spell this inlined access here; the speed-built23B getter remains owned
  // by string_base_inline.cpp rather than emitting a size-built shadow copy.
  const char *buffer=*reinterpret_cast<const char *const *>(&portableName);
  char c=buffer ? buffer[8+i] : 0;
  if(c=='\\' || c==':') reinterpret_cast<StringBase<char> *>(&tempName)->concat('_'); else reinterpret_cast<StringBase<char> *>(&tempName)->concat(c);
 }
 name=tempName;
 reinterpret_cast<StringBase<char> *>(&name)->concat(".tga");
 Image *image=(Image *)TheMappedImageCollection->findImageByName(tempName);
 if(!image) {
  Region2D uv;
  uv.hi.x=1.0f;uv.hi.y=1.0f;uv.lo.x=0.0f;uv.lo.y=0.0f;
  AsciiString artName=tgaName;
  artName.removeLastChar();artName.removeLastChar();artName.removeLastChar();artName.removeLastChar();
  reinterpret_cast<StringBase<char> *>(&artName)->concat("_art.tga");
  if(TheFileSystem->doesFileExist(artName.str())) {tgaName=artName;uv.hi.y=0.0f;uv.lo.y=1.0f;}
  else if(!TheFileSystem->doesFileExist(tgaName.str())) return 0;
  AsciiString mapPreviewDir;
  mapPreviewDir.format("%sMapPreviews/",TheWritableGlobalData->rva002360DE().str());
  reinterpret_cast<Rva003006C4 *>(TheFileSystem)->rva003006C4(mapPreviewDir);
  reinterpret_cast<StringBase<char> *>(&mapPreviewDir)->concat(*reinterpret_cast<const StringBase<char> *>(&name));
  bool success=false;
  try {copyFromBigToDir(tgaName,mapPreviewDir);success=true;} catch(...) {success=false;}
  if(success) {
   image=new Image;
   image->setName(tempName);
   image->setFilename(tgaName);
   image->bfmeSetTexture(BfmeMapPictureTexture(mapPreviewDir.str()));
   image->setStatus(2);
   image->setUV(&uv);
   image->setTextureHeight(128);image->setTextureWidth(128);
   TheMappedImageCollection->addImage(image);
  } else image=0;
 }
 return image;
}
