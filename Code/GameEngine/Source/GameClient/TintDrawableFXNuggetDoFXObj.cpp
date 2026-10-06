// cl: /DNDEBUG /MD
//
// ?doFXObj@TintDrawableFXNugget@@UBEXPBVObject@@0@Z retail 0x001E09D8 99B
// Evidence: chain lane; calls 0x00271779 which this session landed; vtable slot 2 of 0x007DD8E0 TintDrawableFXNugget; BFME1 donor TintDrawableFXNugget_doFXObj_Thunk.cpp doFXObj with getDrawable plus status 0x20 plus applyTint RGB times freq amp; retail status at +0x118; caller none.
typedef float Real;
typedef unsigned int UnsignedInt;
struct RGBColor00271779 {
	Real red;
	Real green;
	Real blue;
};
typedef RGBColor00271779 RGBColor;

class Rva00271779
{
public:
	void rva00271779(RGBColor00271779 color, int preColorTime,
		int postColorTime, int sustainedColorTime, Real frequency, Real amplitude);
};

class Drawable {
public:
	unsigned char m_pad[0x118];
	UnsignedInt m_status;
};
class Object {
public:
	Drawable *getDrawable() const;
};
class TintDrawableFXNugget {
public:
	virtual void v00();
	virtual void doFXPos(const void *, const void *, Real, const void *) const;
	virtual void doFXObj(const Object *primary, const Object *) const;
private:
	unsigned char m_pad[0x144];
	RGBColor m_color;
	UnsignedInt m_preColorTime;
	UnsignedInt m_postColorTime;
	UnsignedInt m_sustainedColorTime;
	Real m_frequency;
	Real m_amplitude;
};
void TintDrawableFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (primary && primary->getDrawable()) {
		Drawable *tintDrawable = primary->getDrawable();
		tintDrawable->m_status |= 0x20;
		((Rva00271779 *)primary->getDrawable())->rva00271779(m_color,
			(int)m_preColorTime, (int)m_postColorTime,
			(int)m_sustainedColorTime, m_frequency, m_amplitude);
	}
}
