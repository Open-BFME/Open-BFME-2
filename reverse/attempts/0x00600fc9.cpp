// ?getFileListInDirectory@FileSystem@@QBEXABVAsciiString@@0AAV?$set@VAsciiString@@UBfmeStringNoCaseLess@@V?$allocator@VAsciiString@@@_STL@@@_STL@@_N@Z
// partial score=0.42159763313609466 date=2026-10-09
// cl: /O1 /G6 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
// ZH FileSystem.cpp getFileListInDirectory supplies local/archive semantics.
// BFME2 caller54E426 proves signature. Native600FC9..60126D adds preferred
// local root and language enumeration, then FilePathGate filtering.
// Global root extent260 is bounded by E06948..E06A4C; its initial bytes are
// zero. Names for the added globals are descriptive, not original identities.
#include <set>
#include <stdio.h>
#include "ascii_string.h"
struct BfmeStringNoCaseLess {bool operator()(const AsciiString&,const AsciiString&)const;};
typedef _STL::set<AsciiString,BfmeStringNoCaseLess> FilenameList;
class LocalFileSystem {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();
 virtual void listRaw(const char*,const char*,const char*,const char*,FilenameList&,bool);
 virtual void slot7();
 virtual void list(const AsciiString&,const AsciiString&,const AsciiString&,FilenameList&,bool);
};
class ArchiveFileSystem {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();
 virtual void list(const AsciiString&,const AsciiString&,const AsciiString&,FilenameList&,bool);
};
extern LocalFileSystem *TheLocalFileSystem;
extern ArchiveFileSystem *TheArchiveFileSystem;
extern bool BFME2PreferLocalFiles;
extern char g_00DD509C[];
char BFME2PreferredLocalRoot[260]={0};
class FilePathGate {public:bool allow(const char*);};
FilePathGate *BFME2FileListGate=0;
typedef _STL::_Rb_tree<AsciiString,AsciiString,_STL::_Identity<AsciiString>,_STL::less<AsciiString>,_STL::allocator<AsciiString> > StringEraseTree;
namespace _STL {template<> void StringEraseTree::erase(StringEraseTree::iterator);}
class FileSystem {public:void getFileListInDirectory(const AsciiString&,const AsciiString&,FilenameList&,bool)const;};
void FileSystem::getFileListInDirectory(const AsciiString &directory,const AsciiString &searchName,FilenameList &files,bool recursive) const {
 char path[260];
 if(BFME2PreferLocalFiles) {
  if(BFME2PreferredLocalRoot[0]) {
   sprintf(path,"%s\\%s",BFME2PreferredLocalRoot,reinterpret_cast<const StringBase<char>*>(&directory)->str());
   const char *search=reinterpret_cast<const StringBase<char>*>(&searchName)->str();
   const char *dir=reinterpret_cast<const StringBase<char>*>(&directory)->str();
   TheLocalFileSystem->listRaw(dir,"",path,search,files,recursive);
  }
  if(g_00DD509C[0]) {
   sprintf(path,"lang\\%s\\%s",g_00DD509C,reinterpret_cast<const StringBase<char>*>(&directory)->str());
   const char *search=reinterpret_cast<const StringBase<char>*>(&searchName)->str();
   const char *dir=reinterpret_cast<const StringBase<char>*>(&directory)->str();
   TheLocalFileSystem->listRaw(dir,"",path,search,files,recursive);
  }
 }
 TheLocalFileSystem->list(AsciiString(""),AsciiString(reinterpret_cast<const StringBase<char>*>(&directory)->str()),AsciiString(reinterpret_cast<const StringBase<char>*>(&searchName)->str()),files,recursive);
 TheArchiveFileSystem->list(AsciiString(""),AsciiString(reinterpret_cast<const StringBase<char>*>(&directory)->str()),AsciiString(reinterpret_cast<const StringBase<char>*>(&searchName)->str()),files,recursive);
 if(BFME2FileListGate) {
  StringEraseTree *tree=reinterpret_cast<StringEraseTree*>(&files);
  StringEraseTree::iterator it=tree->begin();
  while(it!=tree->end()) {
   if(!BFME2FileListGate->allow(reinterpret_cast<const StringBase<char>*>(&*it)->str()))tree->erase(it++);
   else ++it;
  }
 }
}
