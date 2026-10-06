// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/GameClient/GUI/Rva007849C0Clear.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?Rva007849C0Clear@@YAXPAURva007849C0Owner@@@Z 0x000A9DA8 (28B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
struct Rva007849C0Object
{
    void *m_slot0;
};
struct Rva007849C0Owner
{
    unsigned int m_slot0;
    Rva007849C0Object *m_object;
};
void Rva007849C0Clear(Rva007849C0Owner *owner)
{
    Rva007849C0Object *object = owner->m_object;
    if (object)
    {
        object->m_slot0 = 0;
        ::operator delete(object);
    }
    owner->m_object = 0;
}
