// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// Rva004073DCFind, retail 0x004073DC, 177 bytes, __stdcall, sole caller
// 0x004086D4. Walks the null-terminated pointer array returned by the rowed
// Rva002B224BDwordField::get 0x002B224B while the result is still empty;
// for each entry whose slot-42 object answers slot 9, takes the name its
// slot 10 returns by value. Returns the name by value.
// Retail's unwind map tracks the return slot (state 0, flag at ebp-0x18),
// the local result (state 1) and the by-value temporary (state 2), so the
// function returns AsciiString by value rather than filling an out pointer
// by placement copy as the banked 0.80 attempt did.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"


class Rva002B224BDwordField
{
public:
	int get() const;
};

class Rva004073DCThing
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08();
	virtual int v24();
	virtual AsciiString v28(int unused);
};

class Rva004073DCElem
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41();
	virtual Rva004073DCThing *vA8();
};

AsciiString __stdcall Rva004073DCFind(const Rva002B224BDwordField *field)
{
	AsciiString result;
	Rva004073DCElem **cursor = (Rva004073DCElem **)field->get();
	while (result.isEmpty() && *cursor)
	{
		Rva004073DCThing *thing = (*cursor)->vA8();
		if (thing && thing->v24())
			result = thing->v28(0);
		++cursor;
	}
	return result;
}
