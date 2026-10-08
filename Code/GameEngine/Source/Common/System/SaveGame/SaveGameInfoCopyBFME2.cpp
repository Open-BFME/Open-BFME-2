// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// BFME2 record copies with verified StringBase member operations.
// Layouts are read from the complete retail constructors and their STLport
// placement-copy callers. Application names and scalar meanings are unknown.
// String semantics follow BFME1 AsciiString/UnicodeString: the inline derived
// copies call StringBase<char>0x365F0 or StringBase<unsigned short>0x37050.
#include <memory>
#include "ascii_string.h"
#include "unicode_string.h"

// SaveGameInfo's name getter at 0x22CEF1 identifies this class. Its destructor
// at 0x2DD1E9 restores Snapshot's established vtable (VA 0xBBB554), proving
// the state-free polymorphic base and the extra constructor unwind state.
// Retain the address-derived name already used by the enclosing map record.
// BFME1 SaveGameInfo supplies the three-string/date prefix; BFME2 adds the
// following fields. Unresolved application field names remain offset-based.
// This base is NOT canonical Snapshot: retail holds crc/typeName/xfer here
// while canonical Snapshot (Snapshot.cpp, shim) holds crc/xfer/loadPostProcess.
// Same mangled name different virtuals cannot share COMDATs, so the base keeps
// an honest Rva address name here (SaveMapPreviewCopy precedent).
class Xfer;
class Rva0022CE19SnapshotBase {
public:
    inline virtual ~Rva0022CE19SnapshotBase() {}
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
struct BfmeSaveDate { unsigned short values[8]; };
// Complete copy at 0x22C55B is 71 bytes: allocate a vector range of 20-byte
// elements and copy it through 0x2DBEFF. Destructor 0x22CAC4 owns the range.
struct BfmeVector0022C55B {
    void *begin, *end, *capacity;
    BfmeVector0022C55B(const BfmeVector0022C55B &);
    ~BfmeVector0022C55B();
};
// Complete copy at 0x229875 is 141 bytes: vptr 0xBE7460; eight 0x1AC-byte
// elements at +4; blocks at +0xD64/+0xD74; byte +0xD9C; dword +0xDA0.
// Its destructor is the direct +0x44 member cleanup at 0x2DC62C.
// The callbacks are absolute VAs 0x6295D7/0x6294FD, hence RVAs
// 0x2295D7 (271-byte copy) and 0x2294FD (90-byte destructor).
// Both independently prove the Snapshot base and 0x1AC element extent.
// Vtable0xC38D88 slot2 returns "CreateAHeroData" at RVA0x409353.
// Complete339-byte copy and206-byte destructor confirm the Snapshot base,
// owning members and0x140-byte extent. Preserve declarations while their
// own field reconstruction remains separate from this element copy.
class CreateAHeroData : public Rva0022CE19SnapshotBase {
    unsigned char fields[0x13C];
public:
    CreateAHeroData(const CreateAHeroData &);
    virtual ~CreateAHeroData();
};
class GameSlot : Rva0022CE19SnapshotBase {
public:
    GameSlot();
    unsigned int word04;
    unsigned char flag08, flag09, flag0A;
    unsigned int word0C, word10, word14, word18, word1C, word20, word24, word28, word2C;
    UnicodeString text30;
    AsciiString text34;
    unsigned int word38, word3C, word40, word44;
    unsigned char flag48;
    unsigned int word4C, word50, word54, word58, word5C;
    unsigned char flag60;
    CreateAHeroData hero64;
    unsigned char flag1A4;
    AsciiString text1A8;
};
struct BfmeSaveBlock4 { unsigned int values[4]; };
struct BfmeSaveBlock10 { unsigned int values[10]; };
struct BfmeSubobject00229875 : Rva0022CE19SnapshotBase {
    BfmeSubobject00229875();
    void rva002DBA6A();
    virtual ~BfmeSubobject00229875();
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
    GameSlot elements[8];
    BfmeSaveBlock4 blockD64;
    BfmeSaveBlock10 blockD74;
    unsigned char flagD9C;
    unsigned int wordDA0;
};
typedef char BfmeSaveElementSizeCheck[sizeof(GameSlot)==0x1AC ? 1 : -1];
struct BfmeSubobject0022CE19 : Rva0022CE19SnapshotBase {
    virtual ~BfmeSubobject0022CE19();
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
    AsciiString text04, text08, text0C;
    BfmeSaveDate date10;
    UnicodeString text20;
    unsigned int word24, word28;
    AsciiString text2C;
    UnicodeString text30, text34;
    BfmeVector0022C55B range38;
    BfmeSubobject00229875 object44;
    BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
};
typedef char BfmeSaveSizeCheck[sizeof(BfmeSubobject0022CE19)==0xDE8 ? 1 : -1];
typedef char BfmeSaveOffsetsCheck[(offsetof(BfmeSubobject0022CE19,range38)==0x38 && offsetof(BfmeSubobject0022CE19,object44)==0x44) ? 1 : -1];
BfmeSubobject0022CE19::BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &o)
    : Rva0022CE19SnapshotBase(o), text04(o.text04), text08(o.text08), text0C(o.text0C),
      date10(o.date10), text20(o.text20), word24(o.word24), word28(o.word28),
      text2C(o.text2C), text30(o.text30), text34(o.text34),
      range38(o.range38), object44(o.object44) {}

BfmeSubobject0022CE19::~BfmeSubobject0022CE19() {}

BfmeSubobject00229875::~BfmeSubobject00229875() {}

BfmeSubobject00229875::BfmeSubobject00229875()
{
	rva002DBA6A();
}

class GameEngineDeletingBase
{
public:
	GameEngineDeletingBase() throw();
	virtual ~GameEngineDeletingBase();
private:
	int m_pad04;
	int m_pad08;
};

class Rva0022958D : public GameEngineDeletingBase
{
public:
	Rva0022958D();
	virtual ~Rva0022958D();
private:
	AsciiString m_0c;
	AsciiString m_10;
};

// Retail 0x00229557 (26 bytes): default constructor. Base constructor at
// 0x1B4E63, vtable store, then both AsciiString members zeroed at +0x0C and +0x10.
Rva0022958D::Rva0022958D()
	: GameEngineDeletingBase()
{
}

Rva0022958D::~Rva0022958D()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?crc@BfmeSubobject00229875@@UAEXPAVXfer@@@Z=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?typeName@BfmeSubobject00229875@@UBEPBDXZ=?name@Rva00229902Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:?xfer@BfmeSubobject00229875@@UAEXPAVXfer@@@Z=?rva002DBDB4@Rva002DBDB4@@QAEXPAVRva002DBD05@@@Z")
#pragma comment(linker, "/alternatename:?crc@BfmeSubobject0022CE19@@UAEXPAVXfer@@@Z=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?typeName@BfmeSubobject0022CE19@@UBEPBDXZ=?name@Rva0022CEF1Named@@QBEPBDXZ")
