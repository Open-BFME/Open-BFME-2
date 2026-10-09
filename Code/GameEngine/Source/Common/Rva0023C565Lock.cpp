// cl: /MD
// Scoped lock around the subsystem at 0xDFDC14 (theBfmeDfdc14)
// ??0Rva0023C565@@QAE@XZ @ 0x0023C565 22B: calls theBfmeDfdc14->lock()
// Native 0x0023C57B release is rowed in DisplayMovieOpenRva0025C97E.cpp.

class Rva001DBAA4
{
public:
	void lock();
	void unlock();
};

extern class GameWindowTransitionsHandler *TheTransitionHandler;


class Rva0023C565
{
public:
	Rva0023C565();
	~Rva0023C565();
};

Rva0023C565::Rva0023C565()
{
	if ((*(Rva001DBAA4 **)&TheTransitionHandler))
		(*(Rva001DBAA4 **)&TheTransitionHandler)->lock();
}
