// cl: /O1 /MD /EHsc
// ??1Rva005E9FC1@@UAE@XZ retail 0x005EA224 48 bytes.
// Dtor destroys member at +8 via pinned 0x0057417E then restores base vtable 0x008780F4.
// Evidence: slot-0 deleting dtor at 0x005EA208 calls this body; lea ecx [esi+8] call 0x0057417E pinned ??1Rva0057417E@@QAE@XZ; mov [esi] 0x008780F4; layout from rowed ctor 0x005E9FC1 in Rva005E9FC1Ctor.cpp.
extern "C" const void *const __identifier("??_7Rva005E9F92@@6B@")[];

#include "../../Include/Common/Rva0057417E.h"

struct Rva005E9FC1Base
{
	virtual ~Rva005E9FC1Base();
	void *m_04;
};

// ??1Rva005E9FC1Base@@UAE@XZ present-unmatched
inline Rva005E9FC1Base::~Rva005E9FC1Base()
{
	*(const void **)this = __identifier("??_7Rva005E9F92@@6B@");
}

class __declspec(novtable) Rva005E9FC1 : public Rva005E9FC1Base
{
public:
	virtual ~Rva005E9FC1();
private:
	Rva0057417E m_08;
};

Rva005E9FC1::~Rva005E9FC1()
{
}
