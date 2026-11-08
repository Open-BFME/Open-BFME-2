// Canonical BFME2 ImageCollection; Image itself is defined in ImageClass.h, included below.
// Target facts (code addresses are RVAs; vftable addresses are VAs):
// Image ctor 0x002D8FE4 and dtor 0x002D91CC install 0x00C037B8, whose only slot is the deleting dtor 0x002D9262; the next word at 0x00C037BC is string data. No base constructor or base teardown occurs. Allocation 0x0057CE45 pushes 0x34 before new at 0x0057CE47 and the Image ctor call at 0x0057CE5A.
// The ctor initializes strings at +4/+8, texture size at +0x0C/+0x10, UV coordinates at +0x14..+0x20, image size at +0x24/+0x28, holder at +0x2C and status at +0x30. The dtor releases the holder's texture through 0x0061ED10, frees the holder through 0x0002FD60 and destroys strings at +8/+4 through 0x00036410.
// parseImageCoords 0x002D8E83 reads texture size at +0x0C/+0x10 and writes UVs at +0x14..+0x20 and dimensions at +0x24/+0x28. setUV 0x0004D701 copies 16 bytes to +0x14; setImageSize 0x0004D717 copies two integers to +0x24/+0x28. setStatus 0x002D8E63 and clearStatus 0x002D8E72 update +0x30 and return its previous value.
// bfmeSetTexture 0x002D905E allocates a four-byte BfmeMapPictureTexture holder at +0x2C and calls assignment 0x000424D0. rva002D937E uses filename +8, holder +0x2C and status bit 2. Map-picture loader 0x0057CDC3 assigns the name and filename at +4/+8 (0x0057CE64/0x0057CE74) without a by-value string argument.
// Image's field-parse table at 0x00C036E8 names Texture (+8), TextureWidth (+0x0C), TextureHeight (+0x10), Coords (+0x14) and Status (+0x30); parseImageStatus 0x002D8F86 tests bit 1 and swaps the dimensions. ParticleSystemManager 0x001F9F66 reads Image filename +8 and UVs +0x14.
// ImageCollection ctor 0x002D932B calls SubsystemInterface ctor 0x001B4E63, installs 0x00C03878 at +0 (store 0x002D9348), then constructs the map at +0x0C through 0x0033C432. Allocation before call 0x0023A2D9 requests 0x18 bytes. The base ctor initializes flag +4 and string +8; its dtor 0x001B4E74 restores the base table 0x00BD77A0 and destroys +8.
// ImageCollection dtor 0x002D9283 restores 0x00C03878 (0x002D9296), deletes images through their slot 0, destroys the map at +0x0C through 0x002D922A, then calls the base dtor at 0x002D92E2. The base and collection tables belong to separate destruction phases.
// Table 0x00C03878 has 14 slots, followed by string data at 0x00C038B0: 0=0x002D9362, 1=0x000B3FD0, 2=0x001B5384, 3=0x000B3FD0, 4=0x005CB9FF, 5=0x0047A699, 6=0x000D43D0, 7=0x0047A69C, 8..10=0x000B3FD0, 11=0x005CB9FF, 12=0x000B3FD0, 13=0x0047A69C. Slots 1/9/10 override the registered base's init/reset/update.
// findImageByName 0x002D92F6 searches the map at +0x0C by unsigned name key, returning Image* at node+0x14. addImage 0x002D9457 reads the name at Image+4 and inserts that pointer; load 0x002D908D takes one integer. Map ctor worker 0x001F068F stores the header/count at map+0/map+4, so this is STLport's map layout, with total storage ending at ImageCollection+0x18.
// Donor facts: Zero Hour GameClient/Image.h names the fields, image accessors, status bits and collection methods. BFME2's observed allocations use global new and +0x2C holds a texture holder. Image's observed one-slot vptr is modeled directly; these bytes do not establish the absence of a source-level empty base. Unnamed inherited slots retain the registered parent's neutral names.

#pragma once
#ifndef __BFME2_IMAGE_H_
#define __BFME2_IMAGE_H_

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include <map>
#ifndef _STLP_INTERNAL_MAP_H
#error ImageCollection requires STLport headers; compile the unit with its stlport opt-in.
#endif

#include "ImageClass.h"

class ImageCollection : public SubsystemInterface
{
public:
    ImageCollection();
    virtual ~ImageCollection();
    virtual void init() {}
    virtual void reset() {}
    virtual void update() {}
    void load(int textureSize);
    const Image *findImageByName(const AsciiString &name);
    void addImage(Image *image);

    _STL::map<unsigned int, Image *> m_imageMap;
};

typedef char ImageSizeCheck[sizeof(Image) == 0x34 ? 1 : -1];
typedef char ImageCollectionSizeCheck[sizeof(ImageCollection) == 0x18 ? 1 : -1];

extern ImageCollection *TheMappedImageCollection;

#endif
