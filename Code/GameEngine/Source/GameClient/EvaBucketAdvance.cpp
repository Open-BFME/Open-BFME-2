// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?advance@Rva000411084@@QAEPAXXZ, retail 0x003F7925 (47B).
// Shard TU: the EvaMessageName TU owns next/messageToName under the same
// flags, and defining the 47B advance there would capture next's out-of-line
// advance call site, so the advance lives here (same-TU visibility law).
// The bucket table shape {unused+0 begin+4 end+8} plus the node shape
// {next+0 name+4 key+8} are read off the rowed next/messageToName pins'
// archaeology notes; bucketIndex resolves via its ledger pin.

#include "ascii_string.h"

// Inline throughout: retail reaches StringBase's private constructors directly
// from the caller rather than through a wrapper, which is what an inlined
// AsciiString constructor looks like.


#include "../../Include/GameClient/Rva000411084.h"

// The begin field reads twice with different scheduling: the count
// computation folds it into a direct `sub ecx,[esi+4]` (single use, no
// homing) while the loop re-fetches it every iteration (`mov eax,[esi+4]`
// plus indexed `mov eax,[eax+edx*4]`), which also defeats the strength
// reduction that turns the index into a bump pointer. The loop therefore
// reads the member through a volatile view of the same field.
#include "../../Include/GameLogic/Rva000427195.h"

struct EvaMessageNameNode
{
	EvaMessageNameNode *m_next;
	AsciiString m_name;
	int m_message;
};

// ?advance@Rva000411084@@QAEPAXXZ
__declspec(noinline) inline void *Rva000411084::advance()
{
	EvaMessageNameNode *node = (EvaMessageNameNode *)m_current;
	Rva000427195 *table = (Rva000427195 *)m_owner;
	unsigned index = (unsigned)table->bucketIndex(&node->m_name);
	unsigned count = (unsigned)(((char *)table->m_endBuckets - (char *)table->m_beginBuckets) >> 2);
	void *head = 0;
	do {
		++index;
		if (index >= count)
			break;
		head = (*(void ** volatile *)&table->m_beginBuckets)[index];
	} while (head == 0);
	return head;
}
// Select-any: another unit compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva000411084Advance absent-from-retail
void *bfmeAnchorRva000411084Advance(Rva000411084 *p) { return p->advance(); }
