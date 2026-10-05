// cl: /O1 /EHsc
// ?rva003AC8D7@Rva003AC8D7Host@@UAEPAVRva003AC8D7Object@@I@Z @0x003AC8D7 89B
// ?rva003ACA93@Rva003ACA93Host@@UAEPAVRva003ACA93Object@@I@Z @0x003ACA93 89B
// ?rva003ACB08@Rva003ACB08Host@@UAEPAVRva003ACB08Object@@I@Z @0x003ACB08 89B
// ?rva003ACF68@Rva003ACF68Host@@UAEPAVRva003ACF68Object@@I@Z @0x003ACF68 89B
//
// Slot 0 of a particle-module template's secondary vtable (0x00C1C504 for
// 0x003AC8D7, 0x00C1C63C#1 for 0x003ACA93): allocate the module, construct it
// from (the argument, this template), and return it. The vtable belongs to the
// subobject at +0x14, so the body first steps `this` back by 0x14 to the full
// template before passing it on -- the `add edi,-0x14` retail shows, which is
// what MSVC emits for an override of a function a secondary base introduced.
//
// The constructed class's constructor is INLINED (V3NewInlineCtorFactories.cpp
// explains the tell): one call to a rowed out-of-line base constructor, then the
// derived class stamps its three subobject vtables, at {0, 8, 0xC} or
// {0, 8, 0x10}. Sizes are the `new` operands. new + constructor under /EHsc is
// what gives the EH_prolog frame that frees the block if the constructor throws;
// with that frame /O1 declines to inline the constructor on its own (and /O2
// drops EH_prolog), so the constructor is spelled __forceinline.
//
// Every class here is address-named after the slot body; only the rowed base
// constructors carry names from the ledger.

class Rva003AC8D7Slot0	{ public: virtual void s0(); int m_a; };
class Rva003AC8D7Slot1	{ public: virtual void s0(); };
class Rva003AC8D7Slot1N	{ public: virtual void s0(); int m_a; };
class Rva003AC8D7Slot2	{ public: virtual void s0(); };

class Rva003AC8D7Primary
{
public:
	virtual void p0();

private:
	int m_storage[ 4 ];
};

#define MODULE_TEMPLATE_CLONE_SLOT( NAME, METHOD, BASE, SRC, SLOT1, SIZE )    \
	class BASE : public Rva003AC8D7Slot0, public SLOT1, public Rva003AC8D7Slot2 \
	{                                                                        \
	public:                                                                  \
		BASE( unsigned int arg, SRC src );                                    \
	};                                                                       \
	class NAME##Object : public BASE                                         \
	{                                                                        \
	public:                                                                  \
		__forceinline NAME##Object( unsigned int arg, SRC src )              \
			: BASE( arg, src ) {}                                             \
		char m_storage[ SIZE - sizeof( BASE ) ];                              \
	};                                                                       \
	class NAME##Clone                                                        \
	{                                                                        \
	public:                                                                  \
		virtual NAME##Object *METHOD( unsigned int arg ) = 0;                 \
	};                                                                       \
	class NAME##Host : public Rva003AC8D7Primary, public NAME##Clone          \
	{                                                                        \
	public:                                                                  \
		virtual NAME##Object *METHOD( unsigned int arg );                      \
	};

struct Rva0055B52ESrc;
struct Src00562366;
struct Src005646BC;
struct Src0055F218;

MODULE_TEMPLATE_CLONE_SLOT( Rva003AC8D7, rva003AC8D7, Rva0055B52E, const Rva0055B52ESrc *, Rva003AC8D7Slot1, 0x5c )
MODULE_TEMPLATE_CLONE_SLOT( Rva003ACA93, rva003ACA93, Rva00562366, Src00562366 &, Rva003AC8D7Slot1, 0x44 )
MODULE_TEMPLATE_CLONE_SLOT( Rva003ACB08, rva003ACB08, Rva005646BC, Src005646BC &, Rva003AC8D7Slot1N, 0x24 )
MODULE_TEMPLATE_CLONE_SLOT( Rva003ACF68, rva003ACF68, Rva0055F218, Src0055F218 &, Rva003AC8D7Slot1, 0x18 )

Rva003AC8D7Object *Rva003AC8D7Host::rva003AC8D7( unsigned int arg )
{
	return new Rva003AC8D7Object( arg, reinterpret_cast<const Rva0055B52ESrc *>( this ) );
}

Rva003ACA93Object *Rva003ACA93Host::rva003ACA93( unsigned int arg )
{
	return new Rva003ACA93Object( arg, *reinterpret_cast<Src00562366 *>( this ) );
}

Rva003ACB08Object *Rva003ACB08Host::rva003ACB08( unsigned int arg )
{
	return new Rva003ACB08Object( arg, *reinterpret_cast<Src005646BC *>( this ) );
}

Rva003ACF68Object *Rva003ACF68Host::rva003ACF68( unsigned int arg )
{
	return new Rva003ACF68Object( arg, *reinterpret_cast<Src0055F218 *>( this ) );
}
