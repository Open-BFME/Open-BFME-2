#pragma once
// BFME2 bounded retail ABI. See reverse/attempt_support/streakdraw-canonical-qc10-20261031/.
// Snapshot's established name-slot surface matches the native slot2 getter.
#ifndef BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_STREAK_RESTORE_NAME_SLOT
#endif
#include "../../../../../../GameEngine/Include/Common/Module.h"
#ifdef BFME_STREAK_RESTORE_NAME_SLOT
#undef BFME_SNAPSHOT_NAME_SLOT
#undef BFME_STREAK_RESTORE_NAME_SLOT
#endif
class Thing;
class Drawable;
class BfmeStreakObject;
class TextureClass;
// Native306B19 stores ModuleData4 and Drawable8; C07E54 bounds11slots.
// These unregistered base views expose only the target-proven consumed ABI.
class DrawableModule : public Module {
public:
 DrawableModule(Thing *,const ModuleData *);
protected:
 virtual ~DrawableModule();
private:
 virtual void _bfme_drawable_slot9();
 virtual void _bfme_drawable_slot10();
protected:
 Drawable *m_drawable; //8
};
// NativeB19A1 calls DrawableModule and installs BC9690; exactly62slots.
// Opaque private declarations reserve known positions only. No callable
// signature or provider identity is claimed for those declarations.
class DrawModule : public DrawableModule {
public:
 DrawModule(Thing *,const ModuleData *);
protected:
 virtual ~DrawModule();
 virtual void loadPostProcess(); //1
 virtual const char *GetSnapshotName() const; //2
 virtual void xfer(Xfer *); //3
private:
 virtual void _bfme_draw_slot11();
 virtual void _bfme_draw_slot12();
 virtual void _bfme_draw_slot13();
 virtual void _bfme_draw_slot14();
 virtual void _bfme_draw_slot15();
protected:
 // Neutral slot spelling from the owned derived override, not a recovered base provider.
 virtual void Rva000CFF4C(bool); //16
private:
 virtual void _bfme_draw_slot17();
 virtual void _bfme_draw_slot18();
 virtual void _bfme_draw_slot19();
 virtual void _bfme_draw_slot20();
 virtual void _bfme_draw_slot21();
 virtual void _bfme_draw_slot22();
 virtual void _bfme_draw_slot23();
 virtual void _bfme_draw_slot24();
 virtual void _bfme_draw_slot25();
 virtual void _bfme_draw_slot26();
 virtual void _bfme_draw_slot27();
 virtual void _bfme_draw_slot28();
 virtual void _bfme_draw_slot29();
 virtual void _bfme_draw_slot30();
 virtual void _bfme_draw_slot31();
 virtual void _bfme_draw_slot32();
 virtual void _bfme_draw_slot33();
 virtual void _bfme_draw_slot34();
 virtual void _bfme_draw_slot35();
 virtual void _bfme_draw_slot36();
 virtual void _bfme_draw_slot37();
 virtual void _bfme_draw_slot38();
 virtual void _bfme_draw_slot39();
 virtual void _bfme_draw_slot40();
 virtual void _bfme_draw_slot41();
 virtual void _bfme_draw_slot42();
 virtual void _bfme_draw_slot43();
 virtual void _bfme_draw_slot44();
 virtual void _bfme_draw_slot45();
 virtual void _bfme_draw_slot46();
 virtual void _bfme_draw_slot47();
 virtual void _bfme_draw_slot48();
 virtual void _bfme_draw_slot49();
 virtual void _bfme_draw_slot50();
 virtual void _bfme_draw_slot51();
 virtual void _bfme_draw_slot52();
 virtual void _bfme_draw_slot53();
 virtual void _bfme_draw_slot54();
 virtual void _bfme_draw_slot55();
 virtual void _bfme_draw_slot56();
 virtual void _bfme_draw_slot57();
 virtual void _bfme_draw_slot58();
 virtual void _bfme_draw_slot59();
 virtual void _bfme_draw_slot60();
 virtual void _bfme_draw_slot61();
};
class W3DStreakDraw : public DrawModule {
public:
 W3DStreakDraw(Thing *,const ModuleData *);
 virtual ~W3DStreakDraw(); //0
 virtual NameKeyType getModuleNameKey() const; //4
 virtual void Rva000CFF4C(bool); //16, native CFF4C
protected:
 virtual void loadPostProcess(); //1
 virtual const char *GetSnapshotName() const; //2
 virtual void xfer(Xfer *); //3
public:
 // Existing nonvirtual owned spellings do not admit additional virtual providers.
 void rva000D0091();
 void rva000D0459(void *,void *,void *);
 void rva000D0461(void *);
 const char *name() const;
 static Module *friend_newModuleInstance(Thing *,const ModuleData *);
private:
 BfmeStreakObject *m_streak; //C
 TextureClass *m_texture; //10: storage projection only, lifetime not reconstructed here
};
