// cl: /DNDEBUG /MD
// ?rva002DA0CF@Rva002DA0CF@@QAENXZ, retail 0x002DA0CF, 132 bytes.
//
// Double getter with the same mode branches as the matched sibling
// ?rva002DA153@Rva002DA153@@QAEMXZ @0x002DA153 (Code/GameEngine/Source/Common/
// Rva002DA153Scale.cpp), in the same subsystem and with the same flags.
//
// Retail's control flow, read from the bytes:
//   0x2DA0CF  push esi / mov esi,ecx / mov eax,[esi+0x38]
//   0x2DA0D5  dec eax / je 0x2DA104        -> mode 1
//   0x2DA0D8  dec eax / jne 0x2DA11F       -> other modes go to the float path
//   0x2DA0DB  (mode 2) push [esi+0x34] / call findObjectByID
//   0x2DA0EB  test eax,eax / je 0x2DA11F
//   0x2DA0F3  shr 0x14 / not al / test al,1
//   0x2DA0FA  jne 0x2DA11F                <- the JOIN POINT
//   0x2DA0FC  fld BfmeZeroRange / pop esi / ret          <- the ZERO RETURN
//   0x2DA104  (mode 1) call TheGameClient+0x40
//   0x2DA114  test eax,eax / je 0x2DA11F
//   0x2DA116  cmp byte [eax+0x44A],0
//   0x2DA11D  jmp 0x2DA0FA                <- mode 1 hands control to mode 2
//   0x2DA11F  (float path) movss xmm0,[esi+0x24] ...
//
// The two arms share ONE test block and one zero-return block. Mode 2 falls
// through its own condition into the join at 0x2DA0FA, and mode 1 reaches it
// by an UNCONDITIONAL jmp whose flags are consumed by mode 2's jne: there is
// only one copy of fld/pop/ret, and no second copy exists to merge.
//
// The banked attempt (score 0.98) had everything except that branch, and was
// one instruction from the target: retail `jmp 0x2DA0FA` against ours
// `je 0x2DA0FC`. It wrote each arm as "break on failure, then return", which
// gives mode 1 its own conditional branch to the shared return. Writing each
// arm as "return on success, then break" -- and listing mode 1 BEFORE mode 2 --
// makes the arm bodies end in a plain fall-through, so MSVC merges them into
// the single conditional the join expects. Both changes are required: the
// positive form alone (mode 2 still first) splits the arms again.
//
// The mode dispatch is a decrement cascade (dec/je, dec/jne), which is what
// `switch (m_38)` with mode 1 first produces; the reverse order rotates the
// dispatch and costs 10 bytes.
//
// Evidence: TheGameLogic->findObjectByID row 0x49DC5, TheGameClient virtual
// slot 0x40, BfmeZeroRange at 0x00BC26F8, g_00BBB9AC, the rowed neighbour
// 0x002DA153 for the identical branch shape at float width. Body is
// 0x002DA0CF..0x002DA153 with `ret` at 0x002DA152 and 0xCC padding after.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;
extern const float BfmeZeroRange;
extern float g_00BBB9AC;

struct Sub08
{
	char m_pad[0x10];
	float m_10;
};

struct ClientRet40
{
	char m_pad[0x44A];
	unsigned char m_44A;
};

class ClientFrameSubsystem
{
public:
	virtual void s000();
	virtual void s001();
	virtual void s002();
	virtual void s003();
	virtual void s004();
	virtual void s005();
	virtual void s006();
	virtual void s007();
	virtual void s008();
	virtual void s009();
	virtual void s010();
	virtual void s011();
	virtual void s012();
	virtual void s013();
	virtual void s014();
	virtual void s015();
	virtual ClientRet40 *s016(int id);  // +0x40
};

class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Rva002DA0CF
{
public:
	double rva002DA0CF();

private:
	char m_pad00[0x08];
	Sub08 *m_08;
	char m_pad0C[0x24 - 0x0C];
	float m_24;
	char m_pad28[0x2C - 0x28];
	float m_2C;
	char m_pad30[0x34 - 0x30];
	int m_34;
	int m_38;
};

double Rva002DA0CF::rva002DA0CF()
{
	switch (m_38) {
	case 1: {
		ClientRet40 *p = ((ClientFrameSubsystem *)TheGameClient)->s016(m_34);
		if (p != 0 && p->m_44A == 0)
			return BfmeZeroRange;
		break;
	}
	case 2: {
		Object *obj = TheGameLogic->findObjectByID((ObjectID)m_34);
		if (obj != 0) {
			unsigned int v = *(unsigned int *)((char *)obj + 0x98) >> 0x14;
			unsigned char b = (unsigned char)~(unsigned char)v;
			if ((b & 1) == 0)
				return BfmeZeroRange;
		}
		break;
	}
	default:
		break;
	}
	if (m_24 == g_00BBB9AC) {
		if (m_08 != 0)
			return m_08->m_10 * m_2C;
		return m_2C * 0.5;
	}
	return m_2C * m_24;
}
