// Target facts (code addresses are RVAs, tables are VAs): allocations at 0x002A9566/0x002A9568 and 0x002A9680/0x002A9682 request 0x38 bytes and call constructor 0x004E030B at 0x002A957F and 0x002A9697. That constructor has no base call or vptr store: AIStatCollector has no virtual functions. Pointer members require four-byte alignment; the representation below preserves its complete storage without asserting the unresolved container and pointee identities.
// Constructor 0x004E030B stores owned pointers at +0/+4/+8/+0x0C/+0x10, constructs a 0x14-byte count table at +0x14 through 0x004E02B8, stores Player* at +0x28, and constructs the three-word listener vector at +0x2C through 0x00211E58. Register 0x004DF98B reads begin/end at +0x2C/+0x30 and advances by four; addInfoReceiver 0x004DFEC8 calls pointer append 0x004DFCB0. Register 0x004E01E3 and UnRegister 0x004E0425 update the table's four-byte mapped counts. The destructor at 0x004E013B, still rowed as Rva004E013B, deletes the five pointees and tears down +0x2C/+0x14 without installing a table; manager reset calls it at 0x002A90D3 on collectors stored at +0x908.
// The table 0x00C615D4 stored by child constructor 0x004DFC59 and child destructor 0x004DFED8 belongs to the separately allocated 0x24-byte pointee at collector +0x10, not to AIStatCollector. Out-of-line methods below retain ledger spellings: constructor 0x004E030B, Register 0x004DF98B/0x004E01E3, UnRegister 0x004E0425, addInfoReceiver 0x004DFEC8, rva004DFB7E 0x004DFB7E and rva004DF9B9 0x004DF9B9. The destructor is declared out of line to preserve nontrivial destruction; its existing row retains its current owner name.

#ifndef BFME2_AISTATCOLLECTOR_H
#define BFME2_AISTATCOLLECTOR_H

class Player;
class Object;
class ModuleData;

class AIStatCollector
{
public:
    AIStatCollector(Player *player);
    ~AIStatCollector();

    void Register(Object *object, int mask);
    void Register(Object *object);
    void UnRegister(void *object);
    void addInfoReceiver(const ModuleData *receiver);
    bool rva004DFB7E(Object *object);
    void rva004DF9B9(void *object, int mask);

private:
    __declspec(align(4)) unsigned char nativeStorage[0x38];
};

#endif
