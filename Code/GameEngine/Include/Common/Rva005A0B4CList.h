/* Target facts (game.dat 1.06; function addresses are RVAs):
 * append 0x005A0B4C (22 bytes) takes a struct Rva002BA8F1Listener pointer;
 * it is the only member the image proves, so the layout behind it stays opaque.
 */
#pragma once

#ifndef BFME2_RVA005A0B4CLIST_H
#define BFME2_RVA005A0B4CLIST_H

struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

#endif
