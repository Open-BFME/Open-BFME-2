// cl: /DNDEBUG /MD /EHsc
// ??1Rva005F0584@@UAE@XZ retail 0x005F0584 75B
// Virtual MI dtor (through the secondary base) reached by its scalar deleting dtor
// 0x005F06D3. Own vftables at +0 and +4; notifies the listener at +0x14
// through its slot 0 with this, then the two inline base dtors restore their
// vftables (0x00BC6F20 at +4, 0x00BFBCBC at +0).
namespace StrategicHUD { class RegionDetailsStructuresMovieClip { public: class Impl { public: class IconSlot; }; }; }
class Image;


class Rva005F0584Listener
{
public:
	virtual void onRelease(StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot *owner);
};

#include "../../Include/GameClient/Rva005F0584Base0.h"

class Rva005F0584Base1
{
public:
	virtual ~Rva005F0584Base1() {}
};

class StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot : public Rva005F0584Base0, public Rva005F0584Base1
{
public:
	virtual ~IconSlot();
	 virtual void slot01(int);
 virtual int slot02() const;
 virtual void DoSetState(int);
 virtual const Image *slot04() const;
 virtual void slot05(const Image *);
 virtual const Image *slot06() const;
 virtual void slot07(const Image *);
 virtual unsigned char slot08() const;
 virtual void DoShowProgress(int, int);
 virtual void DoHideProgress();
private:
	char m_pad08[0x14 - 0x08];
	Rva005F0584Listener *m_listener; // +0x14
};

StrategicHUD::RegionDetailsStructuresMovieClip::Impl::IconSlot::~IconSlot()
{
	if (m_listener)
		m_listener->onRelease(this);
}
