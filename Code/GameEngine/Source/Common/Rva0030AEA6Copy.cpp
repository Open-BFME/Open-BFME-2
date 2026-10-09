// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ?Rva0030AEA6Copy@@YAXXZ @0x0030AEA6 16B evidence calls rowed Rva0030ADED operator= 0x0030ADED to copy global tail 0x00DFF4B8 to 0x00DFF4F8 chain from operator= landing
#include "ascii_string.h"

class Rva0030ADED
{
public:
    Rva0030ADED &operator=(const Rva0030ADED &other);
};

extern Rva0030ADED TheFireSettings;		// 0x00DFF4F8 (Rva007B6880Thunks.cpp)
extern Rva0030ADED TheFireSettingsSaved;	// 0x00DFF4B8

void Rva0030AEA6Copy()
{
    TheFireSettings = TheFireSettingsSaved;
}
