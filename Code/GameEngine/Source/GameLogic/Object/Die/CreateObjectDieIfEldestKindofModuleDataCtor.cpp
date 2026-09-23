// cl: /O1 /DNDEBUG /MD /GX
//
// ??0CreateObjectDieIfEldestKindofModuleData@@QAE@XZ, retail 0x00485E19,
// 55 bytes. CreateObjectDie-eldest data over the rowed
// CreateObjectDieModuleData base (0x00485D88, size 0x4C): an EldestKindof
// filter at +0x4C built through the rowed Rva00485ADCFilter ctor
// (0x00485ADC). The ModuleData factory at 0x0024C94A news 0x50 and calls
// this ctor as sole caller. Shape follows ObjectHelperCtor (opaque base
// with explicit vtable assigned from the body; the filter member stays
// stateless here so the single EH state needs no advance). Row supersedes
// the ctor pin.

class CreateObjectDieModuleData
{
public:
	CreateObjectDieModuleData();
	~CreateObjectDieModuleData();

protected:
	const void *m_vtable; // +0
	unsigned char m_pad04[0x4C - 4]; // +4..+0x4B, real base tail
};

class Rva00485ADCFilter
{
public:
	Rva00485ADCFilter();

private:
	unsigned char m_filter[4];
};

class CreateObjectDieIfEldestKindofModuleData : public CreateObjectDieModuleData
{
public:
	CreateObjectDieIfEldestKindofModuleData();

private:
	Rva00485ADCFilter m_eldestKindofFilter; // +0x4C
};

// ??0CreateObjectDieIfEldestKindofModuleData@@QAE@XZ @0x485E19
CreateObjectDieIfEldestKindofModuleData::CreateObjectDieIfEldestKindofModuleData()
	: CreateObjectDieModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C4AA08);
}
