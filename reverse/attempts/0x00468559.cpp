// ??0TransportContain@@QAE@PAVThing@@PBVModuleData@@@Z
// partial score=0.21 date=2026-09-23
// cl: /O1 /DNDEBUG /MD /GX /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0TransportContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00468559,
// 254 bytes. TransportContain behavior over the rowed OpenContain base
// (0x004649F8, size 0xFC): re-stores the primary vtable (compiler install
// through the ??_7 pin at 0x00C44278, whose slot2 is the rowed name getter
// 0x00467F26) plus seven secondary table slots, fills a vector<AsciiString>
// at +0x110 from the ModuleData passenger range at +0x180, and zeroes the
// int slots. The instance factory at 0x0024B861 news 0x11C and calls this
// ctor as sole caller. Shape follows OpenContainCtor (opaque virtual base
// with declared-only dtor, init-list member order, EH states over base
// plus vector) over CitadelSlaughterHordeContainModuleDataCtor (AsciiString
// vector through the rowed _Vector_base fold, push_back through its pin).

#include <vector>

class Thing;
class ModuleData;
class Object;

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

// Passenger range block at ModuleData+0x180: start/finish byte pointers
// over 12-byte entries whose heads push as AsciiString (the push_back
// callee at 0x002DBE6 is the AsciiString instantiation, so the callee
// treats each pushed address as one).
struct PassengerRangeBlock
{
	unsigned char m_pad[0x180];
	const char *m_start;
	const char *m_finish;
};

// Opaque OpenContain base; 2-arg ctor resolves to its row. Virtual plus
// declared-only dtor (no code) so the base call takes this undisplaced
// and arms EH state 0; the secondary slots below stand in for the
// inherited interface vptrs this ctor re-stores.
class OpenContain
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);
	virtual ~OpenContain();

protected:
	const ModuleData *m_moduleData; // +4
	Object *m_object; // +8
	const void *m_table0C; // +0x0C
	const void *m_table10; // +0x10
	unsigned char m_pad14[0x20 - 0x14];
	const void *m_table20; // +0x20
	const void *m_table24; // +0x24
	const void *m_table28; // +0x28
	const void *m_table2C; // +0x2C
	const void *m_table30; // +0x30
	const void *m_table34; // +0x34
	unsigned char m_pad38[0xFC - 0x38];
};

class TransportContain : public OpenContain
{
public:
	TransportContain(Thing *thing, const ModuleData *moduleData);
	virtual ~TransportContain();

private:
	// +0xFC slot written twice (init then body); the union defeats the
	// dead-store elimination that folds the first write.
	union FcSlot {
		FcSlot(const void *p) : m_tableFC(p) {}
		const void *m_tableFC;
		unsigned int m_valueFC;
	};
	FcSlot m_fc; // +0xFC
	int m_int100; // +0x100
	int m_int104; // +0x104
	int m_int108; // +0x108
	unsigned char m_byte10C; // +0x10C
	_STL::vector<AsciiString> m_passengers; // +0x110, UpgradeForRingEntry
};

// ??0TransportContain@@QAE@PAVThing@@PBVModuleData@@@Z @0x468559
TransportContain::TransportContain(Thing *thing, const ModuleData *moduleData)
	: OpenContain(thing, moduleData)
	, m_fc(reinterpret_cast<const void *>(0x00C1C780))
{
	m_table0C = reinterpret_cast<const void *>(0x00C441B8);
	m_table10 = reinterpret_cast<const void *>(0x00C441A8);
	m_table20 = reinterpret_cast<const void *>(0x00C44030);
	m_table24 = reinterpret_cast<const void *>(0x00C46064);
	m_table28 = reinterpret_cast<const void *>(0x00C46F78);
	m_table2C = reinterpret_cast<const void *>(0x00C58790);
	m_table30 = reinterpret_cast<const void *>(0x00C43FFC);
	m_table34 = reinterpret_cast<const void *>(0x00C45CEC);
	m_fc.m_tableFC = reinterpret_cast<const void *>(0x00C47834);
	m_int100 = 0;
	m_int104 = 0;
	m_int108 = 0;
	m_byte10C = 0;
	const PassengerRangeBlock *passengers =
		reinterpret_cast<const PassengerRangeBlock *>(m_moduleData);
	unsigned int index = 0;
	if ((unsigned int)((passengers->m_finish - passengers->m_start) / 12) > 0) {
		int offset = 0;
		do {
			m_passengers.push_back(
				*reinterpret_cast<const AsciiString *>(passengers->m_start + offset));
			++index;
			offset += 12;
		} while (index < (unsigned int)((passengers->m_finish - passengers->m_start) / 12));
	}
}
