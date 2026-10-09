// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva00273C47@Rva00273C47Host@@QAEXXZ @0x00273C47 392B
// Target evidence: m_object +0xFC; controlling-player call 0x0028AFA9;
// group-index call 0x002AA191; contain provider +0x250/slot31 and contained
// object +0x274 status gate; DrawGroupInfo at 0x00A01CD8; rectangle +0x460;
// display-string manager at 0x009FEAD8 with slots +0x40/+0x3C/+0x28/+0x38.
// The WB name lead is callgraph-only, so the function stays address-derived.
// The Zero Hour Drawable::drawUIText group-number path supplies the rendering
// purpose and field relationship; target offsets and branch order come from
// the retail disassembly, not the donor layout.
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Object;
class Player;
class Drawable;
class Rva00273C47Host;
class Thing;

class Rva002AA191
{
public:
	Int rva002AA191(const Object *object);
};

class Player
{
public:
	Int getPlayerColor() const { return m_color; }
private:
	char m_pad000[0x280];
	Int m_color;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

#define GROUP_VSLOTS10(p) \
	virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); virtual void p##4(); \
	virtual void p##5(); virtual void p##6(); virtual void p##7(); virtual void p##8(); virtual void p##9();

class GroupNodeView
{
public:
	GROUP_VSLOTS10(s0) GROUP_VSLOTS10(s1) GROUP_VSLOTS10(s2)
	GROUP_VSLOTS10(s3) GROUP_VSLOTS10(s4) GROUP_VSLOTS10(s5)
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual Thing *slot68();
	virtual void s69();
	virtual Thing *slot70();
};

class ContainModuleView
{
public:
	GROUP_VSLOTS10(s0) GROUP_VSLOTS10(s1) GROUP_VSLOTS10(s2)
	virtual void s30();
	virtual GroupNodeView *slot31();
};

#undef GROUP_VSLOTS10

class ObjectStatusView
{
public:
	char m_pad000[0x114];
	UnsignedInt m_status;
};

struct GroupPoint
{
	Int x;
	Int y;
};

struct GroupRegion
{
	GroupPoint lo;
	GroupPoint hi;
	Int width() const { return hi.x - lo.x; }
	Int height() const { return hi.y - lo.y; }
};

struct GroupTextExtentValues
{
	Int height;
	Int width;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void *m_vtable;
	ObjectStatusView *m_statusView;
	char m_pad008[0x250 - 0x008];
	ContainModuleView *m_contain;
	char m_pad254[0x274 - 0x254];
	Object *m_containedBy;
};

struct DrawGroupInfo
{
public:
	char m_pad000[9];
	Bool m_usePlayerColor;
	char m_pad00A[2];
	Int m_colorForText;
	Int m_colorForTextDropShadow;
	Int m_dropShadowOffsetX;
	Int m_dropShadowOffsetY;
	union { Int m_pixelOffsetX; Real m_percentOffsetX; };
	Bool m_usingPixelOffsetX;
	char m_pad021[3];
	union { Int m_pixelOffsetY; Real m_percentOffsetY; };
	Bool m_usingPixelOffsetY;
};
extern DrawGroupInfo *TheDrawGroupInfo;

class DisplayString
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void setColor(Int color, Int dropColor);
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void draw(Int x, Int y, Int xOffset, Int yOffset);
	virtual void getTextExtents(Int *width, Int *height);
};

class DisplayStringManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual DisplayString *getNumeralString(Int number);
};
extern DisplayStringManager *TheDisplayStringManager;

class Rva00273C47Host
{
public:
	virtual void slot00();
	void rva00273C47();
	char m_pad004[0xFC - 4];
	Object *m_object;
	char m_pad100[0x460 - 0x100];
	GroupRegion m_iconRegion;
};

void Rva00273C47Host::rva00273C47()
{
	Object *object = m_object;
	if (object == 0)
		return;

	Player *player = object->getControllingPlayer();
	Int groupNumber = reinterpret_cast<Rva002AA191 *>(player)->rva002AA191(object);
	Int color;
	{
		DrawGroupInfo *colorInfo = TheDrawGroupInfo;
		color = colorInfo->m_usePlayerColor ? player->getPlayerColor() : colorInfo->m_colorForText;
	}
	if (groupNumber <= -1 || groupNumber >= 10)
		return;

	Rva00273C47Host *labelDrawable;
	ContainModuleView *contain;
	if ((object->m_statusView->m_status & 0x2000) != 0 && (contain = object->m_contain) != 0) {
		GroupNodeView *node = contain->slot31();
		if (node == 0)
			return;
		Thing *thing = node->slot70();
		if (thing == 0)
			thing = node->slot68();
		if (thing == 0)
			return;
		labelDrawable = reinterpret_cast<Rva00273C47Host *>(thing->getDrawable());
	} else if (object->m_containedBy != 0 &&
		(object->m_containedBy->m_statusView->m_status & 0x2000) != 0) {
		return;
	} else {
		labelDrawable = this;
	}
	if (labelDrawable == 0)
		return;

	Int x = labelDrawable->m_iconRegion.lo.x;
	Int y = labelDrawable->m_iconRegion.lo.y;
	if (TheDrawGroupInfo->m_usingPixelOffsetX)
		x += TheDrawGroupInfo->m_pixelOffsetX;
	else
		x += m_iconRegion.width() * TheDrawGroupInfo->m_percentOffsetX;
	if (TheDrawGroupInfo->m_usingPixelOffsetY)
		y += TheDrawGroupInfo->m_pixelOffsetY;
	else
		y += m_iconRegion.height() * TheDrawGroupInfo->m_percentOffsetY;

	DisplayString *string = TheDisplayStringManager->getNumeralString(groupNumber);
	GroupTextExtentValues extents;
	string->getTextExtents(&extents.width, &extents.height);
	Int drawX = x - extents.width;
	Int drawY = y - extents.height;
	string->setColor(color, TheDrawGroupInfo->m_colorForTextDropShadow);
	string->draw(drawX, drawY, TheDrawGroupInfo->m_dropShadowOffsetX, TheDrawGroupInfo->m_dropShadowOffsetY);
}
