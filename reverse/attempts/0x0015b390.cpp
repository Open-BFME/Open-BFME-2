// ??0OpaqueRefBuffer@@QAE@ABV0@@Z
// partial score=1.0 date=2026-10-07
// cl: /O2 /arch:SSE /G7 /MD
// Native 0x0015B390..0x0015B3CA RET4. Opaque tail buffer descriptor+108;
// vtable BD3CA4 and rowed base copy175@15ACB0 independently identify family.
// Original pointee and class names remain unknown.
class RefCountClass {
public:
 void Add_Ref(){++NumRefs;}
 virtual void Delete_This();
protected:
 virtual ~RefCountClass(){}
 int NumRefs;
};
template<class T>class ShareBufferClass:public RefCountClass {
public:
 ShareBufferClass(const ShareBufferClass &);
 virtual ~ShareBufferClass();
protected:
 T *RawBuffer,*Array; int Count,Alignment;
};
class OpaqueRefBuffer:public ShareBufferClass<RefCountClass*> {
public:
 OpaqueRefBuffer(const OpaqueRefBuffer &);
 virtual ~OpaqueRefBuffer();
};
OpaqueRefBuffer::OpaqueRefBuffer(const OpaqueRefBuffer &that):ShareBufferClass<RefCountClass*>(that)
{
 for(int i=0;i<Count;++i) if(RawBuffer[i]) RawBuffer[i]->Add_Ref();
}
