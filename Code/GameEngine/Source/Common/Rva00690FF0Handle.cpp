// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// The cached audio file a handle points at; the loop buffer asks its +0x44
// interface whether the file has finished loading (the inline twin of the
// rowed 0x00050DBD).
struct Rva000A89E3Ready
{
	virtual bool check(int v);
};

class Gen0002857E
{
public:
	void handle();
	void release();

	char m_pad[0x44];
	Rva000A89E3Ready m_ready;	// +0x44
};

// The ready file a handle hands out (WorldBuilder: AudioFileContainer). Its
// constructors and destructor are separate functions in WorldBuilder
// (0x008E4710/0x008E4730/0x008E47B0); retail keeps the pointer constructor
// next to its one caller and folds the other two with identical bodies. The
// empty constructor is out of line in MilesAudioManager.cpp, so the empty
// returns below call it as retail does (0x00326BE6).
class AudioFileContainer
{
public:
	AudioFileContainer();
	AudioFileContainer(Gen0002857E *target);
	~AudioFileContainer();

	Gen0002857E *m_target;
};

class Rva00690FF0Handle
{
public:
	Rva00690FF0Handle();
	Rva00690FF0Handle(Gen0002857E *target);
	~Rva00690FF0Handle();

	AudioFileContainer rva000A89E3() const;

	Gen0002857E *m_target;
};

// Retail 0x000A89E3: a new reference to the file once it is ready, else an
// empty container. MilesAudioManager's loop-buffer refill passes the result
// to putFileIntoLoopBuffer (0x0005ED1C and its siblings).
AudioFileContainer Rva00690FF0Handle::rva000A89E3() const
{
	if (m_target == 0)
		return AudioFileContainer();
	if (!m_target->m_ready.check(0))
		return AudioFileContainer();
	return AudioFileContainer(m_target);
}

AudioFileContainer::AudioFileContainer(Gen0002857E *target)
{
	m_target = target;
	if (target)
		target->handle();
}

AudioFileContainer::~AudioFileContainer()
{
	if (m_target)
		m_target->release();
}

// ??0Rva00690FF0Handle@@QAE@PAVGen0002857E@@@Z present-unmatched (masked body has 4 identical retail copies; address ambiguous)
Rva00690FF0Handle::Rva00690FF0Handle(Gen0002857E *target)
{
	m_target = target;
	if (target)
		target->handle();
}

Rva00690FF0Handle::~Rva00690FF0Handle()
{
	if (m_target)
		m_target->release();
}

class Rva006910F0Handle
{
public:
	Rva006910F0Handle(Gen0002857E *target);

	Gen0002857E *m_target;
};

// ??0Rva006910F0Handle@@QAE@PAVGen0002857E@@@Z present-unmatched (masked body has 4 identical retail copies; address ambiguous)
Rva006910F0Handle::Rva006910F0Handle(Gen0002857E *target)
{
	m_target = target;
	if (target)
		target->handle();
}

class Rva00691110Handle
{
public:
	Rva00691110Handle(const Rva00691110Handle &other);

	Gen0002857E *m_target;
};

Rva00691110Handle::Rva00691110Handle(const Rva00691110Handle &other)
{
	Gen0002857E *target = other.m_target;
	m_target = target;
	if (target)
		target->handle();
}

class Rva00691040Handle
{
public:
	Rva00691040Handle &operator=(const Rva00691040Handle &other);

	Gen0002857E *m_target;
};

Rva00691040Handle &Rva00691040Handle::operator=(const Rva00691040Handle &other)
{
	Gen0002857E *target = other.m_target;
	Gen0002857E *old = m_target;
	m_target = target;
	if (target)
		target->handle();
	if (old)
		old->release();
	return *this;
}

class Rva00691140Handle
{
public:
	Rva00691140Handle &operator=(const Rva00691140Handle &other);

	Gen0002857E *m_target;
};

// ??4Rva00691140Handle@@QAEAAV0@ABV0@@Z present-unmatched (masked body identical to the rowed Rva00691040Handle::operator= at 0x000A8A43; one retail copy, so the two BFME1 classes fold there)
Rva00691140Handle &Rva00691140Handle::operator=(const Rva00691140Handle &other)
{
	Gen0002857E *target = other.m_target;
	Gen0002857E *old = m_target;
	m_target = target;
	if (target)
		target->handle();
	if (old)
		old->release();
	return *this;
}
