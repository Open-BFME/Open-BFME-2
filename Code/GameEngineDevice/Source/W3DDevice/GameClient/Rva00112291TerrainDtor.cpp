// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [00112291,0011234C),187B, RET0. BFME1 ba7ddda
// W3DTerrainBackgroundDtor.cpp is the primary lifetime guide.
// Target has four owned texture handles34/38/3C/40, the map at5C,
// and the established buffer and tile-array cleanup calls111F0E/112153.
// Four member unwind states and each clear/release call are target facts.
// Original owning class is not asserted by this borrowed prefix view.
// Existing holder contract from dx8wrapper.cpp: the pointer uses
// BfmeResetResource and its established Release_Ref binding.
struct BfmeResetResource {
public: void Release_Ref();
};
class BfmeResetTextureRef {
public:
 void clear();
 ~BfmeResetTextureRef() { if (pointer) pointer->Release_Ref(); }
private: BfmeResetResource *pointer;
};
class Rva00112291MapRef {
public:
 virtual void Delete_This();
 void Release_Ref() { if (--refs == 0) Delete_This(); }
private: int refs;
};
class Rva00111F0E {public: void rva00111F0E();};
struct Rva0011216CSlotQuartet {void rva00112153();};
class Rva00112291TerrainOwner {
public: ~Rva00112291TerrainOwner();
private:
 char unknown00[0x34];
 BfmeResetTextureRef texture34,texture38,texture3C,texture40;
 char unknown44[0x5C-0x44];
 Rva00112291MapRef *map;
};
Rva00112291TerrainOwner::~Rva00112291TerrainOwner() {
 ((Rva00111F0E *)this)->rva00111F0E();
 texture34.clear();
 texture38.clear();
 texture3C.clear();
 texture40.clear();
 if (map) {map->Release_Ref();map=0;}
 ((Rva0011216CSlotQuartet *)this)->rva00112153();
}
