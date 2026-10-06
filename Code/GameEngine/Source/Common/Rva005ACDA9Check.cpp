// cl: /MD
// ?rva005ACDA9@Rva004ECECD@@QAEHXZ retail 0x005ACDA9 13B
// Evidence: chain via rowed 0x004ECECD; push 0 then neg-sbb-inc null check of its Team result; ecx passes through so same-class method; caller 0x005AD5E1.
class Team;
class Rva004ECECD
{
public:
    Team *rva004ECECD(int id);
    int rva005ACDA9();
};
int Rva004ECECD::rva005ACDA9()
{
    return !rva004ECECD(0);
}
