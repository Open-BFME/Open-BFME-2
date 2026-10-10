// cl: /MD /DNDEBUG
//
// W3DTruckDraw::setHidden, retail 0x000CC781 (32 bytes), ported from Zero
// Hour's GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
// W3DTruckDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// Identity: slot 16 of vtable 0x00BCC650, whose slot-2 name getter returns
// "W3DTruckDraw"; slot 16 of the W3DModelDraw-family vtable 0x00BCBFC0 is the
// base W3DModelDraw::setHidden (0x000B6F6D, pinned), which this body calls
// first, then switches the emitters off when hiding, as Zero Hour does.
// enableEmitters is the rowed ?enableEmitters@W3DTankTruckDraw (0x000CB826),
// so it is modelled on that intermediate class.

typedef bool Bool;

class W3DModelDraw
{
public:
	virtual void setHidden(Bool h);
};

class W3DTankTruckDraw : public W3DModelDraw
{
protected:
	void enableEmitters(Bool enable);
};

typedef int Int;
class RenderObjClass;

class W3DTruckDraw : public W3DTankTruckDraw
{
public:
	virtual void setHidden(Bool h);
	virtual void onRenderObjRecreated(void);

protected:
	void updateBones(void);

private:
	char m_pad04[0x320 - 0x04];
	Int m_bones[16];			// +0x320, the tire/cab/trailer bone indices
	char m_pad360[0x484 - 0x360];
	RenderObjClass *m_prevRenderObj;	// +0x484
};

//-------------------------------------------------------------------------------------------------
void W3DTruckDraw::setHidden(Bool h)
{
	W3DModelDraw::setHidden(h);
	if (h)
	{
		enableEmitters(false);
	}
}

//-------------------------------------------------------------------------------------------------
// W3DTruckDraw::onRenderObjRecreated, retail 0x000CC7A1 (109 bytes), the
// vtable slot after W3DModelDraw's 0x000B3D39, directly after setHidden.
// Zero Hour's body: forget the previous render object and every cached bone
// index, then re-resolve them through the rowed updateBones (0x000CB8CB,
// tail call). BFME 2 keeps sixteen contiguous bone indices (+0x320..+0x35C)
// where Zero Hour named twelve; their individual roles are not established.
void W3DTruckDraw::onRenderObjRecreated(void)
{
	m_prevRenderObj = 0;
	m_bones[0] = 0;
	m_bones[1] = 0;
	m_bones[2] = 0;
	m_bones[3] = 0;
	m_bones[4] = 0;
	m_bones[5] = 0;
	m_bones[6] = 0;
	m_bones[7] = 0;
	m_bones[8] = 0;
	m_bones[9] = 0;
	m_bones[10] = 0;
	m_bones[11] = 0;
	m_bones[12] = 0;
	m_bones[13] = 0;
	m_bones[14] = 0;
	m_bones[15] = 0;
	updateBones();
}
