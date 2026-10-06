// cl: /DNDEBUG /MD
// ?rva000B3BA8@Rva000B3BA8@@QAEXPAVRva000B3BA8Arg@@@Z @0x000B3BA8 39B
// Leaf lane: null-checked arg plus m_110/m_114 via v45 slot 0xb4 (int float int)
// same as Rva000B3B2B v45 shape. Caller 0x000B5FA7. Neighbours Rva000B3B2B/Rva000B3C61.
class Rva000B3BA8Arg
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

class Rva000B3BA8
{
public:
	void rva000B3BA8(Rva000B3BA8Arg *o);
private:
	char m_pad00[0x110];
	int m_110;
	float m_114;
};

void Rva000B3BA8::rva000B3BA8(Rva000B3BA8Arg *o)
{
	if (o == 0)
		return;
	o->v45(m_110, m_114, 0);
}
