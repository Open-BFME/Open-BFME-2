// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva002775C9@Drawable@@QAEXPAUCoord3D@@@Z retail 0x002775C9..0x00277669
// (160 bytes ret 4). Fills the anchor point the veterancy icons are drawn
// above (caller Drawable::drawVeterancy 0x00277DB4). WorldBuilder twin
// 0xCAAFA0 has the same shape: when the template carries KindOf bit 0x6D
// (template +0x108 bit field) and the drawable has an object whose +0x250
// module (+0x258 in WB) answers vtable +0x7C with an interface that fills
// the point through vtable +0x22C the module wins. Otherwise the point is
// the drawable position (0x00276470) raised by the template height
// (+0x538; 10.0 without a template) and by the object's geometry height
// (GeometryInfo at object +0xA8 0x006BD830). Slot and field names are not
// recovered; the method name stays address-derived as pinned.
#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
typedef bool Bool;
typedef unsigned char UnsignedByte;

class GeometryInfo
{
public:
	Real rva006BD830(void) const;
};

class AnchorInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
	virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99();
	virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103();
	virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107();
	virtual void slot108(); virtual void slot109(); virtual void slot110(); virtual void slot111();
	virtual void slot112(); virtual void slot113(); virtual void slot114(); virtual void slot115();
	virtual void slot116(); virtual void slot117(); virtual void slot118(); virtual void slot119();
	virtual void slot120(); virtual void slot121(); virtual void slot122(); virtual void slot123();
	virtual void slot124(); virtual void slot125(); virtual void slot126(); virtual void slot127();
	virtual void slot128(); virtual void slot129(); virtual void slot130(); virtual void slot131();
	virtual void slot132(); virtual void slot133(); virtual void slot134(); virtual void slot135();
	virtual void slot136(); virtual void slot137(); virtual void slot138();
	virtual Bool getAnchorPosition(Coord3D *pos); // +0x22C
};

class AnchorModule
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual AnchorInterface *getAnchorInterface(); // +0x7C
};

class Object
{
public:
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
	AnchorModule *getAnchorModule() const { return m_anchorModule; }

private:
	char m_pad000[0xa8];
	GeometryInfo m_geometryInfo; // +0xA8
	char m_pad0a9[0x250 - 0xa9];
	AnchorModule *m_anchorModule; // +0x250
};

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(int bit) const { return (m_kindOf[bit >> 3] & (1 << (bit & 7))) != 0; }
	Real getHeight() const { return m_height; }

private:
	char m_pad000[0x108];
	UnsignedByte m_kindOf[0x538 - 0x108]; // +0x108
	Real m_height; // +0x538
};

class Rva00276470Drawable
{
public:
	const Coord3D *rva00276470() const;
};

class Drawable
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	void rva002775C9(Coord3D *pos);

private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	char m_pad008[0xfc - 8];
	Object *m_object; // +0xFC
};

void Drawable::rva002775C9(Coord3D *pos)
{
	Object *obj = m_object;
	if (getTemplate()->isKindOf(0x6d) && obj != 0)
	{
		if (obj->getAnchorModule() != 0 && obj->getAnchorModule()->getAnchorInterface() != 0
			&& obj->getAnchorModule()->getAnchorInterface()->getAnchorPosition(pos))
			return;
	}
	*pos = *reinterpret_cast<const Rva00276470Drawable *>(this)->rva00276470();
	Real height = 10.0f;
	const ThingTemplate *tmpl = getTemplate();
	if (tmpl != 0)
		height = tmpl->getHeight();
	pos->z += height;
	if (obj != 0)
		pos->z += obj->getGeometryInfo().rva006BD830();
}
