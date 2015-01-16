IMPLEMENTATION [or1k]:

PRIVATE inline
bool
Task::invoke_arch(L4_msg_tag &, Utcb *)
{
    printf("(NOT IMPLEMENTED) %s in %s\n", __func__, __FILE__);
  return false;
}
