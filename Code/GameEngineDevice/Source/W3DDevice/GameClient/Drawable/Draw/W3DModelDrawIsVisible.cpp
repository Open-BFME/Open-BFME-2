// cl: /MD /DNDEBUG
//
// W3DModelDraw::isVisible, retail 0x000B37F0 (28 bytes), ported from Zero
// Hour's GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/
// W3DModelDraw.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference).
// Identity: slot 37 of the W3DModelDraw-family vtable 0x00BCBFC0 (slot-2 name
// getter returns "W3DSupplyDraw"), two after the rowed
// setFullyObscuredByShroud as in Zero Hour's DrawModule (BFME 2 inserts one
// slot between them), followed by the large reactToTransformChange and the
// empty reactToGeometryChange; the body is Zero Hour's
// "m_renderObject && m_renderObject->Is_Really_Visible()".
// BFME 2 differences (target evidence): m_renderObject sits at +0x50, and
// the visibility test is RenderObjClass vtable slot 96 (+0x180), a virtual
// call where Zero Hour inlines a bit test; the slot's name is carried over
// from Zero Hour as an inference. Retail is size-optimised (/O1: xor/inc for
// true), which the /O2 W3DModelDraw.cpp port does not reproduce, so the body
// lives here.

typedef bool Bool;

class RenderObjClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot0A();
	virtual void slot0B();
	virtual void slot0C();
	virtual void slot0D();
	virtual void slot0E();
	virtual void slot0F();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot1A();
	virtual void slot1B();
	virtual void slot1C();
	virtual void slot1D();
	virtual void slot1E();
	virtual void slot1F();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot2A();
	virtual void slot2B();
	virtual void slot2C();
	virtual void slot2D();
	virtual void slot2E();
	virtual void slot2F();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot3A();
	virtual void slot3B();
	virtual void slot3C();
	virtual void slot3D();
	virtual void slot3E();
	virtual void slot3F();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot4A();
	virtual void slot4B();
	virtual void slot4C();
	virtual void slot4D();
	virtual void slot4E();
	virtual void slot4F();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot5A();
	virtual void slot5B();
	virtual void slot5C();
	virtual void slot5D();
	virtual void slot5E();
	virtual void slot5F();
	virtual int Is_Really_Visible(void);
};

class W3DModelDraw
{
public:
	virtual Bool isVisible() const;
private:
	unsigned char m_pad04[0x50 - 0x04];
	RenderObjClass *m_renderObject; // +0x50
};

//-------------------------------------------------------------------------------------------------
Bool W3DModelDraw::isVisible() const
{
	return (m_renderObject && m_renderObject->Is_Really_Visible());
}
