// cl: /MD /DNDEBUG
//
// W3DTankDraw::setHidden, retail 0x000CE129 (30 bytes), ported from Zero
// Hour's GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
// W3DTankDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// Identity: slot 16 of vtable 0x00BCCBE8, whose slot-2 name getter returns
// "W3DTankDraw"; slot 16 of the W3DModelDraw-family vtable 0x00BCBFC0 is the
// base W3DModelDraw::setHidden (0x000B6F6D, pinned), which this body calls
// first, then stops the tread debris when hiding, as Zero Hour does.
// stopMoveDebris is the rowed opaque ?rva000CE0EA@W3DTankDraw (it acts on
// the two tread-debris particle handles at +0x2E8/+0x2F4).

typedef bool Bool;

class W3DModelDraw
{
public:
	virtual void setHidden(Bool h);
};

class W3DTankDraw : public W3DModelDraw
{
public:
	virtual void setHidden(Bool h);
	void rva000CE0EA(); // stopMoveDebris
};

//-------------------------------------------------------------------------------------------------
void W3DTankDraw::setHidden(Bool h)
{
	W3DModelDraw::setHidden(h);
	if (h)
	{
		rva000CE0EA();
	}
}
