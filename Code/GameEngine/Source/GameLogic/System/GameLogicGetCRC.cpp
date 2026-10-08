// cl: /DNDEBUG /MD /EHsc -Ireference/shims/moduledata
//
// ?getCRC@GameLogic@@QAEIH@Z @0x0023CB2C 542B
// Evidence: LINK BONUS 1 file 51B; donor BFME1 GameLogicCRC.cpp getCRC plus BFME2 BFMECRCWriter ctor 0x00225A2D; callers 0x0024583A 0x00245861 0x002CEA44 0x002CEA8D; neighbours 0x0023CAD2 0x0023CD97 same class GameLogic first at +0xAC.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
void setFPMode();
unsigned int GetGameLogicRandomSeedCRC();

#include "Common/Snapshot.h"

class SystemBase
{
public:
	virtual ~SystemBase();
private:
	char m_pad[8];
};

class PartitionManager : public SystemBase, public Snapshot
{
};

class CollisionManager : public SystemBase, public Snapshot
{
};

class ShroudManager : public SystemBase, public Snapshot
{
};

class TaintManager : public SystemBase, public Snapshot
{
};

class SkirmishAIManager : public SystemBase, public Snapshot
{
};

class PlayerList : public SystemBase, public Snapshot
{
};

class AI : public SystemBase, public Snapshot
{
};

class Rva002BA8F1Logic : public SystemBase, public Snapshot
{
};

class ObjectBase
{
public:
	virtual ~ObjectBase();
private:
	char m_pad[0x5C];
};

class Object : public ObjectBase, public Snapshot
{
public:
	Object *getNextObject() { return m_next; }
private:
	char m_pad2[0x28];
	Object *m_next;
};

class Xfer
{
public:
	virtual ~Xfer();
};

class XferSave
{
public:
	XferSave();
	virtual ~XferSave();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual int beginBlock(const char *name);
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
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
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void xferUnsignedInt(unsigned int *value);
	virtual void slot31();
	virtual void slot32();
private:
	char m_data[0x3C];
};

class BFMECRCWriter : public XferSave
{
public:
	BFMECRCWriter(bool full);
	bool m_full;
	unsigned int m_crc;
};

class Rva0060D4C9
{
public:
	unsigned char rva0060D4C9(Xfer *stream);
};

class Rva002CEC0A
{
public:
	void rva002CED26(Xfer *xfer);
};

class Gen009D6DD0
{
public:
	void bfmeClose();
};

class Rva00210C66CmpBoolField
{
public:
	bool get() const;
};

extern "C" void *theLogicRandomLogFile;
extern unsigned char g_Rva00A02D87;
extern bool g_bfmeDoneAPB;
extern unsigned char g_00E02D7C;
extern unsigned char g_00E02D7D;
extern unsigned char g_00E02D7E;
extern unsigned char g_00E02D7F;
extern unsigned char g_00E02D80;
extern unsigned char g_00E02D81;
extern unsigned char g_00E02D83;
extern unsigned char g_00E02D84;
extern unsigned char g_00E02D88;
extern PartitionManager *ThePartitionManager;
extern PartitionManager *TheShroudManager;
extern PlayerList *ThePlayerList;
extern CollisionManager *g_00DFE754;
extern TaintManager *g_00DFE750;
extern SkirmishAIManager *g_00DFEEF8;
extern class AI *TheAI;

class GameLogic
{
public:
	unsigned int getCRC(int mode);
private:
	char m_pad[0xAC];
	Object *m_first;
};

unsigned int GameLogic::getCRC(int mode)
{
	setFPMode();
	BFMECRCWriter writer(g_bfmeDoneAPB);
	BFMECRCWriter *xfer = &writer;
	if (mode != 0)
		((Rva0060D4C9 *)&writer)->rva0060D4C9((Xfer *)mode);
	if (theLogicRandomLogFile != 0)
		((Rva002CEC0A *)theLogicRandomLogFile)->rva002CED26((Xfer *)&writer);
	if (g_Rva00A02D87 != 0 || g_00E02D7C == 0)
	{
		for (Object *obj = m_first; obj != 0; obj = obj->getNextObject())
			xfer->xferSnapshot(obj);
	}
	unsigned int seed = GetGameLogicRandomSeedCRC();
	xfer->xferUnsignedInt(&seed);
	if (g_Rva00A02D87 != 0 || g_00E02D7D == 0)
		xfer->xferSnapshot(ThePartitionManager);
	if (g_Rva00A02D87 != 0 || g_00E02D7E == 0)
		xfer->xferSnapshot(g_00DFE754);
	if (g_Rva00A02D87 != 0 || g_00E02D7F == 0)
		xfer->xferSnapshot(TheShroudManager);
	if (g_Rva00A02D87 != 0 || g_00E02D80 == 0)
		xfer->xferSnapshot(g_00DFE750);
	if (g_Rva00A02D87 != 0 || g_00E02D81 == 0)
		xfer->xferSnapshot(g_00DFEEF8);
	if (g_Rva00A02D87 != 0 || g_00E02D83 == 0)
		xfer->xferSnapshot(ThePlayerList);
	if (g_Rva00A02D87 != 0 || g_00E02D84 == 0)
		xfer->xferSnapshot(TheAI);
	if ((g_Rva00A02D87 != 0 || g_00E02D88 == 0) && ((Rva00210C66CmpBoolField *)this)->get())
		xfer->xferSnapshot((*(Rva002BA8F1Logic **)&TheLivingWorldLogic));
	((Gen009D6DD0 *)&writer)->bfmeClose();
	return writer.m_crc;
}
