// cl: /MD
// ?xfer@Rva0034149B@@MAEXPAVXfer@@@Z @0x003414F6 97B: Rva0034149B xfer slot 3.
// IsLightCRC early-out via slot 0x10 then Version1 via rowed 0x000053EE then bool has=(m_20!=0) via slot 0x90 then lazy create via m_machine slot 0x24 then Snapshot via slot 0x30.
// Precedent Rva0033F33D Snapshot via slot 0x30 plus bool via slot 0x90 shape.
// Vtable 0x008112C0 slot 3.
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class Xfer
{
public:
	class Version;
	Xfer();
	virtual ~Xfer();
	void Version1();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;
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
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};
class StateMachine;
class SnapshotCreator
{
public:
	virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
	virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
	virtual void c08();
	virtual Snapshot *createSnapshot();
};
class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	SnapshotCreator *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};
class Rva0034149B : public State
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	Snapshot *m_20;
};
void Rva0034149B::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	bool has = (m_20 != 0);
	*xfer == has;
	if (has) {
		if (m_20 == 0)
			m_20 = m_machine->createSnapshot();
		if (has)
			*xfer == *m_20;
	}
}
