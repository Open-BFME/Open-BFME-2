// Target facts (RVAs): copy constructor 0x000424BB (21 bytes) and CountedAsset* constructor 0x0061FC30 (15 bytes) store the owned pointer at +0; neither stores a vptr or calls a base constructor. AssetReference has no virtual functions or vtable. Traversal at 0x000C931C/0x000C9320 and 0x000C9347 advances by four bytes, establishing sizeof 4.
// The copy constructor conditionally increments WORD [pointer+4]; the CountedAsset* constructor increments it unconditionally. Getter 0x0007B9FD calls the copy constructor. Unwind tails 0x007A7463/0x007A747C call destructor 0x0017098D (12 bytes), which loads +0 and conditionally tail-calls release 0x0061ED10. These members remain out of line.
// The empty return path at 0x0061F354/0x0061F356 and registry miss paths 0x006212AB/0x0062157C store a null pointer. Assignment in 0x001171FF..0x00117227 retains the incoming pointer at 0x0011720A, releases the old pointer at 0x00117215 and replaces it at 0x0011721A/0x00117227; it must not become an implicit shallow copy. The ledger's constructor parameter proves the CountedAsset class spelling; field00 is a neutral name for the sole pointer. No parent or Zero Hour declaration is established.

#ifndef BFME2_ASSETREFERENCE_H
#define BFME2_ASSETREFERENCE_H

class CountedAsset;

class AssetReference
{
public:
	AssetReference() : field00(0) {}
	AssetReference(const AssetReference &);
	AssetReference(CountedAsset *);
	~AssetReference();
	AssetReference &operator=(const AssetReference &);

	CountedAsset *field00;
};

#endif
