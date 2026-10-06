// cl: /O1 /Ob2 /EHsc /MD
// ??1Rva009111B@@UAE@XZ retail 0x0009111B 56B
// Derived VideoPlayer dtor: vptr BC7EA8 then rowed ?rva000907A7@Rva009111B
// under EH state 0 then rowed base ??1VideoPlayer@@UAE@XZ 0x00689350.
// Shape matches Generals BinkVideoPlayer::~BinkVideoPlayer() { deinit(); }.

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class VideoPlayerBase : public SubsystemInterface
{
public:
	virtual ~VideoPlayerBase();
};

class VideoPlayer : public VideoPlayerBase
{
public:
	virtual ~VideoPlayer();
};

class Rva009111B : public VideoPlayer
{
public:
	virtual ~Rva009111B();
	void rva000907A7();
};

Rva009111B::~Rva009111B()
{
	rva000907A7();
}
