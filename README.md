# Private code libraries
This repo contains my libraries that I use often in my private development work. Where possible the library contains a directory called tests that contain unittests.
## sqlibc
Various reimplementations of libc functions. Why? I want to be sure how they work and they do not sneakily use some ram or other resources. Depricated and merged in sqlibembedded.
### TODO
Time to remove dependencies and delete.
## sqlibembedded
Merger of various libc functions with additional functionality like higher level data structures like queues, string buffers and much more. All functions have corresponding unittests, striving for 100% code coverage.
### TODO
* Move over stuff from embedded snippets repo here so it is easier to use
* Verify code coverage with gcov
* integrate with buildbot automatic build system
