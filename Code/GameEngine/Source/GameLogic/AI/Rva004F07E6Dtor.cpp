// cl: /O1 /MD /GX /arch:SSE
// ??1Rva004F07E6@@UAE@XZ @0x004F07E6 51B AIPlayer-like dtor with EH.
// Evidence: stores vtable at [this] twice (0x00C62DC8 then 0x00BBB554 via g_00BBB554), calls rowed AIPlayer::clearTeamsInQueue 0x004F05D6, EH prolog with handler 0x00792CB5 and Unwind@00b92bad, callers 0x004EF443/0x004F111F, prev/next flags.
extern const void *const g_00BBB554[];
class AIPlayer
{
public:
	void clearTeamsInQueue();
};
class SnapBase
{
public:
	virtual ~SnapBase() { *(const void **)this = g_00BBB554; }
};
class Rva004F07E6 : public SnapBase
{
public:
	virtual ~Rva004F07E6();
};
void __cdecl operator delete(void *p);
Rva004F07E6::~Rva004F07E6()
{
	((AIPlayer *)this)->clearTeamsInQueue();
}
