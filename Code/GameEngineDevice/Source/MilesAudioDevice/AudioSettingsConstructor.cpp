// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Target41589..416CB full322B constructor. Existing deleting destructor416CB
// and its primary vtableBC2420 establish neutral owner Rva000416E7. Base
//238AC7 independently establishes54B strings/volume prefix. Three48B
// microphone records12C and26 scalar volumesC4 are target layout evidence.
// ZH AudioSettings supplies semantic audio-settings purpose and the shared
// defaults; BFME2 extends it, so unresolved fields retain offset labels.
#include "ascii_string.h"
class Rva00238B90 {
public:Rva00238B90();virtual ~Rva00238B90();
private:AsciiString strings04[6];float volumes1C[5],volumes30[5];int words44[3];AsciiString string50;
};
class Rva0004149D {float values[18];public:Rva0004149D();};
class Rva000416E7:public Rva00238B90 {
 bool flag54,flag55;
 int word58,word5C,word60,word64,word68,word6C,word70,word74,word78,word7C;
 unsigned word80,word84,word88,word8C,word90,word94,word98,word9C,wordA0,wordA4;
 int wordA8,wordAC;
 float floatB0;
 int wordB4;
 float floatB8;
 bool flagBC;
 float floatC0;
 float factorsC4[26];
 Rva0004149D microphones12C[3];
public:Rva000416E7();virtual ~Rva000416E7();
};
typedef char SettingsSize[sizeof(Rva000416E7)==0x204 ? 1:-1];
Rva000416E7::Rva000416E7():flag54(true),flag55(false),word58(44100),word5C(16),word60(2),word64(4),word68(16),word6C(4),word70(100),word74(5000),word78(1000),word7C(5),word80(0x400000),word84(64),word88(224),word8C(64),word90(6),word94(8000),word98(320),word9C(8),wordA0(0x2FFFBF40),wordA4(0x7FFF8040),wordA8(0),wordAC(0),floatB0(10.0f),wordB4(1000),floatB8(0.01f),flagBC(false),floatC0(0.1f) {
 for(unsigned i=0;i<26;i++)factorsC4[i]=1.0f;
}
