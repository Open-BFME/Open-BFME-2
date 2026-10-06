// cl: /DNDEBUG /MD
//
// ??1CitadelSlaughterHordeContain@@UAE@XZ retail 0x00480718 5 bytes.
// CitadelSlaughterHordeContain virtual dtor is a 5-byte jmp thunk to the rowed
// SlaughterHordeContain base dtor at 0x004803FB. Retail stores no vptr (novtable).
// Identity via deleting wrapper 0x004806FC slot 0 vtable 0x00C48CC0
// and pool key 0x00480600 with CitadelSlaughterHordeContain string.
// Shape follows HordeGarrisonContainDtor 5B precedent (novtable jmp thunk).

class SlaughterHordeContain
{
public:
	virtual ~SlaughterHordeContain();
};

class __declspec(novtable) CitadelSlaughterHordeContain : public SlaughterHordeContain
{
public:
	virtual ~CitadelSlaughterHordeContain();
};

CitadelSlaughterHordeContain::~CitadelSlaughterHordeContain()
{
}
