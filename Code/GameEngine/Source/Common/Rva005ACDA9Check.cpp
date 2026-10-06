// cl: /MD
// ?rva005ACDA9@AITactic@@QAEHXZ retail 0x005ACDA9 13B
// Evidence: chain via rowed 0x004ECECD; push 0 then neg-sbb-inc null check of its Team result; ecx passes through so same-class method; caller 0x005AD5E1.
class Team;
class AITactic
{
public:
    Team *rva004ECECD(int id);
    int rva005ACDA9();
};
int AITactic::rva005ACDA9()
{
    return !rva004ECECD(0);
}
