// cl: /O1 /arch:SSE /G7 /MD
//
// ?rva002BE8F9@Rva002BE8F9@@QAEXPAX@Z @0x002BE8F9 279B.
// Branch on +0x18/+0x14: +0x18==0 returns; +0x14==1 runs the living-world
// item gate plus mouse/manager notifies; +0x14==0 runs the v38 fill plus the
// 8-key lookup and v58/v4c tails with a float pair to the manager.
// Evidence: caller at 0x002B8A92 passes +0x8c pointer; callees rowed
// 0x002B2B2D 0x0020F27E 0x00211075 0x002B38A3 0x00504138 0x002BE7DB 0x00213AFC;
// globals TheLivingWorldLogic TheMouse TheLivingWorldManager; prev 0x002BE8D4
// next 0x002BECCD share /MD in the same dir.

struct Rva002B3740Item;

class Rva002BA8F1Logic
{
public:
	Rva002B3740Item *rva002B2B2D();
};

class Rva0020F27EHost
{
public:
	bool rva0020F27E(int idx, int v);
};

class Rva00211075
{
public:
	void rva00211075();
};

class Rva002B38A3
{
public:
	void *rva002B38A3(int key);
};

class Rva00504138
{
public:
	void *rva00504138(int n);
};

struct Rva002BE7DBValue
{
	float x;
	float y;
	float z;
};

class Rva002BE7DB
{
public:
	float m_x;
	float m_y;
	float m_z;
	Rva002BE7DBValue &rva002BE7DB(Rva002BE7DBValue &out) const;
};

class Rva00213A85
{
public:
	void rva00213AFC(void *value);
};

class LivingWorldLogic
{
public:
	char m_pad[0xB0];
	Rva0020F27EHost *m_b0;
};
extern LivingWorldLogic *TheLivingWorldLogic;

class Mouse
{
public:
	virtual void m00();
	virtual void m01();
	virtual void m02();
	virtual void m03();
	virtual void m04();
	virtual void m05();
	virtual void m06();
	virtual void m07();
	virtual void m08();
	virtual void m09();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14();
	virtual void m15();
	virtual void m16();
	virtual void m17();
	virtual void m18();
	virtual void m19(int flag);
};
extern Mouse *TheMouse;

class LivingWorldManager
{
public:
	char m_pad[0x204];
};
extern LivingWorldManager *TheLivingWorldManager;

struct Rva002BE8F9Pair
{
	float a;
	float b;
};

class Rva002BE8F9
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
	virtual void v14(void *a, void *b);
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19(int a, int b);
	virtual void v20();
	virtual void v21();
	virtual void v22(void *p);
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
	virtual void v40(int a);
	void rva002BE8F9(void *arg);
private:
	char m_pad04[0x14 - 0x04];
	int m_14;
	unsigned char m_18;
	char m_pad19[0x1C - 0x19];
	int m_1c;
};

// ?rva002BE8F9@Rva002BE8F9@@QAEXPAX@Z
void Rva002BE8F9::rva002BE8F9(void *arg)
{
	if (m_18 == 0)
		return;
	switch (m_14)
	{
	case 1:
		{
			Rva002B3740Item *item = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B2B2D();
			if (item == 0)
				return;
			int itemValue = *(int *)((char *)item + 0x12C);
			Rva0020F27EHost *host = TheLivingWorldLogic->m_b0;
			if (!host->rva0020F27E(itemValue, (int)&m_1c))
				return;
			v40(1);
			TheMouse->m19(0);
			v19(2, 0);
			if (TheLivingWorldManager == 0)
				return;
			((Rva00211075 *)TheLivingWorldManager)->rva00211075();
			return;
		}
	case 0:
		{
			Rva002BE7DBValue local14;
			Rva002BE7DBValue tmp20;
			v14(arg, &local14);
			void *found = ((Rva002B38A3 *)TheLivingWorldLogic)->rva002B38A3(8);
			if (found != 0)
			{
				void *node = ((Rva00504138 *)((char *)found + 0x0C))->rva00504138(0);
				if (node != 0)
					local14 = ((Rva002BE7DB *)node)->rva002BE7DB(tmp20);
			}
			v22(&local14);
			v19(1, 0);
			if (TheLivingWorldManager == 0)
				return;
			Rva002BE8F9Pair pair;
			pair.a = local14.x;
			pair.b = local14.y;
			((Rva00213A85 *)TheLivingWorldManager)->rva00213AFC(&pair);
			return;
		}
	default:
		return;
	}
}
