// cl: /O1 /DNDEBUG /MD
//
// ?rva004C69FA@WoundArrowUpdate@@UAE_NH@Z, retail 0x004C69FA, 38 bytes: slot 8
// of the vtable 0x00C5DEDC that WoundArrowUpdate's ctors (0x004C6929,
// 0x004C6957) install at +0x20. False when bit 0 of the module data's +0xCC
// byte is set and the owner Object is KindOf 0xD6 (rowed Object::isKindOf);
// true otherwise. The argument is unread. Compiled with the +0x20 subobject
// this. Names by address.
enum KindOfType
{
	KINDOF_INVALID = -1
};

class Object
{
public:
	bool isKindOf(KindOfType t) const;
};

struct WoundArrowUpdateModuleData
{
	unsigned char m_pad00[0xCC];
	unsigned char m_CC; // +0xCC
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
protected:
	const WoundArrowUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
private:
	unsigned char m_pad0C[0x20 - 0x0C];
};

class WoundArrowUpdateInterface
{
public:
	virtual void slot0() = 0; virtual void slot1() = 0; virtual void slot2() = 0; virtual void slot3() = 0;
	virtual void slot4() = 0; virtual void slot5() = 0; virtual void slot6() = 0; virtual void slot7() = 0;
	virtual bool rva004C69FA(int unused) = 0;
};

class WoundArrowUpdate : public UpdateModule, public WoundArrowUpdateInterface
{
public:
	virtual bool rva004C69FA(int unused);
};

bool WoundArrowUpdate::rva004C69FA(int unused)
{
	if ((m_moduleData->m_CC & 1) && m_object->isKindOf((KindOfType)0xD6))
		return false;
	return true;
}
