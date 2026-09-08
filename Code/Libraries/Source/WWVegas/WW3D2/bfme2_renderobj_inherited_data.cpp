// cl: /O2 /G7 /EHsc /MD /DNDEBUG
//
// Neutral BFME2 ABI view for the inherited render-data walk at RVA 0x0013BEC0.
// The original retail method spelling is not established.  The corrected
// RenderObj prefix independently places Container at +0x7C and the opaque
// inherited slot at +0xC0.  The target Render pipeline calls this walk at
// 0x0054763C and 0x0054A86D, saving/restoring the result through DEDA78.
// Keep this view descriptive; it is not a claim about RenderObj RTTI.
class BFME2RenderObjInheritedDataView {
    unsigned char Prefix[0x7c];
    BFME2RenderObjInheritedDataView *Container;
    unsigned char Between[0x40];
    void *InheritedRenderData;

public:
    void *Get_Inherited_Render_Data(void);
};

void *BFME2RenderObjInheritedDataView::Get_Inherited_Render_Data(void)
{
    void *data = InheritedRenderData;
    BFME2RenderObjInheritedDataView *container = Container;
    while (data == 0 && container != 0) {
        data = container->InheritedRenderData;
        container = container->Container;
    }
    return data;
}
