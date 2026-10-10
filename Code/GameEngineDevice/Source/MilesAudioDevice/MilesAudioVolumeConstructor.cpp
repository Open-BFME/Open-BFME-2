// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native5A2E6..5A3FA is the complete276-byte constructor of the existing
// neutral1C4-byte owner Rva006ABC60 (array callback in Miles ctor5CF5F).
// Dtor5925E independently establishes six12-byte vectors at4C, AsciiString
// treeA0 and trailing tree1B8. Native initialization and existing volume
// methods independently establish scalar volumes4/product34, factors94/98/9C,
// six*two*four floatsC8 and matching byte flags188. Original field names
// remain uncertain; the target constructor supplies constants and loop sizes.
// ZH MilesAudioManager provides the audio purpose; these BFME2 per-view
// volume records are target-specific. BFME1 Rva006ABC60 destructor provenance
// remains in its existing provider. The trailing map is an empty-header view:
// it asserts no original mapped-value identity or complete tree-node layout.
// refreshAll28B calls the existing scalar refreshPair296B loop. The closed
// implementation has scalar/CRT memcpy/memset operations and no C++ throwing
// path. Its nonthrowing declaration preserves retail's last unwind state1
// and single four-byte local; SEH behavior is unaffected under EHsc.
// stlport
#include <vector>
#include <set>
#include <map>
#include "ascii_string.h"
struct BfmePod8 {int m_at00,m_viewType;};
struct OpaqueVolumeWord {unsigned char data[4];};
class MilesAudioManager {public: class GlobalVolumeData{public:void refreshAll() throw();};};
class Rva006ABC60 {
 int word00;
 float volumes[6][2];
 float product[6];
 _STL::vector<BfmePod8> requests[6];
 float float94,float98,float9C;
 _STL::set<AsciiString> names;
 float floatAC,floatB0,floatB4,floatB8,floatBC,floatC0;
 bool flagC4;
 float tableC8[6][2][4];
 bool flags188[6][2][4];
 _STL::map<AsciiString,OpaqueVolumeWord> table1B8;
public:Rva006ABC60();~Rva006ABC60();
};
typedef char VolumeExtent[sizeof(Rva006ABC60)==0x1C4 ? 1 : -1];
Rva006ABC60::Rva006ABC60():word00(3),float94(1.0f),float98(1.0f),float9C(1.0f),floatAC(1.0f),floatB0(1.0f),floatB4(0.0f),floatB8(0.0f),floatBC(0.0f),floatC0(0.0f),flagC4(false) {
 for(int i=0;i<6;i++){
  product[i]=1.0f;
  for(int j=0;j<2;j++){
   volumes[i][j]=1.0f;
   for(int k=0;k<4;k++){
    tableC8[i][j][k]=1.0f;
    flags188[i][j][k]=false;
   }
  }
 }
 ((MilesAudioManager::GlobalVolumeData*)this)->refreshAll();
}
