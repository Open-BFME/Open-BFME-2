// Native28B virtual deleting-destructor wrapper: direct qualified virtual destructor call, then optional class deallocation.
// Existing11B destructor0x000658BA installs native vtable0x00BC5C74 and tails to MultiListObjectClass::~MultiListObjectClass.
// Pool data evidence associates0x00065D0E with the camera-shaker allocator; complete object layout is unused here.
// cl: /O1 /EHsc /MD
class Rva00065D24Element {
public:
 virtual ~Rva00065D24Element();
 static void operator delete(void*);
 void* deletingDestructor(unsigned flags);
};
void* Rva00065D24Element::deletingDestructor(unsigned flags) {
 Rva00065D24Element* saved = this;
 this->Rva00065D24Element::~Rva00065D24Element();
 if(flags & 1) Rva00065D24Element::operator delete(saved);
 return saved;
}
