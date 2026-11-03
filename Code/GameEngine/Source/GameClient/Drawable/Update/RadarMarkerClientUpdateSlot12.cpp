// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?clientUpdate@RadarMarkerClientUpdate@@UAEXXZ, retail 0x004C9CF7, 128 bytes.
// Slot 12 of the vtable 0x00C5EDB8 that the matched RadarMarkerClientUpdate
// ctor 0x004C9BCD installs (15 slots; the next vtable start is 0x00C5EDF8).
// The name is the base-slot name: ZH's ClientUpdateModule adds clientUpdate()
// as its one virtual over DrawableModule, and slot 12 is the only non-default
// slot this class adds; the identity is inferred, not proven.
// With a drawable at +0x08: when the smart marker at +0x0C is still empty
// and TheRadar exists, fills it from TheRadar's slot 12 (returns the smart
// pointer by value, given the module data's +0x08 AsciiString), assigning
// through the rowed Rva004C9B8F::operator= and destroying the temporary
// (unwind funclet 0x007905A2 calls the rowed ??1Rva004C9B8F 0x0004E4E1);
// then hands the drawable's position to the marker through 0x005CB265, a
// folded forwarder to the referent's own slot 3 (pinned here with the
// one-pointer signature this caller gives it).

#include "ascii_string.h"

struct Coord3D;

#include "../../../../Include/GameClient/Drawable.h"

class AnimateWindow;

// 0x005CB265 is the folded body matched as
// ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow; called directly.
class ProcessAnimateWindowSlideFromBottomTimed
{
public:
	virtual bool reverseAnimateWindow(AnimateWindow *window);
};

#include "../../../../Include/GameClient/RadarMarker.h"

class Rva004C9B8F
{
public:
	~Rva004C9B8F()
	{
		if (m_ptr != 0)
			reinterpret_cast<RadarMarker *>(m_ptr)->DeleteReference();
	}
	Rva004C9B8F &operator=(const Rva004C9B8F &other);
	void *get() const { return m_ptr; }
private:
	void *m_ptr;
};

template <int N> class Rva004C9CF7Slots : public Rva004C9CF7Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C9CF7Slots<0>
{
};

class Radar : public Rva004C9CF7Slots<12>
{
public:
	virtual Rva004C9B8F rva004C9CF7Slot12(const char *name) = 0;
};

extern Radar *TheRadar;

#include "../../../../Include/Common/DrawableModule.h"

class __declspec(novtable) RadarMarkerClientUpdateModuleDataBase : public Snapshot
{
public:
	RadarMarkerClientUpdateModuleDataBase() {}
};

class RadarMarkerClientUpdateModuleData : public RadarMarkerClientUpdateModuleDataBase
{
public:
	virtual ~RadarMarkerClientUpdateModuleData();
private:
	friend class RadarMarkerClientUpdate;
	int m_unused04;
	AsciiString m_markerType;
};


class Rva00362EC7 : public DrawableModule
{
public:
	Rva00362EC7(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00362EC7();
};

class RadarMarkerClientUpdate : public Rva00362EC7
{
public:
	RadarMarkerClientUpdate(Thing *thing, const ModuleData *moduleData);
	virtual NameKeyType getModuleNameKey() const;
	virtual void clientUpdate();
private:
	Rva004C9B8F m_marker; // +0x0C
};

// ?clientUpdate@RadarMarkerClientUpdate@@UAEXXZ @0x004C9CF7
void RadarMarkerClientUpdate::clientUpdate()
{
	Drawable *draw = m_drawable;
	if (!draw)
		return;
	if (m_marker.get() == 0)
	{
		if (!TheRadar)
			return;
		const RadarMarkerClientUpdateModuleData *data = (const RadarMarkerClientUpdateModuleData *)m_moduleData;
		m_marker = TheRadar->rva004C9CF7Slot12(data->m_markerType.str());
	}
	((ProcessAnimateWindowSlideFromBottomTimed *)m_marker.get())->ProcessAnimateWindowSlideFromBottomTimed::reverseAnimateWindow((AnimateWindow *)draw->getPosition());
}
