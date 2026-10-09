// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva00083A50@RenderableRiverArea@@QAE?AV?$RefCountPtr@VRenderingMethod@FXShader@@@@XZ
// retail 0x00083A50..0x00083A7A (42 bytes) thiscall ret 4 hidden return.
// By-value getter of the rendering method held at +0x54: when the +0x58
// dirty byte is set it first rebuilds the method (unrowed 0x000835D0 which
// reads the +0x40 string holder through the rowed 0x0030BBA9 getter as
// RenderableRiverArea::createTexture does then assigns the 0x00152C47
// shader result to +0x54 and clears +0x58) and then copies the handle
// into the return slot bumping the int count at +4.
// Caller: WaterRenderObjClass::drawRiverWater 0x00100A0B (WB 0x765E80)
// tests the result and passes it to the rowed
// RenderInfoClass::Push_Rendering_Method (0x001431B0) by value.
// WB twin 0x00742590 has the same flag test and copy.
// Method names are address-derived; class from the shared +0x40 holder.
class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

namespace FXShader {
class RenderingMethod : public RefCountClass
{
};
}

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			Referent->Add_Ref();
	}
	~RefCountPtr(void)
	{
		if (Referent)
			Referent->Release_Ref();
	}

private:
	T *Referent;
};

class RenderableRiverArea
{
public:
	void rva000835D0();
	RefCountPtr<FXShader::RenderingMethod> rva00083A50();

private:
	char m_pad[0x54];
	RefCountPtr<FXShader::RenderingMethod> m_method;	// +0x54
	bool m_methodDirty;	// +0x58
};

RefCountPtr<FXShader::RenderingMethod> RenderableRiverArea::rva00083A50()
{
	if (m_methodDirty)
		rva000835D0();
	return m_method;
}
