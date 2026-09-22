// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0KeepObjectDieModuleData@@QAE@XZ at retail 0x00253B78 (29B).
// KeepObjectDie ModuleData default ctor over the unidentified SEH
// intermediate base 0x00253510 (pinned opaque as Rva00253510): base call,
// vtable 0x00C4ED70 (slot0 is ??_GObjectModule, slot1 the ret-stub -- the
// ObjectModule vtable family), CollapsingTime +0x38 = 0x19, StayOnRadar byte
// +0x3C = 0, matching the class parse table at 0x00BF0994 (rowed proc
// 0x253B95). Factory 0x00253BB7 builds size 0x40, matching
// sizeof(KeepObjectDieModuleData) = 0x38 + 4 + 1 (+pad). Identity vote: the
// ModuleFactory registrar at 0x00258D9B maps the KeepObjectDie INI name to
// factory 0x253BB7 which sole-calls this ctor and pushes the class proc.
// The sibling body 0x00253A78 shares base, vtable and size but stores
// (and-zero, byte 1) -- a different class under the folded vtable, or a
// different overload; not claimed here. The Zero Hour lead
// (DockUpdateModuleData, 0/TRUE) is REFUTED by the retail consts (0x19/0).
class Thing;
class ModuleData;

// Opaque 0x38-byte intermediate; default ctor resolves to the opaque pin at
// 0x00253510. Do NOT declare an explicit vptr member: the hidden one is +0.
class Rva00253510
{
public:
	Rva00253510();
	virtual ~Rva00253510();

protected:
	unsigned char m_pad[0x38 - 4];
};

// ??1Rva00253510@@UAE@XZ present-unmatched
Rva00253510::~Rva00253510()
{
}

class KeepObjectDieModuleData : public Rva00253510
{
public:
	KeepObjectDieModuleData();
	virtual ~KeepObjectDieModuleData();

protected:
	int m_collapsingTime;
	unsigned char m_stayOnRadar;
};

KeepObjectDieModuleData::KeepObjectDieModuleData()
	: Rva00253510()
{
	m_collapsingTime = 0x19;
	m_stayOnRadar = 0;
}

// ??1KeepObjectDieModuleData@@UAE@XZ present-unmatched
KeepObjectDieModuleData::~KeepObjectDieModuleData()
{
}
