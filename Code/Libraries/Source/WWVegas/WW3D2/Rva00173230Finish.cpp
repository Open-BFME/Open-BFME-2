// ?Register_For_Rendering@MeshModelClass@@QAEXXZ
// cl: /DNDEBUG /MD
// MeshModelClass::Register_For_Rendering, retail RVA 0x00173230, 150 bytes.
//
// Provenance: the three callee identities are UNPROVEN and address-derived. The
// bank recorded their pins with placeholder argument types (P6A0@Z, PAV0@), which
// no C++ declaration can mangle to, so the REL32 sites emitted call 0 and the body
// could not be compared past +0x5A at all. The three pins are respelled here to the
// MeshMatDescClass/MeshModelClass-typed names this TU actually mangles to; the
// addresses, and therefore the callees they name, are unchanged.
//
// The renderer block layout was reached with an explicit goto. Both the if/else and
// the inverted !=/|| spellings canonicalise under this compiler to `jne ELSE / jne
// BOTH`, emitting the both-zero block first. Retail emits `jne SPECIALIZED / je
// PLAIN` -- the specialized block at 0x1732AA is the fallthrough and the plain one
// at 0x1732B8 the branch target -- which is what two early `goto`s out of a plain
// fallthrough block produce. The prior bank concluded this layout was unreachable
// from source; the layout is reachable, just not from a conditional.
//
// MeshModelClass and MeshMatDescClass here are TU-local spellings carrying the
// retail offsets (0x19 flags, 0x94 cur_mat_desc, 0xB8/0x108 descriptor fields,
// 0xC0 has_been_in_use); they are not recovered class definitions.
class MeshMatDescClass;
class MeshModelClass {
public:
    void Init_For_NPatch_Rendering();
    void Register_For_Rendering();
private:
    unsigned char pad0[0x19];
    unsigned char flags;
    unsigned char pad1[0x94 - 0x1A];
    MeshMatDescClass *cur_mat_desc;
    unsigned char pad2[0xC0 - 0x98];
    unsigned char has_been_in_use;
};
class MeshMatDescClass {
public:
    unsigned char pad0[0xB8];
    unsigned *field_b8;
    unsigned char pad1[0x108 - 0xBC];
    unsigned *field_108;
};
class Rva001735F9 { public: int rva001735F9(MeshModelClass *mesh); };
class Rva00145C30 { public: int rva00145C30(MeshModelClass *mesh); };
class Rva00199FFB { public: static void rva00199FFB(MeshMatDescClass *, MeshModelClass *); };

// The five globals this body reads. No ledger unit defines any of them, so
// tools/name_globals.py has no owner to bind them to and there is no recovered
// identity to spend on a name; the address-derived g_0ADDRESS spelling is what
// link_debt prescribes for exactly that case. The addresses and the widths read
// here are fixed by the bytes at 0x00173230, and nothing below depends on the names.
extern volatile unsigned g_0DB5F94;        // renderer mode gate
extern volatile unsigned g_0DB5F90;        // NPatch mode gate
extern volatile unsigned char g_0DEC410;   // force-register flag
extern class Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;            // specialized renderer
extern class DX8MeshRendererClass *TheDX8MeshRenderer;            // plain renderer

void MeshModelClass::Register_For_Rendering()
{
    has_been_in_use = true;
    if (g_0DB5F94 > 1) {
        if (g_0DB5F90 != 0) {
            Init_For_NPatch_Rendering();
        }
    } else if (g_0DB5F90 == 2) {
        Init_For_NPatch_Rendering();
    }

    MeshMatDescClass *desc = cur_mat_desc;
    if (desc->field_b8 == 0 && desc->field_108 == 0) {
        if (g_0DEC410 != 0 || (flags & 4) != 0) {
            Rva00199FFB::rva00199FFB(desc, this);
        }
    }

    desc = cur_mat_desc;
    // The two renderer globals sit on opposite arms of the source's branch order from
    // a naive reading: the 0x00DF363C renderer takes the field_b8==0 && field_108==0
    // arm. Only which branch each sits on is asserted here; the identity of the two
    // globals is untouched.
    //
    // The layout is reached with an explicit goto. See the header: every conditional
    // spelling canonicalises to the both-zero block first, which is not retail's.
    if (desc->field_b8 != 0) goto specialized;
    if (desc->field_108 != 0) goto specialized;
    {
        Rva00145C30 *renderer = (*(Rva00145C30 **)&TheDX8MeshRenderer);
        renderer->rva00145C30(this);
    }
    return;
specialized:
    {
        Rva001735F9 *renderer = (*(Rva001735F9 **)&TheMeshGapFillerContext);
        renderer->rva001735F9(this);
    }
}
