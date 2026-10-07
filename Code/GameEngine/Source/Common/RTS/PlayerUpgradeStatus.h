#ifndef BFME2_PLAYER_UPGRADE_STATUS_H
#define BFME2_PLAYER_UPGRADE_STATUS_H

class Upgrade;

// PlayerRva002AE329.cpp, RVA 0x002AE329: status 1 marks the template's
// in-progress mask; status 2 marks it completed and calls onUpgradeCompleted.
// These are the Zero Hour UpgradeStatusType values, independently confirmed
// by the BFME2 body and the callers that grant completed upgrades with 2.
enum UpgradeStatusType
{
    UPGRADE_STATUS_INVALID = 0,
    UPGRADE_STATUS_IN_PRODUCTION,
    UPGRADE_STATUS_COMPLETE
};

#endif
