// cl: /O1 /DNDEBUG /MD
//
// ?clearTeamsInQueue@AIPlayer@@IAEXXZ, retail 0x00098A6F, 61 bytes.
// AIPlayer queue teardown: drops the two team queues at +0xE24 (build) and
// +0xE20 (ready) that the 0x98BD4 creator fills through the rowed 0x62AF20
// helper. Called by the AISkirmishPlayer destructor (0x98B8B) and twice on
// the creator's failure paths (0x98C02/0x98C2A); the body bytes are unique
// in .text (not an ICF alias), prev is a C2 ret, next is a frame prologue,
// and only the two internal je arms target the interior.
//
// BFME1 donor (AIPlayer.cpp) is two removeAll calls with the deleteQueue
// callback; BFME2 diverges to an explicit stdcall function table (9 slots):
// each object publishes its vtable pointer at +0 and takes itself as an
// explicit argument (push obj / call [table+slot]), so the callees need no
// pins and leave no relocs. Slot 2 (+8) is the removeAll step both queues
// use; slot 8 (+0x20) is the extra delete step the build queue runs first.
// The build pointer is reloaded for the second call (a call clobbers it and
// frameless code keeps no callee-saved copy), and both slots are nulled with
// the and-zero idiom (= 0 compiles to AND at /O1, Sibling OrnamentData
// precedent). The ready slot goes through a (char *)this + 0xE20 pointer,
// which is what emits the mid-body add esi,0xE20; after that this is dead.
// Which queue is build vs ready follows the donor's call order; the vtable
// slot roles are by shape (the table callees carry no identities).

struct AIQueueList;

typedef void (__stdcall *AIQueueSlotFn)(AIQueueList *queue);

struct AIQueueVTable
{
	AIQueueSlotFn slot0;
	AIQueueSlotFn slot1;
	AIQueueSlotFn removeAll;
	AIQueueSlotFn slot3;
	AIQueueSlotFn slot4;
	AIQueueSlotFn slot5;
	AIQueueSlotFn slot6;
	AIQueueSlotFn slot7;
	AIQueueSlotFn deleteQueued;
};

struct AIQueueList
{
	AIQueueVTable *m_vtable;
};

class AIPlayer
{
protected:
	void clearTeamsInQueue();

private:
	unsigned char m_pad[0xE20];
	AIQueueList *m_readyQueue; // +0xE20
	AIQueueList *m_buildQueue; // +0xE24
};

// ?clearTeamsInQueue@AIPlayer@@IAEXXZ @0x00098A6F
void AIPlayer::clearTeamsInQueue()
{
	if (m_buildQueue != 0)
	{
		m_buildQueue->m_vtable->deleteQueued(m_buildQueue);
		m_buildQueue->m_vtable->removeAll(m_buildQueue);
		m_buildQueue = 0;
	}
	AIQueueList **slot = (AIQueueList **)((char *)this + 0xE20);
	if (*slot != 0)
	{
		(*slot)->m_vtable->removeAll(*slot);
		*slot = 0;
	}
}
