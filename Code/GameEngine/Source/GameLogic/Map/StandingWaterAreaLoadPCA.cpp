// ?LoadPCAFile@StandingWaterArea@@QAEXXZ
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// Native 3093F6..309CF8; WorldBuilder BDE250 names StandingWaterArea::LoadPCAFile.
// Reconstructed from both binaries; no reusable reference implementation found.
// Record offsets and channel order come from retail; original record type is unknown.
// The float-returning normalization boundary reproduces native x87 store ordering.
// Neutral record type: native proves 16 bytes and four float components, not original type name.
#include <stdlib.h>
#include <new>
#define _STLP_BFME_COPY_TRIVIAL_EXTERN
#include <string>
#include <vector>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> vector<basic_string<char, char_traits<char>, allocator<char> >, allocator<basic_string<char, char_traits<char>, allocator<char> > > >::~vector(); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Suppress this TU's non-retail copy of ??1?$_Vector_base@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@V?$alloc:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Vector_base<basic_string<char,char_traits<char>,allocator<char> >,allocator<basic_string<char,char_traits<char>,allocator<char> > > >::~_Vector_base(); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@D@_STL@@QBEPADIPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * allocator<char>::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * _STL::_STLP_alloc_proxy<char *,char,_STL::allocator<char> >::allocate(unsigned int); }
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
void __cdecl Rva00030830GameFree(void *);
// Bind deallocation to the verified game allocator; retain imported atof/atoi.
namespace _STL
{
    template<> __declspec(dllimport) __forceinline void __malloc_alloc<0>::deallocate(void *p,size_t)
    {
        Rva00030830GameFree(p);
    }
}
// Reuse existing string/vector providers instead of emitting unnecessary copies.
extern template class _STL::vector<std::string, _STL::allocator<std::string> >;
extern template _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::basic_string();
extern template _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >& _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::operator=(const char *);
struct StandingWaterPCARecord
{
    StandingWaterPCARecord();
    float values[4];
    float &operator[](unsigned i)
    {
        return values[i];
    }
};
static __forceinline float pcaNormalize(const char *text)
{
    return static_cast<float>(atof(text)/255.0);
}
class Rva00308DF0Ref;
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/Rva00308DF0.h"
struct Rva00199FCCRec
{
    AsciiString key;
    char pad[32];
};
class Rva00199FCC
{
    public:
    void *rva00199FCC(const AsciiString &name);
    private:
    Rva00199FCCRec *begin,*end;
};
inline void *Rva00199FCC::rva00199FCC(const AsciiString &name)
{
    Rva00199FCCRec *p=begin;
    for(;p!=end;++p)
    {
        if(p->key.compareNoCase(name)==0)break;
    }
    return p!=end?p:0;
}
struct StandingWaterPCAProperty
{
    AsciiString key;
    unsigned pad;
    AsciiString value;
};
#include "../../../Include/Common/File.h"
#include "../../../Include/Common/FileSystem.h"
extern FileSystem *TheFileSystem;
void Rva00309358Tokenize(const std::string&,std::vector<std::string>&,const std::string&);
class StandingWaterArea
{
    unsigned char prefix[0xa0];
    unsigned count;
    float scale;
    StandingWaterPCARecord *mean;
    StandingWaterPCARecord *channelsX[3],*channelsY[3],*channelsZ[3];
    bool needsLoad;
    public:
    void rva003080CE();
    void LoadPCAFile();
};
void StandingWaterArea::LoadPCAFile()
{
    if(!needsLoad)return;
    needsLoad=false;
    rva003080CE();
    Rva00308DF0Ref *material=reinterpret_cast<Rva00308DF0*>(this)->rva00308DF0();
    if(!material)return;
    Rva00199FCC *properties=reinterpret_cast<Rva00199FCC*>(reinterpret_cast<char*>(material)+12);
    StandingWaterPCAProperty *entry=static_cast<StandingWaterPCAProperty*>(properties->rva00199FCC(AsciiString("WaterPCATexture1")));
    if(!entry)return;
    AsciiString filename(entry->value);
    for(int k=0;k<3;++k)filename.removeLastChar();
    filename.concat("basis");
    AsciiString path("Art\\Textures\\");
    path.concat(filename);
    File *file=TheFileSystem->openFile(path.str(),0x21,0);
    if(!file)return;
    std::string header,scaleText,meanText,basisText[12];
    std::vector<std::string> headerTokens;
    char headerBuffer[128];
    file->nextLine(headerBuffer,128);
    header=headerBuffer;
    {
        std::string delimiters(" ");
        Rva00309358Tokenize(header,headerTokens,delimiters);
    }
    count=atoi(headerTokens[1].c_str());
    int bufSize=count*60;
    char *buffer=new char[bufSize];
    file->nextLine(buffer,bufSize);
    scaleText=buffer;
    file->nextLine(buffer,bufSize);
    meanText=buffer;
    for(int j=0;j<3;++j)
    {
        file->nextLine(buffer,bufSize);
        basisText[j*4]=buffer;
        file->nextLine(buffer,bufSize);
        basisText[j*4+1]=buffer;
        file->nextLine(buffer,bufSize);
        basisText[j*4+2]=buffer;
        file->nextLine(buffer,bufSize);
        basisText[j*4+3]=buffer;
    }
    delete[]buffer;
    file->close();
    std::vector<std::string> scaleTokens,meanTokens,basisTokens[12];
    {
        std::string delimiters(" ");
        Rva00309358Tokenize(scaleText,scaleTokens,delimiters);
    }
    {
        std::string delimiters(" ");
        Rva00309358Tokenize(meanText,meanTokens,delimiters);
    }
    for(int j=0;j<3;++j)
    {
        {
            std::string delimiters(" ");
            Rva00309358Tokenize(basisText[j*4],basisTokens[j*4],delimiters);
        }
        {
            std::string delimiters(" ");
            Rva00309358Tokenize(basisText[j*4+1],basisTokens[j*4+1],delimiters);
        }
        {
            std::string delimiters(" ");
            Rva00309358Tokenize(basisText[j*4+2],basisTokens[j*4+2],delimiters);
        }
        {
            std::string delimiters(" ");
            Rva00309358Tokenize(basisText[j*4+3],basisTokens[j*4+3],delimiters);
        }
    }
    scale=(float)atof(scaleTokens[1].c_str());
    mean=new StandingWaterPCARecord[count];
    for(int j=0;j<3;++j)
    {
        channelsX[j]=new StandingWaterPCARecord[count];
        channelsY[j]=new StandingWaterPCARecord[count];
        channelsZ[j]=new StandingWaterPCARecord[count];
    }
    for(unsigned i=1;i<=count;++i)
    {
        int recordIndex=i-1;
        mean[recordIndex][0]=pcaNormalize(meanTokens[i].c_str());
        for(int j=0;j<3;++j)
        {
            channelsX[j][recordIndex][0]=pcaNormalize(basisTokens[j*4][i].c_str());
            channelsX[j][recordIndex][1]=pcaNormalize(basisTokens[j*4+1][i].c_str());
            channelsX[j][recordIndex][2]=pcaNormalize(basisTokens[j*4+2][i].c_str());
            channelsX[j][recordIndex][3]=pcaNormalize(basisTokens[j*4+3][i].c_str());
        }
        unsigned channelBase=count;
        mean[recordIndex][2]=pcaNormalize(meanTokens[channelBase+i].c_str());
        for(int j=0;j<3;++j)
        {
            channelsZ[j][recordIndex][0]=pcaNormalize(basisTokens[j*4][channelBase+i].c_str());
            channelsZ[j][recordIndex][1]=pcaNormalize(basisTokens[j*4+1][channelBase+i].c_str());
            channelsZ[j][recordIndex][2]=pcaNormalize(basisTokens[j*4+2][channelBase+i].c_str());
            channelsZ[j][recordIndex][3]=pcaNormalize(basisTokens[j*4+3][channelBase+i].c_str());
        }
        channelBase+=count;
        mean[recordIndex][1]=pcaNormalize(meanTokens[channelBase+i].c_str());
        for(int j=0;j<3;++j)
        {
            channelsY[j][recordIndex][0]=pcaNormalize(basisTokens[j*4][channelBase+i].c_str());
            channelsY[j][recordIndex][1]=pcaNormalize(basisTokens[j*4+1][channelBase+i].c_str());
            channelsY[j][recordIndex][2]=pcaNormalize(basisTokens[j*4+2][channelBase+i].c_str());
            channelsY[j][recordIndex][3]=pcaNormalize(basisTokens[j*4+3][channelBase+i].c_str());
        }
    }
}
StandingWaterPCARecord::StandingWaterPCARecord()
{
}
