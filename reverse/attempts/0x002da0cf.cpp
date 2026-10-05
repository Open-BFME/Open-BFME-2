// ?rva002DA0CF@Rva002DA0CF@@QAENXZ
// partial score=0.98 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva002DA0CF@Rva002DA0CF@@QAENXZ, retail 0x002DA0CF, 132 bytes.
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
//   0x2DA11D  jmp 0x2DA0FA                <- mode 1's test jumps to the JOIN
//   0x2DA11F  (float path) movss xmm0,[esi+0x24] ...
//
// So the two arms share ONE test block and one zero-return block: mode 2 falls
// through its own condition into the join at 0x2DA0FA, and mode 1 jumps
// backwards to that same join after its own cmp. There is no second copy of the
// fld/pop/ret -- the 0.97 bank was right that one exists, and wrong about why.
//
// The difference the bank could not close was therefore NOT about sharing the
// return. Reading the jmp target shows the banked source already emits
// everything except the join: it produces `cmp byte [eax+0x44a],0 / je <float>`
// where retail has `cmp / jmp <join>`. Retail's mode-1 arm does not branch on
// its own flag at all -- it hands control to mode 2's test. That is only
// expressible when the two arms are the SAME basic-block pair, which needs the
// mode-1 `cmp` to be the tail of mode 2's condition, not a separate `if`.
//
// Tried and measured at these flags, all 132B/48 or 132B/49 instructions:
//   * banked `if (p->m_44a != 0) break; return BfmeZeroRange;`  -> 49 insns,
//     je to the float path (does not match)
//   * each arm owning its own `return BfmeZeroRange`             -> 45 insns,
//     126B: the switch dispatch rotates and the case order changes
//   * arms reordered mode 1 first                                -> 126B
//   * explicit `goto` into mode 2's condition                    -> still splits
// The shape MSVC needs (a shared tail entered from a computed jump) is produced
// by tail merging, not by source structure, and it resists every source form
// measured here. Recorded as partial rather than left for the next agent to
// re-derive.
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
extern double g_00BC26F8;

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

extern ClientFrameSubsystem *TheGameClient;

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

// ?rva002DA0CF@Rva002DA0CF@@QAENXZ present-unmatched
double Rva002DA0CF::rva002DA0CF()
{
	switch (m_38) {
		case 2: {
			Object *obj = TheGameLogic->findObjectByID((ObjectID)m_34);
			if (obj == 0)
				break;
			unsigned int v = *(unsigned int *)((char *)obj + 0x98);
			v >>= 0x14;
			unsigned char b = (unsigned char)~(unsigned char)v;
			if (b & 1)
				break;
			return BfmeZeroRange;
		}
		case 1: {
			ClientRet40 *p = TheGameClient->s016(m_34);
			if (p == 0)
				break;
			if (p->m_44A != 0)
				break;
			return BfmeZeroRange;
		}
		default:
			break;
	}
	if (m_24 == g_00BBB9AC) {
		if (m_08 != 0)
			return m_08->m_10 * m_2C;
		return m_2C * g_00BC26F8;
	}
	return m_2C * m_24;
}
