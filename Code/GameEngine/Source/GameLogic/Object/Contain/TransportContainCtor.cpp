// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0TransportContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00468559,
// 254 bytes (pinned; instance factory 0x0024B861). Over the rowed OpenContain
// ctor 0x004649F8 (its dtor 0x00464692 is state 0 of retail's unwind map):
// the +0xFC interface base installs its own vtable (0x00C1C780) and then the
// class installs all ten of its vtables; four BFME2 fields at +0x100..+0x10C
// are cleared; and the name of every 12-byte entry of the module data's
// vector at +0x180 is copied into the AsciiString vector at +0x110 (state 1)
// through the pinned push_back 0x0002DBE6. OpenContain's nine polymorphic
// subobjects (+0x00/+0x0C/+0x10/+0x20..+0x34) are positional stand-ins; the
// Zero Hour body (clearing extra slots and exit frame) does not carry over.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
class Thing;
class ModuleData;
class Object;

#include "ascii_string.h"

class B0 { public: virtual void b0(); protected: const ModuleData *m_moduleData; Object *m_object; };
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };
class B3 { public: virtual void b3(); };
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char m_pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4, public B5, public B6, public B7, public B8
{
public:
	OpenContain(Thing *thing, const ModuleData *moduleData);
	virtual ~OpenContain();
};

class TransportExtra { public: virtual void transportExtra(); };

struct TransportPayloadEntry
{
	AsciiString m_name;
	int m_04;
	int m_08;
};

class TransportContainModuleData
{
public:
	unsigned char m_pad[0x180];
	_STL::vector<TransportPayloadEntry> m_payload;	// +0x180
};

class TransportContain : public OpenContain, public TransportExtra
{
public:
	TransportContain(Thing *thing, const ModuleData *moduleData);
	virtual ~TransportContain(); // declared only; defined in TransportContainDtor.cpp (0x00467E61)
	const TransportContainModuleData *getTransportContainModuleData() const { return (const TransportContainModuleData *)m_moduleData; }
private:
	int m_100;
	int m_104;
	int m_108;
	bool m_10C;
	_STL::vector<AsciiString> m_names;		// +0x110
};

TransportContain::TransportContain(Thing *thing, const ModuleData *moduleData)
	: OpenContain(thing, moduleData)
{
	const _STL::vector<TransportPayloadEntry> &payload = getTransportContainModuleData()->m_payload;
	m_100 = 0;
	m_104 = 0;
	m_108 = 0;
	m_10C = false;
	for (unsigned int i = 0; i < payload.size(); ++i)
		m_names.push_back(payload[i].m_name);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?b1@B1@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?b6@B6@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
