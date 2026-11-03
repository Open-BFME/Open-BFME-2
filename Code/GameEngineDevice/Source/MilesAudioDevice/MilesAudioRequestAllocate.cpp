// The complete native parents and associative EH code/data graphs prove
// the naturally emitted handlers recorded with this unit. Each has one
// primary owner and its full 10-byte extent.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// Native 0x51107..0x51139; allocator called by MilesAudioManager request sites.
// Target allocates 24B and calls the already rowed address-derived ctor A8684.
// Record purpose follows manager callers; the neutral ctor name is preserved.
struct Rva00051107AudioRequest;
class Rva000A8684 {public:Rva000A8684();private:char storage[0x18];};
#include "../../Include/MilesAudioDevice/MilesAudioManager.h"
Rva00051107AudioRequest *MilesAudioManager::rva00051107(){return reinterpret_cast<Rva00051107AudioRequest *>(new Rva000A8684);}
