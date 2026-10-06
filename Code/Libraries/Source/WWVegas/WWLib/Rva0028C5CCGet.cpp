// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// ?Rva0028C5CCGet@@YAPAVRva0028C5CC@@PAV1@PAD@Z @0x0028C5CC 95B: guard index via vtable +0x78 then throw formatted on 4 else loop 4x via +0x88. Evidence: same 95B shape as rowed Rva002DBD05Get 0x002DBD05 plus rowed _bfmeFormatText 0x0060C36E plus pin _CxxThrowException 0x00629094.
class Rva0028C5CC
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
	virtual void unk78(int *idx);
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void unk88(void *p);
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	void *text;
	int tag;
};


Rva0028C5CC *__cdecl Rva0028C5CCGet(Rva0028C5CC *obj, char *base)
{
	int idx = 4;
	obj->unk78(&idx);
	if (idx != 4) {
		throw XferException(0, 0);
	}
	for (unsigned int i = 0; i < 4; ++i) {
		obj->unk88(base + i);
	}
	return obj;
}
