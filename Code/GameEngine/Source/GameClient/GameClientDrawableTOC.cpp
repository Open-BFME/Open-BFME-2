// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// GameClient's drawable table of contents: the save-game list pairing each
// drawable template name with the 16-bit id stored in its place.
// Donor: ZH GameEngine/Source/GameClient/GameClient.cpp (shouldSaveDrawable,
// findTOCEntryByName, findTOCEntryById, addTOCEntry, xferDrawableTOC), same
// control flow.
// Target evidence for the layout: xferDrawableTOC (0x0023AC36) clears the list
// at this+0xF4 through the folded list clear 0x00239D49, walks the drawables
// from virtual slot 35 (+0x8C, ZH getDrawableList) along next at +0x104, takes
// each template (+4) name (+0x64), stores the count (Xfer slot 30) and each
// node's name (+8, slot 27) and id (+0xC, slot 32). The name search 0x00239C5E
// (StringBase compare 0x000069D6 per node) and the append 0x0023AB78 (list
// push_back 0x0023A014) take the same this; the id search 0x002399EB, called
// from GameClient::xfer at 0x0023B68C, walks the same list for node+0xC. shouldSaveDrawable (0x00238F79)
// tests status bit 0x10 at +0x114 and the object pointer at +0xFC, and is
// called with the drawable in EAX: a TU-local static, kept out of line
// (__declspec(noinline)) as retail calls it.
// BFME 2 opens with the out-of-line Xfer::Version1 (0x000053EE) instead of
// xferVersion, as GameLogic::xferObjectTOC does.
#include <list>
#include "ascii_string.h"

// The TOC list's out-of-line members fold onto addresses other lists already
// name, so its allocator is a placeholder class (as GameLogic's ObjectTOC list).
template <class T> class Rva0023AC36Allocator : public _STL::allocator<T>
{
};

class Xfer;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

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
	const AsciiString &getName(void) const { return m_name; }

private:
	char m_pad00[0x64];
	AsciiString m_name;
};

class Object;

enum DrawableStatus
{
	DRAWABLE_STATUS_NO_SAVE = 0x10
};

class Drawable
{
public:
	const ThingTemplate *getTemplate(void) const { return m_template; }
	Object *getObject(void) const { return m_object; }
	Drawable *getNextDrawable(void) const { return m_nextDrawable; }
	bool testDrawableStatus(DrawableStatus bit) const { return (m_status & bit) != 0; }

private:
	void *m_vtbl;
	const ThingTemplate *m_template;                                     // +0x04
	char m_pad08[0xfc - 0x08];
	Object *m_object;                                                    // +0xFC
	char m_pad100[0x104 - 0x100];
	Drawable *m_nextDrawable;                                            // +0x104
	char m_pad108[0x114 - 0x108];
	unsigned int m_status;                                               // +0x114
};

class GameClient
{
public:
	// ZH GameClient.h DrawableTOCEntry; retail list node: name at +8, id at +0xC.
	struct DrawableTOCEntry
	{
		AsciiString name;
		unsigned short id;
	};
	typedef _STL::list<DrawableTOCEntry, Rva0023AC36Allocator<DrawableTOCEntry> > DrawableTOCList;
	typedef DrawableTOCList::iterator DrawableTOCListIterator;

	virtual ~GameClient();
	virtual void vf01();
	virtual void vf02();
	virtual void vf03();
	virtual void vf04();
	virtual void vf05();
	virtual void vf06();
	virtual void vf07();
	virtual void vf08();
	virtual void vf09();
	virtual void vf10();
	virtual void vf11();
	virtual void vf12();
	virtual void vf13();
	virtual void vf14();
	virtual void vf15();
	virtual void vf16();
	virtual void vf17();
	virtual void vf18();
	virtual void vf19();
	virtual void vf20();
	virtual void vf21();
	virtual void vf22();
	virtual void vf23();
	virtual void vf24();
	virtual void vf25();
	virtual void vf26();
	virtual void vf27();
	virtual void vf28();
	virtual void vf29();
	virtual void vf30();
	virtual void vf31();
	virtual void vf32();
	virtual void vf33();
	virtual void vf34();
	virtual Drawable *getDrawableList(void);                            // slot 35 (+0x8C)

	DrawableTOCEntry *findTOCEntryByName(AsciiString name);
	DrawableTOCEntry *findTOCEntryById(unsigned short id);
	void addTOCEntry(AsciiString name, unsigned short id);
	void xferDrawableTOC(Xfer *xfer);

private:
	char m_pad04[0xf4 - 0x04];
	DrawableTOCList m_drawableTOC;                                      // +0xF4
};

// Retail's clear is the shared fold at 0x00239D49; emit no copy of it here.
namespace _STL
{
template<> void _List_base<GameClient::DrawableTOCEntry, Rva0023AC36Allocator<GameClient::DrawableTOCEntry> >::clear();
}

static __declspec(noinline) bool shouldSaveDrawable(const Drawable *draw)
{
	if (draw->testDrawableStatus(DRAWABLE_STATUS_NO_SAVE))
	{
		if (draw->getObject() == 0)
			return false;
	}
	return true;
}

GameClient::DrawableTOCEntry *GameClient::findTOCEntryByName(AsciiString name)
{
	for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		if ((*it).name == name)
			return &(*it);
	return 0;
}

GameClient::DrawableTOCEntry *GameClient::findTOCEntryById(unsigned short id)
{
	for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it)
		if ((*it).id == id)
			return &(*it);
	return 0;
}

void GameClient::addTOCEntry(AsciiString name, unsigned short id)
{
	DrawableTOCEntry tocEntry;
	tocEntry.name = name;
	tocEntry.id = id;
	m_drawableTOC.push_back(tocEntry);
}

void GameClient::xferDrawableTOC(Xfer *xfer)
{
	xfer->Version1();
	m_drawableTOC.clear();
	unsigned int tocCount = 0;
	if (xfer->IsStoring()) {
		AsciiString templateName;
		for (Drawable *draw = getDrawableList(); draw; draw = draw->getNextDrawable()) {
			if (!shouldSaveDrawable(draw))
				continue;
			templateName = draw->getTemplate()->getName();
			if (findTOCEntryByName(templateName) != 0)
				continue;
			addTOCEntry(draw->getTemplate()->getName(), ++tocCount);
		}
		*xfer == tocCount;
		for (DrawableTOCListIterator it = m_drawableTOC.begin(); it != m_drawableTOC.end(); ++it) {
			DrawableTOCEntry *tocEntry = &(*it);
			*xfer == tocEntry->name;
			*xfer == tocEntry->id;
		}
	} else {
		AsciiString templateName;
		unsigned short id;
		*xfer == tocCount;
		for (unsigned int i = 0; i < tocCount; ++i) {
			*xfer == templateName;
			*xfer == id;
			addTOCEntry(templateName, id);
		}
	}
}
