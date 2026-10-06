// cl: /DNDEBUG /MD
//
// ??1HordeTransportContain@@UAE@XZ retail 0x004771E6 5 bytes.
// HordeTransportContain virtual dtor is a 5-byte jmp thunk to the rowed
// TransportContain base dtor at 0x00467E61. Retail stores no vptr (novtable).
// Identity via deleting wrapper 0x004771CA slot 0 vtable 0x00C45EB8
// and pool key 0x00477185 with HordeTransportContain string.
// Donor BFME1 HordeTransportContainDestructorThunk (naked).
// Shape follows HordeGarrisonContainDtor 5B precedent (novtable jmp thunk).

class TransportContain
{
public:
	virtual ~TransportContain();
};

class __declspec(novtable) HordeTransportContain : public TransportContain
{
public:
	virtual ~HordeTransportContain();
};

HordeTransportContain::~HordeTransportContain()
{
}
