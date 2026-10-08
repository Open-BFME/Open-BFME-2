// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// GameClient's drawable table of contents, after ZH GameClient.cpp
// (findTOCEntryByName, findTOCEntryById, shouldSaveDrawable,
// xferDrawableTOC). GameLogic::xferObjectTOC (GameLogicInit.cpp, 0x00245F79)
// is the same code over the object list.
//
// Target evidence: the TOC list sits at GameClient+0xF4 (both finds and the
// xfer read it there); the xfer walks the drawable list from vslot 35
// (ZH's virtual getDrawableList), next drawable at +0x104, thing template at
// +4 and its name at +0x64; shouldSaveDrawable reads the status bits at
// +0x114 and the object at +0xFC. Callers: GameClient::xfer at 0x0023B5D5
// (name) and 0x0023B68C (id).

#include <list>
#include "ascii_string.h"

class Xfer;
class UnicodeString;
class PooledString;
class Snapshot;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;

// BFME 2's Xfer (as GameLogicInit.cpp): MSVC lays the operator== overloads
// out in reverse, so AsciiString is slot 27, unsigned int 30, unsigned
// short 32.
class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }

private:
	char m_pad000[0x64];
	AsciiString m_name; // +0x64
};

class Object;

enum DrawableStatus
{
	DRAWABLE_STATUS_NO_SAVE = 0x10
};

class Drawable
{
public:
	virtual ~Drawable();

	const ThingTemplate *getTemplate() const { return m_template; }
	const Object *getObject() const { return m_object; }
	Drawable *getNextDrawable() const { return m_nextDrawable; }
	bool testDrawableStatus(DrawableStatus bit) const { return (m_status & bit) != 0; }

private:
	const ThingTemplate *m_template; // +0x04
	char m_pad008[0xFC - 0x08];
	Object *m_object; // +0xFC
	char m_pad100[0x104 - 0x100];
	Drawable *m_nextDrawable; // +0x104
	char m_pad108[0x114 - 0x108];
	unsigned int m_status; // +0x114
};

// The TOC list's clear is the body every {AsciiString, short} list folds to
// (0x00239D49); the ledger names it after this placeholder element.
struct Rva00239D49Element
{
	AsciiString name;
	unsigned short id;
};
typedef _STL::list<Rva00239D49Element> Rva00239D49List;

namespace _STL
{
template<> void _List_base<Rva00239D49Element, allocator<Rva00239D49Element> >::clear();
}

// addTOCEntry (0x0023AB78) is still rowed under its address-named class.
class Rva0023AB78
{
public:
	void rva0023AB78(AsciiString s, unsigned short v);
};

class GameClient
{
public:
	struct DrawableTOCEntry
	{
		AsciiString name;
		unsigned short id;
	};
	typedef _STL::list<DrawableTOCEntry> DrawableTOCList;
	typedef DrawableTOCList::iterator DrawableTOCListIterator;

	virtual ~GameClient();
	virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
	virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08();
	virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
	virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32();
	virtual void v33(); virtual void v34();
	virtual Drawable *getDrawableList(); // vslot 35

	DrawableTOCEntry *findTOCEntryByName(AsciiString name);
	DrawableTOCEntry *findTOCEntryById(unsigned short id);
	void xferDrawableTOC(Xfer *xfer);

private:
	char m_pad004[0xF4 - 0x04];
	DrawableTOCList m_drawableTOC; // +0xF4
};

// Retail 0x00239C5E, 89 bytes.
GameClient::DrawableTOCEntry *GameClient::findTOCEntryByName(AsciiString name)
{
	for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		if ((*it).name == name)
			return &(*it);

	return 0;
}

// Retail 0x002399EB, 37 bytes.
GameClient::DrawableTOCEntry *GameClient::findTOCEntryById(unsigned short id)
{
	for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		if ((*it).id == id)
			return &(*it);

	return 0;
}

// Retail 0x00238F79, 24 bytes; as a file static cl passes the drawable in EAX.
// Retail calls it from GameClient::xfer too (not in this unit yet), so it is
// kept out of line here.
static __declspec(noinline) bool shouldSaveDrawable(const Drawable *draw)
{
	if (draw->testDrawableStatus(DRAWABLE_STATUS_NO_SAVE))
	{
		if (draw->getObject() == 0)
			return false;
	}
	return true;
}

// Retail 0x0023AC36, 347 bytes. As GameLogic::xferObjectTOC, BFME 2 opens
// with Xfer::Version1 instead of xferVersion.
void GameClient::xferDrawableTOC(Xfer *xfer)
{
	xfer->Version1();
	((Rva00239D49List *)&m_drawableTOC)->clear();

	unsigned int tocCount = 0;
	if (xfer->IsStoring())
	{
		AsciiString templateName;
		for (Drawable *draw = getDrawableList(); draw; draw = draw->getNextDrawable())
		{
			if (!shouldSaveDrawable(draw))
				continue;

			templateName = draw->getTemplate()->getName();
			if (findTOCEntryByName(templateName) != 0)
				continue;

			((Rva0023AB78 *)this)->rva0023AB78(draw->getTemplate()->getName(), ++tocCount);
		}
		*xfer == tocCount;
		for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		{
			DrawableTOCEntry *tocEntry = &(*it);
			*xfer == tocEntry->name;
			*xfer == tocEntry->id;
		}
	}
	else
	{
		AsciiString templateName;
		unsigned short id;
		*xfer == tocCount;
		for (unsigned int i = 0; i < tocCount; ++i)
		{
			*xfer == templateName;
			*xfer == id;
			((Rva0023AB78 *)this)->rva0023AB78(templateName, id);
		}
	}
}
