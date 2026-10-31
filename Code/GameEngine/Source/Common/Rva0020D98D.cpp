// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0020D98D@@QAE@ABV0@@Z 0x0020D98D 67B copy ctor via base Overridable and member Rva003ED658
// Evidence: retail calls base copy 0x003664DD then stores vtable then calls member copy 0x003ED658 with +0x10; caller 0x0020DE68; layout base size 0x10 from donor
#include "../../Include/Common/Overridable.h"

class Rva003ED658
{
public:
	Rva003ED658(const Rva003ED658 &that);
private:
	char m_pad[12];
};

class Rva0020D98D : public Overridable
{
public:
	Rva0020D98D(const Rva0020D98D &that);
private:
	Rva003ED658 m_10;
};

Rva0020D98D::Rva0020D98D(const Rva0020D98D &that) : Overridable(that), m_10(that.m_10)
{
}
