// cl: /O1 /G7 /MD /EHsc
// WB10488D0 names LivingWorldBattle::BattleResults::DoXfer in
// GameLogic/System/LivingWorld/LivingWorldBattle.cpp. Native3F3FFE..3F4096
// proves a player pointer at0 and four transferred integers at4/8/C/10.
// The player's ID at14 is independently used by the rowed lookup2B51F8.
// Xfer's native vtable7BB910 proves Version10 and signed integer31.
// Original field labels and full player extent remain unresolved; these
// address-qualified views preserve the existing lookup's type and ABI.
// Typed player access closes the earlier saved-ID register mismatch.
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned char UnsignedByte;
class AsciiString;
struct XferVersionFields
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

union XferVersion
{
	XferVersionFields m_fields;
	UnsignedInt m_value;
};

class Snapshot;

class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual void slot03();
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *data, UnsignedInt size);
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void xferAsciiString(AsciiString *value);
	virtual void xferReal(Real *value);
	virtual void slot29();
	virtual void xferUnsignedInt(UnsignedInt *value);
 virtual void xferInt(Int *value);
};

void XferLivingWorldPlayerID(Xfer *, int *);
class Rva002E2903Player
{
public:
	int getID() const { return id; }
	char unknown00[0x14];
	int id;
};
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int, unsigned *);
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva003F3FFE
{
public:
	void rva003F3FFE(Xfer &);
private:
	Rva002E2903Player *player;
	int counts[4];
};

void Rva003F3FFE::rva003F3FFE(Xfer &xfer)
{
	XferVersion version;
	version.m_fields.m_version = 1;
	version.m_fields.m_currentVersion = 1;
	xfer.xferVersion(&version);
	xfer.xferInt(&counts[0]);
	xfer.xferInt(&counts[1]);
	xfer.xferInt(&counts[2]);
	xfer.xferInt(&counts[3]);
	if (xfer.IsLoading()) {
		int id;
		XferLivingWorldPlayerID(&xfer, &id);
		player = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(id, 0);
	} else {
		int id = player ? player->getID() : -1;
		XferLivingWorldPlayerID(&xfer, &id);
	}
}
