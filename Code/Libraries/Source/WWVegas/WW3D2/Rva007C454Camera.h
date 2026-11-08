#pragma once
// Hand-written, not generated: the lane's generator refuses this class (30 attributes undecided, mostly inherited field names). Its
// contract does decide bases [CameraClass] from retail's ctor and size 0x408, which is all this header states.
// Target-owned ABI view of the CameraClass subclass whose ctor is 0x0007C3CD; its original name is not recovered.
// Target facts: retail's ctor 0x0007C3CD and copy ctor 0x0007C404 call CameraClass's and store vftables 0x00BC6C58 and
// 0x00BC6C54 through `this`; the vector at +0x3FC is built there and released by the dtor 0x0007C454; slots 129 and 130
// of 0x00BC6C58 hold 0x0007BEA7 and 0x0007BEDA, overriding CameraClass's const Cull_Sphere and Cull_Box. Complete size 0x408.
// A unit that includes this defines BFME_RO_DTOR_DECL_ONLY first, as for CameraClass.h.
#include "CameraClass.h"
#include <vector>
#include "../../../Include/Lib/BfmeE16.h"

class Rva007C454 : public CameraClass
{
public:
	Rva007C454();
	Rva007C454(const Rva007C454 &that);
	virtual ~Rva007C454();
	virtual RenderObjClass *Clone(void) const;
	virtual bool Cull_Sphere(const SphereClass &sphere) const;
	virtual bool Cull_Box(const AABoxClass &box) const;

private:
	_STL::vector<BfmeE16> m_3FC;
};
