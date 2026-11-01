// Target facts: GameMessage constructors (RVAs 0x0030F47A, 0x00311097) and destructor (0x0030F4AF) store VA 0x00C09840 at +0; its sole slot is deleting destructor 0x0030F8E3, and the next table starts at 0x00C09844. Allocation sites 0x0030F6D6, 0x0030F706 and 0x004D692D request 0x24 bytes; the constructors write links +4/+8, list +0x0C, type +0x10, player index +0x14, count byte +0x18 and argument pointers +0x1C/+0x20. No base constructor or secondary table is observed.
// Target facts: getArgument (0x0030F4EA) walks +0x1C through argument +4 and returns data +8; getArgumentDataType (0x0030F50C) reads argument +0x18. allocArg (0x0030F8FF) allocates 0x1C bytes and updates count/head/tail. The append bodies (0x0030F936..0x0030FA44) prove their parameter types and tags; the copy constructor and void copy (0x0031123E) call these bodies out of line. getCommandAsAsciiString (0x003113DD) forwards type +0x10 to getCommandTypeAsAsciiString (0x0030FA44), whose matched cases and strings prove the Type enumerators below. The existing wb00EC9680 row aliases the integer append at 0x0030F936. The out-of-line friend_setList setter at 0x005F69C4 writes +0x0C and is called at 0x005C92F2. Numeric placeholders are proved by native immediates at 0x00429641, 0x00429688, 0x004294CF, 0x004295AD, 0x00429637, 0x0042952C, 0x0041C6B5, 0x0041C6C8, 0x002B5FA8, 0x0043145C, 0x004313B8, 0x00352E95, 0x00398DEE, 0x00298E10.
// Donor facts: Zero Hour GeneralsMD Common/MessageStream.h names the links, list, type, player index, argument count/head/tail and inline accessors. BFME2's stores and argument traversal above establish their offsets; the destructor (0x0030F4AF) tears down the argument chain and removes this message through list slot +0x40. The special members are declarations so consumers call the rowed bodies.

// Target facts: MessageStream constructor RVA 0x0030F697 calls GameMessageList's 0x0030F562, clears +0x14/+0x18, stores VA 0x00C09890 at +0 (0x0030F6A7), and sets +0x1C to 1. Destructor 0x00310FA1 restores that same table at 0x00310FB3 and calls GameMessageList's destructor 0x0030F57C at 0x00310FE2. GameMessageList's constructor/destructor store their own table 0x00C09848 at 0x0030F572/0x0030F58D and call SubsystemInterface's 0x001B4E63/0x001B4E74. These are successive base lifetimes at +0, with no secondary table. The factory 0x00225F12 pushes 0x20 at 0x00225F1D and calls MessageStream's constructor at 0x00225F33: sizeof MessageStream is 0x20, with GameMessageList occupying 0x14 bytes.
// Target facts: GameMessageList's table 0x00C09848 has 18 slots, ending at MessageStream's 0x00C09890. MessageStream has 20 slots, ending at CommandList's table 0x00C098E0. Slot 0 is deleting destructor 0x003113F9, which calls 0x00310FA1; slots 1/3/8/9/10/12 are empty 0x000B3FD0, slot 2 is SubsystemInterface::loadIniFilesFromLegend 0x001B5384, slots 4/11 are false-ret-4 0x005CB9FF, slot 5 is false-ret 0x0047A699, slot 6 is zero-ret 0x000D43D0, and slots 7/13 are ret-4 0x0047A69C. Slots 14/15 are GameMessageList::appendMessage/insertMessage (0x0030F5D2/0x0030F604); slots 16/17 unlink a message (0x0030F642) and test its type (0x0030F679); slots 18/19 are the rowed MessageStream::appendMessage/insertMessage overloads (0x0030F6D4/0x0030F704). SubsystemInterface's registered header supplies slots 0-13 through BFME_SUBSYSTEM_SLOTS.
// Target facts: GameMessageList's constructor clears dwords +0x0C/+0x10, and append/insert (0x0030F5D2/0x0030F604) maintain these message links. propagateMessages (0x00310FF5) reads the translator head +0x14 and message head +0x0C, then clears +0x0C/+0x10. attachTranslator (0x0030F738) allocates 0x14-byte nodes, initializes next/prev/id/translator/priority at +0/+4/+8/+0x0C/+0x10, increments stream +0x1C, and updates stream head/tail +0x14/+0x18. findTranslator (0x0030F7D7) and removeTranslator (0x0030F7F3) prove the same offsets. TranslatorData's out-of-line destructor 0x0030F463 destroys its +0x0C translator through slot 1; MessageStream's destructor calls this body, then operator delete. All rowed lifetime and translator methods below are declarations.
// Donor facts: Zero Hour GeneralsMD Common/MessageStream.h names GameMessageList, its list fields and four list methods, MessageStream's three translator fields, TranslatorData's five fields, and the init/reset/update/getFirstMessage methods. Retail's base calls, tables, accesses and rowed method signatures above establish their BFME2 placement; the empty init/reset/update slots use the proven empty bodies.
// Target facts: the call at 0x00513879 dispatches slot 18 after pushing integer 29 at 0x00513877. The nonvirtual integer overload converts such message IDs to the rowed enum overload without adding a virtual slot.

