// cl: /MD
// ??_GMetaMapRec@@QAEPAXI@Z @0x001DB51B 28B
// MetaMapRec deleting dtor: calls rowed ??1MetaMapRec 0x1DB48E then plain operator delete 0x2FD60.
// Evidence: retail push esi mov esi ecx call 0x1DB48E test [esp+8] 1 je push esi call delete; ZH donor
// MetaMapRec layout with two UnicodeStrings; BFME1 destructor thunk precedent for force-delete emission.
class MetaMapRec
{
public:
	~MetaMapRec();
};
void famgenDelete(MetaMapRec *p) { delete p; }
