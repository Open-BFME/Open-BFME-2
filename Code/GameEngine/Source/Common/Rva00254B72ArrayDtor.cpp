// cl: /O1 /MD /EHsc /DNDEBUG
// Complete native254B72..254B8216B helper, called by the ThingTemplate
// constructor for array cleanup. The eh-vector destructor arguments prove
// stride8, count56, and callback4C9F38; they are not stride56/count8.
// Callback owner Rva002390CB establishes the eight-byte two-word record,
// whose second word owns a reference. The application element type and
// original containing class name remain unknown.
class OpaqueRefCounted;
class Rva002390CB {void*unknown00;OpaqueRefCounted*owner04;public:~Rva002390CB();};
class Rva00254B72 {Rva002390CB records[56];public:~Rva00254B72();};
Rva00254B72::~Rva00254B72(){}
