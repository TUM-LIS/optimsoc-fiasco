IMPLEMENTATION [or1k]:

IMPLEMENT inline
void
Space::switchin_ldt() const
{
    printf("\x1b[31mSpace::switchin_ldt()\n\x1b[0m");
}
