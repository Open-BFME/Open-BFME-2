// cl: /MD
//
// ??0BfmeThingSH@@QAE@XZ @0x000FE2A3 182B.
// Evidence: stores vtable bfmeVftSH at +0x0 and nulls +0x4 like
// BfmeThingSH::bfmeResetSH in BfmeThreeHundredThirtySix.cpp; float pattern
// 0.0f via xorps plus 1.0f and -1.0f via movss matches Rva00263653Ctor
// literal precedent; member offsets +0x30/+0x34/+0x38/+0x3c/+0x68-0x74/
// +0x78-0xAC/+0xB0-0xB4 match FeNode usage in Rva000FE001Move and Find.

extern "C" unsigned char bfmeVftSH[];

class BfmeSubSH
{
public:
	void bfmeTailSH();
};

class BfmeThingSH
{
public:
	BfmeThingSH();

private:
	void *m_vft00;
	BfmeSubSH *m_sub04;
	unsigned char m_pad08[0x30 - 0x08];
	int m_30;
	int m_34;
	int m_38;
	unsigned char m_3c;
	unsigned char m_pad3d[0x68 - 0x3d];
	int m_68;
	int m_6c;
	int m_70;
	int m_74;
	float m_78;
	float m_7c;
	float m_80;
	float m_84;
	float m_88;
	float m_8c;
	float m_90;
	float m_94;
	float m_98;
	float m_9c;
	float m_a0;
	float m_a4;
	float m_a8;
	float m_ac;
	void *m_b0;
	void *m_b4;
};

BfmeThingSH::BfmeThingSH() :
	m_vft00(bfmeVftSH),
	m_sub04(0),
	m_30(0),
	m_34(2),
	m_38(2),
	m_3c(0),
	m_68(0),
	m_6c(1),
	m_70(0),
	m_74(0),
	m_78(0.0f),
	m_7c(0.0f),
	m_80(1.0f),
	m_84(0.0f),
	m_88(1.0f),
	m_8c(1.0f),
	m_90(0.0f),
	m_94(1.0f),
	m_98(-1.0f),
	m_9c(1.0f),
	m_a0(1.0f),
	m_a4(0.0f),
	m_a8(0.0f),
	m_ac(0.0f),
	m_b0(0),
	m_b4(0)
{
}
