// cl: /MD

// VideoPlayer::closeAllStreams, retail 0x006891B0, 36B (vtable slot19).
// Shape-proof: the body calls vtable slot18 in a null-tested loop and
// closes each result through its own slot7, exactly the donor
// closeAllStreams walk (while ((stream = firstStream())) stream->close()).
// Slot18 already reads as the stream-head accessor (rowed 6B global getter
// at 0x006891A0); slot7 is VideoStreamInterface::close, reached here only
// through a virtual call so it needs no pin. Placeholder slot names follow
// the parseSubtitle.cpp TU convention; indices are the proof.

class VideoStreamInterface
{
public:
	virtual void streamSlot00() = 0;
	virtual void streamSlot01() = 0;
	virtual void streamSlot02() = 0;
	virtual void streamSlot03() = 0;
	virtual void streamSlot04() = 0;
	virtual void streamSlot05() = 0;
	virtual void streamSlot06() = 0;
	virtual void close() = 0;
};

class VideoPlayer
{
public:
	virtual ~VideoPlayer() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual VideoStreamInterface *firstStream() = 0;
	virtual void closeAllStreams() = 0;
};

// ?closeAllStreams@VideoPlayer@@UAEXXZ
void VideoPlayer::closeAllStreams()
{
	VideoStreamInterface *stream;

	while ((stream = firstStream()) != 0)
	{
		stream->close();
	}
}
