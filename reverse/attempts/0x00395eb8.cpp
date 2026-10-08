// ?Rva00395EB8Clear@@YGXPAVObject@@@Z
// partial score=0.97 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /MD
// ?Rva00395EB8Clear@@YGXPAVObject@@@Z @0x00395EB8 83B
// evidence: leaf caller 0x00397D45; rowed Object setProducer 0x0028AFD2 plus setStatus 0x0023DB0E plus notify 0x0028AE6D; pinned clearDisabled 0x00291CAC; flag byte 0x117 bit 0x80 then 3 setStatus false
enum DisabledType
{
	DISABLED_TYPE_0 = 0,
	DISABLED_TYPE_1 = 1,
	DISABLED_TYPE_2 = 2,
	DISABLED_TYPE_3 = 3
};
enum ObjectStatusTypes
{
	OBJECT_STATUS_3 = 3,
	OBJECT_STATUS_5 = 5,
	OBJECT_STATUS_4F = 0x4F
};
class Object
{
public:
	void setProducer(Object *producer);
	bool clearDisabled(DisabledType type);
	void setStatus(ObjectStatusTypes status, bool flag);
	void rva0028AE6D();
public:
	char m_pad000[0x117];
	struct
	{
		unsigned char _lo : 7;
		bool m_80 : 1;
	} m_117;
};
void __stdcall Rva00395EB8Clear(Object *obj)
{
	obj->setProducer(0);
	obj->clearDisabled((DisabledType)3);
	if (obj->m_117.m_80)
	{
		obj->m_117.m_80 = false;
		obj->rva0028AE6D();
	}
	obj->setStatus((ObjectStatusTypes)3, false);
	obj->setStatus((ObjectStatusTypes)0x4F, false);
	obj->setStatus((ObjectStatusTypes)5, false);
}
