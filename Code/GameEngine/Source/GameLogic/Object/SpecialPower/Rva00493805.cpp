// cl: /MD
// ?rva00493805@SpecialPowerModule@@UAEXXZ @0x00493805 64B: vslot 12 frame-store guard.
// Evidence: vtable slot 12 of SpecialPowerModule family; callees testStatus Overridable TheGameLogic.
class Overridable {
public:
	const Overridable *friend_getFinalOverride() const;
};
struct TemplateView00493805 {
	unsigned char pad[0x59];
	unsigned char flag59;
};
class SpecialPowerModuleData {
public:
	void *vptr;
	unsigned char pad04[4];
	const Overridable *m_template;
};
enum ObjectStatusTypes {
	Status46_00493805 = 0x46
};
class Object {
public:
	bool testStatus(ObjectStatusTypes s) const;
};
class Sub10_00493805 {
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual bool v3();
};
class GameLogic;
extern GameLogic *TheGameLogic;
struct FrameView00493805 {
	unsigned char prefix[0x40];
	unsigned frame;
};
class SpecialPowerModule {
public:
	virtual void rva00493805();
	const SpecialPowerModuleData *m_data;
	Object *m_object;
	unsigned char pad0C[4];
	Sub10_00493805 m_sub10;
	unsigned char pad14[4];
	unsigned m_frame18;
	unsigned char pad1C[12];
	unsigned char m_flag28;
};
void SpecialPowerModule::rva00493805()
{
	if (m_sub10.v3())
		return;
	if (m_flag28)
		return;
	if (m_object->testStatus((ObjectStatusTypes)0x46))
		return;
	const Overridable *fin = m_data->m_template->friend_getFinalOverride();
	if (((const TemplateView00493805 *)fin)->flag59)
		return;
	m_frame18 = ((const FrameView00493805 *)TheGameLogic)->frame;
}
