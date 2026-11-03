// Target facts: GameSlot ctor RVA 0x003FFB87 stores zero dword at +0x38 and RVA 0x003FFB8A zero word at +0x3C; setState RVAs 0x003FFD90/0x003FFD99 read record offsets 0/4 and 0x003FFD96/0x003FFD9F copy them to +0x38/+0x3C. The next GameSlot field starts at +0x40 (copy ctor RVA 0x0022966C), bounding the record at 8 bytes.
// GameSlot reset RVA 0x003FF574 initializes only the temporary's port word before the dword read at 0x003FF578, leaving two padding bytes untouched. GameSlotConnectInfo has no base, vptr or virtual functions and no rowed out-of-line special members. The table VA 0x00BE7420 at GameSlot ctor RVA 0x003FFB60 belongs to GameSlot; its destructor RVA 0x00229547 restores Snapshot's VA 0x00BBB554 at GameSlot +0, outside this record.
// Donor names: Zero Hour GeneralsMD GameNetwork/GameInfo.h declares GameSlotConnectInfo as a struct with m_nat then m_port; retail setState's PBU spelling confirms the struct class-key. No donor header or shim is required.
#pragma once

#ifndef BFME2_GAME_SLOT_CONNECT_INFO_H
#define BFME2_GAME_SLOT_CONNECT_INFO_H

struct GameSlotConnectInfo
{
	GameSlotConnectInfo() : m_nat(0), m_port(0) {}

	unsigned int m_nat;
	unsigned short m_port;
};

#endif
