# AK-2 | Lab Work #7
Debugging Techniques in Linux Kernel

### Task:
> - Add `BUG_ON()` instead of printing the message and returning `-EINVAL` for an invalid parameter value.
> - Add a forced error "like kmalloc() returned 0" when generating a list item for some message (the last, the 5th, ... - on your choice).
> - Modify the Makefile.
> - Receive both messages, look at them, and search for the crash place for one of them.
