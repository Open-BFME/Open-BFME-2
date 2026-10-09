// cl: /O1 /G7 /arch:SSE /Oy- /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Native3B3AE2 full88B plus559-byte compressed selector table: action id4,
// signed parameter count8, parameter pointer arrayC, parameter string10.
// All cases and their target0/1/default come from retail table3B3B46.
// The126 supported actions use parameter0; three use parameter1. Source
// lead: ZH Scripts.cpp ScriptAction parameter access; BF2 IDs are target facts.
// Original getter name unknown. No full ScriptAction/Parameter layout inferred.
#include "ascii_string.h"
class Team;
class ScriptEngine {public: Team *getTeamNamed(AsciiString,bool);};
extern ScriptEngine *TheScriptEngine;
struct Rva003B3AE2ParameterPrefix {unsigned int unknown[4]; AsciiString text;};
struct Rva003B3AE2ActionPrefix {
 unsigned int unknown00; int id; int count; Rva003B3AE2ParameterPrefix *parameters[12];
 Team *getTeam() const;
 Rva003B3AE2ParameterPrefix *parameter(int i) const { return count>i?parameters[i]:0; }
};
Team *Rva003B3AE2ActionPrefix::getTeam() const {
 switch(id) {
 case 12:
 case 13:
 case 33:
 case 34:
 case 36:
 case 37:
 case 43:
 case 46:
 case 50:
 case 51:
 case 52:
 case 54:
 case 56:
 case 59:
 case 61:
 case 70:
 case 73:
 case 76:
 case 81:
 case 94:
 case 95:
 case 96:
 case 106:
 case 108:
 case 109:
 case 115:
 case 116:
 case 144:
 case 156:
 case 159:
 case 160:
 case 178:
 case 179:
 case 180:
 case 181:
 case 182:
 case 183:
 case 184:
 case 187:
 case 188:
 case 194:
 case 195:
 case 196:
 case 199:
 case 200:
 case 206:
 case 207:
 case 208:
 case 218:
 case 232:
 case 236:
 case 237:
 case 238:
 case 239:
 case 242:
 case 243:
 case 245:
 case 247:
 case 249:
 case 253:
 case 255:
 case 261:
 case 265:
 case 266:
 case 267:
 case 268:
 case 269:
 case 270:
 case 271:
 case 272:
 case 274:
 case 282:
 case 283:
 case 284:
 case 285:
 case 287:
 case 296:
 case 304:
 case 309:
 case 310:
 case 316:
 case 326:
 case 329:
 case 330:
 case 345:
 case 355:
 case 356:
 case 357:
 case 369:
 case 370:
 case 380:
 case 391:
 case 392:
 case 393:
 case 394:
 case 397:
 case 398:
 case 399:
 case 400:
 case 402:
 case 403:
 case 413:
 case 414:
 case 433:
 case 435:
 case 455:
 case 468:
 case 469:
 case 479:
 case 480:
 case 482:
 case 487:
 case 490:
 case 498:
 case 501:
 case 503:
 case 514:
 case 517:
 case 520:
 case 524:
 case 537:
 case 541:
 case 544:
 case 545:
 case 549:
 case 570:
  return TheScriptEngine->getTeamNamed(parameter(0)->text,false);
 case 273:
 case 462:
 case 510:
  return TheScriptEngine->getTeamNamed(parameter(1)->text,false);
 default: return 0;
 }
}
