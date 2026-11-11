// BfmeObjectDlinkBase: canonical declarations for the members 15 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMEOBJECTDLINKBASE_H
#define CANONICAL_BFMEOBJECTDLINKBASE_H

class Object;

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

#endif // CANONICAL_BFMEOBJECTDLINKBASE_H
