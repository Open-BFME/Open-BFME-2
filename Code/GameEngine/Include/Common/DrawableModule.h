// Target facts (RVAs unless marked VA): DrawableModule ctor 0x00306B19 stores VA 0x00C07E54 at +0, ModuleData at +4 and the result of Thing slot +0x10 at +8 (sizeof 0x0C).
// VA 0x00C07E54 has eleven slots: Module's nine, then slots 9 and 10 both 0x000D43D0 (return zero), unnamed in retail. Slot 2, 0x00252B84, returns VA 0x00BEFE94 "DrawableModule".
// ~DrawableModule and ~Module are empty and inline; DrawModule's destructor 0x000CEB6F reaches Snapshot's table restore through 0x0049B47C.
#pragma once

#ifndef __BFME2_DRAWABLEMODULE_H_
#define __BFME2_DRAWABLEMODULE_H_

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "Module.h"

class Thing;
class Drawable;

class DrawableModule : public Module
{
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
	virtual void *vslot09() { return 0; }
	virtual void *vslot10() { return 0; }

protected:
	virtual ~DrawableModule();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
	Drawable *getDrawable() { return m_drawable; }
	const Drawable *getDrawable() const { return m_drawable; }
	Drawable *m_drawable;
};

#endif
