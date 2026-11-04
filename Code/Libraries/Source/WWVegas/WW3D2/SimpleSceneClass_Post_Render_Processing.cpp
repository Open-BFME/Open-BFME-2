// cl: /DNDEBUG /MD /EHsc

class RenderObjClass
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void slot0a(void);
	virtual void slot0b(void);
	virtual void slot0c(void);
	virtual void slot0d(void);
	virtual void slot0e(void);
	virtual void slot0f(void);
	virtual void Remove(void);
};

#include "SimpleSceneClass.h"

void SimpleSceneClass::Post_Render_Processing(RenderInfoClass &rinfo)
{
	RefMultiListClass<RenderObjClass> *list = &ReleaseList;
	MultiListNodeClass *node = ReleaseList.Head.Next;
	MultiListNodeClass *head = &list->Head;

	if (node != head) {
		do {
			RenderObjClass *object =
				node->Object != 0
					? reinterpret_cast<RenderObjClass *>(
						reinterpret_cast<char *>(node->Object) - 8)
					: 0;
			object->Remove();
			node = node->Next;
		} while (node != head);
	}

	list->Reset_List();
}
