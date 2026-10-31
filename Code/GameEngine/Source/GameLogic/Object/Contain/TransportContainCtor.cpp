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
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
class Thing;
class ModuleData;
class Object;

#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString&);
template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString*, const AsciiString&, const __false_type&, size_t, bool);
}

class B0
{
public:
	virtual void b0();
	virtual void onCapture(int a1, int a2) = 0;
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char m_pad[12]; };
class B3 { public: virtual void b3(); virtual void onCapture(int a1, int a2) = 0; };
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

class ThingTemplate;
class PayloadContainView;

// Retail's TransportExtra vftable (0x00C1C780) holds __purecall in slot 0;
// TransportContain's (0x00C47834) holds createPayloadMember (0x00466FE0).
class TransportExtra { public: virtual Object *createPayloadMember(const ThingTemplate *what, PayloadContainView *contain, Object *parent, const char *name, int index) = 0; };

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
	virtual Object *createPayloadMember(const ThingTemplate *what, PayloadContainView *contain, Object *parent, const char *name, int index);
	TransportContain(Thing *thing, const ModuleData *moduleData);
	virtual void onCapture(int a1, int a2);
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
