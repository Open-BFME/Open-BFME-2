// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Existing ctor pin; Drawable 27675F calls it twice for its 8B value return
// and local. Target writes all-one first word and null shared-member pointer.
class Rva002390CB { public: Rva002390CB(); int id; void *ref; };
Rva002390CB::Rva002390CB():id(-1),ref(0){}
