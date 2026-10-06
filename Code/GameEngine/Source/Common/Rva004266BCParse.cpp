// cl: /MD
//
// ?Rva004266BCProcess@@YAPAXPAX0@Z, retail 0x004266BC, 87 bytes.
// Record-field dispatch through the object's vtable: slot 0x28 takes a pair
// of 1-bytes, slot 0x6C takes the record, slot 0x90 takes record+4, record+5
// and record+6 in turn; returns the object. The +4/+5/+6 field pattern matches
// the 8-byte AsciiString-plus-3-flags records of neighbour 0x004266A1.
// Evidence: vtable immediates 0x28/0x6C/0x90; callers at 0x00426F7C/0x00426FE3;
// ret with no pop (cdecl); mov eax,esi return of the object.
class Rva004266BCObj
{
public:
	virtual void v00(void *);
	virtual void v01(void *);
	virtual void v02(void *);
	virtual void v03(void *);
	virtual void v04(void *);
	virtual void v05(void *);
	virtual void v06(void *);
	virtual void v07(void *);
	virtual void v08(void *);
	virtual void v09(void *);
	virtual void v10(void *);
	virtual void v11(void *);
	virtual void v12(void *);
	virtual void v13(void *);
	virtual void v14(void *);
	virtual void v15(void *);
	virtual void v16(void *);
	virtual void v17(void *);
	virtual void v18(void *);
	virtual void v19(void *);
	virtual void v20(void *);
	virtual void v21(void *);
	virtual void v22(void *);
	virtual void v23(void *);
	virtual void v24(void *);
	virtual void v25(void *);
	virtual void v26(void *);
	virtual void v27(void *);
	virtual void v28(void *);
	virtual void v29(void *);
	virtual void v30(void *);
	virtual void v31(void *);
	virtual void v32(void *);
	virtual void v33(void *);
	virtual void v34(void *);
	virtual void v35(void *);
	virtual void v36(void *);
};

struct Rva004266BCPair
{
	unsigned char a;
	unsigned char b;
};

void *Rva004266BCProcess(void *objRaw, void *rec)
{
	Rva004266BCObj *obj = (Rva004266BCObj *)objRaw;
	struct Rva004266BCPair fixed;
	fixed.a = 1;
	fixed.b = 1;
	obj->v10(&fixed);
	obj->v27(rec);
	obj->v36((char *)rec + 4);
	obj->v36((char *)rec + 5);
	obj->v36((char *)rec + 6);
	return obj;
}
