// cl: /DNDEBUG /MD
// ?Rva00239D02Insert@@YGPAPAXPAPAXPAX0@Z @0x00239D02 37B: freelist node insert.
// Allocates a node through rowed ?Rva00239BD8Alloc@@YGPAXPAPAX@Z (same pool
// at 0x009BA5E0), links it after pos (next at +4: node+0=pos node+4=old
// next old-next+0=node pos+4=node), stores it into *out and returns out.
// Caller at 0x00239E1C plus 25 more. No donor; honest address name.
void *__stdcall Rva00239BD8Alloc(void **arg);
void **__stdcall Rva00239D02Insert(void **out, void *pos, void **allocArg)
{
	void *node = Rva00239BD8Alloc(allocArg);
	void *next = ((void **)pos)[1];
	((void **)node)[0] = pos;
	((void **)node)[1] = next;
	((void **)next)[0] = node;
	((void **)pos)[1] = node;
	*out = node;
	return out;
}
