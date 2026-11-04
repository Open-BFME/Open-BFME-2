// Native28B virtual deleting-destructor wrapper: direct qualified virtual destructor call, then optional class deallocation.
// Existing11B CameraShakerClass destructor0x000658BA installs native vtable0x00BC5C74 and tails to MultiListObjectClass::~MultiListObjectClass.
// Deallocation is the camera shaker's AutoPoolClass<CameraShakerClass,256>::operator delete at 0x00065D0E; complete object layout is unused here.
// cl: /O1 /EHsc /MD
class CameraShakeSystemClass {
public:
 class CameraShakerClass {
 public:
  virtual ~CameraShakerClass();
 };
};
template<class T, int BLOCK_SIZE> class AutoPoolClass {
public:
 static void operator delete(void* memory);
};
class Rva00065D24Element {
public:
 void* deletingDestructor(unsigned flags);
};
void* Rva00065D24Element::deletingDestructor(unsigned flags) {
 Rva00065D24Element* saved = this;
 ((CameraShakeSystemClass::CameraShakerClass*)this)->CameraShakeSystemClass::CameraShakerClass::~CameraShakerClass();
 if(flags & 1) AutoPoolClass<CameraShakeSystemClass::CameraShakerClass,256>::operator delete(saved);
 return saved;
}
