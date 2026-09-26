// cl: /O1 /DNDEBUG /MD /GX
//
// ??1CreateObjectDieIfEldestKindofModuleData@@UAE@XZ, retail 0x00485E88, 59 bytes.
// EldestKindof dtor over the rowed CreateObjectDieModuleData base 0x00485DDA
// (size 0x4C): destroys the +0x4C filter through the pinned 0x00360D26
// (state 0) then calls the base dtor (state -1). The filter rides as a
// second base to reproduce retail's null-checked this-adjustment (neg plus
// sbb plus and plus lea eax) which a plain member does not emit (53B).
// Layout from the rowed ctor 0x00485E19 (base plus filter at +0x4C via
// rowed 0x00485ADC size 0x50 via factory 0x0024C94A) and own vtable
// 0x00C4AA08. Caller is the slot-0 ??_G at 0x00485E6C. Shape follows
// DominateEnemySpecialPowerModuleDataDtor (novtable suppressing the derived
// store retail lacks plus base call restoring the table).
class CreateObjectDieModuleData
{
public:
	virtual ~CreateObjectDieModuleData();
private:
	unsigned char m_pad[0x4C - 4];
};
class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	unsigned m_unknown;
};
class __declspec(novtable) CreateObjectDieIfEldestKindofModuleData : public CreateObjectDieModuleData, public Rva00360D26Member
{
public:
	virtual ~CreateObjectDieIfEldestKindofModuleData();
};
CreateObjectDieIfEldestKindofModuleData::~CreateObjectDieIfEldestKindofModuleData()
{
}
