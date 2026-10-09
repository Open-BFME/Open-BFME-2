// ?Remove_Head@?$MultiListClass@VRenderObjClass@@@@QAEPAVRenderObjClass@@XZ
// partial score=1.0 date=2026-10-09
// cl: /O1 /G7 /DNDEBUG /MD
// BF1 f989 multilist.h structural candidate, not a target template identity.
// Native 6EF7D calls Internal_Remove_List_Head6109A0 then preserves null
// while adjusting a nonnull result -8. The concrete payload remains unknown.
class MultiListObjectClass { public: void *ListNode; };
class RefCountClass { public: virtual void Delete_This(); int RefCount; };
class RenderObjClass : public RefCountClass, public MultiListObjectClass {};
class GenericMultiListClass {
protected: MultiListObjectClass *Internal_Remove_List_Head();
};
template<class T> class MultiListClass : public GenericMultiListClass {
public: T *Remove_Head();
};
RenderObjClass *MultiListClass<RenderObjClass>::Remove_Head() {
    return static_cast<RenderObjClass *>(Internal_Remove_List_Head());
}
