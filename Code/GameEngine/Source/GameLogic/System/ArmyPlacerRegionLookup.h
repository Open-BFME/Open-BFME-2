#ifndef ARMY_PLACER_REGION_LOOKUP_H
#define ARMY_PLACER_REGION_LOOKUP_H
// Target-only lookup view: native callers read the region manager from +0xb0
// of TheLivingWorldLogic and call the existing 0x0020EAF6 provider.
class Rva0020E89C;
class Rva0020EAF6View { public: Rva0020E89C *rva0020EAF6(int); };
class LivingWorldLogic {
public:
    unsigned char opaque_00[0xb0];
    Rva0020EAF6View *lookup;
    Rva0020EAF6View *getLookup() const { return lookup; }
};
extern LivingWorldLogic *TheLivingWorldLogic;
#endif
