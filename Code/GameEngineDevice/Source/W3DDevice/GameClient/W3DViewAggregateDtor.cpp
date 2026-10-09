// cl: /DNDEBUG /MD /EHsc /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /ICode/GameEngine/Include/GameClient /Ireference/shims/bfme2_ascii
// stlport
// Reference-guided W3DView teardown: BFME1 revision874e38488c7dcf8cf3343452e8e5371bb3a0e64c
// and GeneralsMD release the two cameras. Native8BD5E..8BE6B proves
// camera fields104/108 and refcount+4 plus Delete_This slot0. It also proves
// nine lifetime states: primary Snapshot-like base; SubsystemInterface atB4;
// camera-path280; record22F4/2368; request buffer23DC; strings243C/2440;
// narrow STL string2458. Member layouts are target-proven teardown prefixes;
// the existing address-derived owner/member names preserve identity uncertainty.
// Release_Ref as an inline member preserves cached ECX; ::delete owns235C.
// The raw request storage mirrors the donor vector's three-word ownership
// representation and uses the rowed BFME2 game-allocator provider.
#include "ascii_string.h"
#include <string>
template<> _STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >::~basic_string();
void Rva00030830GameFree(void*);
struct BfmeViewRequestStorage {void *start,*finish,*end;~BfmeViewRequestStorage(){if(start)Rva00030830GameFree(start);}};
class Rva0025EF18 {public:virtual ~Rva0025EF18();char pad[0xb0];};
class SubsystemInterface {public:virtual ~SubsystemInterface();char pad[8];};
#include "Rva0008990CArrayOwner.h"
class Rva008B77D {public:virtual ~Rva008B77D();char pad[0x70];};
class CameraRef {public:virtual void Delete_This();int refs;void Release_Ref(){refs--;if(refs==0)Delete_This();}};
class ViewOwned235C {public:virtual ~ViewOwned235C();};
class Rva008BD5E : public Rva0025EF18, public SubsystemInterface {
public:virtual ~Rva008BD5E();
private:
 char gapc0[0x104-0xc0];CameraRef *camera3d,*camera2d;
 char gap10c[0x280-0x10c];Rva0089971 path;
 Rva008B77D animationA;
 Rva008B77D animationB;
 BfmeViewRequestStorage requests;
 char gap23e8[0x243c-0x23e8];AsciiString name,bone;
 char gap2444[0x2458-0x2444];std::string text;
};
Rva008BD5E::~Rva008BD5E(){
 if(camera2d){camera2d->Release_Ref();camera2d=0;}
 if(camera3d){camera3d->Release_Ref();camera3d=0;}
 ::delete *reinterpret_cast<ViewOwned235C**>(reinterpret_cast<char*>(this)+0x235c);
}
