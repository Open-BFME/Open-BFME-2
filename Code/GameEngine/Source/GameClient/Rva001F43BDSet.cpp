// cl: /GX-
// ?rva001F43BD@Rva001F43BD@@QAEXPAX@Z @0x001F43BD 33B
// Owned-pointer setter: releases the old object through its virtual slot 0
// with a 0 argument, frees the returned pointer with operator delete, then
// stores the new pointer. Evidence: retail pushes 0 (reused xor-ed eax) for
// the slot call, deletes unconditionally (je lands on push+delete), stores
// [esp+0xC] after; sole direct callee is rowed ??3@YAXPAX@Z 0x0002FD60;
// virtual slot call needs no row; 8 INI Parse bodies (0x001F83C9 et al)
// call it, landing this unblocks 6 of them.
class Rva001F43BD
{
    struct Ifc
    {
        virtual void *slot0(int flags);
    };
    Ifc *m_ptr;
public:
    void rva001F43BD(void *p);
};

// ?rva001F609F@Rva001F609FOwner@@QAEXPAX@Z @0x001F609F 11B: offsets this to the Rva001F43BD embedded at +0xA4 and
// tail-jumps Rva001F43BD::rva001F43BD. Owner and name are address-derived; no
// referencing site was found in this pass.
class Rva001F609FOwner
{
public:
	void rva001F609F(void *p);
};

// Seven more of the 0x001F609F shape, contiguous at 0x001F617C..0x001F61C9
// (11 bytes each): offset this to the Rva001F43BD at +0xA8..+0xC0 (one per
// four-byte slot) and tail-jump Rva001F43BD::rva001F43BD. Owners and names are
// address-derived; no referencing site was found in this pass.
#define BFME_RVA001F43BD_SLOT_SETTER(NAME, DISP) \
	class NAME \
	{ \
	public: \
		void set(void *p); \
	}; \
	void NAME::set(void *p) \
	{ \
		((Rva001F43BD *)((char *)this + DISP))->rva001F43BD(p); \
	}


// Eight more forwarders to the same setters (+0xA4..+0xC0), contiguous at
// 0x001F68AF and 0x001F68CE..0x001F693E (16 bytes each): the same offset and
// call, but as file-statics in cl 7.1's register convention - the owner stays
// in ECX and the caller cleans the argument, so they call the ret-4 setter and
// end in a plain ret instead of tail-jumping. No call to any of them survives
// in the image; the anchor below only forces cl to emit them in that
// convention. Owners and names are address-derived.
#define BFME_RVA001F43BD_STATIC_SETTER(NAME, DISP) \
	static __declspec(noinline) void NAME(char *owner, void *p) \
	{ \
		((Rva001F43BD *)(owner + DISP))->rva001F43BD(p); \
	}

BFME_RVA001F43BD_STATIC_SETTER(Rva001F68AFSet, 0xA4)
BFME_RVA001F43BD_STATIC_SETTER(Rva001F68CESet, 0xA8)
BFME_RVA001F43BD_STATIC_SETTER(Rva001F68DESet, 0xAC)
BFME_RVA001F43BD_STATIC_SETTER(Rva001F68EESet, 0xB0)
BFME_RVA001F43BD_STATIC_SETTER(Rva001F68FESet, 0xB4)
BFME_RVA001F43BD_STATIC_SETTER(Rva001F690ESet, 0xB8)
BFME_RVA001F43BD_STATIC_SETTER(Rva001F691ESet, 0xBC)
BFME_RVA001F43BD_STATIC_SETTER(Rva001F692ESet, 0xC0)

// ?Rva001F68AFAnchor absent-from-retail
void Rva001F68AFAnchor(char *owner, void *p)
{
	Rva001F68AFSet(owner, p);
	Rva001F68CESet(owner, p);
	Rva001F68DESet(owner, p);
	Rva001F68EESet(owner, p);
	Rva001F68FESet(owner, p);
	Rva001F690ESet(owner, p);
	Rva001F691ESet(owner, p);
	Rva001F692ESet(owner, p);
}
