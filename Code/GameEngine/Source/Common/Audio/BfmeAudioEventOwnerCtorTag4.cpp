// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /EHsc /MD
#include "Common/BfmeAudioEventPrefix136.h"
// ??0Rva002DA5D3@@QAE@ABUOpaqueRefElement4@@H@Z, RVA 0x002DA5D3 size 126.
// Owner-tag ctor sibling of 0x002DA461 (tag 2/object) and 0x002DA4DB
// (tag 1/drawable): same vtable 0x00803908, same shared initializer
// rva002D96D3, m_int30=1, m_int38=4 when id != 0 else m_int34=0, then
// position worker rva002DA1CC. Evidence: abuts rowed 0x002DA4DB in the
// same page; identical prolog/zeros/EH shape; unblocks 5 callers
// 0x003FDD41/0x003FDDAC/0x003FDF1B/0x003FDF8B/0x003FDFFB.
// Name: Bfme (ref,int) spelling already rowed at 0x002D97D6, so this uses
// the honest TU-local Rva class with identical layout; calls go through
// BfmeAudioEventPrefix136 by cast so they mangle to the rowed names.
// Opaque 32-bit owner-ID ABI view for the tag-3 constructor. Its original
// application type is unknown; the distinct spelling separates native overloads.
enum Rva002DA555Id { Rva002DA555Id_Zero = 0 };

struct Rva002DA5D3
{
	Rva002DA5D3(const OpaqueRefElement4 &, int);
	Rva002DA5D3(const OpaqueRefElement4 &, Rva002DA555Id);
	virtual ~Rva002DA5D3();
	AsciiString m_string04;
	BfmePoolRef08 m_pool08;
	int m_int0C;
	BfmePoolRef10 m_pool10;
	int m_int14;
	int m_int18;
	AsciiString m_string1C;
	AsciiString m_string20;
	float m_f24;
	float m_f28;
	float m_f2C;
	int m_int30;
	int m_int34;
	int m_int38;
	BfmeEventPositionView m_position;
	unsigned char m_b48;
	unsigned char m_b49;
	unsigned char m_b4A;
	unsigned char m_b4B;
	unsigned char m_b4C;
	unsigned char m_b4D;
	unsigned char m_b4E;
	unsigned char m_b4F;
	unsigned char m_b50;
	unsigned char m_b51;
	unsigned char m_b52;
	unsigned char m_b53;
	float m_f54;
	float m_f58;
	float m_f5C;
	float m_f60;
	float m_f64;
	int m_int68;
	int m_int6C;
	int m_int70;
	int m_int74;
	int m_int78;
	int m_int7C;
	int m_int80;
	AsciiString m_string84;
};
typedef char VerifyRva002DA5D3Size[(sizeof(Rva002DA5D3) == 0x88) ? 1 : -1];

Rva002DA5D3::Rva002DA5D3(const OpaqueRefElement4 &ref, int id)
{
	BfmeAudioEventPrefix136 *self = (BfmeAudioEventPrefix136 *)this;
	self->rva002D96D3(ref);
	self->m_int34 = id;
	self->m_int30 = 1;
	if (id)
		self->m_int38 = 4;
	else
		self->m_int34 = 0;
	bool valid;
	self->rva002DA1CC(valid);
}

// Native 0x002DA555..0x002DA5D3: same vtable and 0x88-byte member layout
// as the tag-4 sibling above. All stores and calls are identical except the
// nonzero-ID owner tag at +0x38 is 3. Both use initializer 0x002D96D3 and
// position worker 0x002DA1CC; no application owner-kind identity is asserted.
Rva002DA5D3::Rva002DA5D3(const OpaqueRefElement4 &ref, Rva002DA555Id id)
{
	BfmeAudioEventPrefix136 *self = (BfmeAudioEventPrefix136 *)this;
	self->rva002D96D3(ref);
	self->m_int34 = id;
	self->m_int30 = 1;
	if (id)
		self->m_int38 = 3;
	else
		self->m_int34 = 0;
	bool valid;
	self->rva002DA1CC(valid);
}
