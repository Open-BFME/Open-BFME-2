// cl: /DNDEBUG /MD
// ?Rva002ACF9CInsert@@YGPAPAXPAPAXPAX0@Z @0x002ACF9C (37B): freelist node insert.
// Allocates a node through rowed ?Rva002AC04EAlloc@@YGPAXPAPAX@Z (same pool
// at 0x009BBD2C), links it after pos (next at +4: node+0=pos node+4=old
// next old-next+0=node pos+4=node), stores it into *out and returns out.
// Callers at 0x002AD045 and 0x002ADCD8. No donor; honest address name
// matching Rva00239D02Insert pattern.
void *__stdcall Rva002AC04EAlloc(void **arg);
void **__stdcall Rva002ACF9CInsert(void **out, void *pos, void **allocArg)
{
	void *node = Rva002AC04EAlloc(allocArg);
	void *next = ((void **)pos)[1];
	((void **)node)[0] = pos;
	((void **)node)[1] = next;
	((void **)next)[0] = node;
	((void **)pos)[1] = node;
	*out = node;
	return out;
}
