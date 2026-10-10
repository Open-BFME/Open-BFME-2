// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// Native5C4D4B..5C4DE0 RET4,149B and WB1566560 show the same template
// pointer0, default string4, serial8 and consumed byteC. Existing subobject
// constructors5C4280/56BA07 use this helper as creation parameters; its original
// class name remains unknown, so retain the established Helper005C4D4B name.
// Template name at18 is appended with the decimal serial from DFEF18.
// Genuine non-POD concat-node layout comes from matched RegistryAsciiPath and
// ThingTemplateGetAssetList; the empty pair constructor prevents an extra POD
// copy. Materializing the template-name reference before _itoa reproduces
// native evaluation order. Existing sole global owner and callees are reused.
template<class T> struct StringInlineData {int m_refCount,m_length;T m_text[1];};
#include "ascii_string.h"
struct AsciiStringRef { const AsciiString *m_string; };
class Rva000B3F84Pair { public: Rva000B3F84Pair() {} const char *m_ptr; int m_len; };
struct AsciiStringPlusText : AsciiStringRef { operator AsciiString(); Rva000B3F84Pair m_right; };
AsciiStringPlusText operator+(const AsciiString&,const char*);
extern "C" __declspec(dllimport) char *__cdecl _itoa(int,char*,int);
class Rva002D3627Host {public: int rva002BED69();};
extern Rva002D3627Host *g_00DFEF18;
struct IconTemplateName {char pad[0x18]; AsciiString name;};
struct Helper005C4D4B {
 void *m_00; AsciiString m_str; int m_08; unsigned char m_0c; char pad[3];
 Helper005C4D4B(void*);
};
Helper005C4D4B::Helper005C4D4B(void *arg) : m_00(arg) {
 m_0c=0;
 m_08=g_00DFEF18->rva002BED69();
 const AsciiString &name=((IconTemplateName*)m_00)->name;
 char buffer[128];
 m_str=name + _itoa(m_08,buffer,10);
}
