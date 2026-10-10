// Thing-class diagnostic labels, native VA DBEC90..DBECD4 (17 pointers).
// BFME1 semantic donor: game/GameEngine/Source/Common/Thing/ThingTemplate.cpp
// at 575ba2b04743f190f069805fbdc59936123c45da. Its sixteen labels and
// terminating null agree independently with every native BFME2 pointer.
// Native 50C91D indexes this table with the signed class byte at +5F6.
// These descriptive identifiers are new; the original BFME2 names are unknown.
// Every label owns only its measured null-terminated extent; no padding claim.

extern const char BfmeThingClassUnspecified[];
const char BfmeThingClassUnspecified[] = "UNSPECIFIED";
extern const char BfmeThingClassHordeUnit[];
const char BfmeThingClassHordeUnit[] = "HORDE_UNIT";
extern const char BfmeThingClassCharacterUnit[];
const char BfmeThingClassCharacterUnit[] = "CHARACTER_UNIT";
extern const char BfmeThingClassCavalryUnit[];
const char BfmeThingClassCavalryUnit[] = "CAVALRY_UNIT";
extern const char BfmeThingClassMediumMonster[];
const char BfmeThingClassMediumMonster[] = "MEDIUM_MONSTER";
extern const char BfmeThingClassLargeMonster[];
const char BfmeThingClassLargeMonster[] = "LARGE_MONSTER";
extern const char BfmeThingClassProp[];
const char BfmeThingClassProp[] = "PROP";
extern const char BfmeThingClassCivBuilding[];
const char BfmeThingClassCivBuilding[] = "CIV_BUILDING";
extern const char BfmeThingClassWallPiece[];
const char BfmeThingClassWallPiece[] = "WALL_PIECE";
extern const char BfmeThingClassFactionBuilding[];
const char BfmeThingClassFactionBuilding[] = "FACTION_BUILDING";
extern const char BfmeThingClassLandmarkBuilding[];
const char BfmeThingClassLandmarkBuilding[] = "LANDMARK_BUILDING";
extern const char BfmeThingClassGroundCover[];
const char BfmeThingClassGroundCover[] = "GROUND_COVER";
extern const char BfmeThingClassBush[];
const char BfmeThingClassBush[] = "BUSH";
extern const char BfmeThingClassTree[];
const char BfmeThingClassTree[] = "TREE";
extern const char BfmeThingClassMachine[];
const char BfmeThingClassMachine[] = "MACHINE";
extern const char BfmeThingClassBuff[];
const char BfmeThingClassBuff[] = "BUFF";

extern const char *const BfmeThingClassNames[];
const char *const BfmeThingClassNames[] = {
    BfmeThingClassUnspecified,
    BfmeThingClassHordeUnit,
    BfmeThingClassCharacterUnit,
    BfmeThingClassCavalryUnit,
    BfmeThingClassMediumMonster,
    BfmeThingClassLargeMonster,
    BfmeThingClassProp,
    BfmeThingClassCivBuilding,
    BfmeThingClassWallPiece,
    BfmeThingClassFactionBuilding,
    BfmeThingClassLandmarkBuilding,
    BfmeThingClassGroundCover,
    BfmeThingClassBush,
    BfmeThingClassTree,
    BfmeThingClassMachine,
    BfmeThingClassBuff,
    0
};
