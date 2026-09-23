// cl: /O1 /MD /DNDEBUG
//
// ??0HordeTransportContainModuleData@@QAE@XZ, retail 0x00477D61 (18 bytes).
// Frameless derived ctor over the pinned TransportContainModuleData base
// (0x00468301): the base call builds the 4-byte base, then the derived
// installs vtable 0x00C45FB0 explicitly (Defector law: a source-written
// store lands in position right after the base call; the classes carry no
// virtuals so the compiler emits no store of its own). No EH (no calls past
// the base, no destructible members). Identity is the ModuleFactory
// registration under "HordeTransportContain" (sole-caller data factory per
// the superseded ctor pin).

class TransportContainModuleData
{
public:
	TransportContainModuleData();
};

class HordeTransportContainModuleData : public TransportContainModuleData
{
public:
	HordeTransportContainModuleData();
};

HordeTransportContainModuleData::HordeTransportContainModuleData()
	: TransportContainModuleData()
{
	*(unsigned int *)this = 0x00C45FB0;
}
