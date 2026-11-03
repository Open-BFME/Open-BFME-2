// Target facts (BFME2 retail RVAs): ScriptCounter has no virtual functions or base.
// 0x00208792/95/98 initialize its value and two flags to zero; no vptr is stored.
// 0x00204A93-9B copy two dwords from the counter into pair+8/+0xC; 0x00204B20-29
// copy that same eight-byte value. 0x00206C13 allocates a 0x20-byte tree node,
// and 0x002087E5 returns node+0x18: sizeof(ScriptCounter) is 8, aligned to 4.
// 0x00208FC9-0x00208FF8 compare the signed integer at +0. setTimer stores that
// value at 0x002095BD and the countdown flag at +4 (0x002095BF); pauseTimer
// clears +4 at 0x002095F6 and restartTimer sets it at 0x00209630.
// setTimer's floating-duration path multiplies by 1000 at 0x00209560 and sets
// the millisecond flag at +5 (0x0020957D); its integer path clears +5 at
// 0x002095BA. Bytes +6/+7 are padding, copied with the flags by the pair helpers.
// update tests node+0x1D at 0x0020D32C to select _adjustVariable's last argument
// at 0x0020D34C/0x0020D379; 0x00205560-80 uses it to format seconds, proving
// the +5 flag's seconds-display purpose. update tests +4 and decrements +0 at
// 0x0020D154-62, independently proving the countdown flag and integer value.
// No standalone ScriptCounter constructor, destructor, copy or assignment row
// exists. 0x002046BB destroys the enclosing string-key pair, not this value.
// Ledger template names at 0x00204A83/0x00204B12 use the struct class-key.

#pragma once

#ifndef __BFME2_SCRIPTCOUNTER_H_
#define __BFME2_SCRIPTCOUNTER_H_

struct ScriptCounter
{
	int m_value;
	bool m_isCountdownTimer;
	bool m_isMillisecondTimer;

	ScriptCounter() : m_value(0), m_isCountdownTimer(false), m_isMillisecondTimer(false) {}
};

#endif
