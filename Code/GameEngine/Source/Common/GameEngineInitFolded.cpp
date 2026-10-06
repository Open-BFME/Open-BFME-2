// cl: /O1 /DNDEBUG /MD /EHsc
// Retail ICF bodies called by GameEngine::init. These are ordinary C++
// definitions compiled separately so init retains the retail calls.
// ZH supplies the addSubsystem/init/setSeed roles; BFME2's direct call sites
// prove the empty registration operation, reset vslot +0x28 and seed +0x50.
class SubsystemInterface;
class SubsystemInterfaceList {
public:
    void addSubsystem(SubsystemInterface *sys);
};
void SubsystemInterfaceList::addSubsystem(SubsystemInterface *) {}

class GameInfo {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0C(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1C(); virtual void v20();
    virtual void v24(); virtual void reset();
    void init();
    void setSeed(int seed);
private:
    char m_04[0x4C];
    int m_seed;
};
void GameInfo::init() { reset(); }
void GameInfo::setSeed(int seed) { m_seed = seed; }

// The early argc/argv hook is a bare RET in this build; its original name
// and disabled-purpose identity are unknown.
void Rva000B3FD0(int, char *[]) {}
