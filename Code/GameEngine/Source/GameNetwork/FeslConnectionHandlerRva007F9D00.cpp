// ?rva007F9D00@FeslConnectionHandler@@QAEXPAURva00800E50Header@@@Z
// cl: /O2 /GX-
// BFME 2 RVA 0x00666250, 710 bytes: FESL incoming-packet dispatch.
// Clean C++ donor: Open-BFME-1 10af19f44a89ab7ecc23195bb9a842ceafbc02c9,
// game/GameEngine/Source/GameNetwork/FeslConnectionHandlerRva007F9D00.cpp,
// BFME 1 RVA 0x007F9D00. Original symbols are unknown; class and method
// labels retain the donor's descriptive/address-derived names.
//
// Target evidence: native callback table VA 0x00CE32D4 places this body in
// slot 3 after the already-matched onConnectionMade/onConnectionBroken and
// the conn-error callback. The native body consumes one stack argument and
// returns with ret 4. It walks 32 slots at this+0x24 in steps of 0x1C,
// uses hub this+0x20 and dispatch depth this+0x10, and calls the transactor
// with this-4. These offsets independently support the scoped views below.
// Header-to-message fields and branch behavior follow the clean donor;
// native loads/stores, nine string references and every byte verify them.
// The original packet/header and diagnostic class names remain unknown.
//
// Native call 0x0066638C passes a message and slot to helper 0x00665D20,
// with ECX=this-4. That helper reads slot+0x18 and returns ret 8 at
// 0x00665EBB. This establishes the new member-call pin independently of
// the donor's generated 0x007F97B0 body; it does not claim that body recovered.
// Replies complete blocking buffers or nonblocking callbacks; unmatched
// packets use the existing TXN dispatch. The diagnostic literals anchor
// those paths independently of the donor's interpretation.

#include <string.h>

struct Rva00800E50Header
{
	unsigned m_type;
	int m_flags;
	const char *m_text;
	unsigned m_textLength;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
};

void __cdecl Rva007F91D0(Rva00800E50Header *header, const char *direction);

#include "../../Include/GameNetwork/Rva007EB810Diag.h"

Rva007EB810Diag *Rva007EB810Get();

#pragma intrinsic(memcpy)

class Rva007E8810Message
{
public:
	Rva007E8810Message();
	~Rva007E8810Message();
	int getError();
	void setError(int code);

	void *m_vtable;
	int m_04;
	int m_08;
	int m_0C;
	char *m_10;
	unsigned m_14;
	unsigned m_18;
	unsigned m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;
};

struct Rva007FA170Slot
{
	int m_00;
	int m_04;
	Rva007E8810Message *m_08;
	void (__cdecl *m_0C)(Rva007E8810Message *message, void *context);
	void *m_10;
	int m_14;
	int m_18;
};

class Rva007F9D00Hub
{
public:
	virtual void v0();
	virtual int v1(Rva007E8810Message *message);
	virtual int v2(Rva007E8810Message *message);
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual bool v6(Rva007E8810Message *message);
	virtual bool v7(Rva007E8810Message *message);
};

class Rva007FA2C0
{
public:
	bool onTxn(Rva007E8810Message *message);
	void rva007F97B0(Rva007E8810Message *message, Rva007FA170Slot *slot);
	void clearSlot(void *slot);
};

class FeslConnectionHandler
{
public:
	void rva007F9D00(Rva00800E50Header *header);

private:
	Rva007FA2C0 *transactor() { return (Rva007FA2C0 *)((char *)this - 4); }

	void *m_vtable;
	char m_pad04[0x0C];
	int m_dispatchDepth;
	char m_pad14[0x0C];
	Rva007F9D00Hub *m_hub;
	Rva007FA170Slot m_slots[0x20];
};

void FeslConnectionHandler::rva007F9D00(Rva00800E50Header *header)
{
	Rva007E8810Message message;
	message.m_10 = (char *)header->m_text;
	message.m_14 = header->m_textLength;
	message.m_20 = header->m_flags;
	message.m_1C = header->m_type;
	message.m_04 = header->m_18;
	message.m_08 = header->m_1C;
	message.m_0C = header->m_20;

	message.setError(m_hub->v2(&message));
	int tid = m_hub->v1(&message);
	message.m_28 = tid;
	bool report = m_hub->v7(&message);

	if (tid != 0 && !m_hub->v6(&message))
	{
		Rva007FA170Slot *slot;
		int i;
		for (i = 0, slot = m_slots; i < 0x20; ++i, ++slot)
		{
			if (slot->m_00 == tid)
				goto found;
		}
		slot = 0;
found:
		if (!slot)
		{
			if (report)
				Rva007F91D0(header, "<-[bad]");
			else
			{
				Rva007F91D0(header, "<-U");
				if (!transactor()->onTxn(&message))
					Rva007EB810Get()->log(0, "tid %d not found\n", tid);
			}
			return;
		}

		if (m_hub->v7(&message))
		{
			transactor()->rva007F97B0(&message, slot);
			return;
		}
		if (slot->m_08)
		{
			Rva007F91D0(header, "<-B");
			slot->m_08->m_20 = message.m_20;
			slot->m_08->m_1C = message.m_1C;
			slot->m_08->setError(message.getError());
			unsigned length = header->m_textLength;
			if (slot->m_08->m_14 < length)
				slot->m_08->setError(-100);
			else
			{
				slot->m_08->m_18 = length;
				memcpy(slot->m_08->m_10, header->m_text, header->m_textLength);
			}
			slot->m_04 = 2;
			return;
		}
		if (slot->m_0C)
		{
			Rva007F91D0(header, "<-N");
			++m_dispatchDepth;
			slot->m_0C(&message, slot->m_10);
			--m_dispatchDepth;
			transactor()->clearSlot(slot);
			return;
		}
		Rva007F91D0(header, "<-?");
		Rva007EB810Get()->log(0, "tid %d state is wacky\n", tid);
		return;
	}

	if (report)
		Rva007F91D0(header, "<-[bad]");
	else
	{
		Rva007F91D0(header, "<-A");
		transactor()->onTxn(&message);
	}
}
