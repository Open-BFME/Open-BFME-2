// cl: /O1 /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?Rva00314C3E@Rva008FCA3@@UAEPBVImage@@PBD@Z, retail 0x00314C3E, 85 bytes.
// Virtual slot 71 (offset 0x11C) of vtable 0x007C7C90 (class of rowed
// ??1Rva008FCA3 at 0x0008FCA3 with ??_G at 0x0008FF22). Returns null when
// TheMappedImageCollection (0x009FF078) is null, else looks up the name in
// that collection through rowed StringBase<char> ctor 0x00037BA0, rowed
// findImageByName 0x002D92F6 and pinned StringBase dtor 0x00036410 with EH
// states 0/-1. Shape follows INI::parseMappedImage (same three callees
// plus null-collection guard). Honest address name: slot index is the proof.
class Image;

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	~StringBase();

private:
	StringBase(const T *s);
	T *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const char *s) : StringBase<char>(s) {}
};

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

class Rva008FCA3
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual const Image *Rva00314C3E(const char *name) = 0;
};

const Image *Rva008FCA3::Rva00314C3E(const char *name)
{
	if (TheMappedImageCollection != 0)
	{
		AsciiString str(name);
		const Image *img = TheMappedImageCollection->findImageByName(str);
		return img;
	}
	else
		return 0;
}
