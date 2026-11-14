// Transferred unchanged from Open-BFME-1 5cae4bdff game/GameEngine/Source/GameNetwork/Rva007F51B0GameKeyRecord.cpp;
// bfme1_sweep ambiguous: byte-identical bodies placed by the BFME1->BFME2 address map at 0x00661B90.
// Addresses in the donor text are BFME1.
class Rva007E8810Message;

#include "../../Include/Common/Rva007FBC30GameKey.h"

class Rva007F51B0GameKeyRecord : public Rva007FBC30GameKey
{
public:
    explicit Rva007F51B0GameKeyRecord(Rva007E8810Message *message);
};

Rva007F51B0GameKeyRecord::Rva007F51B0GameKeyRecord(Rva007E8810Message *message)
    : Rva007FBC30GameKey(message)
{
}
