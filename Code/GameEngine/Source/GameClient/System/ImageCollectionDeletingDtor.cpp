// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /O1 /MD
//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// These minimal declarations emit the wrappers, not complete class layouts.
// No member layout or destructor implementation is claimed here. A dummy tag
// constructor (absent from retail) makes this unit emit the vtable and so the
// wrapper; the wrapper's call resolves to the rowed complete destructor
// (ImageCollectionDtor.cpp), which this unit no longer duplicates.

// ??_GImageCollection@@UAEPAXI@Z @0x002D9362 28B: slot 0 of vtable 0x00C03878; calls ??1 at 0x002D9283.
// Owner evidence (audited 2026-09-26): ctor RVA 0x002D932B stores primary vptr at RVA 0x002D9348; caller RVA 0x0023A1BB stores result at VA 0x00DFF078; donor findImageByName/addImage bodies corroborate image-map ownership.
// The SubsystemInterface base and the init/reset/update overrides only give the
// emitted vtable the retail 14-slot shape (0x00C03878) shared with the ctor/dtor units.
typedef bool Bool;
#include "subsystem_interface.h"
class ImageCollection : public SubsystemInterface { public: ImageCollection(struct EmitVtableTag *); virtual ~ImageCollection(); virtual void init() {} virtual void reset() {} virtual void update() {} };
// ?<ImageCollection::ImageCollection> absent-from-retail
ImageCollection::ImageCollection(struct EmitVtableTag *) {}
void ImageCollection_Delete(ImageCollection *p) { delete p; }