#pragma once
#ifndef CANONICAL_GAMEMESSAGE_H
#define CANONICAL_GAMEMESSAGE_H

class AsciiString;
class GameMessageList;
class GameMessageArgument;
union GameMessageArgumentType;
enum GameMessageArgumentDataType;
enum ObjectID;
enum DrawableID;
struct Coord3D;
struct ICoord2D;
struct IRegion2D;

class GameMessage
{
public:
    enum Type
    {
        MSG_INVALID = 0,
        MSG_RAW_MOUSE_BEGIN = 2,
        MSG_RAW_MOUSE_POSITION = 3,
        MSG_RAW_MOUSE_LEFT_BUTTON_DOWN = 4,
        MSG_RAW_MOUSE_LEFT_DOUBLE_CLICK = 5,
        MSG_RAW_MOUSE_LEFT_BUTTON_UP = 6,
        MSG_RAW_MOUSE_LEFT_CLICK = 7,
        MSG_RAW_MOUSE_LEFT_DRAG = 8,
        MSG_RAW_MOUSE_MIDDLE_BUTTON_DOWN = 10,
        MSG_RAW_MOUSE_MIDDLE_DOUBLE_CLICK = 11,
        MSG_RAW_MOUSE_MIDDLE_BUTTON_UP = 12,
        MSG_RAW_MOUSE_MIDDLE_DRAG = 13,
        MSG_RAW_MOUSE_RIGHT_BUTTON_DOWN = 14,
        MSG_RAW_MOUSE_RIGHT_DOUBLE_CLICK = 15,
        MSG_RAW_MOUSE_RIGHT_BUTTON_UP = 16,
        MSG_RAW_MOUSE_RIGHT_DRAG = 18,
        MSG_RAW_MOUSE_WHEEL = 19,
        MSG_RAW_MOUSE_END = 20,
        MSG_RAW_KEY_DOWN = 21,
        MSG_RAW_KEY_UP = 22,
        MSG_MOUSE_LEFT_CLICK = 23,
        MSG_MOUSE_LEFT_DOUBLE_CLICK = 24,
        MSG_MOUSE_MIDDLE_CLICK = 25,
        MSG_MOUSE_MIDDLE_DOUBLE_CLICK = 26,
        MSG_MOUSE_RIGHT_CLICK = 27,
        MSG_MOUSE_RIGHT_DOUBLE_CLICK = 28,
        MSG_CLEAR_GAME_DATA = 29,
        MSG_NEW_GAME = 30,
        MSG_START_LIVING_WORLD_LOGIC = 31,
        MSG_START_LINEAR_CAMPAIGN = 32,
        MSG_CURRENT_LINEAR_CAMPAIGN_MISSION_COMPLETE = 33,
        MSG_EXIT_LINEAR_CAMPAIGN = 34,
        MSG_BEGIN_META_MESSAGES = 35,
        MSG_META_SAVE_VIEW1 = 36,
        MSG_META_SAVE_VIEW2 = 37,
        MSG_META_SAVE_VIEW3 = 38,
        MSG_META_SAVE_VIEW4 = 39,
        MSG_META_SAVE_VIEW5 = 40,
        MSG_META_SAVE_VIEW6 = 41,
        MSG_META_SAVE_VIEW7 = 42,
        MSG_META_SAVE_VIEW8 = 43,
        MSG_META_VIEW_VIEW1 = 44,
        MSG_META_VIEW_VIEW2 = 45,
        MSG_META_VIEW_VIEW3 = 46,
        MSG_META_VIEW_VIEW4 = 47,
        MSG_META_VIEW_VIEW5 = 48,
        MSG_META_VIEW_VIEW6 = 49,
        MSG_META_VIEW_VIEW7 = 50,
        MSG_META_VIEW_VIEW8 = 51,
        MSG_META_CREATE_TEAM0 = 52,
        MSG_META_CREATE_TEAM1 = 53,
        MSG_META_CREATE_TEAM2 = 54,
        MSG_META_CREATE_TEAM3 = 55,
        MSG_META_CREATE_TEAM4 = 56,
        MSG_META_CREATE_TEAM5 = 57,
        MSG_META_CREATE_TEAM6 = 58,
        MSG_META_CREATE_TEAM7 = 59,
        MSG_META_CREATE_TEAM8 = 60,
        MSG_META_CREATE_TEAM9 = 61,
        MSG_META_SELECT_TEAM0 = 62,
        MSG_META_SELECT_TEAM1 = 63,
        MSG_META_SELECT_TEAM2 = 64,
        MSG_META_SELECT_TEAM3 = 65,
        MSG_META_SELECT_TEAM4 = 66,
        MSG_META_SELECT_TEAM5 = 67,
        MSG_META_SELECT_TEAM6 = 68,
        MSG_META_SELECT_TEAM7 = 69,
        MSG_META_SELECT_TEAM8 = 70,
        MSG_META_SELECT_TEAM9 = 71,
        MSG_META_ADD_TEAM0 = 72,
        MSG_META_ADD_TEAM1 = 73,
        MSG_META_ADD_TEAM2 = 74,
        MSG_META_ADD_TEAM3 = 75,
        MSG_META_ADD_TEAM4 = 76,
        MSG_META_ADD_TEAM5 = 77,
        MSG_META_ADD_TEAM6 = 78,
        MSG_META_ADD_TEAM7 = 79,
        MSG_META_ADD_TEAM8 = 80,
        MSG_META_ADD_TEAM9 = 81,
        MSG_META_VIEW_TEAM0 = 82,
        MSG_META_VIEW_TEAM1 = 83,
        MSG_META_VIEW_TEAM2 = 84,
        MSG_META_VIEW_TEAM3 = 85,
        MSG_META_VIEW_TEAM4 = 86,
        MSG_META_VIEW_TEAM5 = 87,
        MSG_META_VIEW_TEAM6 = 88,
        MSG_META_VIEW_TEAM7 = 89,
        MSG_META_VIEW_TEAM8 = 90,
        MSG_META_VIEW_TEAM9 = 91,
        MSG_META_SELECT_MATCHING_UNITS = 92,
        MSG_META_SELECT_NEXT_UNIT = 93,
        MSG_META_SELECT_PREV_UNIT = 94,
        MSG_META_SELECT_NEXT_WORKER = 95,
        MSG_META_SELECT_PREV_WORKER = 96,
        MSG_META_VIEW_HOME_BASE = 97,
        MSG_META_VIEW_LAST_RADAR_EVENT = 98,
        MSG_META_SELECT_HERO = 99,
        MSG_META_SELECT_ALL = 100,
        MSG_META_SCATTER = 101,
        MSG_META_STOP = 102,
        MSG_META_DEPLOY = 103,
        MSG_META_CREATE_FORMATION = 104,
        MSG_META_AUTO_SAVE = 105,
        MSG_META_FOLLOW = 106,
        MSG_META_CHAT_PLAYERS = 107,
        MSG_META_CHAT_BUDDIES = 108,
        MSG_META_CHAT_ALLIES = 109,
        MSG_META_CHAT_EVERYONE = 110,
        MSG_META_DIPLOMACY = 111,
        MSG_META_OPTIONS = 112,
        MSG_META_TOGGLE_CONTROL_BAR = 113,
        MSG_META_BEGIN_PATH_BUILD = 114,
        MSG_META_END_PATH_BUILD = 115,
        MSG_META_BEGIN_FORCEATTACK = 116,
        MSG_META_END_FORCEATTACK = 117,
        MSG_META_BEGIN_FORCEMOVE = 118,
        MSG_META_END_FORCEMOVE = 119,
        MSG_META_BEGIN_WAYPOINTS = 120,
        MSG_META_END_WAYPOINTS = 121,
        MSG_META_BEGIN_PREFER_SELECTION = 122,
        MSG_META_END_PREFER_SELECTION = 123,
        MSG_META_TAKE_SCREENSHOT = 124,
        MSG_META_ALL_CHEER = 125,
        MSG_META_TOGGLE_ATTACKMOVE = 126,
        MSG_META_BEGIN_CAMERA_ROTATE_LEFT = 127,
        MSG_META_END_CAMERA_ROTATE_LEFT = 128,
        MSG_META_BEGIN_CAMERA_ROTATE_RIGHT = 129,
        MSG_META_END_CAMERA_ROTATE_RIGHT = 130,
        MSG_META_BEGIN_CAMERA_ZOOM_IN = 131,
        MSG_META_END_CAMERA_ZOOM_IN = 132,
        MSG_META_BEGIN_CAMERA_ZOOM_OUT = 133,
        MSG_META_END_CAMERA_ZOOM_OUT = 134,
        MSG_META_CAMERA_RESET = 135,
        MSG_META_BEGIN_CAMERA_SCROLL_LEFT = 136,
        MSG_META_END_CAMERA_SCROLL_LEFT = 137,
        MSG_META_BEGIN_CAMERA_SCROLL_RIGHT = 138,
        MSG_META_END_CAMERA_SCROLL_RIGHT = 139,
        MSG_META_BEGIN_CAMERA_SCROLL_UP = 140,
        MSG_META_END_CAMERA_SCROLL_UP = 141,
        MSG_META_BEGIN_CAMERA_SCROLL_DOWN = 142,
        MSG_META_END_CAMERA_SCROLL_DOWN = 143,
        MSG_META_PLACE_BEACON = 144,
        MSG_META_DELETE_BEACON = 145,
        MSG_META_SPELL_STORE = 146,
        MSG_META_STANCE_AGGRESSIVE = 147,
        MSG_META_STANCE_HOLDGROUND = 148,
        MSG_META_STANCE_BATTLE = 149,
        MSG_META_ORDERMODE_IMMEDIATE = 150,
        MSG_META_ORDERMODE_WAYPOINT = 151,
        MSG_META_ORDER_SYNCHRONIZE = 152,
        MSG_META_TOGGLE_PLANNING_MODE = 153,
        MSG_META_SELL = 154,
        MSG_META_DEMO_PERFORM_STATISTICAL_DUMP = 155,
        MSG_META_TOGGLE_FAST_FORWARD_MODE = 156,
        MSG_META_RELOAD_RAPID_ITERATION_FEATURE = 157,
        MSG_META_REFRESH_RAPID_ITERATION_FEATURE = 158,
        MSG_META_DEBUG_TOGGLE_SHOWVISIONEGGS = 159,
        MSG_META_DEBUG_TOGGLE_STRINGTAGS = 160,
        MSG_END_META_MESSAGES = 161,
        MSG_MOUSEOVER_DRAWABLE_HINT = 162,
        MSG_MOUSEOVER_LOCATION_HINT = 163,
        MSG_VALID_GUICOMMAND_HINT = 164,
        MSG_INVALID_GUICOMMAND_HINT = 165,
        MSG_AREA_SELECTION_HINT = 166,
        MSG_DO_ATTACK_OBJECT_HINT = 167,
        MSG_DO_FORCE_ATTACK_OBJECT_HINT = 169,
        MSG_DO_FORCE_ATTACK_GROUND_HINT = 170,
        MSG_GET_REPAIRED_HINT = 171,
        MSG_GET_HEALED_HINT = 172,
        MSG_DO_REPAIR_HINT = 173,
        MSG_RESUME_CONSTRUCTION_HINT = 174,
        MSG_ENTER_HINT = 175,
        MSG_CONTEST_HINT = 176,
        MSG_DOCK_HINT = 177,
        MSG_HARVEST_HINT = 178,
        MSG_DO_MOVETO_HINT = 179,
        MSG_DO_ATTACKMOVETO_HINT = 180,
        MSG_ADD_WAYPOINT_HINT = 181,
        MSG_HIJACK_HINT = 182,
        MSG_FIREBOMB_HINT = 183,
        MSG_CONVERT_TO_CARBOMB_HINT = 184,
        MSG_CAPTUREBUILDING_HINT = 185,
        MSG_SNIPE_VEHICLE_HINT = 186,
        MSG_DEFECTOR_HINT = 187,
        MSG_SET_RALLY_POINT_HINT = 188,
        MSG_DO_SALVAGE_HINT = 190,
        MSG_DO_INVALID_HINT = 191,
        MSG_DO_ATTACK_OBJECT_AFTER_MOVING_HINT = 192,
        MSG_APT_SKIP_NEXT_MSG = 195,
        MSG_BEGIN_NETWORK_MESSAGES = 1000,
        MSG_CREATE_SELECTED_GROUP = 1001,
        MSG_CREATE_SELECTED_GROUP_NO_SOUND = 1002,
        MSG_CREATE_SELECTED_GROUP_IDLE_WORKER_VOICE = 1003,
        MSG_DESTROY_SELECTED_GROUP = 1004,
        MSG_REMOVE_FROM_SELECTED_GROUP = 1005,
        MSG_CREATE_TEAM0 = 1006,
        MSG_CREATE_TEAM1 = 1007,
        MSG_CREATE_TEAM2 = 1008,
        MSG_CREATE_TEAM3 = 1009,
        MSG_CREATE_TEAM4 = 1010,
        MSG_CREATE_TEAM5 = 1011,
        MSG_CREATE_TEAM6 = 1012,
        MSG_CREATE_TEAM7 = 1013,
        MSG_CREATE_TEAM8 = 1014,
        MSG_CREATE_TEAM9 = 1015,
        MSG_SELECT_TEAM0 = 1016,
        MSG_SELECT_TEAM1 = 1017,
        MSG_SELECT_TEAM2 = 1018,
        MSG_SELECT_TEAM3 = 1019,
        MSG_SELECT_TEAM4 = 1020,
        MSG_SELECT_TEAM5 = 1021,
        MSG_SELECT_TEAM6 = 1022,
        MSG_SELECT_TEAM7 = 1023,
        MSG_SELECT_TEAM8 = 1024,
        MSG_SELECT_TEAM9 = 1025,
        MSG_ADD_TEAM0 = 1026,
        MSG_ADD_TEAM1 = 1027,
        MSG_ADD_TEAM2 = 1028,
        MSG_ADD_TEAM3 = 1029,
        MSG_ADD_TEAM4 = 1030,
        MSG_ADD_TEAM5 = 1031,
        MSG_ADD_TEAM6 = 1032,
        MSG_ADD_TEAM7 = 1033,
        MSG_ADD_TEAM8 = 1034,
        MSG_ADD_TEAM9 = 1035,
        MSG_DO_ATTACKSQUAD = 1036,
        MSG_DO_WEAPON = 1037,
        MSG_DO_WEAPON_AT_LOCATION = 1038,
        MSG_DO_WEAPON_AT_OBJECT = 1039,
        MSG_DO_SPECIAL_POWER = 1040,
        MSG_DO_SPECIAL_POWER_AT_LOCATION = 1041,
        MSG_DO_SPECIAL_POWER_AT_OBJECT = 1042,
        MSG_SET_RALLY_POINT = 1043,
        MSG_PURCHASE_SCIENCE = 1044,
        MSG_QUEUE_UPGRADE = 1045,
        MSG_CANCEL_UPGRADE = 1046,
        MSG_QUEUE_UNIT_CREATE = 1047,
        MSG_CANCEL_UNIT_CREATE = 1048,
        MSG_FOUNDATION_CONSTRUCT = 1049,
        MSG_DOZER_CONSTRUCT = 1050,
        MSG_DOZER_CANCEL_CONSTRUCT = 1051,
        MSG_SELL = 1052,
        MSG_EXIT = 1053,
        MSG_EVACUATE = 1054,
        MSG_EVACUATE_CONTESTERS = 1055,
        MSG_SACRIFICE = 1056,
        MSG_COMBATDROP_AT_LOCATION = 1057,
        MSG_COMBATDROP_AT_OBJECT = 1058,
        MSG_COMBINE_HORDES_WITH_OBJECT = 1059,
        MSG_AREA_SELECTION = 1060,
        MSG_DO_ATTACK_OBJECT = 1061,
        MSG_DO_FORCE_ATTACK_OBJECT = 1062,
        MSG_DO_FORCE_ATTACK_GROUND = 1063,
        MSG_GET_REPAIRED = 1064,
        MSG_GET_HEALED = 1065,
        MSG_DO_REPAIR = 1066,
        MSG_RESUME_CONSTRUCTION = 1067,
        MSG_ENTER = 1068,
        MSG_DOCK = 1069,
        MSG_HARVEST = 1070,
        MSG_DO_MOVETO = 1071,
        MSG_DO_ATTACKMOVETO = 1072,
        MSG_DO_FORCEMOVETO = 1073,
        MSG_ADD_WAYPOINT = 1074,
        MSG_DO_GUARD_POSITION = 1075,
        MSG_DO_GUARD_OBJECT = 1076,
        MSG_DO_STOP = 1077,
        MSG_DO_SCATTER = 1078,
        MSG_OPEN_GATE = 1079,
        MSG_DO_CHEER = 1080,
        MSG_CLOSE_GATE = 1081,
        MSG_SWITCH_WEAPONS = 1082,
        MSG_CONVERT_TO_CARBOMB = 1083,
        MSG_CAPTUREBUILDING = 1084,
        MSG_CASTLE_UNPACK = 1085,
        MSG_CASTLE_PACK = 1086,
        MSG_CASTLE_UNPACK_EXPLICIT_OBJECT = 1087,
        MSG_SNIPE_VEHICLE = 1088,
        MSG_DO_SPECIAL_POWER_OVERRIDE_DESTINATION = 1089,
        MSG_DO_SALVAGE = 1090,
        MSG_CLEAR_INGAME_POPUP_MESSAGE = 1091,
        MSG_PLACE_BEACON = 1092,
        MSG_REMOVE_BEACON = 1093,
        MSG_SET_BEACON_TEXT = 1094,
        MSG_SET_REPLAY_CAMERA = 1095,
        MSG_SELF_DESTRUCT = 1096,
        MSG_CREATE_FORMATION = 1097,
        MSG_LOGIC_CRC = 1098,
        MSG_SET_MINE_CLEARING_DETAIL = 1099,
        MSG_DO_USER1 = 1100,
        MSG_DO_USER2 = 1101,
        MSG_DO_USER3 = 1102,
        MSG_DO_USER4 = 1103,
        MSG_MOVE_ARMY_TO_POSITION = 1104,
        MSG_AUTO_SAVE = 1105,
        MSG_CHANGE_CAMERA_ARRIVED_AT_WAYPOINTID = 1106,
        MSG_HORDE_TOGGLE_FORMATION = 1107,
        MSG_ONE_RING = 1108,
        MSG_CREW_EVACUATE = 1109,
        MSG_DO_SPELLBOOK_SPECIAL_POWER = 1110,
        MSG_WEAPONSET_TOGGLE = 1111,
        MSG_DO_AUTO_ABILITY = 1112,
        MSG_DO_AUTO_ABILITY_WEAPON = 1113,
        MSG_REVIVE = 1114,
        MSG_TOGGLE_NO_AUTO_ACQUIRE = 1115,
        MSG_WAKE_AUTO_PICKUP = 1116,
        MSG_START_SELF_REPAIR = 1117,
        MSG_SUMMON_REINFORCEMENTS = 1118,
        MSG_CALL_IN_REINFORCEMENTS = 1119,
        MSG_HORDE_SET_FORMATION = 1120,
        MSG_CREATE_SELECT_ALL_GROUP = 1121,
        MSG_ENABLE_RETALIATION_MODE = 1122,
        MSG_WALL_HUB_CONSTRUCT_SPAN = 1123,
        MSG_DO_MOVETO_FORMATION = 1124,
        MSG_DO_MOVE_AND_ORIENTATE_OBJECTTO = 1125,
        MSG_GIVE_MONEY = 1126,
        MSG_DO_ROTATE_FIRINGARC = 1127,
        MSG_CHANGE_STANCE = 1128,
        MSG_CHANGE_ORDERMODE = 1129,
        MSG_ACTIONQUEUE_EXECUTE_PLANNED = 1130,
        MSG_ACTIONQUEUE_CLEAR_ALL = 1131,
        MSG_ACTIONQUEUE_CLEAR_PLANNED = 1132,
        MSG_ACTIONQUEUE_CLEAR_LAST = 1133,
        MSG_START_NEIGHBORHOOD_REPAIR = 1134,
        MSG_CANCEL_NEIGHBORHOOD = 1135,
        MSG_ORDER_SYNCHRONIZE = 1136,
        MSG_ADD_ALL_FACTION_UPGRADE = 1137,
        MSG_LW_DONE_SESSION = 1701,
        MSG_LW_DONE_PHASE = 1702,
        MSG_LW_SET_CONFLICT_RESOLUTION_METHOD = 1703,
        MSG_LW_ARMY_MOVE_REQUEST = 1704,
        MSG_LW_CANCEL_ARMY_MOVE_REQUEST = 1705,
        MSG_LW_BUILD_BUILDING = 1706,
        MSG_LW_DESTROY_BUILDING = 1707,
        MSG_LW_QUEUE_UNIT = 1708,
        MSG_LW_DEQUEUE_UNIT = 1709,
        MSG_LW_DEQUEUE_UNIT_AT_INDEX = 1710,
        MSG_LW_SWAP_ARMY_MEMBERS = 1711,
        MSG_LW_CANCEL_ARMY_MEMBER_MOVE = 1712,
        MSG_LW_DISBAND_ARMY_MEMBER = 1713,
        MSG_LW_DISBAND_ARMY = 1714,
        MSG_LW_CANCEL_ARMY_MEMBER_DISBAND = 1715,
        MSG_LW_SWAP_ARMIES_IN_BATTLE = 1716,
        MSG_LW_FORCE_ENTER_REALTIME_BATTLE = 1717,
        MSG_LW_DEBUG_QUICKWIN_BATTLE = 1718,
        MSG_LW_RESOLVE_REGION_AWARD_DISPUTE = 1719,
        MSG_LW_PLAYER_SURRENDERED = 1720,
        MSG_LW_REQUEST_ENDGAME = 1721,
        MSG_LW_TRANSITION_TO_TACTICAL_COMPLETE = 1722,
        MSG_LW_TRANSITION_TO_STRATEGIC_COMPLETE = 1723,
        MSG_LW_SCORESCREEN_DONE = 1724,
        MSG_END_NETWORK_MESSAGES = 1999,
        MSG_TIMESTAMP = 2000,
        MSG_OBJECT_CREATED = 2001,
        MSG_OBJECT_DESTROYED = 2002,
        MSG_OBJECT_POSITION = 2003,
        MSG_OBJECT_ORIENTATION = 2004,
        MSG_OBJECT_JOINED_TEAM = 2005,
        MSG_GIVE_UPGRADE_HINT = 2006,
        MSG_JOIN_HORDE_HINT = 2007,
        MSG_CAN_GRAB_HINT = 2008,
        MSG_40D = 0x40d,
        MSG_40E = 0x40e,
        MSG_40F = 0x40f,
        MSG_TYPE_193 = 0xc1,
        MSG_TYPE_194 = 0xc2,
        T_6A6 = 0x6a6,
        TYPE_433 = 0x433,
        TYPE_434 = 0x434,
        MSG_BFME2_0x7EA = 0x7ea,
        MSG_BFME2_0x7DE = 0x7de,
        MSG_BFME2_0x7DF = 0x7df,
    };

