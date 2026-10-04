// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
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

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class Rva005CB265
{
public:
	void rva005CB265(const Coord3D *pos);
};

class Rva002D76BB
{
public:
	void release();
};

class Rva004C9B8F
{
public:
	~Rva004C9B8F()
	{
		if (m_ptr != 0)
			reinterpret_cast<Rva002D76BB *>(m_ptr)->release();
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

struct RadarMarkerClientUpdateModuleData
{
	unsigned char m_pad00[0x08];
	AsciiString m_name; // +0x08
};

class ModuleData;

class DrawableModule
{
public:
	virtual ~DrawableModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	BFMERopeDrawable *m_drawable; // +0x08
};

class ClientUpdateModule : public DrawableModule
{
public:
	virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void clientUpdate() = 0;
};

class RadarMarkerClientUpdate : public ClientUpdateModule
{
public:
	virtual void clientUpdate();
private:
	Rva004C9B8F m_marker; // +0x0C
};

// ?clientUpdate@RadarMarkerClientUpdate@@UAEXXZ @0x004C9CF7
void RadarMarkerClientUpdate::clientUpdate()
{
	BFMERopeDrawable *draw = m_drawable;
	if (!draw)
		return;
	if (m_marker.get() == 0)
	{
		if (!TheRadar)
			return;
		const RadarMarkerClientUpdateModuleData *data = (const RadarMarkerClientUpdateModuleData *)m_moduleData;
		m_marker = TheRadar->rva004C9CF7Slot12(data->m_name.str());
	}
	((Rva005CB265 *)m_marker.get())->rva005CB265(draw->getPosition());
}
