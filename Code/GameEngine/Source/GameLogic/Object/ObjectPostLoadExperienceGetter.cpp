// cl: /O1 /G7 /DNDEBUG /MD
// Native B49A1 is seven-byte pointer2C -> word0C getter. The existing
// MeshGeometry get_polys code is an ICF owner, not this receiver's type.
// Object Snapshot post-load uses the result as the argument of the owned
// integer setter39B227 on the same tracker. Original field types unknown.
struct Rva00293EFFXPNode {char pad[12];int value;};
class Rva00293EFFXPField {public:int getField();char pad[0x2C];Rva00293EFFXPNode*node;};
int Rva00293EFFXPField::getField(){return node->value;}
