// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// Native 002E1F88..002E1FA5 (29B RET0), WB DE4040 and the
// RemovePlayer 002B7DE6 call prove the player lost guard at3C4, set-before-
// broadcast and listener-list receiver+4. Name remains address-derived.
// Listener member pointer is slot0; its emitted4B vcall thunk is the
// existing 001FF3A9 byte-and-relocation twin, not a new retail body.
class Rva002E1E51Listener {public:virtual void notify(void*);};
class Rva002E1E51List {public:void forEach(void(Rva002E1E51Listener::*)(void*),void*);};
class Rva002E1F88 {public:void markLost();private:char prefix[0x3c4];bool lost;};
void Rva002E1F88::markLost(){if(!lost){lost=true;((Rva002E1E51List*)((char*)this+4))->forEach(&Rva002E1E51Listener::notify,this);}}
