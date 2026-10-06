// cl: /DNDEBUG /MD /GX-
// ?xferRandomVariable@@YAAAVXfer@@AAV1@AAVGameClientRandomVariable@@@Z retail 0x00306183 149 bytes.
// BFME1 donor: Code/GameEngine/Source/GameClient/System/FXParticleSystem/xferRandomVariable.cpp
// BFME2 deltas: Version1 helper for the 1/1 version pair, XferDistributionType helper for the enum,
// xferReal at vtable slot 28 (0x70). Callers: 40+ DoXfer bodies including 0x0055EA8E vslot candidate.
// Callees rowed: Version1 0x53EE, XferDistributionType 0x305F92, setRange 0x2341E7.
class Xfer
{
public:
	virtual void r0();
	virtual void r1();
	virtual bool isSaving();
	virtual void r3();
	virtual void r4();
	virtual void r5();
	virtual void r6();
	virtual void r7();
	virtual void r8();
	virtual void r9();
	virtual void xferVersion(unsigned char *version);
	virtual void r11();
	virtual void r12();
	virtual void r13();
	virtual void r14();
	virtual void r15();
	virtual void r16();
	virtual void r17();
	virtual void r18();
	virtual void r19();
	virtual void r20();
	virtual void r21();
	virtual void r22();
	virtual void r23();
	virtual void r24();
	virtual void r25();
	virtual void r26();
	virtual void r27();
	virtual void xferReal(float *value);

	void Version1();
};

class GameClientRandomVariable
{
public:
	enum DistributionType
	{
		CONSTANT,
		UNIFORM,
		GAUSSIAN,
		TRIANGULAR,
		LOW_BIAS,
		HIGH_BIAS
	};

	void setRange(float low, float high, DistributionType type);

	DistributionType m_type;
	float m_low;
	float m_high;
};

void XferDistributionType(Xfer *xfer, int *value);

Xfer &xferRandomVariable(Xfer &xfer, GameClientRandomVariable &var)
{
	float low;
	float high;
	GameClientRandomVariable::DistributionType type;

	xfer.Version1();

	low = 0.0f;
	high = 0.0f;
	type = GameClientRandomVariable::CONSTANT;

	if (xfer.isSaving()) {
		low = var.m_low;
		high = var.m_high;
		type = var.m_type;
	}

	xfer.xferReal(&low);
	xfer.xferReal(&high);
	XferDistributionType(&xfer, (int *)&type);

	if (!xfer.isSaving()) {
		var.setRange(low, high, type);
	}
	return xfer;
}
