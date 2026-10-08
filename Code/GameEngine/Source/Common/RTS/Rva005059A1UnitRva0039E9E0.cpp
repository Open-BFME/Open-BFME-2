// cl: /DNDEBUG /MD
// ?disband@Team@@QAEXXZ @0x0039E9E0 47B
// Unit teardown via Team transfer or Object fallback. If the +0x30 team's
// +8 link carries a +0x2EC unit different from this transfer to it via rowed
// Team::transferUnitsTo else drain +0x38 via pinned Object::setTeam.
// Evidence: pin owner pin callers at 0x004F06E5 and 0x005059A1 rowed callees.
class Team;
class Object
{
public:
    void setTeam(Team *t);
};
struct Rva0039Mid
{
    char m_pad[8];
    Team *m_team08;
};
struct Rva0039Owner
{
    char m_pad[0x2EC];
    Team *m_unit;
};
class Team
{
public:
    void transferUnitsTo(Team *other);
    void disband();
    char m_pad00[0x30];
    Rva0039Mid *m30;
    char m_pad34[4];
    Object *m38;
};
void Team::disband()
{
    Team *t = m30->m_team08;
    if (t) {
        Team *u = ((Rva0039Owner *)t)->m_unit;
        if ((Team *)this != u)
            ((Team *)this)->transferUnitsTo(u);
    } else {
        Object *o;
        do {
            o = m38;
            if (o == 0)
                break;
            o->setTeam(0);
        } while (o != 0);
    }
}
