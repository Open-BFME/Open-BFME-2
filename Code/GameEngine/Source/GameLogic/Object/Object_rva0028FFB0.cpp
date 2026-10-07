// cl: /DNDEBUG /MD
//
// ?WallUpgradeSell@Object@@QAEXXZ @0x0028FFB0 (155B).
// Object flag-clear plus timed special-model-condition queue.
// Evidence: neighbours ?healCompletely@Object (0x0028FF9E) and
// ?rva0029004B@Object (0x0029004B) prove Object TU and /O1 flags; callees
// 0x004BDA67 rowed ?rva004BDA67@Rva004BDA67, 0x0023DB0E rowed
// ?setStatus@Object, 0x0028AE6D rowed ?rva0028AE6D@Object, 0x004DE85F rowed
// ObjectSMCHelper::setModelConditionState; offsets +0x114 cond word 2, +0x230 smcHelper,
// +0x254 body with vtable slots 9 (+0x24) and 41 (+0xA4); global g_Va00DBA4E4.

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0,
	OBJECT_STATUS_1 = 1,
	OBJECT_STATUS_2 = 2,
	OBJECT_STATUS_UNDER_CONSTRUCTION = 3,
	OBJECT_STATUS_4 = 4,
	OBJECT_STATUS_5 = 5,
	OBJECT_STATUS_6 = 6,
	OBJECT_STATUS_7 = 7,
	OBJECT_STATUS_8 = 8,
	OBJECT_STATUS_9 = 9,
	OBJECT_STATUS_10 = 10,
	OBJECT_STATUS_11 = 11,
	OBJECT_STATUS_12 = 12,
	OBJECT_STATUS_13 = 13,
	OBJECT_STATUS_14 = 14,
	OBJECT_STATUS_15 = 15,
	OBJECT_STATUS_16 = 16,
	OBJECT_STATUS_17 = 17,
	OBJECT_STATUS_18 = 18,
	OBJECT_STATUS_SOLD = 0x13
};

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};

class Rva004BDA67
{
public:
	void rva004BDA67();
};

class Body254
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09(int a);
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual Rva004BDA67 *v41();
};

class ObjectSMCHelper
{
public:
	void setModelConditionState(ModelConditionFlagType mc, unsigned int frames);
};

extern int g_Va00DBA4E4;

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool flag);
	void rva0028AE6D();
	void WallUpgradeSell();

private:
	char m_pad000[0x114];
	union {
		volatile unsigned int m_dw114;
		volatile unsigned char m_b114;
	};
	char m_pad118[0x230 - 0x118];
	ObjectSMCHelper *m_smcHelper;
	char m_pad234[0x254 - 0x234];
	Body254 *m_body254;
};

void Object::WallUpgradeSell()
{
	Body254 *body = m_body254;
	Rva004BDA67 *r = body->v41();
	r->rva004BDA67();
	body->v09(0);
	setStatus((ObjectStatusTypes)3, false);
	setStatus((ObjectStatusTypes)0x13, false);
	if (m_b114 & 0x10) {
		m_dw114 &= ~0x10u;
		rva0028AE6D();
	}
	if (m_b114 & 0x20) {
		m_dw114 &= ~0x20u;
		rva0028AE6D();
	}
	if ((m_dw114 & 0x400) == 0) {
		m_dw114 |= 0x400;
		rva0028AE6D();
	}
	m_smcHelper->setModelConditionState((ModelConditionFlagType)0x68, (unsigned int)(3 * g_Va00DBA4E4));
}
