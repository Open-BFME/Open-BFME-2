// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// ?Rva002E7FEDGet@@YAPAVRva002E7FED@@PAV1@PAH@Z @0x002E7FED 88B: guard index via vtable +0x78 then throw formatted on 0x40 else loop 64x via +0x70. Evidence: same shape as rowed Rva002DBD05Get 0x002DBD05 plus rowed _bfmeFormatText 0x0060C36E plus pin _CxxThrowException 0x00629094.
class Rva002E7FED
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
	virtual void unk70(void *p);
	virtual void v29();
	virtual void unk78(int *idx);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern int g_guardTargetTypeThrowInfo;

Rva002E7FED *__cdecl Rva002E7FEDGet(Rva002E7FED *obj, int *vals)
{
	int idx = 0x40;
	int n = 0x40;
	obj->unk78(&idx);
	if (idx != 0x40) {
		XferException error;
		bfmeFormatText(&error, 0, 0);
		_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
	}
	int *p = vals;
	do {
		obj->unk70(p++);
	} while (--n != 0);
	return obj;
}
