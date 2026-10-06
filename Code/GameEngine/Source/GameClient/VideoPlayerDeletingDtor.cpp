// cl: /MD

// Scalar deleting destructor (vtable slot0) for VideoPlayer, retail
// 0x006894E0, 28B flag-test shape. The destructor itself is rowed at
// 0x00689350 (VideoPlayerDestructorThunk.cpp) and that row wins the symbol
// map, so this TU's in-class destructor is only a codegen stand-in: the
// three-vptr MI model keeps it from inlining and the emitted ??_G calls out
// to the rowed destructor plus the pinned scalar operator delete, exactly
// the OpaqueScalarDeletingDtors.cpp arrangement with the real owner name.

class VideoPlayerMiBase1
{
public:
	virtual ~VideoPlayerMiBase1();

private:
	char m_pad04[8];
};

class VideoPlayerMiBase2
{
public:
	virtual void f1();
};

class VideoPlayerMiBase3
{
public:
	virtual void f2();
};

class VideoPlayer : public VideoPlayerMiBase1, public VideoPlayerMiBase2, public VideoPlayerMiBase3
{
public:
	virtual ~VideoPlayer()
	{
	}
};

// Anchor: forces out-of-line emission of the in-class destructor COMDAT,
// including the scalar deleting destructor.
void VideoPlayerDeletingDtorAnchor(VideoPlayer *instance)
{
	instance->VideoPlayer::~VideoPlayer();
}
