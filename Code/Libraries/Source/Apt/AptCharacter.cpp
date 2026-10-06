// cl: /DNDEBUG /MD /EHsc
// AptCharacter.cpp: the two flag-setting forwarders to the three-argument Apt
// helper (aptHelper008AE3A0, unrowed), which retail links from this TU (tu_map approved, by
// address contiguity inside the AptCharacter span), folded from two split
// units with these exact flags.
class AptValue;
AptValue *aptHelper008AE3A0(void *entry, int count, int flag);

// Retail 0x006ED450 (21B, named 008AE450 by its split unit): invoke the helper with its flag clear.
AptValue *aptHelperClearFlag008AE450(void *entry, int count)
{
    return aptHelper008AE3A0(entry, count, 0);
}

// Retail 0x006ED470 (21B, named 008AE470 by its split unit): invoke the helper with its flag set.
AptValue *aptHelperSetFlag008AE470(void *entry, int count)
{
    return aptHelper008AE3A0(entry, count, 1);
}
