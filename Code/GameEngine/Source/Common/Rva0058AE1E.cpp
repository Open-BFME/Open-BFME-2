// cl: /MD
// ?Rva0058AE1EGet@@YGHPAX@Z 0x0058AE1E 24B evidence: AIUpdateInterface+0x258 victim !=0 via rowed getCurrentVictim; ret 4 stdcall
class Object;
class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

int __stdcall Rva0058AE1EGet(void *p)
{
	AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)p + 0x258);
	return ai->getCurrentVictim() != 0;
}
