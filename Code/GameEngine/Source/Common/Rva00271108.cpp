// cl: /MD
// Built from the banked attempt reverse/attempts/0x00271108.cpp; fix: the floats
// read through g_Va00BBAEAC, g_Va00BC7468 are compiler literals holding the retail
// values, not extern globals, which is what gives retail's operand order.

// ?handleWeaponFireFX@Drawable@@QAE_NHHHMMMH@Z retail 0x00271108 190B.
// Unlock lane: float guard vs pooled 0.0 at 0x00BBAEAC, adjust angle at
// [ebp+0x1c] via [esi+0xfc]+0x44 and global at 0x00BC7468, Cos/Sin scale by
// [ebp+0x18] into [esi+0x13c]+0x1c/+0x24, then null-terminated list at
// [esi+0x14c] calling slot 0xA8 then slot 0x58. Caller 0x002CBBF5.
// Evidence: callees rowed Cos 0x0002FBC0 Sin 0x0002FBB0, prev/next /O1 /MD.

float Cos(float);
float Sin(float);

class Target
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
	virtual bool check(int a0, int a1, int a2, float a3, int a4);
};

class Node
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
	virtual Target *get();
};

struct Offset44
{
	char m_pad[0x44];
	float m_44;
};

struct Accum
{
	char m_pad[0x1c];
	float m_1c;
	float m_20;
	float m_24;
};

class Drawable
{
public:
	bool handleWeaponFireFX(int a0, int a1, int a2, float a3, float a4, float a5, int a6);

private:
	char m_pre[0xfc];
	Offset44 *m_fc;
	char m_mid[0x3c];
	Accum *m_acc;
	char m_mid2[0xc];
	Node **m_list;
};

bool Drawable::handleWeaponFireFX(int a0, int a1, int a2, float a3, float a4, float a5, int a6)
{
	if (a4 != 0.0f) {
		if (m_fc != 0)
			a5 -= m_fc->m_44;
		a5 = a5 + 3.1415927410125732f;
		if (m_acc != 0) {
			float c = Cos(a5);
			m_acc->m_1c += c * a4;
			float s = Sin(a5);
			m_acc->m_24 += s * a4;
		}
	}
	Node **pp = m_list;
	for (; *pp != 0; pp++) {
		Target *t = (*pp)->get();
		if (t != 0) {
			if (t->check(a0, a1, a2, a3, a6))
				return true;
		}
	}
	return false;
}
