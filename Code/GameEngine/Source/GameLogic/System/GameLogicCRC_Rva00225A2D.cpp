// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/System

// BFMECRCWriter::BFMECRCWriter(bool) from the donor GameLogicCRC.cpp. The base
// block-writer ctor is retail 0x0060D1F7 (the donor's own comment fixes the
// ctor/dtor RVAs 0x0060D1F7/0x0060D0B3); full lands at +0x40 and crc at +0x44
// after the base's vptr + 0x3C bytes. Only the target ctor is emitted here; the
// donor's GameLogic::getCRC body is omitted.
class BfmeByteStream;

class Rva009D8630BlockWriter
{
public:
	Rva009D8630BlockWriter();
	virtual ~Rva009D8630BlockWriter();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();

private:
	char data[0x3c];
};

class BFMECRCWriter : public Rva009D8630BlockWriter
{
public:
	BFMECRCWriter( bool full );

	bool full;			// +0x40
	unsigned int crc;	// +0x44
};

BFMECRCWriter::BFMECRCWriter( bool full ) : full( full ), crc( 0 )
{
}
