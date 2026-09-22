// ?Register_For_Rendering@MeshModelClass@@QAEXXZ
// partial score=0.9 date=2026-09-23
// cl: /G7 /DNDEBUG /MD
// Scratch candidate for target RVA 0x00173230; opaque names are address-derived
// placeholders, not recovered identities. Do not import into Code/.
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
class Rva00DF6F94Context { public: void Handle_Mesh(MeshModelClass *mesh); };
class Rva00DF363CContext { public: void Handle_Mesh(MeshModelClass *mesh); };
extern void __cdecl Rva00199FFBHelper(MeshMatDescClass *, MeshModelClass *);

void MeshModelClass::Register_For_Rendering()
{
    has_been_in_use = true;
    if (*reinterpret_cast<volatile unsigned *>(0x00DB5F94) > 1) {
        if (*reinterpret_cast<volatile unsigned *>(0x00DB5F90) != 0) {
            Init_For_NPatch_Rendering();
        }
    } else if (*reinterpret_cast<volatile unsigned *>(0x00DB5F90) == 2) {
        Init_For_NPatch_Rendering();
    }

    MeshMatDescClass *desc = cur_mat_desc;
    if (desc->field_b8 == 0 && desc->field_108 == 0) {
        if (*reinterpret_cast<volatile unsigned char *>(0x00DEC410) != 0 || (flags & 4) != 0) {
            Rva00199FFBHelper(desc, this);
        }
    }

    desc = cur_mat_desc;
    if (desc->field_b8 == 0 && desc->field_108 == 0) {
        Rva00DF363CContext *renderer = *reinterpret_cast<Rva00DF363CContext * volatile *>(0x00DF363C);
        renderer->Handle_Mesh(this);
    } else {
        Rva00DF6F94Context *renderer = *reinterpret_cast<Rva00DF6F94Context * volatile *>(0x00DF6F94);
        renderer->Handle_Mesh(this);
    }
}
