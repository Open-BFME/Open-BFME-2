// ?aiDoCommand@AIUpdateInterface@@UAEXPBUAICommandParms@@@Z
// partial score=0.995 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Reference: ZH AIUpdate.cpp::aiDoCommand; donor 9cbfb551fe20dae985f91f2319d8997287b6a705.
// Identity: DozerAIUpdate::aiDoCommand calls this base; secondary vtable slot0.
// BFME2 command IDs, argument locations and handler slots are retail jump-table facts.
// Unnamed handler slots retain their slot numbers rather than guessed semantics.

#include "../../../../../../reference/open-bfme-1/game/GameEngine/Source/GameLogic/command_source_type.h"
struct Coord3D { float x,y,z; };
class Object;
struct AICommandParms {
 int m_cmd; CommandSourceType m_cmdSource; Coord3D m_pos;
 Object *m_obj; void *m_extra18; void *m_team;
 char m_coords[12]; void *m_waypoint; void *m_polygon;
 int m_intValue; float m_floatValue; char m_damage[0x7c]; void *m_commandButton;
};
class AIUpdateInterface;
class Rva001E3591 { public: bool rva001E3591(); };
struct Rva00351570Src;
class Rva00351570 { public: void rva00351570(const Rva00351570Src &); char m_data[0xC4]; };
class Module;
enum NameKeyType { NAMEKEY_INVALID = 0 };
class StancesBehavior { public: void rva0045F21C(); };
NameKeyType Rva0045EE2CGet();
enum ObjectStatusTypes { STATUS_26=0x26, STATUS_41=0x41, STATUS_46=0x46, STATUS_4A=0x4A };
class Object {
public:
 bool testStatus(ObjectStatusTypes) const;
 Module *findModule(NameKeyType) const;
 void *rva0028C1A9() const;
 void rva00293105();
 char m_unknown00[0x1c9];
 unsigned char m_flags1C9;
 char m_unknown1CA[0x258-0x1ca];
 AIUpdateInterface *m_ai;
 char m_unknown25C[0x274-0x25c];
 Object *m_containedBy;
};
class Rva0026228F { public: void rva0026228F(int, int); };
class Rva00262271 { public: void rva00262271(int, int, int); };
class CommandRedirectInterface {
public:
 virtual void slot0(); virtual void stop(); virtual void slot2(); virtual bool testObject(Object *);
};
extern unsigned char g_00DFE7A8;
class AICommandInterface { public: virtual void aiDoCommand(const AICommandParms *)=0; };
class AIUpdateInterface24 { public: virtual void slot0(); };
class UpdateModule {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13(const Coord3D *, float, CommandSourceType);
 virtual void slot14(const Coord3D *, float, int, CommandSourceType);
 virtual void slot15(Object *, CommandSourceType);
 virtual void slot16(const Coord3D *, CommandSourceType);
 virtual void slot17(const Coord3D *, int, CommandSourceType);
 virtual void slot18(Object *, CommandSourceType);
 virtual void slot19(const Coord3D *, CommandSourceType);
 virtual void slot20(const Coord3D *, CommandSourceType);
 virtual void slot21(const Coord3D *, CommandSourceType);
 virtual void slot22(const Coord3D *, CommandSourceType);
 virtual void slot23(Object *, CommandSourceType);
 virtual void slot24(CommandSourceType);
 virtual void slot25(const Coord3D *, CommandSourceType);
 virtual void slot26(void *, CommandSourceType);
 virtual void slot27(void *, CommandSourceType);
 virtual void slot28(void *, CommandSourceType);
 virtual void slot29(void *, CommandSourceType);
 virtual void slot30(const void *, Object *, CommandSourceType, bool);
 virtual void slot31(const void *, Object *, float, CommandSourceType);
 virtual void slot32(const void *, Object *, float, CommandSourceType);
 virtual void slot33(const Coord3D *, CommandSourceType);
 virtual void slot34(Object *, int, CommandSourceType);
 virtual void slot35(Object *, CommandSourceType);
 virtual void slot36(Object *, CommandSourceType);
 virtual void slot37(const Coord3D *, CommandSourceType);
 virtual void slot38(Object *, int, CommandSourceType);
 virtual void slot39(void *, int, CommandSourceType);
 virtual void slot40(const Coord3D *, int, CommandSourceType);
 virtual void slot41(Object *, CommandSourceType);
 virtual void slot42(void *, int, bool, CommandSourceType);
 virtual void slot43(CommandSourceType);
 virtual void slot44(Object *, CommandSourceType);
 virtual void slot45(Object *, CommandSourceType);
 virtual void slot46(Object *, CommandSourceType);
 virtual void slot47(Object *, CommandSourceType);
 virtual void slot48(Object *, CommandSourceType);
 virtual void slot49(Object *, CommandSourceType);
 virtual void slot50(Object *, CommandSourceType);
 virtual void slot51(Object *, CommandSourceType);
 virtual void slot52(const Coord3D *, CommandSourceType);
 virtual void slot53(Object *, CommandSourceType);
 virtual void slot54(Object *, const Coord3D *, CommandSourceType);
 virtual void slot55(Object *, const void *, CommandSourceType);
 virtual void slot56(Object *, CommandSourceType);
 virtual void slot57(Object *, const Coord3D *, CommandSourceType);
 virtual void slot58(Object *, const void *, CommandSourceType);
 virtual void slot59(Object *, const Coord3D *, CommandSourceType);
 virtual void slot60(int, CommandSourceType);
 virtual void slot61(const void *, CommandSourceType);
 virtual void slot62(int, CommandSourceType);
 virtual void slot63(const Coord3D *, int, CommandSourceType);
 virtual void slot64(Object *, int, CommandSourceType);
 virtual void slot65(void *, int, CommandSourceType);
 virtual void slot66(Object *, const Coord3D *, int, CommandSourceType);
 virtual void slot67(void *, int, CommandSourceType, const Coord3D *);
 virtual void slot68(void *, CommandSourceType);
 virtual void slot69(Object *, CommandSourceType);
 virtual void slot70(const Coord3D *, CommandSourceType);
 virtual void slot71();
 virtual void slot72(void *, CommandSourceType);
 virtual void slot73(void *, const Coord3D *, CommandSourceType);
 virtual void slot74(void *, Object *, CommandSourceType);
 virtual void slot75(void *, CommandSourceType);
 virtual void slot76(CommandSourceType);
 virtual void slot77(CommandSourceType);
 virtual void slot78(void *, CommandSourceType);
 virtual void slot79(Object *, CommandSourceType);
 virtual void slot80(int, CommandSourceType);
 virtual void slot81(Object *, const Coord3D *, CommandSourceType);
 virtual void slot82(Object *, CommandSourceType);
 virtual void slot83(Object *, CommandSourceType);
 virtual void slot84(CommandSourceType);
 virtual void slot85(Object *, CommandSourceType);
 virtual void slot86(Object *, CommandSourceType);
 virtual void slot87(float, CommandSourceType);
 virtual void slot88();
 virtual void slot89();
 virtual void slot90();
 virtual void slot91();
 virtual void slot92();
 virtual void slot93();
 virtual void slot94();
 virtual void slot95();
 virtual void slot96();
 virtual void slot97();
 virtual void slot98();
 virtual void slot99();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void slot104();
 virtual void slot105();
 virtual void slot106();
 virtual void slot107();
 virtual void slot108();
 virtual void slot109();
 virtual void slot110();
 virtual void slot111();
 virtual void slot112();
 virtual void slot113();
 virtual void slot114();
 virtual void slot115();
 virtual void slot116();
 virtual void slot117();
 virtual void slot118();
 virtual void slot119();
 virtual void slot120();
 virtual void slot121();
 virtual void slot122();
 virtual void slot123();
 virtual void slot124();
 virtual void slot125();
 virtual void slot126();
 virtual void slot127();
 virtual void slot128();
 virtual void slot129();
 virtual void slot130();
 virtual void slot131();
 virtual void slot132();
 virtual void slot133();
 virtual void slot134();
 virtual void slot135();
 virtual void slot136();
 virtual void slot137();
 virtual void slot138();
 virtual void slot139();
 virtual void slot140();
 virtual void slot141();
 virtual void slot142();
 virtual void slot143();
 virtual void slot144();
 virtual void slot145();
 virtual void slot146();
 virtual void slot147();
 virtual bool isAllowedToRespondToAiCommands(const AICommandParms *) const;
 char m_unknown04[4]; Object *m_object; char m_unknown0C[0x20-0x0C];
};
class AIUpdateInterface : public UpdateModule, public AICommandInterface, public AIUpdateInterface24 {
public:
 virtual void aiDoCommand(const AICommandParms *);
 __forceinline void storeCommand(const AICommandParms *parms) { m_lastOutsideCommand.rva00351570(*reinterpret_cast<const Rva00351570Src *>(parms)); }
 void rva0026331C();
 char m_unknown28[0x34-0x28];
 void *m_extraStateMachine;
 char m_unknown38[0x140-0x38];
 Rva001E3591 *m_path;
 char m_unknown144[0x1a4-0x144];
 unsigned int m_extra1A4;
 char m_unknown1A8[0x1fc-0x1a8];
 int m_locomotorGoalType;
 char m_unknown200[0x2ec-0x200];
 Rva00351570 m_lastOutsideCommand;
 char m_unknown3B0[0x3c7-0x3b0];
 bool m_extra3C7;
 char m_unknown3C8[4];
 bool m_extra3CC;
};
// ?aiDoCommand@AIUpdateInterface@@ present-unmatched
void AIUpdateInterface::aiDoCommand(const AICommandParms *parms) {
 CommandSourceType cmdSource = parms->m_cmdSource;
 m_extra1A4 = 0;
 if (g_00DFE7A8) return;
 if (!isAllowedToRespondToAiCommands(parms)) return;
 bool defer = false;
 if (m_path && m_locomotorGoalType && m_path->rva001E3591()) defer = true;
 Object *obj = m_object;
 if ((obj->m_flags1C9 & 1) || defer || (obj->testStatus(STATUS_4A) && cmdSource != CMD_FROM_AI)) {
  storeCommand(parms);
  return;
 }
 if (m_extraStateMachine && cmdSource != CMD_FROM_AI) rva0026331C();
 if (cmdSource != CMD_FROM_AI) {
  StancesBehavior *stance = reinterpret_cast<StancesBehavior *>(obj->findModule(Rva0045EE2CGet()));
  if (stance) stance->rva0045F21C();
 }
 if (obj->testStatus(STATUS_26) && obj->m_containedBy && obj->m_containedBy->m_ai && cmdSource != CMD_FROM_AI
     && (parms->m_cmd == 0x1c || parms->m_cmd == 0x3b || parms->m_cmd == 0x43)) {
  m_object->m_containedBy->m_ai->aiDoCommand(parms);
  return;
 }
 if (obj->testStatus(STATUS_41)) {
  CommandRedirectInterface *redirect = reinterpret_cast<CommandRedirectInterface *>(obj->rva0028C1A9());
  if (redirect) {
   if ((parms->m_cmd != 0x0c && parms->m_cmd != 0x36) || (parms->m_obj && !redirect->testObject(parms->m_obj))) redirect->stop();
  }
 }
 m_extra3C7 = false;
 if (parms->m_cmd != 5 && cmdSource == CMD_FROM_PLAYER && m_extra3CC) m_extra3CC = false;
 switch (parms->m_cmd) {
case 0x0: case 0x36:
 reinterpret_cast<Rva0026228F *>(this)->rva0026228F(reinterpret_cast<int>(&parms->m_pos), cmdSource); break;
case 0x4E:
 slot13(&parms->m_pos, parms->m_floatValue, cmdSource); break;
case 0x51:
 slot14(&parms->m_pos, parms->m_floatValue, parms->m_intValue, cmdSource); break;
case 0x47:
 slot16(&parms->m_pos, cmdSource); break;
case 0x52:
 slot17(&parms->m_pos, parms->m_intValue, cmdSource); break;
case 0x1:
 slot15(parms->m_obj, cmdSource); break;
case 0x48:
 slot18(parms->m_obj, cmdSource); break;
case 0x49:
 slot41(parms->m_obj, cmdSource); break;
case 0x2:
 slot25(&parms->m_pos, cmdSource); break;
case 0x3:
 slot19(&parms->m_pos, cmdSource); break;
case 0x4:
 slot20(&parms->m_pos, cmdSource); break;
case 0x38:
 slot21(&parms->m_pos, cmdSource); break;
case 0x41:
 slot22(&parms->m_pos, cmdSource); break;
case 0x42:
 slot23(parms->m_obj, cmdSource); break;
case 0x5:
 slot24(cmdSource); break;
case 0x6:
 slot26(parms->m_waypoint, cmdSource); break;
case 0x7:
 slot27(parms->m_waypoint, cmdSource); break;
case 0x32:
 slot28(parms->m_waypoint, cmdSource); break;
case 0x33:
 slot29(parms->m_waypoint, cmdSource); break;
case 0x9:
 slot30(parms->m_coords, parms->m_obj, cmdSource, false); break;
case 0x24:
 slot31(parms->m_coords, parms->m_obj, parms->m_pos.x, cmdSource); break;
case 0x25:
 slot32(parms->m_coords, parms->m_obj, parms->m_pos.x, cmdSource); break;
case 0x35:
 slot33(&parms->m_pos, cmdSource); break;
case 0xA:
 slot30(parms->m_coords, parms->m_obj, cmdSource, true); break;
case 0xB:
 slot34(parms->m_obj, parms->m_intValue, cmdSource); break;
case 0xC:
 slot38(parms->m_obj, parms->m_intValue, cmdSource); break;
case 0x39:
 slot35(parms->m_obj, cmdSource); break;
case 0x3F:
 slot36(parms->m_obj, cmdSource); break;
case 0x40:
 slot37(&parms->m_pos, cmdSource); break;
case 0xD:
 slot39(parms->m_team, parms->m_intValue, cmdSource); break;
case 0xE:
 slot40(&parms->m_pos, parms->m_intValue, cmdSource); break;
case 0xF:
 reinterpret_cast<Rva00262271 *>(this)->rva00262271(reinterpret_cast<int>(&parms->m_pos), parms->m_intValue, cmdSource); break;
case 0x10:
 slot42(parms->m_waypoint, parms->m_intValue, false, cmdSource); break;
case 0x11:
 slot42(parms->m_waypoint, parms->m_intValue, true, cmdSource); break;
case 0x12:
 slot43(cmdSource); break;
case 0x23:
 slot68(parms->m_polygon, cmdSource); break;
case 0x13:
 slot44(parms->m_obj, cmdSource); break;
case 0x14:
 slot45(parms->m_obj, cmdSource); break;
case 0x15:
 slot46(parms->m_obj, cmdSource); break;
case 0x16:
 slot47(parms->m_obj, cmdSource); break;
case 0x45:
 slot50(parms->m_obj, cmdSource); break;
case 0x17:
 slot48(parms->m_obj, cmdSource); break;
case 0x3D:
 slot49(parms->m_obj, cmdSource); break;
case 0x18:
 slot51(parms->m_obj, cmdSource); break;
case 0x19:
 slot52(&parms->m_pos, cmdSource); break;
case 0x1A:
 slot53(parms->m_obj, cmdSource); break;
case 0x4B:
 slot54(parms->m_obj, &parms->m_pos, cmdSource); break;
case 0x4D:
 slot55(parms->m_obj, parms->m_coords, cmdSource); break;
case 0x3E:
 slot56(parms->m_obj, cmdSource); break;
case 0x4A:
 slot57(parms->m_obj, &parms->m_pos, cmdSource); break;
case 0x4C:
 slot58(parms->m_obj, parms->m_coords, cmdSource); break;
case 0x54:
 slot59(parms->m_obj, &parms->m_pos, cmdSource); break;
case 0x1B:
 slot60(parms->m_intValue, cmdSource); break;
case 0x1D:
 slot61(parms->m_damage, cmdSource); break;
case 0x1E:
 slot63(&parms->m_pos, parms->m_intValue, cmdSource); break;
case 0x1F:
 slot64(parms->m_obj, parms->m_intValue, cmdSource); break;
case 0x20:
 slot65(parms->m_team, parms->m_intValue, cmdSource); break;
case 0x37:
 slot62(parms->m_intValue, cmdSource); break;
case 0x21:
 slot67(parms->m_polygon, parms->m_intValue, cmdSource, 0); break;
case 0x44:
 slot67(parms->m_polygon, parms->m_intValue, cmdSource, &parms->m_pos); break;
case 0x46:
 slot66(parms->m_obj, &parms->m_pos, parms->m_intValue, cmdSource); break;
case 0x26:
 slot69(parms->m_obj, cmdSource); break;
case 0x27:
 slot70(&parms->m_pos, cmdSource); break;
case 0x2A:
 slot72(parms->m_commandButton, cmdSource); break;
case 0x29:
 slot74(parms->m_commandButton, parms->m_obj, cmdSource); break;
case 0x28:
 slot73(parms->m_commandButton, &parms->m_pos, cmdSource); break;
case 0x2B:
 slot75(parms->m_waypoint, cmdSource); break;
case 0x2C:
 slot76(cmdSource); break;
case 0x53:
 slot77(cmdSource); break;
case 0x2D:
 slot78(parms->m_waypoint, cmdSource); break;
case 0x2E:
 slot79(parms->m_obj, cmdSource); break;
case 0x2F:
 slot83(parms->m_obj, cmdSource); break;
case 0x31:
 slot80(parms->m_intValue, cmdSource); break;
case 0x34:
 slot81(parms->m_obj, &parms->m_pos, cmdSource); break;
case 0x3A:
 slot84(cmdSource); break;
case 0x43:
 slot85(parms->m_obj, cmdSource); break;
case 0x3C:
 slot82(parms->m_obj, cmdSource); break;
case 0x4F:
 slot86(parms->m_obj, cmdSource); break;
case 0x50:
 slot87(parms->m_floatValue, cmdSource); break;
 }
 if (obj->testStatus(STATUS_46) && cmdSource != CMD_FROM_AI) obj->rva00293105();
}
