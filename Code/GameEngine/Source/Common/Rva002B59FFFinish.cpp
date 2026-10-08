// ?rva002B59FF@Rva002B59FF@@QAE_NXZ @0x002B59FF 96B
// cl: /DNDEBUG /MD /EHsc /Ob2
// stlport
//
// Gap-page unlock draining 002B5xxx: a bool predicate with no stack args (ret,
// not ret 4).  Returns false unless the int at +0xF4 is 0 or 4 and the int
// vector at +0xB0 (start +0x14, finish +0x18) is empty; then it consults two
// singletons and two members.  Evidence: callers 0x002B5A6B (adjacent
// 0x002B5A5F, same-this) and 0x003FA8AA; every callee is rowed
// (0x0023C6A4, 0x002BE8D4, 0x002B5073, 0x0063C6A4, 0x006BE8D4).  Layout is a
// TU-local honest view; the original class identity is unproven, so the class
// is address-named.
//
// Four findings fixed the predicate itself, and they are the reusable ones for
// this shape:
//
//  1. The empty test is `vec.size() <= 0`, not `== 0`.  `size() == 0` folds to
//     the `test ecx,0xfffffffc` fast path that skips the element-size division;
//     only the `<= 0` comparison forces stlport to emit `sar ecx,2` and then
//     `jne`, which is what retail has.
//  2. Retail's layout is `xor al,al / pop esi / ret` FIRST and `mov al,1 / pop
//     esi / ret` second, so the FALSE exit is the fall-through block.
//  3. The first singleton is called under a negation: retail's `test al,al` is
//     followed by `je` to the TRUE exit, so a FALSE result answers true.
//  4. The second singleton is NOT negated (its `jne` goes to the false exit) and
//     the mask call is not negated either (its `je` goes to the true exit).
//     Only the first is.
//
// The final gap was the single branch at 0x002B5A48, `jne 0x002B5A57` (the
// false exit) where the early-return form emitted `jne` to the true exit -- the
// `cmp byte [esi+0xe8],al` and its operand were already right, only the block
// that branch targeted was swapped.  Three earlier passes each read that as an
// MSVC block-placement artifact and tried to reach it through the predicate:
// `!m_E8`, `m_E8` with an early `return false`, an `m_E8 == 0 && mask()` && form
// (identical 1-byte diff), a nested else, inverting the mask test and splitting
// the byte test out.  All confirmed the polarity was byte-optimal and none moved
// the branch.
//
// The fix is not the predicate but the EXIT STRUCTURE.  Written as early returns
// MSVC ends the chain by falling through to the last statement, which pins the
// true exit as the fall-through block and sends every guard's forward branch to
// it.  Naming the two exits with labels and branching to them explicitly lets
// each test pick its own successor, and the m_E8 branch lands on the false exit
// exactly as retail has.  Same 96 bytes, all 96 exact.
#include <vector>

typedef bool Bool;

class Rva0023C6A4
{
public:
	bool rva0023C6A4();
};

class Rva002BE8D4
{
public:
	bool rva002BE8D4();
};

// The two singletons the predicate consults.  Both are pinned in
// reverse/symbols.csv, so the globals get their real addresses rather than
// literals: a hard-coded image address here would break the linked build the
// moment data moved.
extern class GameLogic *TheGameLogic;	// VA 0x00DFE78C
extern class Rva002D3627Host *g_00DFEF18;	// VA 0x00DFEF18

class Rva002B5073
{
public:
	bool rva002B5073(int mask);
};

#define TheRva00DFE78C (*(Rva0023C6A4 **)&TheGameLogic)
#define TheRva00DFEF18 (*(Rva002BE8D4 **)&g_00DFEF18)

struct Rva002B59FFHolder
{
	char pad[0x14];
	_STL::vector<int> vec;	// +0x14
};

class Rva002B59FF
{
public:
	bool rva002B59FF();

private:
	char pad00_B0[0xB0];
	Rva002B59FFHolder *m_B0;
	char padB4_CC[0xCC - 0xB4];
	char vecCC[12];
	char padD8_E8[0xE8 - 0xD8];
	bool m_E8;
	char padE9_F4[0xF4 - 0xE9];
	int m_F4;
};

bool Rva002B59FF::rva002B59FF()
{
	if (m_F4 != 0 && m_F4 != 4)
		goto ret_false;
	if (m_B0->vec.size() > 0)
		goto ret_false;
	if (!TheRva00DFE78C->rva0023C6A4())
		goto ret_true;
	if (TheRva00DFEF18->rva002BE8D4())
		goto ret_false;
	if (m_E8 != 0)
		goto ret_false;
	if (((Rva002B5073 *)this)->rva002B5073(4))
		goto ret_false;
	goto ret_true;
ret_false:
	return false;
ret_true:
	return true;
}
