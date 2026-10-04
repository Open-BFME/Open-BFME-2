// cl: /O1 /MD /GX /arch:SSE
// ??1Rva004EF41D@@UAE@XZ @0x004EF41D 56B derived dtor with EH.
// Evidence: stores vtable 0x00C62AF8 at [this], calls rowed AIPlayer::clearTeamsInQueue 0x004F05D6, calls rowed base ??1Rva004F07E6 0x004F07E6, EH prolog handler 0x00792BB5, caller 0x004EF638, chain from 0x004F07E6.
class AIPlayer
{
public:
	void clearTeamsInQueue();
};
class Rva004F07E6
{
public:
	virtual ~Rva004F07E6();
};
class Rva004EF41D : public Rva004F07E6
{
public:
	virtual ~Rva004EF41D();
};
void __cdecl operator delete(void *p);
Rva004EF41D::~Rva004EF41D()
{
	((AIPlayer *)this)->clearTeamsInQueue();
}
