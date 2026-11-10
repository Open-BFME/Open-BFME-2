/* Target facts (game.dat 1.06; function addresses are RVAs, tables are VAs):
 * ctor 0x0026FFA4 clears +4 and installs 0x00BFAD10; sizeof 8, no own fields.
 * Table 0x00BFAD10: slot 0 the shared deleting-dtor wrapper 0x00395A19 (base
 * teardown 0x0049C38A), slot 1 allow 0x0026119D, slot 2 getPlayerMask 0x0036CC7A.
 * allow 0x0026119D tests the candidate Object's +0x438 bit 0.
 */
#pragma once

#ifndef BFME2_RVA0026119DFILTER_H
#define BFME2_RVA0026119DFILTER_H

#include "PartitionFilter.h"

class Object;

class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

#endif
