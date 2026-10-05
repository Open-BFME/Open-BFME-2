// cl: /O1 /EHsc /MD
extern "C" void* __cdecl memset(void*,int,unsigned);
struct Rva00151248String { 
 // ?Rva00151248String::Rva00151248String present-unmatched
 Rva00151248String():data(0){} ~Rva00151248String(); void*data; void clear(); void assign(const char*); };
class Rva00151248 {
 Rva00151248String first;
 unsigned flag;
 Rva00151248String second;
 unsigned data[4];
 unsigned other;
 bool enabled;
 public: Rva00151248(); Rva00151248(const char*,unsigned); void reset();
};
void Rva00151248::reset() {
 first.clear(); flag=0; second.clear();
 memset(data,0,sizeof(data));
 memset(&other,0,sizeof(other));
 memset(&enabled,0,sizeof(enabled));
}

Rva00151248::Rva00151248() {reset();}
Rva00151248::Rva00151248(const char*s,unsigned kind) {reset();first.assign(s);flag=kind;}

// Native layout: string-sized handles at +0/+8; dword +4; cleared blocks
// +C length16, +1C length4, +20 length1. Calls to the matched narrow
// StringBase releaseBuffer/set establish string behavior, without claiming
// the original owning class name. EH initialization order comes from both
// native constructor extents (51B and69B); reset is64B ending in ret.
#pragma comment(linker, "/alternatename:?clear@Rva00151248String@@QAEXXZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")
#pragma comment(linker, "/alternatename:??1Rva00151248String@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")
#pragma comment(linker, "/alternatename:?assign@Rva00151248String@@QAEXPBD@Z=?set@?$StringBase@D@@QAEXPBD@Z")
