// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
// ?Rva0030AEA6Copy@@YAXXZ @0x0030AEA6 16B evidence calls rowed Rva0030ADED operator= 0x0030ADED to copy global tail 0x00DFF4B8 to 0x00DFF4F8 chain from operator= landing
#include "ascii_string.h"

class Rva0030ADED
{
public:
    Rva0030ADED &operator=(const Rva0030ADED &other);
};

extern AsciiString g_00DFF4F8;
extern unsigned int g_Va00DFF4B8;	// object at 0x00DFF4B8 (Rva007B6880Thunks.cpp)

void Rva0030AEA6Copy()
{
    ((Rva0030ADED &)g_00DFF4F8) = (Rva0030ADED &)g_Va00DFF4B8;
}
