// cl: /MD
// ?rva002D7714@Rva002D7714@@QAEXPAURva002D76C6Owner@@@Z @0x002D7714 48B: remove owner from dual lists via ICF twin of rowed 0x002D76C6.
struct Rva002D76C6Node
{
    virtual void *v0(int);
    void *m04;
    Rva002D76C6Node *m08;
};
struct Rva002D76C6Owner
{
    char pad[0x260];
    int m260;
};
class Rva002D7714
{
public:
    void rva002D7714(Rva002D76C6Owner *owner);
    bool rva002D76C6(Rva002D76C6Owner *owner, Rva002D76C6Node **head);
    char pad[0x14];
    Rva002D76C6Node *head14;
    Rva002D76C6Node *head18;
};
void Rva002D7714::rva002D7714(Rva002D76C6Owner *owner)
{
    if (owner->m260 == 0)
        return;
    if (this->rva002D76C6(owner, &head18) == 1)
        return;
    this->rva002D76C6(owner, &head14);
}
