# GDB log

One dated section per week. Paste the commands you used and the output you saw, then explain what it means in your own words. Pasted output with no explanation earns partial credit at most.

## Week 10 (Lab 5)

### Part A: basics with `buggy_rooms.cpp`

Build and run:

```
cmake -S . -B build
cmake --build build --target buggy_rooms
./build/buggy_rooms
```

Record:

- The backtrace (`bt`) after the crash:
- The function and line number where your own code crashed (use `frame N` to move to it):
- The value of the pointer that caused the crash (`print`):
- How you stepped through the program (`break main`, `run`, `next`, `step`): list the commands and what each showed:
- The fix, and how you checked it:

Notes:

Part A:
#1  0x00005555555563de in describe (room=0x0) at /home/ubuntu/cosc1437/lab10/gdb/buggy_rooms.cpp:36
#2  0x00005555555566b6 in main () at /home/ubuntu/cosc1437/lab10/gdb/buggy_rooms.cpp:53
The function and line number that crashed is line 36 in the describe function
room was evaluated to 0x0 as shown in the error message

- 'break main': start from inside of main
- 'run': started and ran the program in main
- 'next': goes through each line and running, occassionally printing out the statements
- 'step': using step I investigated describe and on the final step, room was 0x0

describe (room=0x55555556d2d0) at /home/ubuntu/cosc1437/lab10/gdb/buggy_rooms.cpp:36

- for the fix, I added a check to see if current location it is trying to describe is a nullpointer
- it then returns a statement saying you cannot go that way if that is the case.

Output:
You are in the hall. A long, cold hall.
You are in the kitchen. Pots hang from hooks.
You are in the pantry. Shelves of jars.
Segmentation fault (core dumped)




### Part B: memory with `deck_bugs.cpp`

Build with AddressSanitizer and run each bug on its own (`./deck_bugs 1`, `2`, `3`).

For each bug, write one or two sentences: what kind of error AddressSanitizer reported, where the memory was allocated, and where it was freed.

| Bug | Report kind | Allocated at | Freed at | Cause in one sentence |
| --- | --- | --- | --- | --- |
| 1 |Memory Leak | new Card[52] | Memory was never freed | The dynamic memory was never freed|
| 2 |Double free error | new Card[52]|destructor |shallow copy makes the delete remove both rawdeck objects |
| 3 | | | | |

Confirm one bug in GDB. Use at least two of `watch`, `finish`, and `x`. Paste the session and explain what each command showed:
- I ran GDB for Bug 2
- I set a breakpoint for the deck copy function and watched for back up
- it returned this:
Hardware watchpoint 2: backup

Old value = {cards_ = 0x55555556f460, size_ = -7728}
New value = {cards_ = 0x55555556f460, size_ = 52}
RawDeck::RawDeck (this=0x7fffffffe140, other=...) at

- this showcases a shallow copy, which mean't the new deck points to the address of the original
- instead of making a new one, so I will need make a copy constructor due to the rule of 3
- I then ran finish which let the function run till the end
Fixes for all three bugs (describe each change):
- Bug 1's fix was to delete the allocated memory hand, by using the delete function
- Bug 2's fix was to make a copy constructor for RawDeck
