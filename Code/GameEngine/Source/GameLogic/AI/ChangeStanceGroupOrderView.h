#pragma once
#ifndef BFME2_CHANGE_STANCE_GROUP_ORDER_ABI_VIEW_H
#define BFME2_CHANGE_STANCE_GROUP_ORDER_ABI_VIEW_H
class Xfer;
class Rva0036E346;
struct Coord3D;
struct GroupOrderCommand;
enum ObjectID;
enum NameKeyType;
// Native table RVA 0x0086A36C has fourteen slots. This temporary, TU-scoped
// ABI view is shared by the two emitters so existing rowed names occupy their
// native slots. GroupOrder's 0x18-byte storage and ChangeStance's +0x18 stance
// are proved by the rowed constructors and factory allocation of 0x1C bytes.
// The full canonical Snapshot/GroupOrder hierarchy remains separate recovery.
// Slot 5 returns true; slot 8 passes through its incoming word. No additional
// argument role is inferred from these trivial bodies.
class GroupOrder {
public:
    GroupOrder();
    GroupOrder(const GroupOrder &);
    GroupOrder(Rva0036E346 *);
    virtual ~GroupOrder();
    virtual void loadPostProcess() {}
    virtual const char *getClassName() = 0;
    virtual void xfer(Xfer *);
    virtual void rva00546BED(ObjectID) = 0;
    virtual bool slot05(ObjectID) = 0;
    virtual void slot06(ObjectID) = 0;
    virtual void slot07Set(int) {}
    virtual Coord3D *getDestination(int) = 0;
    virtual bool isNearDestination(const Coord3D *) { return false; }
    virtual int slot10() { return -1; }
    virtual bool slot11Command(int *, GroupOrderCommand *) = 0;
    virtual NameKeyType getClassKey() = 0;
    virtual GroupOrder *rva00546B34() = 0;
    int *m_field04;
    int *m_field08;
    void *m_field0C;
    unsigned int m_field10;
    unsigned int m_field14;
};
class ChangeStanceGroupOrder : public GroupOrder {
public:
    ChangeStanceGroupOrder();
    ChangeStanceGroupOrder(Rva0036E346 *, int);
    ChangeStanceGroupOrder(const ChangeStanceGroupOrder &);
    virtual ~ChangeStanceGroupOrder();
    virtual const char *getClassName();
    virtual void xfer(Xfer *);
    virtual void rva00546BED(ObjectID);
    virtual bool slot05(ObjectID) { return true; }
    virtual void slot06(ObjectID) {}
    virtual Coord3D *getDestination(int value) { return reinterpret_cast<Coord3D *>(value); }
    virtual bool slot11Command(int *, GroupOrderCommand *) { return false; }
    virtual NameKeyType getClassKey();
    virtual ChangeStanceGroupOrder *rva00546B34();
private:
    int m_stance;
};
typedef char GroupOrderStorageSize[(sizeof(GroupOrder) == 0x18) ? 1 : -1];
typedef char ChangeStanceStorageSize[(sizeof(ChangeStanceGroupOrder) == 0x1C) ? 1 : -1];
#endif
