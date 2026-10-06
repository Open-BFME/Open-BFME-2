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

class W3DTruckDraw : public W3DTankTruckDraw
{
public:
	virtual void setHidden(Bool h);
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
