// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?xfer@Rva004EED02@@UAEXPAVXfer@@@Z, retail 0x004EF039 (598 bytes). Slot 28
// of the vtable 0x00862A60 whose deleting destructor is the rowed
// ??_GRva004EED02 0x004EF28F (slot 25; slot 18 the rowed rva004EE260 with a
// LivingWorldBattle argument). The snapshot xfer, version 7 (minimum 1).
// Target evidence (callees all rowed or pinned):
//  - nothing under CRC; when storing, the +0x40 list first gets
//    TheLivingWorldLogic +0xFC (rowed vector push_back 0x004DFCB0);
//  - +0x28 through the pinned 0x004EE9E9; the +0x34 +0x40 +0x4C lists
//    through 0x0040E269; the +0x58 bool vector through 0x0060C253;
//  - +0x6C as a time stamp: when storing with +0x70 set it is written
//    relative to the CRT time() (+0x6C - +0x70 + now);
//  - ints +0x78, +0x7C (version 6), five at +0x80, +0x94, +0x98; the
//    template count map +0x9C (rowed xferThingTemplateCountMap 0x0055AC77);
//    ints +0xA8 +0xAC +0xB0; +0xE0 +0xE4 (version 4, else a dummy int read
//    and both cleared); ints +0xE8 +0xEC +0xF0; version 3: unsigned +0x74,
//    count maps +0xB4 +0xC0 +0xCC, ints +0xD8 +0xDC; the player ID +0xF4
//    (rowed XferLivingWorldPlayerID 0x002034C4); version 7 bool +0xF8, else
//    cleared.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

extern "C" __declspec(dllimport) long __cdecl time(long *timer);

