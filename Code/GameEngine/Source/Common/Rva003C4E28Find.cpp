// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// Built from the banked attempt reverse/attempts/0x003c4e28.cpp; fix: the
// 1000.0f scale is a compiler literal (retail constant at RVA 0x007BE358), not
// an extern global, which is what keeps retail's operand order.
// Rva003C4E28Find @0x003C4E28 155B. Free stdcall
// lookup by name then scaled place via two singletons. Evidence: leaf lane,
// ret 0x10 four args, StringBase<char>::compare row 0x69D6, virtual head at
// +0x84 from dword 0x009FEC50, virtual place at +0xC8 on 0x009FEA3C with
// float scale at 0x007BE358. Layout honest-address only.
#include "ascii_string.h"
struct Rva003C4E28Entry
{
	char m_pad00[8];
	AsciiString m_name;
	float m_x;
	float m_y;
	float m_z;
	int m_unk18;
	Rva003C4E28Entry *m_next;
};
class Rva003C4E28ListMgr
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
	virtual Rva003C4E28Entry *GetHead();
};
class Rva003C4E28PlaceMgr
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
	virtual void w17();
	virtual void w18();
	virtual void w19();
	virtual void w20();
	virtual void w21();
	virtual void w22();
	virtual void w23();
	virtual void w24();
	virtual void w25();
	virtual void w26();
	virtual void w27();
	virtual void w28();
	virtual void w29();
	virtual void w30();
	virtual void w31();
	virtual void w32();
	virtual void w33();
	virtual void w34();
	virtual void w35();
	virtual void w36();
	virtual void w37();
	virtual void w38();
	virtual void w39();
	virtual void w40();
	virtual void w41();
	virtual void w42();
	virtual void w43();
	virtual void w44();
	virtual void w45();
	virtual void w46();
	virtual void w47();
	virtual void w48();
	virtual void w49();
	virtual void Place(float *pos, int n, float y, float z);
};
extern class TerrainLogic *TheTerrainLogic;
extern class View *TheTacticalView;

void __stdcall Rva003C4E28Find(const AsciiString &name, float x, float y, float z)
{
	Rva003C4E28Entry *p = (*(Rva003C4E28ListMgr **)&TheTerrainLogic)->GetHead();
	goto test;
loop:
	if (p->m_name.compare(name) == 0)
		goto found;
	p = p->m_next;
test:
	if (p)
		goto loop;
	goto end;
found:
	float tz = z;
	float pos[3];
	pos[0] = p->m_x;
	pos[1] = p->m_y;
	pos[2] = p->m_z;
	int ix = (int)(x * 1000.0f);
	float fy = y * 1000.0f;
	float fz = tz * 1000.0f;
	(*(Rva003C4E28PlaceMgr **)&TheTacticalView)->Place(pos, ix, fy, fz);
end:;
}
