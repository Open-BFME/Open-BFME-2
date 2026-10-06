// cl: /DNDEBUG /MD /EHsc
// ??1W3DLightDraw@@UAE@XZ @0x000CFA42 87B
// BFME2 W3DLightDraw destructor. Donor: reference/open-bfme-1/Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDrawDestructor.cpp
// (BFME1 retail 0x00758580, same body: setEnabled(false) + Release_Ref + null).
// Target facts: vtable 0x00BCD728 slot 0 (deleting dtor 0x000CFBF0 calls here);
// slot 4 -> 0x000CFAF9 pool key with string "W3DLightDraw"; base vtable 0x00BC9690
// then folded base dtor 0x0049B47C (pinned ??1DrawableModule@@MAE@XZ).

typedef unsigned int UnsignedInt;
typedef bool Bool;

class RefCountClass
{
public:
	virtual void Delete_This();

	void Release_Ref() const
	{
		--m_numRefs;
		if (m_numRefs == 0)
			const_cast<RefCountClass *>(this)->Delete_This();
	}

protected:
	virtual ~RefCountClass();

private:
	mutable int m_numRefs; // +0x04
};

class RenderObjClass : public RefCountClass
{
protected:
	virtual ~RenderObjClass();
};

class LightClass : public RenderObjClass
{
protected:
	virtual ~LightClass();
};

class W3DDynamicLight : public LightClass
{
public:
	void setEnabled(Bool enabled);
};

class DrawableModule
{
protected:
	virtual ~DrawableModule();

	void *m_moduleData; // +0x04
	void *m_drawable; // +0x08
};

class DrawModule : public DrawableModule
{
protected:
	virtual ~DrawModule() {}
};

class W3DLightDraw : public DrawModule
{
public:
	virtual ~W3DLightDraw();

private:
	W3DDynamicLight *m_light; // +0x0C
};

W3DLightDraw::~W3DLightDraw()
{
	m_light->setEnabled(false);
	if (m_light)
	{
		m_light->Release_Ref();
		m_light = 0;
	}
}
