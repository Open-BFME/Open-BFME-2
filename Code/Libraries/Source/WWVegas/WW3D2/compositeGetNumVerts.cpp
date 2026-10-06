// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD
// CompositeRenderObjClass::Get_Num_Verts, retail 0x001A5F00, named by the
// WorldBuilder lead (vtable pairing, composite.cpp). BFME2's twin of
// Get_Num_Polys: sums the sub-objects' vertex counts (render-object slot 11,
// the slot after Get_Num_Polys that rendobj.h calls _bfme_ro_v9), releasing
// each sub-object reference. Dedicated unit with a slot-level view: adding
// the override to composite.cpp needs the shared composite.h/rendobj.h.

class RenderObjClass
{
public:
	virtual void Delete_This();					// 0x00
	virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08();
	virtual void s09(); virtual void s10();
	virtual int Get_Num_Verts() const;				// 0x2C
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual int Get_Num_Sub_Objects() const;			// 0x70
	virtual void s29();
	virtual RenderObjClass *Get_Sub_Object(int index) const;	// 0x78

	void Release_Ref()
	{
		if (--NumRefs == 0)
			Delete_This();
	}

protected:
	int NumRefs;							// +0x04
};

class CompositeRenderObjClass : public RenderObjClass
{
public:
	virtual int Get_Num_Verts() const;
};

// CompositeRenderObjClass::Get_Num_Verts, retail 0x001A5F00.
int CompositeRenderObjClass::Get_Num_Verts() const
{
	int count = 0;
	for (int ni = 0; ni < Get_Num_Sub_Objects(); ni++)
	{
		RenderObjClass *robj = Get_Sub_Object(ni);
		count += robj->Get_Num_Verts();
		robj->Release_Ref();
	}
	return count;
}
