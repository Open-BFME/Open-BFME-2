// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native5CC788..5CC7DC: 84B virtual-base destructor. The existing
// ctor5CE93E and its base-constructor binding5CC698 prove the owner;
// native5CC698 starts with the rowed57B Rva005CC5E5 constructor and
// carries its primary0/vbptr4 layout, owned holder8 and counted vbaseC.
// Like matched5E73FB, destruction clears holder8 through owned29B AD6F4
// and restores parent tables C74E6C/C74E68. Same real inheritance chain
// produces the native negative-this destructor entry without assembly.
// Original class/function spellings remain unproven. The older opaque
// 8B negative-adjust call view in RvaNegativeAdjustFwds is reverified.
#include "../../Include/Common/Rva0007DF07.h"
class Rva005CC5E5 : public virtual Rva0007DF07 {public: Rva005CC5E5() throw(); virtual void slot0(); virtual ~Rva005CC5E5(){};};
#include "../../Include/Common/Rva000AD6F4.h"
struct Rva005CE93EContext;
class Rva005CC698 : public Rva005CC5E5 {public:Rva005CC698(void*,void*,Rva005CE93EContext*);virtual ~Rva005CC698();private:Rva000AD6F4 payload;};
Rva005CC698::~Rva005CC698() {}
