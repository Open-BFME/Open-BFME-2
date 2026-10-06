// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// Rva002DBDB4::rva002DBDB4, retail 0x002DBDB4 (174 bytes). Built from the banked
// attempt reverse/attempts/0x002dbdb4.cpp; fix: the eight 0x1AC-stride
// subobjects at this+4 are embedded (retail lea then vtable load), not
// pointers the loop dereferences.
class Rva002DBD05
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
	virtual void unk28(void *p);
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
	virtual void unk78(int *idx);
	virtual void unk7c(void *p);
	virtual void v32();
	virtual void v33();
	virtual void unk88(void *p);
	virtual void v35();
	virtual void unk90(void *p);
};

class BfmeSubobject
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void unk0c(void *p);
};

Rva002DBD05 * __cdecl Rva002DBD05Get(Rva002DBD05 *obj, char *base);

class Rva002DBDB4
{
public:
	void rva002DBDB4(Rva002DBD05 *obj);

	unsigned char m_pad[0xD64];
	char m_dataD64[0x10];
	char m_dataD74[0x28];
	char m_dataD9C[0x4];
	char m_dataDA0[0x4];
};

void Rva002DBDB4::rva002DBDB4(Rva002DBD05 *obj)
{
	struct TwoBytes { unsigned char b1; unsigned char b2; } ver;
	ver.b1 = 1;
	ver.b2 = 3;
	obj->unk28(&ver);
	int bound = 8;
	int counter = bound;
	obj->unk7c(&counter);
	counter = 0;
	for (; counter < bound; ++counter) {
		int off = counter * 0x1AC;
		BfmeSubobject *sub = (BfmeSubobject *)((char *)this + off + 4);
		sub->unk0c(obj);
	}
	Rva002DBD05Get(obj, (char *)this + 0xD64);
	char *p = (char *)this + 0xD74;
	for (int j = 0; j < 10; ++j) {
		obj->unk7c(p);
		p += 4;
	}
	if (ver.b2 >= 2) {
		obj->unk90((char *)this + 0xD9C);
	}
	if (ver.b2 >= 3) {
		obj->unk7c((char *)this + 0xDA0);
	}
}
