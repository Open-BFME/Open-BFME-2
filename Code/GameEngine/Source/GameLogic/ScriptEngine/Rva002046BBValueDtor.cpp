// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ??1Rva002046BBValue@@QAE@XZ @0x002046BB 5B. Dtor tail-jmp to rowed pair dtor 0x0002C0C0.
// Evidence: 5B jmp to ??1?$pair@$$CBVAsciiString@@V1@@_STL@@QAE@XZ; LINK BONUS 591B; callers include pair erase/destroy.
#include "ascii_string.h"
namespace _STL
{
template <typename T1, typename T2>
struct pair
{
	~pair();
	T1 first;
	T2 second;
};
}
class Rva002046BBValue : public _STL::pair<const AsciiString, AsciiString>
{
public:
	~Rva002046BBValue();
};
Rva002046BBValue::~Rva002046BBValue()
{
}
