// Target facts: DrawableInfo is a nonvirtual record with no base or vftable. Drawable constructor RVA 0x002797BD initializes its four dwords at +0x248/+0x24C/+0x250/+0x254 with zero (stores 0x002799C8..0x002799DA), then constructs the next member at +0x258 (0x002799E0). W3DGhostObject constructor RVA 0x00063912 initializes the same record at +0xD0 (0x00063963..0x00063975), followed by list pointers at +0xE0/+0xE4 (0x000639A1/0x000639A7): the record occupies 0x10 bytes with fields at +0/+4/+8/+0xC and no vptr.
// Drawable constructor stores 0x00279C5B/0x00279C61/0x00279C67/0x00279C6D bind those fields to zero/this/zero/zero; RenderVolume 0x000F49F9 reads the +4 Drawable pointer before calling its getTransformMatrix at 0x000F4A10. Visibility_Check stores flags at +0xC (0x00071437/0x0007146B/0x000714CF). All constructor stores are inline in their containing objects; the ledger has no DrawableInfo constructor, destructor, assignment or other member row.
// Donor names and types: GeneralsMD/Code/GameEngine/Include/GameClient/DrawableInfo.h declares this struct's ObjectID, Drawable pointer, GhostObject pointer and int in that order, with a zero-initializing constructor. BFME2 W3DGhostObject::xfer RVA 0x00063F78 transfers the +0xD0 ID and +0xDC flags; addGhostObject RVA 0x00063B1E assigns the ghost pointer at +0xD8. These identify embedded render-user-data storage, distinct from the registered Drawable containing it.

#pragma once
#ifndef __BFME2_DRAWABLEINFOCLASS_H_
#define __BFME2_DRAWABLEINFOCLASS_H_

enum ObjectID;
class Drawable;
class GhostObject;

struct DrawableInfo
{
	DrawableInfo() : m_shroudStatusObjectID((ObjectID)0), m_drawable(0), m_ghostObject(0), m_flags(0) {}

	ObjectID m_shroudStatusObjectID;
	Drawable *m_drawable;
	GhostObject *m_ghostObject;
	int m_flags;
};

#endif
