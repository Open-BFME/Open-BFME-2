// cl: /DNDEBUG /MD
// ?rva000B3B2B@Rva000B3B2B@@QAEXPAVRva000B3B2BArg@@@Z @0x000B3B2B 125B
// Unlock lane: null-checked o plus m_110 plus m_12c; v44 slot 0xb0 (5 args)
// vs v45 slot 0xb4 (3 args); ratio m_90/m_94 subtracted from g_Va00BBB8D8.
// Evidence: same +0x110/+0x12c as Rva000B3A68; caller 0x000C7BC4.
extern float g_Va00BBB8D8;

class Rva000B3B2BArg
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
	virtual void v09();
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
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44(int a, float b, int c, float d, float e);
	virtual void v45(int a, float b, int c);
};

class Rva000B3B2B
{
public:
	void rva000B3B2B(Rva000B3B2BArg *o);
private:
	char m_pad00[0x90];
	float m_90;
	float m_94;
	char m_pad98[0x78];
	int m_110;
	float m_114;
	char m_pad118[0x14];
	int m_12c;
	float m_130;
};

void Rva000B3B2B::rva000B3B2B(Rva000B3B2BArg *o)
{
	if (o == 0)
		return;
	int v110 = m_110;
	if (v110 == 0)
		return;
	int v12c = m_12c;
	if (v12c != 0) {
		float f = g_Va00BBB8D8 - m_90 / m_94;
		o->v44(v110, m_114, v12c, m_130, f);
	} else {
		o->v45(v110, m_114, 0);
	}
}