namespace _STL
{
template <class T> class allocator;
template <class T> struct less;
template <class T1, class T2> struct pair;
template <class T, class A> class vector
{
public:
	void push_back(const T &value);
private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
template <class K, class V, class C, class A> class map
{
private:
	void *m_header;
	UnsignedInt m_count;
	Int m_compare;
};
}

class ModuleData;
struct TemplateCountKey;

typedef _STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > Rva004EED02List;
typedef _STL::vector<bool, _STL::allocator<bool> > Rva004EED02BoolList;
typedef _STL::map<TemplateCountKey, Int, _STL::less<TemplateCountKey>,
	_STL::allocator<_STL::pair<const TemplateCountKey, Int> > > Rva004EED02CountMap;

struct XferVersion
{
	UnsignedByte m_first;
	UnsignedByte m_version;
	UnsignedByte m_pad[2];
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading(); // +0x04
	virtual Bool isStoring(); // +0x08
	virtual Bool isCRC(); // +0x0C
	virtual void slot10(); virtual void slot14(); virtual void slot18();
	virtual void slot1C(); virtual void slot20(); virtual void slot24();
	virtual void xferVersion(XferVersion *version); // +0x28
	virtual void slot2C(); virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C(); virtual void slot40();
	virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58();
	virtual void slot5C(); virtual void slot60(); virtual void slot64();
	virtual void slot68(); virtual void slot6C(); virtual void slot70();
	virtual void slot74();
	virtual void xferUnsignedInt(UnsignedInt *value); // +0x78
	virtual void xferInt(Int *value); // +0x7C
	virtual void slot80(); virtual void slot84(); virtual void slot88();
	virtual void slot8C();
	virtual void xferBool(Bool *value); // +0x90
};

class Xfer0051FFF5;
void Rva004EE9E9(Xfer0051FFF5 *xfer, void *data);
void Rva0040E269(Xfer0051FFF5 *xfer, void *data);
Xfer *Rva0060C253Xfer(Xfer *xfer, Rva004EED02BoolList *list);
void xferThingTemplateCountMap(Xfer *xfer, Rva004EED02CountMap *map);
void XferLivingWorldPlayerID(Xfer *xfer, Int *id);

class LivingWorldLogic
{
public:
	unsigned char m_pad000[0xFC];
	const ModuleData *m_FC; // +0xFC
};

extern LivingWorldLogic *TheLivingWorldLogic;

class Rva004EED02
{
public:
	virtual void xfer(Xfer *xfer);
private:
	unsigned char m_pad004[0x28 - 0x04];
	unsigned char m_28[0x0C]; // +0x28
	Rva004EED02List m_34; // +0x34
	Rva004EED02List m_40; // +0x40
	Rva004EED02List m_4C; // +0x4C
	Rva004EED02BoolList m_58; // +0x58
	unsigned char m_pad64[0x6C - 0x64];
	UnsignedInt m_timeStamp; // +0x6C
	UnsignedInt m_timeBase; // +0x70
	UnsignedInt m_74; // +0x74
	Int m_78; // +0x78
	Int m_7C; // +0x7C
	Int m_80[5]; // +0x80
	Int m_94; // +0x94
	Int m_98; // +0x98
	Rva004EED02CountMap m_9C; // +0x9C
	Int m_A8; // +0xA8
	Int m_AC; // +0xAC
	Int m_B0; // +0xB0
	Rva004EED02CountMap m_B4; // +0xB4
	Rva004EED02CountMap m_C0; // +0xC0
	Rva004EED02CountMap m_CC; // +0xCC
	Int m_D8; // +0xD8
	Int m_DC; // +0xDC
	Int m_E0; // +0xE0
	Int m_E4; // +0xE4
	Int m_E8; // +0xE8
	Int m_EC; // +0xEC
	Int m_F0; // +0xF0
	Int m_playerID; // +0xF4
	Bool m_F8; // +0xF8
};

void Rva004EED02::xfer(Xfer *xfer)
{
	XferVersion version;
	version.m_first = 1;
	version.m_version = 7;
	xfer->xferVersion(&version);
	if (xfer->isCRC())
		return;

	if (xfer->isStoring() && !xfer->isCRC())
	{
		const ModuleData *current = TheLivingWorldLogic->m_FC;
		m_40.push_back(current);
	}

	Rva004EE9E9((Xfer0051FFF5 *)xfer, m_28);
	Rva0040E269((Xfer0051FFF5 *)xfer, &m_34);
	Rva0040E269((Xfer0051FFF5 *)xfer, &m_40);
	Rva0040E269((Xfer0051FFF5 *)xfer, &m_4C);
	Rva0060C253Xfer(xfer, &m_58);

	if (!xfer->isCRC())
	{
		if (xfer->isStoring() && m_timeBase != 0)
		{
			UnsignedInt stamp = time(0) + (m_timeStamp - m_timeBase);
			xfer->xferUnsignedInt(&stamp);
		}
		else
		{
			xfer->xferUnsignedInt(&m_timeStamp);
		}
	}

	xfer->xferInt(&m_78);
	if (version.m_version >= 6)
		xfer->xferInt(&m_7C);
	for (Int i = 0; i < 5; ++i)
		xfer->xferInt(&m_80[i]);
	xfer->xferInt(&m_94);
	xfer->xferInt(&m_98);
	xferThingTemplateCountMap(xfer, &m_9C);
	xfer->xferInt(&m_A8);
	xfer->xferInt(&m_AC);
	xfer->xferInt(&m_B0);
	if (version.m_version >= 4)
	{
		xfer->xferInt(&m_E0);
		xfer->xferInt(&m_E4);
	}
	else
	{
		Int unused = 0;
		xfer->xferInt(&unused);
		m_E0 = 0;
		m_E4 = 0;
	}
	xfer->xferInt(&m_E8);
	xfer->xferInt(&m_EC);
	xfer->xferInt(&m_F0);
	if (version.m_version >= 3)
	{
		xfer->xferUnsignedInt(&m_74);
		xferThingTemplateCountMap(xfer, &m_B4);
		xferThingTemplateCountMap(xfer, &m_C0);
		xferThingTemplateCountMap(xfer, &m_CC);
		xfer->xferInt(&m_D8);
		xfer->xferInt(&m_DC);
	}
	XferLivingWorldPlayerID(xfer, &m_playerID);
	if (version.m_version >= 7)
		xfer->xferBool(&m_F8);
	else
		m_F8 = false;
}
