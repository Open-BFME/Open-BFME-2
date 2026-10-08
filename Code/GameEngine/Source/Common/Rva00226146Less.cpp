// cl: /MD
// ?Rva00226146Less@@YG_NHH@Z @0x00226146 (16B): signed int less predicate.
// Retail is frameless: mov ecx [esp+4]; xor eax eax; cmp ecx [esp+8];
// setl al; ret 8. Two stack args popped by callee so __stdcall. setl proves
// signed <. Callers push two dwords then call: 0x00226510 in FUN_006264B3
// and 0x0056DF61 in FUN_0096DF04. No callees. Precedent for Less naming
// and YG_NHH shape: Rva0006038D4CStrLess and Rva0056866ALess.
bool __stdcall Rva00226146Less(int a, int b)
{
	return a < b;
}

// Lead: current BFME1 9cbfb551 RespawnUpdateNewRule.cpp record comparison.
// Native 17097E..17098D follows bounded 170960/30B and returns a full EAX 0/1
// from unsigned receiver-word < argument-word, with ret 4 cleanup.
// Only the raw-word operation and ABI are claimed; record identity is unknown.
class Rva0017097EWord
{
public:
    unsigned int lessThan(const unsigned int *other) const;
    unsigned int m_word;
};
unsigned int Rva0017097EWord::lessThan(const unsigned int *other) const
{
    return m_word < *other;
}
