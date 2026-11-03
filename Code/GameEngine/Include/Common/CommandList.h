// FILE: CommandList.h ///////////////////////////////////////////////////////////////////////////
// Desc:   Canonical BFME2 CommandList.
//
// Target facts:
//  - ??0CommandList (0x0030F842) calls ??0GameMessageList (0x0030F562) at 0x0030F845, then
//    stores its own table 0x00C098E0 at +0 (0x0030F84A) and writes nothing else.
//  - ??1CommandList (0x0031105A) stores 0x00C098E0 at 0x0031106B, calls destroyAllMessages
//    (0x0030F854) at 0x00311075 and ~GameMessageList (0x0030F57C) at 0x00311080, which stores
//    0x00C09848 (0x0030F58D). 0x00C09848 is GameMessageList's own table (its constructor stores it
//    at 0x0030F572); 0x00C098E0 is CommandList's. Both sit at +0: one base, no secondary table.
//  - GameEngine::init pushes 0x14 to operator new 0x0002FDA0 (0x0022E3EE, 0x0022E41D) before each
//    call of the constructor (0x0022E403, 0x0022E432): sizeof 0x14, which is GameMessageList's size
//    (MessageStream.h), so CommandList adds no data member.
//  - Table 0x00C098E0 has 18 slots (the word after slot 17 is string data). It differs from
//    0x00C09848 only in slot 0, the deleting destructor ??_GCommandList 0x00311415 (which calls
//    the destructor out of line), and slot 9, SubsystemInterface's reset slot, holding 0x00311092,
//    a tail jump to destroyAllMessages. Slots 1 (init) and 10 (update) hold the shared empty body
//    0x000B3FD0 as GameMessageList's table does, so the class inherits them.
//  - destroyAllMessages (0x0030F854) walks +0x0C through each message's +4, deletes each through
//    its slot 0 and operator delete 0x0002FD60, then clears +0x0C/+0x10. appendMessageList
//    (0x0030F880) walks the same links and calls slot 14, appendMessage (0x0030F894). Both ledger
//    names mangle public (QAE); ?TheCommandList@@3PAVCommandList@@A (0x00A00954) mangles `class`.
// Donor (Zero Hour MessageStream.h) facts: the names CommandList, reset, appendMessageList,
// destroyAllMessages and TheCommandList, and the base GameMessageList.
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef CANONICAL_COMMANDLIST_H
#define CANONICAL_COMMANDLIST_H

#include "MessageStream.h"

class CommandList : public GameMessageList
{
public:
	CommandList();
	virtual ~CommandList();
	virtual void reset();

	void appendMessageList(GameMessage *list);
	void destroyAllMessages();
};

extern CommandList *TheCommandList;

#endif // CANONICAL_COMMANDLIST_H
