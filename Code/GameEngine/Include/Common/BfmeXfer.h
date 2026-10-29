// Xfer: the shared BFME2 Xfer interface view, adopted by tools/header_adopt_lane.py.
// The declaration is the private view 354 ledger units carried verbatim
// (class_views layout fb2837e782): retail-dispatched virtual slots in vtable
// order, the out-of-line Version1 (0x000053EE), SkipBadBlock (0x0050B238),
// XferRawBytes (0x0060B886) and XferEnum (0x0060BBD5) spellings the ledger rows use.
// reverse/class_contracts/Xfer.json leaves slots 4-38 undecided (their names
// differ across views); this header keeps the majority spelling. Slot names
// are not identity claims beyond the rows above and the notes below.
//
// Slots 5-7 are _purecall in Xfer's own table (RVA 0x007BB910). XferLoad's table
// (RVA 0x0087AF18) fills them with 0x0060C629 int(const char *), 0x0060C469
// void() and 0x0060C6F6 void(const char *) (ledger rows in xfer_load.cpp);
// WorldBuilder names the overriders XferLoad::BeginBlock, ::EndBlock and
// ::SkipBlock (XferSave and XferSaveAsText: EndBlock, SkipBlock), so the
// base slots carry those names and signatures.
// Slot 11 is _purecall too and sits inside the operator== run (MSVC keeps
// overloads together), so it is one more operator== overload. Its operand
// is the container type name callers pass as a string literal ("std::list",
// "std::vector", ...): the 59 private views that call it agree on
// `const char *const &`, and XferSave's slot-11 body (0x0060CE41) reads the
// interned string pointer through the reference.
//
// The operand types (Snapshot, AsciiString, the Coord/Region value types,
// RealRange, the RGBA colors, PooledString) are deliberately
// not forward-declared here: units declare them with their own class-keys
// before including this header; a forward declaration here could disagree
// with the class-key a unit already uses.
#ifndef BFME_XFER_H
#define BFME_XFER_H

class Xfer
{
public:
	class Version;

	// XferSaveAsText inlines base construction without emitting another
	// external constructor; System/Xfer.cpp owns the out-of-line body.
#ifdef BFME_XFER_INLINE_CTOR
	__declspec(dllimport) __forceinline Xfer() {}
#else
	Xfer();
#endif
	// Retail's scalar deleting destructor (Xfer.cpp) calls ~Xfer instead of
	// inlining its vtable restore; only the defining TU sees the body.
	// XferVectorDeletingDtor.cpp defines BFME_XFER_INLINE_DTOR: retail's
	// vector deleting destructor inlines the vptr store.
#ifdef BFME_XFER_INLINE_DTOR
	virtual ~Xfer();
#else
	__declspec(noinline) virtual ~Xfer();
#endif

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual int BeginBlock(const char *name) = 0;
	virtual void EndBlock() = 0;
	virtual void SkipBlock(const char *name) = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(const char *const &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

#endif // BFME_XFER_H