    GameMessage(Type type);
    GameMessage(const GameMessage &source);
    virtual ~GameMessage();
    void rva0031123E(const GameMessage &source);

    GameMessage *next() { return m_next; }
    GameMessage *prev() { return m_prev; }
    Type getType() const { return m_type; }
    unsigned char getArgumentCount() const { return m_argCount; }
    int getPlayerIndex() const { return m_playerIndex; }
    void friend_setNext(GameMessage *message) { m_next = message; }
    void friend_setPrev(GameMessage *message) { m_prev = message; }
    void friend_setList(GameMessageList *list);
    void friend_setPlayerIndex(int index) { m_playerIndex = index; }
    void deleteInstance() { if (this) delete this; }

    const GameMessageArgumentType *getArgument(int index) const;
    GameMessageArgumentDataType getArgumentDataType(int index);
    void appendIntegerArgument(int arg);
    void wb00EC9680(int arg);
    void appendRealArgument(float arg);
    void appendBooleanArgument(bool arg);
    void appendObjectIDArgument(ObjectID arg);
    void appendDrawableIDArgument(DrawableID arg);
    void appendTeamIDArgument(unsigned int arg);
    void appendLocationArgument(const Coord3D &arg);
    void appendPixelArgument(const ICoord2D &arg);
    void appendPixelRegionArgument(const IRegion2D &arg);
    void appendTimestampArgument(unsigned int arg);
    void appendWideCharArgument(const unsigned short &arg);
    AsciiString getCommandAsAsciiString();
    static AsciiString getCommandTypeAsAsciiString(Type type);

