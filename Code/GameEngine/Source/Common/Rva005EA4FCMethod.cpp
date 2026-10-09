// cl: /O1 /MD /EHsc
// Native 77-byte factory tail at 0x005EA136; preserve its opaque identity.
// Its caller at 0x005EA4FC is already rowed in
// GameClient/LivingWorld/InGameUI/StrategicInGameUIDynamicAutoResolveDialog.cpp.
// Retire that caller's obsolete private copy and its unused message-stream view.
class Rva005EA4FCM14
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual bool v07();
};

struct Rva005EA4FCM0C
{
	char m_pad[0x34];
	int m34;
};

struct Rva005EA4FCM08
{
	char m_pad[0x0C];
	Rva005EA4FCM0C *m0c;
	int m_pad10;
	Rva005EA4FCM14 *m14;
	void rva005EA136();
};

// Target 5EA136..5EA183 is the complete 77-byte factory tail called by
// 5EA4FC. Native allocation size16 and rowed constructor5E9FC1 establish
// the temporary's extent; constructor's member8 explains the remaining8.
// The receiver pointer is passed to that constructor, then installed in
// the existing member14 through the rowed pooled setter575674, followed
// by member14 virtual slot4. The pointer field is the setter's one-word
// access view; original subsystem and method identity remain unproven.
class Object;
class Rva00575674 {public:void rva00575674(Object *);};
class Rva005E9FC1 {
public:
Rva005E9FC1(void *);
virtual ~Rva005E9FC1();
private:char m_rest[12];
};
void Rva005EA4FCM08::rva005EA136() {
Rva005E9FC1 *replacement=new Rva005E9FC1(this);
((Rva00575674*)&m14)->rva00575674((Object*)replacement);
m14->v01();
}
