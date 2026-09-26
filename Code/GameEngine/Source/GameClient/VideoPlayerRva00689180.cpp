// cl: /DNDEBUG /MD /GX- /O2 /Ob2
//
// ?Rva00689180@VideoPlayer@@UAEXXZ, retail 0x00689180, 21 bytes. Virtual
// slot 9 (offset 0x24) of vtable 0x008E4918 (class of ??1VideoPlayer@@UAE@XZ):
// if (!m_flag18) closeAllStreams(); m_flag18 = false; where closeAllStreams
// is slot 19 (0x4c, rowed at 0x006891B0) and flag is at +0x18.
//
// Donor: VideoPlayerCloseAllStreams.cpp (same VideoPlayer layout with slot09
// placeholder plus slot18 firstStream plus slot19 closeAllStreams; slot indices
// are the proof) plus VideoPlayerDestructorThunk.cpp (same // cl: plus
// VideoPlayerBase). Caller is the tail-jmp at 0x000907B7. No new pins:
// slot19 resolves through the vtable, slot09 is the honest address name.

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
	virtual void Rva00689180() = 0;
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

private:
	unsigned char m_pad04[0x14];
	bool m_flag18;
};

void VideoPlayer::Rva00689180()
{
	if (!m_flag18)
	{
		closeAllStreams();
	}
	m_flag18 = false;
}