    GameMessage *m_next;
    GameMessage *m_prev;
    GameMessageList *m_list;
    Type m_type;
    int m_playerIndex;
    unsigned char m_argCount;
    GameMessageArgument *m_argList;
    GameMessageArgument *m_argTail;

private:
    GameMessageArgument *allocArg();
};

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include MessageStream.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class GameMessageTranslator;

class GameMessageList : public SubsystemInterface
{
public:
    GameMessageList();
    virtual ~GameMessageList();
    virtual void init() {}
    virtual void reset() {}
    virtual void update() {}
    virtual void appendMessage(GameMessage *message);
    virtual void insertMessage(GameMessage *message, GameMessage *messageToInsertAfter);
    virtual void removeMessage(GameMessage *message);
    virtual bool containsMessageOfType(GameMessage::Type type);

    GameMessage *getFirstMessage() { return m_firstMessage; }

    GameMessage *m_firstMessage;
    GameMessage *m_lastMessage;
};

class MessageStream : public GameMessageList
{
public:
    MessageStream();
    virtual ~MessageStream();
    virtual void init() {}
    virtual void reset() {}
    virtual void update() {}
    virtual GameMessage *appendMessage(GameMessage::Type type);
    virtual GameMessage *insertMessage(GameMessage::Type type, GameMessage *messageToInsertAfter);

    GameMessage *appendMessage(int type) { return appendMessage(static_cast<GameMessage::Type>(type)); }

    void propagateMessages();
    unsigned int attachTranslator(GameMessageTranslator *translator, unsigned int priority);
    GameMessageTranslator *findTranslator(unsigned int id);
    void removeTranslator(unsigned int id);

    struct TranslatorData
    {
        TranslatorData() : m_next(0), m_prev(0), m_id(0), m_translator(0), m_priority(0) {}
        ~TranslatorData();
        TranslatorData *m_next;
        TranslatorData *m_prev;
        unsigned int m_id;
        GameMessageTranslator *m_translator;
        unsigned int m_priority;
    };

    TranslatorData *m_firstTranslator;
    TranslatorData *m_lastTranslator;
    unsigned int m_nextTranslatorID;
};

#endif
