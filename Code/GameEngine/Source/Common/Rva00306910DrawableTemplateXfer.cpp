// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// ?xfer@Rva00306910@@QAEXPAVXfer@@@Z
// Retail 0x00306910..0x00306A36 (294 bytes).
// Xfers a {Drawable * at +0 / const ThingTemplate * at +4} pair by id and
// name: returns at once in light-CRC mode (Xfer slot 4) else writes version 1
// (rowed Xfer::Version1). Loading reads an ObjectID and a template name then
// resolves the drawable through TheGameLogic->findObjectByID and
// Thing::getDrawable and the template through TheThingFactory->findTemplate
// when the name is not empty. Saving writes the drawable's object id (+0xFC
// object / +0x74 id; 0 when absent) and the template name (+0x64; empty when
// absent).
// Evidence (target): rowed callees Xfer::Version1 0x000053EE
// XferObjectID 0x003060B2 GameLogic::findObjectByID 0x00049DC5
// Thing::getDrawable 0x005508E2 StringBase<char> ctor(const char *) 0x00037BA0
// / set 0x000366F0 / releaseBuffer 0x00036410; pinned
// ThingFactory::findTemplate 0x002D06CA; globals TheGameLogic 0x009FE78C and
// TheThingFactory 0x009FF000; Xfer slots 1/2/4/27 (IsLoading IsStoring
// IsLightCRC xferAsciiString as in ObjectFilterCollectionXfer.cpp) and
// ThingTemplate name +0x64 as there. WorldBuilder 0x00DF6840 has the same
// calls and branch structure (unnamed). Owner class identity is unproven;
// names are address-derived.
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
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
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual Xfer &xferAsciiString(AsciiString *value);

	void Version1();
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
public:
	ObjectID getID() const { return m_id; }
private:
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
};

class Drawable
{
public:
	Object *getObject() const { return m_object; }
private:
	unsigned char m_pad00[0xFC];
	Object *m_object; // +0xFC
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
private:
	unsigned char m_pad00[0x64];
	AsciiString m_name; // +0x64
};

extern GameLogic *TheGameLogic;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;

class Rva00306910
{
public:
	void xfer(Xfer *xfer);
private:
	Drawable *m_drawable;               // +0x00
	const ThingTemplate *m_template;    // +0x04
};

void Rva00306910::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	if (xfer->IsLoading())
	{
		ObjectID id = INVALID_OBJECT_ID;
		AsciiString name("");
		XferObjectID(xfer, &id);
		xfer->xferAsciiString(&name);
		if (id != INVALID_OBJECT_ID)
		{
			Object *object = TheGameLogic->findObjectByID(id);
			if (object)
				m_drawable = object->getDrawable();
		}
		if (!name.isEmpty())
			m_template = TheThingFactory->findTemplate(name);
	}
	else if (xfer->IsStoring())
	{
		ObjectID id = INVALID_OBJECT_ID;
		if (m_drawable && m_drawable->getObject())
			id = m_drawable->getObject()->getID();
		AsciiString name("");
		if (m_template)
			name = m_template->getName();
		XferObjectID(xfer, &id);
		xfer->xferAsciiString(&name);
	}
}
