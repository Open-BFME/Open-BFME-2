// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// NativeAB83B..AB8F1 enumerates baseDirectory+_geometry/ with *.ru and
// no recursive search. Its this+0 AsciiString is established by copy365F0.
// WB8A92A0 maps the full caller by both literals and its callee8A9470,
// independently named AptAnimData::createRenderData in W3DAptAux.cpp.
// The caller method name is unresolved and remains address-derived.
// No other AptAnimData members or original layout are asserted.
#include <set>
#include "ascii_string.h"
struct BfmeStringNoCaseLess {bool operator()(const AsciiString&,const AsciiString&)const;};
typedef _STL::set<AsciiString,BfmeStringNoCaseLess,_STL::allocator<AsciiString> > FilenameList;
class FileSystem {public:void getFileListInDirectory(const AsciiString&,const AsciiString&,FilenameList&,bool)const;};
extern FileSystem*TheFileSystem;
class AptAnimData {public:void rva000AB83B();AsciiString baseDirectory;private:void createRenderData(const AsciiString&);};
void AptAnimData::rva000AB83B(){
 FilenameList files;
 AsciiString directory(baseDirectory);
 directory+="_geometry/";
 TheFileSystem->getFileListInDirectory(directory,AsciiString("*.ru"),files,false);
 for(FilenameList::iterator it=files.begin();it._M_node!=files.end()._M_node;++it)
  createRenderData(*it);
}
