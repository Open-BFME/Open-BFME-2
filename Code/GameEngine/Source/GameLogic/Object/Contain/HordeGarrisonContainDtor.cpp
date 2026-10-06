// cl: /DNDEBUG /MD
//
// ??1HordeGarrisonContain@@UAE@XZ retail 0x0047A147 5 bytes.
// HordeGarrisonContain virtual dtor is a 5-byte jmp thunk to the rowed
// GarrisonContain base dtor at 0x00478067. Retail stores no vptr (novtable);
// Region3D at +0x9E0 from ctor 0x0047A040 has trivial 3-byte ctor so no teardown.
// Identity via deleting wrapper 0x0047A12B slot 0 vtable 0x00C46570
// and pool key 0x0047A0E6 with HordeGarrisonContain string.
// Donor BFME1 HordeGarrisonContainDestructorThunk plus ZH GarrisonContain.
// Shape follows ProductionQueueHordeContainDtor 67B precedent (direct
// GarrisonContain base; Horde intermediate is the thunk).

class GarrisonContain
{
public:
	virtual ~GarrisonContain();
};

class __declspec(novtable) HordeGarrisonContain : public GarrisonContain
{
public:
	virtual ~HordeGarrisonContain();
};

HordeGarrisonContain::~HordeGarrisonContain()
{
}
