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
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

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
    GameSlot &rva002DBAB9(const GameSlot &other);	// 0x002DBAB9
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
    int word24;
    unsigned int word28;
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

// Xfer as BFME2's save code calls it: slot 1 isLoading, slot 10 the
// two-byte version, slot 12 a snapshot, slots 26/27 the strings and the
// reversed overload run ending with int (31) and unsigned short (32).
template <int N> class VSlots : public VSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class VSlots<0>
{
};
struct BfmeXferVersion
{
	BfmeXferVersion(unsigned char v) : current(1), version(v) {}
	unsigned char current;
	unsigned char version;	// the loaded version after xferVersion
};
class Xfer
{
public:
	virtual ~Xfer();
	virtual bool isLoading();
	virtual void slot02(); virtual void slot03(); virtual void slot04();
	virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void xferVersion(BfmeXferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(Rva0022CE19SnapshotBase *snapshot);
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18();
	virtual void slot19(); virtual void slot20(); virtual void slot21();
	virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25();
	virtual void xferUnicodeString(UnicodeString *value);
	virtual void xferAsciiString(AsciiString *value);
	virtual void xferReal(float *value);
	virtual void xferInt64(__int64 *value);
	virtual void xferUnsignedInt(unsigned int *value);
	virtual void xferInt(int *value);
	virtual void xferUnsignedShort(unsigned short *value);
};
void XferSaveFileType(Xfer *xfer, int *value);	// 0x00305D52
struct Rva002DB9EFObj;
int Rva002DB9EFGet(Rva002DB9EFObj *xfer, void *value);	// 0x002DB9EF, "IsAutoSaveOrNot"

// The +0x38 range holds SaveMapPreview (vtable 0x007E7258):
// an army id at +4 (-1 when unset) and its position. Its own xfer 0x2DBA3F
// keeps an address name.
class SaveMapPreview : public Rva0022CE19SnapshotBase
{
public:
	SaveMapPreview() : word04(-1) { pos.x = 0.0f; pos.y = 0.0f; pos.z = 0.0f; }
	virtual ~SaveMapPreview() {}
	virtual void crc(Xfer *);
	virtual const char *typeName() const;
	virtual void xfer(Xfer *);
	int word04;
	Coord3D pos;
};
struct Rva002DBA3F
{
	void rva002DBA3F(Xfer *xfer);	// SaveMapPreview's xfer
};
// The range's erase and push_back keep the spellings their rows were landed
// under (StlportVectorEraseRangeFamily.cpp, Rva002DDD48Insert.cpp).
struct Rva002DCFEEElement { unsigned int w[5]; };
namespace _STL
{
template <class T, class A> class vector;
template <> class vector<Rva002DCFEEElement, allocator<Rva002DCFEEElement> >
{
public:
	Rva002DCFEEElement *erase(Rva002DCFEEElement *first, Rva002DCFEEElement *last);
	Rva002DCFEEElement *begin() { return m_start; }
	Rva002DCFEEElement *end() { return m_finish; }
	void clear() { erase(begin(), end()); }
	Rva002DCFEEElement *m_start, *m_finish, *m_end;
};
}
typedef _STL::vector<Rva002DCFEEElement, _STL::allocator<Rva002DCFEEElement> > BfmePreviewRange;
class Rva002DDD48
{
public:
	void push_back(const SaveMapPreview &x);	// 0x002DDE6E
};

// TheLivingWorldLogic: a subsystem with its Snapshot base at +0xC; the
// region manager at +0xB0 holds the army set at +0x08, whose army list
// is a base at +0x2C (LivingWorldLogic.cpp's Rva002B5334ArmySet).
class SystemBase
{
public:
	virtual ~SystemBase();
private:
	char m_pad[8];
};
struct BfmeSaveArmy
{
	unsigned char m_pad000[0x12c];
	int m_id;				// +0x12C
	unsigned char m_pad130[0x13c - 0x130];
	int m_playerID;				// +0x13C
	int getID() const { return m_id; }
	int getPlayerID() const { return m_playerID; }
};
struct BfmeSaveArmyList
{
	BfmeSaveArmy **m_start, **m_finish, **m_end;
	unsigned int size() const { return (unsigned int)(m_finish - m_start); }
	BfmeSaveArmy *operator[](unsigned int i) const { return m_start[i]; }
};
struct BfmeSaveArmySetBase
{
	unsigned char m_pad00[0x2c];
};
struct BfmeSaveArmySet : public BfmeSaveArmySetBase, public BfmeSaveArmyList
{
};
struct BfmeSaveRegionManager
{
	unsigned char m_pad00[0x8];
	BfmeSaveArmySet *m_armySet;		// +0x08
};
class Rva002E2903Player
{
	unsigned char m_pad000[0x184];
public:
	Coord3D m_position;			// +0x184
};
class Rva002BA8F1Logic : public SystemBase, public Rva0022CE19SnapshotBase
{
public:
	Rva002E2903Player *find(int playerID, unsigned int *index);	// 0x002B51F8
	unsigned char m_pad10[0xB0 - 0x10];
	BfmeSaveRegionManager *m_regionManager;	// +0xB0
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

// The game info of the session TheGameLogic's mode at +0x114 names.
class GameLogic;
extern GameLogic *TheGameLogic;
struct BfmeSaveGameMode
{
	unsigned char m_pad[0x114];
	int m_mode;				// +0x114
};
class GameInfo : public VSlots<12>
{
public:
	virtual bool slot12();
	GameSlot *getSlot(int index);		// 0x003FF29F
	unsigned char m_pad04[0x58 - 0x04];
	int m_58;				// +0x58
};
class LANGameInfo : public GameInfo
{
};
class GameSpyStagingRoom : public GameInfo
{
};
class LANAPI : public VSlots<56>
{
public:
	virtual LANGameInfo *GetMyGame() = 0;
};
extern GameInfo *TheSkirmishGameInfo;
extern LANAPI *TheLAN;
extern GameSpyStagingRoom *TheGameSpyGame;
extern GameInfo *TheGameInfo;
struct Rva002DB9B6
{
	void rva002DB9B6(void *out);	// copies the info's 28 bytes at +0x60
};

// The MD5 block writer (ctor 0x0052B42B, vtable 0x00868620). Its destructor
// 0x52B497 keeps that address name, so the class is split to reach it.
class XferSave : public Xfer
{
public:
	XferSave();
	virtual ~XferSave();
	void close();				// 0x0060C8CD
private:
	char m_data[0x3C];
};
class Rva0052B497 : public XferSave
{
public:
	virtual ~Rva0052B497();
private:
	unsigned char m_40;
	unsigned char m_digest[16];
	void *m_ctx;
	unsigned char m_done;
};
class Rva0052B53C : public Rva0052B497
{
public:
	Rva0052B53C(unsigned char v);
	void rva0052B53C();
	unsigned char *rva0052B559();
};
class BFMECRCWriter : public XferSave
{
public:
	BFMECRCWriter(bool full);
	bool m_full;
	unsigned int m_crc;
};
extern bool TheLiteCRC;
extern "C" void *__cdecl memset(void *, int, unsigned int);
extern "C" void *__cdecl memcpy(void *, const void *, unsigned int);

// Retail 0x002DDEC0, 1105 bytes: SaveGameInfo's xfer (vtable 0x007E7560 slot
// 3). Version 3; the file type, map, date, description and label, an
// auto-save flag from version 3. Living-world saves (types 4 and 6) carry the
// army previews and the session's slots, digest and CRC.
void BfmeSubobject0022CE19::xfer(Xfer *xfer)
{
	BfmeXferVersion version(3);
	xfer->xferVersion(&version);
	XferSaveFileType(xfer, &word24);
	xfer->xferAsciiString(&text2C);
	xfer->xferUnsignedShort(&date10.values[0]);
	xfer->xferUnsignedShort(&date10.values[1]);
	xfer->xferUnsignedShort(&date10.values[2]);
	xfer->xferUnsignedShort(&date10.values[3]);
	xfer->xferUnsignedShort(&date10.values[4]);
	xfer->xferUnsignedShort(&date10.values[5]);
	xfer->xferUnsignedShort(&date10.values[6]);
	xfer->xferUnsignedShort(&date10.values[7]);
	xfer->xferUnicodeString(&text20);
	xfer->xferAsciiString(&text0C);
	if (version.version < 2)
	{
		AsciiString unusedText;
		int unusedValue = 0;
		xfer->xferAsciiString(&unusedText);
		xfer->xferInt(&unusedValue);
	}
	if (version.version >= 3)
		Rva002DB9EFGet((Rva002DB9EFObj *)xfer, &word28);
	else if (xfer->isLoading())
		word28 = 0;
	xfer->xferUnicodeString(&text30);
	xfer->xferUnicodeString(&text34);
	if (word24 != 4 && word24 != 6)
		return;
	if (xfer->isLoading())
	{
		BfmePreviewRange *range = (BfmePreviewRange *)&range38;
		range->clear();
		int count = range->m_finish - range->m_start;
		xfer->xferInt(&count);
		for (int i = 0; i < count; ++i)
		{
			SaveMapPreview preview;
			((Rva002DBA3F *)&preview)->rva002DBA3F(xfer);
			((Rva002DDD48 *)range)->push_back(preview);
		}
		object44.rva002DBA6A();
		Rva0022CE19SnapshotBase *loaded = &object44;
		loaded->xfer(xfer);
		return;
	}
	else
	{
		{
		BfmeSaveArmySet *set = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_regionManager->m_armySet;
		BfmeSaveArmyList *armies;
		if (set != 0)
			armies = set;
		else
			armies = 0;
		if (armies != 0)
		{
			BfmePreviewRange *range = (BfmePreviewRange *)&range38;
			range->clear();
			for (unsigned int i = 0; i < armies->size(); ++i)
			{
				BfmeSaveArmy *army = (*armies)[i];
				Rva002E2903Player *player = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(army->getPlayerID(), 0);
				if (player != 0)
				{
					SaveMapPreview preview;
					preview.pos = player->m_position;
					preview.word04 = army->getID();
					((Rva002DDD48 *)&range38)->push_back(preview);
				}
			}
			int count = range->m_finish - range->m_start;
			xfer->xferInt(&count);
			for (int i = 0; i < count; ++i)
				((SaveMapPreview *)range->m_start)[i].xfer(xfer);
		}
		}
		GameInfo *game;
		int mode = ((BfmeSaveGameMode *)TheGameLogic)->m_mode;
		if (mode == 0)
			game = TheSkirmishGameInfo;
		else if (mode == 1)
			game = TheLAN->GetMyGame();
		else if (mode == 2)
			game = TheGameSpyGame;
		else
			game = TheGameInfo;
		if (game == 0)
			return;
		for (int slot = 0; slot < 8; ++slot)
			object44.elements[slot].rva002DBAB9(*game->getSlot(slot));
		if (TheLivingWorldLogic != 0)
		{
			memset(&object44.blockD64, 0, sizeof(object44.blockD64));
			Rva0052B53C digest(0);
			(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->xfer((Xfer *)&digest);
			digest.rva0052B53C();
			memcpy(&object44.blockD64, digest.rva0052B559(), 16);
			BFMECRCWriter crc(TheLiteCRC);
			Xfer *writer = &crc;
			writer->xferSnapshot(*(Rva002BA8F1Logic **)&TheLivingWorldLogic);
			crc.close();
		}
		((Rva002DB9B6 *)game)->rva002DB9B6(&object44.blockD74);
		object44.flagD9C = game->slot12();
		object44.wordDA0 = game->m_58;
		Rva0022CE19SnapshotBase *info = &object44;
		info->xfer(xfer);
	}
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
