// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?Rva002FDB93Callback@@YAXPAVObject@@PAX@Z @0x002FDB93 49B
// Iteration callback that keeps the highest attack priority seen: for each
// target it asks the user data's AttackPriorityInfo (+4) for
// getPriority(hunter (+8), target, true) -- 0x00357CDE, pinned -- and
// raises the running best at +0 when exceeded. The AI-region callers at
// 0x002FF61C and 0x002FFB8B push this function's address with that record.
// Retail compares with fcompi, which MSVC 7.1 emits only under /arch:SSE.
// Names are address-derived.
class Object;
class AttackPriorityInfo
{
public:
	float getPriority(const Object *hunter, const Object *target, bool flag) const;
};
struct Rva002FDB93Best
{
	float m_bestPriority;			// +0x00
	const AttackPriorityInfo *m_info;	// +0x04
	const Object *m_hunter;			// +0x08
};
void __cdecl Rva002FDB93Callback(Object *target, void *userData)
{
	Rva002FDB93Best *best = (Rva002FDB93Best *)userData;
	float priority = best->m_info->getPriority(best->m_hunter, target, true);
	if (priority > best->m_bestPriority)
		best->m_bestPriority = priority;
}
