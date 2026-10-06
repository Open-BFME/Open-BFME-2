// cl: /MD
// Scoped lock around the subsystem at 0xDFDC14 (theBfmeDfdc14)
// ??0Rva0023C565@@QAE@XZ @ 0x0023C565 22B: calls theBfmeDfdc14->lock()
// ??1Rva0023C565@@QAE@XZ @ 0x0023C57B 16B: calls theBfmeDfdc14->unlock()

class Rva001DBAA4
{
public:
	void lock();
	void unlock();
};

extern Rva001DBAA4 *theBfmeDfdc14;

#pragma comment(linker, "/alternatename:?theBfmeDfdc14@@3PAVRva001DBAA4@@A=?theBfmeDfdc14@@3PAVAudioManager@@A")

class Rva0023C565
{
public:
	Rva0023C565();
	~Rva0023C565();
};

Rva0023C565::Rva0023C565()
{
	if (theBfmeDfdc14)
		theBfmeDfdc14->lock();
}

Rva0023C565::~Rva0023C565()
{
	if (theBfmeDfdc14)
		theBfmeDfdc14->unlock();
}
