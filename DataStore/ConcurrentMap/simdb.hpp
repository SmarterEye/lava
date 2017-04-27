
// -todo: test 128 bit atomics
// -todo: find memory corruption bug on looping insert of random numbers - just put key where value should be in C++ string put
// -todo: figure out why all keys are being printed - getKeys() returns a single empty string
// -todo: figure out why getKeys returns one empty string - for short blocks, the last block is a key/starting block because it is also the first block. The make_BlkLst function made non keys have length and key length automatically set to 0.
// -todo: figure out why duplicate keys aren't overwriting each other - putHashed needs to match without using version, then compare and swap using version, checking the match each time
// -todo: test with multiple threads in a loop
// -todo: take out infinite loop possibility in rm
// -todo: take out any inf loops in runMatch
// -todo: change getKeyStrs() to get the number looped through by nxtKey() so it isn't O(n^2)
// -todo: put in osx stuff here - likely mmmap with shared memory
// -todo: try using NtOpenFile
// -todo: make a standard "simdb" shared memory file that contains the paths of all other shared memory files? - not needed for now
// -todo: make realloc that changes the size of a block list - would have to find a way to not break concurrency to be able to resize block lists, with reference counting and some sort of flag, it would still be the same as blinking the key out of existence while a thread updates the block list size
// -todo: make windows version have permissions for just read and write
// -todo: check if memset to 0 is still anywhere in the release build - line 1827 still has a memset to 0 on free
// -todo: get compiler warning out of windows build - just need to take out unneccesary headers and copy in any struct and function definitions?
// -todo: make function to swap two VerIdxs of ConcurrentHash
// -todo: make function to swap the hi and low 32 bits of VerIdx, swapping the order
// -todo: make sure that versions for even and odd VerIdx are kept to be even and odd version numbers - odds need to start at 1 and both need to be incremented by 2
// -todo: make VerIdx layout in ConcurrentHash have a ping pong memory layout
// -todo: make 128 bit swap increment both versions - no need
// -todo: make versions increment by 2 - no need, versions come from the block version
// -todo: make 128 bit atomic function
// -todo: make resize function so block lists can be resized rather than freed, only to be reallocated - doesn't work like this!
// -todo: convert to 64 bit integers - not now, just need to clean up type aliases and signs
// -todo: test windows permissions - ok now that \\Global isn't used and the shared memory 'Segment' goes into the current session?
// -todo: take out WINNT namespace for windows NT definitions
// -todo: make readers for blocks only exist on the head of the list? - not needed
// -todo: move make_BlkLst to constructor
// -todo: change BlkLst union to hold hash values
// -todo: writeup why robin hood hashing will work for put, get, and delete (and their interactions)
// -todo: store hash of key in ConcurrentStore
// -todo: make alloc give back the blocks if allocation fails - already done
// -todo: make sure when comparing VerIdxs that they compare both the version and the index - already done, compared as a single 64 bit int ?
// -todo: make sure ConcurrentStore.put() tests each block for LIST_END - not needed because alloc checks for LIST_END
// -todo: make the BlkLst hash be checked before comparing keys
// -todo: make ConcurrentStore get() stop before exceeding maxlen? - already done
// -todo: clean up type aliases with ui32 to u32
// -todo: make arguments to listDBs for the prefix? 'type' is windows specific and should be ok to be hardcoded - not neccesary because windows will be hardcoded and unix and linux don't have types
// -todo: make a macro to have separate windows and unix paths
// -todo: initialize ConcurrentHash with a pointer to ConcurrentStore
// -todo: change rm() to del()
// -todo: change i8* to u8* and ui8* to u8*
// -todo: get rid of unused uiX type aliases
// -todo: take out IDX alias
// -todo: make del() delete a VerIdx, duplicate the VerIdx ahead into the deleted slot, check that the indices are the same, and if they are, mark the one further ahead as deleted
// -todo: make a DELETED value for hash entries so that when something is removed, it doesn't block a linear search
// -todo: take out stack based m_blocksUsed
// -todo: give a ConcurrentStore pointer to ConcurrentHash 
// -todo: change ConcurrentHash  to CncrHsh or LfHsh
// -todo: change ConcurrentStore to CncrStr
// -todo: change ConcurrentList  to CncrLst
// -todo: make compexchange_kv take VerIdx instead u64
// -todo: make deleted_i64 function - made a vi_i64 function instead
// -todo: make deleted indices that have an empty index on their right side become empty indices
// -todo: take out simdb_ prefix? - if this happens, how will listDBs be able to find, think about this later, an answer will likely become clear
// -todo: change compexchange_kv to cmpex_vi
// -todo: need to do anything special to guarantee that readers is aligned so it is atomic? - no it is 64 bit so alignement doesn't matter for atomicity and barely matters for performance
// -todo: clean up inconsitent signs and usage of negative numbers - VerIdx and BlkLst both have i32 for their idx field
// -todo: switch negative numbers to a bitfield struct instead of implicitly using the sign bit for different purposes - use a bitfield struct with a flag for hitting LIST_END for out_blocks in alloc()
// -todo: this conflates and assumes that EMPTY_KEY is both the CncrStr block index EMPTY_KEY and the CncrHsh EMPTY_KEY - probably fine
// -todo: use the VersionIdx struct with the return from alloc()
// -todo: stop using lambdas and templates - step 1, moving functions to CncrHsh
//       | len()
//       | get()
//       | del()
//       | put()
// -todo: stop using match function as a template in del() 
// -todo: change load_kv and store_kv to load_vi and store_vi
// -todo: check the hash in each BlkLst index as an early out for failed reads - already done through CncrStr::compare()
// -todo: get() - short circuit as not found on finding an empty slot - will need a deleted value - already was returning false on EMPTY, but needed to keep going on DELETED_KEY
// -todo: check if reads can be made non-atomic if they already aren't - not worth looking in to now
// -todo: redo EMPTY_KEY and DELETED_KEY to use last two values of u32
// -todo: put supporting windows functions into anonymous namespace - only typedefs needed to be outside the anonymous namespace
// -todo: put prefetching into reading of blocks - put in to nxtBlock()
// -todo: look at making a memory access to the next block that can't be optimized away
// -todo: prefetch memory for next block when looping through blocks - does this require a system call for shared memory and does it lock? it should just be the prefetch instruction or an unoptimized away load? use intrinsic?
// -todo: change CncrStr::get() to check the version after reading and not before - is this not technically correct!!1! this checks that the next version is the same and then reads it, but shouldn't it read the block and then check if the version is still the same? - version is checked in readblock already
// -todo: fix infinite loop on put
// -todo: fix infinite loop on delete
// -todo: make a swapped VerIdx type? - no because it won't do any good due to the VerIdx struct being used moslty to store the info on the stack and store it in memory 
// -todo: make sure that 128 bit atomics are actually being called - breakpoint is hit when setting inside the function
// -todo: refine putHashed to have proper names
// -todo: change CncrStr::free() to take a VerIdx instead of separate variables? - might as well not 
// -todo: fix infinite loop when deleting "wat" for the second time - alloc was not setting the first BlkLst index correctly
// -todo: re-evaluate CncrHsh main loops' back tracking on compare exchange failure - just use prevIdx(i) - could use a goto to the top of the loop to avoid running prevIdx and then nxtIdx
// -todo: make cmpex_vi swap hi and lo on odd indices - also had to feed it the actual address of the shared memory vi instead of the address of the copied (and possibly swapped)
// -todo: rename m_kvs to m_vis
// -todo: flatten putHashed into having the block comparison embedded 

// todo: debug len returning 0 when key seems to exist in memory
// todo: redo CncrHsh to use the shared memory instead of the lava_vec allocated on heap mistake - this will require aligning to 128 bit memory
// todo: print or visualize CncrHsh 
// todo: redo the BlkLst struct with calibrated bitfield size and without sub structures
// todo: make put give back FAILED_PUT on error - isn't EMPTY_KEY enough?
// todo: make put return VerIdx ? - is having an out_version pointer enough?
// todo: make bulk free by setting all list blocks first, then freeing the head of the list - does only the head of the list need to be freed anyway since the rest of the list is already linked together? could this reduce contention over the block atomic?
// todo: Make frees happen from the last block to the first so that allocation might happen with contiguous blocks
// todo: flatten runIfMatch function to only take a function template argument but not a match function template argument
// todo: change CncrHsh init to set ints directly instead of using store_vi
// todo: find and remnants of KeyVal or kv and change them to VerIdx or vi
// todo: stop using match function as a template in and just run a function in CncrHsh
//       | len()
//       | get()
//       | put()
// todo: make sure that the important atomic variables like BlockLst next are aligned? need to be aligned on cache line false sharing boundaries and not just 64 bit boundaries?
// todo: make a function to use a temp directory that can be called on linux and osx - use tmpnam/tmpfile/tmpfile from stdio.h ?
// todo: put files in /tmp/var/simdb/ ? have to work out consistent permissions and paths
// todo: make sure readers is only used on the key block list
// todo: make sure readers deletes the block list if it is the last reader after deletion
// todo: search for any embedded todo comments
// todo: clean out old commented lines
// todo: compile with maximum warnings
// todo: run existing tests

// robin hood hashing
// todo: do rm()/del() first and make deletion take care of holes in spans?
// todo: make put() insert at the first available slot then swap with one index lower if it has a IPD that is at least 2 less
//       | after swapping, set the block list's version to the new version of the index? - what if the found version is not what the old version was? leave it? 
// todo: align ConcurrentHash's lava vec on 128 bit boundary - need to make an extra 128bit value and 
// todo: -organize ConcurrentHash entry to have the index on the left side, version on the right side. 
//       Put hash in the middle and use the first two bits of the index as empty and deleted flags
//       empty : 1, deleted : 1, index : 35, hash : 35, version : 56 - total 128 bits, 34 billion entry limit 
// todo: test alignment
// todo: figure out deletion - look back at tbl with EMPTY and NONE types 
//       | even without robin hood hashing are 128 bit atomics needed to swap/bubble sort keys into the new free slot?
//       | when deleting, instead of swapping the deleted key, duplicate the next key to the previous key and so on until reaching either an empty slot, a key that is further from its optimal distance, or two of the same key in a row (indicating another thread is moving keys around)

// todo: make a 'waiting' flag or type for keys so that they can be rewritten and resized in place? - would mean that they could not be read from at any time like they can be now
// todo: make alloc look for multiple blocks then check the next block variable for its version and if the version has not changed, allocate all blocks at once?
// todo: make a resize/realloc function to change the size of a block list instead of destroying and creating all indices when updating a key? - would need a different putWeak, since the writing of the index needs  to be atomic and re-writing the currently used blocks would not work with concurrency
// todo: integrate realloc into put() function - will need to query to see if the key exists, delete it, then insert the reallocated version? - if done like this, does it disrupt for a moment a key existing, and if so, is this an insurmountable problem?

// q: do the Index numbers in VerIdx need a flag saying that they haven't been changed? - what if before a thread switches two indices, other threads delete both VerIdxs and create new VerIdxs with different ideal position distances, but the exact same Indexes? can storing the Index as an xor of the Version and the Index solve this or will there still be non unique combinations? Ths would also mean that the Index would not line up immediatly after the swap. Do the upper bits of a 64 bit version counter need to be used? If even/odd versions are used, does that alleviate the problem? Is there a way to do XOR swapping and be able to see the XOR in progress?
// q: what operations need ConcurrentHash Index values to have versions with them? 
//       | get() does not, since it can check the key value to verify the block list is what it wants and it can check the version number on the block list to make sure the blocks did not change while reading
//       | put() does, since it needs to know that the Index value it is going to change still points to the same data
//       | del() does, since it needs to know that the Index value it is going to change still points to the same data
// q: what if two version numbers are put into each block list starting entry? verA, verB, hash, and index - 128 bits
// q: if Index values are swapped atomically but their version numbers can not be known to be the same, does this require more flexibility on the part of the linear search? only stop when hitting IPD (ideal position distances) less than the IPD of the searched item more than once? 
// q: the 64 bit Index swap needs to check that both IPD are still the same after the swap?
// q: is it possible to know to go backwards when finding an element if the same index is seen with a different version on an adjacent VerIdx ?

// q: can cleanup be done by a ring buffer of block lists? would the ring buffer only need to be as long as the number of threads if each thread helps clear out the ring buffer after every free()? Probably not, because delayed deallocation would be useful only when there is a reader/ref count, which would mean many more reads than writes could stall the ability to free? But each thread can really only hold one reference at a time so maybe it would work? 
// q: if using a ring buffer, indices might be freed in between non-freed indices, in which case the pointer to beginning and end would not be able to shift, and therefore would need space for more indices than just the number of threads
// q: if using a ring buffer for frees, could a thread freeing the index then bubble sort backwards and move the begin pointer forwards until the begin and end pointers have only non freed indices between them 
// q: what is the benefit of a ring buffer? does it prevent the need for a spinlock anywhere?
// q: does the main program even need a key value store? can't it just use the block list indices directly?
// q: should maximum probe length be used here?
// q: should use a separate 'tombstone' value for a deleted value?
// q: should store hash to be able to know probe length and as a short circuit for false matches?
// q: can deleted entries be returned to empty entries on removal or some other operation somehow? if robinhood hashing means keeping the probe distance to only partial overlapping spans, does that open up the possibility?
//    - on removal, if the previous entry is EMPTY or if the previous entry has a probe span of 0, set the current entry to EMPTY
//      can actually loop backwards the (length of the span) - 1 (to the natural position + 1) to see if there are any overlapping spans?
//      on removal, loop backwards to robin hood hash any overlapping span
//      after robin hood hashing from the natural position set any DELETED keys after to EMPTY since they are after a span of 0 or after EMPTY 
//    - if the current entry is EMPTY, loop forward setting adjacent DELETED entries to EMPTY
// q: does robinhood hashing mean keeping a stack of moved values until the end of a robery chain is complete, then copying from the end of the chain to beggining? 
// q: could ISPC be compiled to C++ intrinsics to integrate into a one header file structure? - should be useful for hashing and comparison?
// q: can make a bitmap for filled hash indices if the bit is set after the KV is set, and the bit is unset before unsetting the KV
// q: can intrinsics be used for 128bit atomics?
// q: make ConcurrentHash be a 48 bit index and a 48 bit version
//    - pack them together and use unaligned atomic reads and writes?
//    - be able to modify an index,version,index triplet with a 128 bit atomic or a version,index,version triplet?  
// q: can some sort of stack or list or current outstanding version reads be used to make sure version numbers don't wrap around, therefore needing less bits for the version number?
// q: can a high bits version number and low bits version number be used to detect vesion number wrap arounds?  One 64 bit number while just the lower bits are stored?
// q: interleave reference counting / readers count on both hash and store?
//    - when reading from a ConcurrentHash value, increment the readers by 1, increment the block idx by 1, then decrement the ConcurrentHash
//    - does this destroy the ability to do robinhood hashing without spinlocking?
// q: on removal, follow DELETED entries forward until hitting a key entry, and if the removed entry was inside its probe span, bring the found entry up by copying, then remove the found entry, then loop forward, trying to set DELETED entries to EMPTY if they are after EMPTY or after the end of a probe span
// q: can part of the version be put on one side of a struct and part on the other side? maybe even interleave bits?
// q: just have a flag bit on each side? this would allow signaling that only one thread at a time is doing the removal cleanup and allow cleanup concurrently with insertion? 
//    1. flip bits in between two entries
//    ////2. consider the opposite bits to be 'changed' bits and flip them only if an insert sees either of the bits flipped
//    ///////3. if the removal process detects a 'changed' bit, ... 
//    //////4. is it needed if versions are involved, and even so would it work?
//    2. what is the problem? - need to be able to tell if previous entry is the same when changing the next entry 
//    3. keep index first and version second so that it is possible to loop forward and look at the previous version and the current index - if a high bit is used as a flag for empty, then the low bits of the version and the high bits of the index could be change atomically, meaning 32 bit precision for versions only in one brief moment 
//       !- if only the upper bit is needed, can the 64 bit atomic operation happen with 56 bits for the version and only 8 bits for the index?
//    4. then check the whole version and do some sort of error handling and recovery if the version is not the same - although 56 bits should be a year's worth of cpu cycles, so having 72 quadrillion allocations between a few instructions on another thread seems unlikely 
//    5. in theory a mutex could be used and the entire range of versions could be remapped and the master version atomic could be set to the new max+1
// q: is it possible to defragment and if so it is possible to do on removal?

/*
 SimDB

 What it does:
 |  SimDB is a key value store that uses arbitrary byte data as both the key and the value. 
 |  It additionally uses shared memory, which allows processes to communicate with each other quickly.  
 |  It is lock free and scales well with multiple threads writing, reading, and removing concurrently.  

 How it works:
 |-simdb:
   | This contains the interface as well as ConcurrentHash, ConcurentStore, and SharedMem classes.
   |-SharedMem:
   |  |  Interface to OS specific shared memory functions.
   |-ConcurrentHash:
   |  |  Hash map that uses atomics along with 64 bit values to make sure that reading and writing is lock free.
   |-ConcurrentStore:
   |  |  Keeps track of block lists.  This exposes an alloc() function and a free() function. 
   |  |  alloc() gets the index of the next block from the BlockStore.
   |  |  The BlkLst lava_vec is used to make linked lists of block indices. 
   |  |  It is an array of one integer per block with the integer at a given index representing the index of the next block.  
   |  |  This keeps the total length and the key length / value offset since it is already reference counted
   |  |-BlockStore:
   |  |-BlockList (lava_vec):

 Terms:
 |-Block List: 
 |  A sequence of block indices.  The entry in ConcurrentHash gives the position in the block list array where the list starts.  
 |  The value at each index in the array contains the index of the next block.  
 |  The list end is know when a special value of LIST_END is found as the value in the array.
 |-Block List Version:
 |  This is a version number given to each block list on allocation (not each block). 
 |  It is used to link a ConcurrentHash value to the block list. 
 |  If the versions are the same, it is known that the block list at the index read from ConcurrentHash has not changed.
 |  This change could happen if:
 |  |  1. Thread ONE reads the entry in ConcurrentHash but has not accessed the block list index in the entry yet. Pretend that thread one stalls and nothing more happens until further down.
 |  |  2. Thread TWO has already allocated a block list and swaps its new entry for the old entry which is still carried by thread one. 
 |  |  3. Thread TWO now must free the block list given by the old entry, which it does, because no thread is reading it since thread one is still stalled.
 |  |  4. Thread TWO allocates another block list, which ends up using the blocks it just deallocated.
 |  |  5. Thread ONE wakes up and reads from the block index it found in the ConcurrentHash entry, which is no longer the same and may not even be the head of the list.
 |  |  If the index is used purely for matching the binary key, this wouldn't be a problem. 
 |  |  When the index is used to find a binary value however, this is a problem, since the length of a different value could be the same, and there would be no data to be able to tell that they are different.

 How it achieves lock free concurrency:
 |  ConcurrentHash is treated as the authority of what is stored in the database. 
 |  It has an array of 64 bit integers. Each 64 bit integer is dealt with atomically.
 |  Its individual bits are used as a bitfied struct containing an index into ConcurrentStore's block list as well as the version number of that list.
 |-Finding a matching index: 
 |  |  1. Use the hash of the key bytes to jump to an index.
 |  |  2. Load the integer atomically from that index and cast to the bitfield struct.
 |  |  3. Use the index from that struct to read the bytes from the list of blocks in BlkLst. 
 |  |  4. Use version from that struct to verify that each block is part of the list given by the ConcurrenHash entry.
 |  |  5. If there is a match, keep reading the list of blocks to fill the output buffer with the value section of the block list.

 Robin Hood Hashing:
 |  The ConcurrentHash indices are organized so that when searching for a key by linear search, no encountered key has an ideal position distance lower than the key being searched for
 |  To do this concurrently, instead of looking for an empty or deleted slot in the ConcurrentHash array and simply inserting there (as with linear search), the VerIdx is put into a free slot and continuously swapped with its VerIdx to the left if the distance to its ideal position is larger.
 |  The concurrent swapping of two 64 bit structures is complicated by the fact that while 128 bit atomic compare and exchange instructions are present on most modern CPUs, they are only able to operate on 128 bit aligned memory. 
 |  While half the 128 bit pairs of two 64 bit structures could be swapped with this instruction, the other half can not.
 |  On x64 64 bit atomic compare and exchanges CAN be unaligned, meaning that if Index values are next to each other in memory, they can be compare-exchanged atomically or read atomically
 |  There are multiple insights and techniques working together that allow the concurrent swapping to happen:
 |  |  The Index of the VerIdx struct stored in the ConcurrentHash array is always unique, since it is the index into the block list.
 |  |  The Version of the VerIdx struct stored in the ConcurrentHash array is always unique if the BlockList's atomic version counter has not wrapped around after overflow
 |  |  Because both the Version AND the Index are unique, the same Version + Index combination cannot occur twice over the lifetime of the database unless the version has overflowed and wrapped around (and the same index into the BlockList ends up with the same Version)
 |  |  The 64 bit Version+Index structure (Version is 32 bits and Index is 32 bits) is flipped on even indices in the ConcurrentHash array. The memory is ordered as  |Idx Ver Ver Idx|Idx Ver Ver Idx| with '|' here representing 128 bit alignment boundaries
 |  |  The Index values, next to each other in an unaligned 64 bit configuration can be swapped atomically, though their indices can not be 
 |  del():
 |  |  Finds the matching key
 |  |  Makes sure the VerIdx matches in ConcurrentHash and atomically comapare exchanges it for a VerIdx with a DELETED_KEY index value
 |  |  Calls cleanupDeleted(i) with the current ConcurrentHash slot
 |  |  |  Checks the next slot to see if there is a VerIdx in it, and if so, check to see what its ideal position distance is
 |  |  |  If the ideal position distance is more than 0, it can be moved backwards, so duplicate it into the current slot with an atomic compare-exchange to make sure it is deleted
 |  |  |  Check the indices of the current and next slots to see if the indices are still identical and atomically compare-exchange the right index value to DELETED_KEY if they are
 |  |  |  The possibility exists that after duplication but before deletion of the duplicate, put() could swap the duplicate to the right (higher slot). Because of this, put will need to delete any indices that it finds that link to non-key block lists
 |  |  |  put() will also need to check for duplicate indices, since if they are bubble sorting a robin hood span, they could separate duplicate indices from being next to each other, but also sort them back together
 |  |  |  should get() also check for duplicates? - probably, since it would have tighter cleanup of the ConcurrentHash only at the expense of one or two extra atomic loads per read
*/

#ifdef _MSC_VER
  #pragma once
#endif

#ifndef __SIMDB_HEADER_GUARD__
#define __SIMDB_HEADER_GUARD__

#if !defined(SECTION)
  #define       SECTION(_msvc_only_collapses_macros_with_arguments, ...)
#endif

// platform specifics - mostly for shared memory mapping and auxillary functions like open, close and the windows equivilents
#if defined(_WIN32)      // windows
  // use _malloca ? - would need to use _freea and also know that _malloca always allocates on the heap in debug mode for some crazy reason
  #define STACK_VEC(TYPE, COUNT) lava_vec<TYPE>(_alloca(lava_vec<TYPE>::sizeBytes(COUNT)), COUNT, true);
  
  #include <tchar.h>
  #define NOMINMAX
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #include <strsafe.h>

  #ifdef _MSC_VER
    #if !defined(_CRT_SECURE_NO_WARNINGS)
      #define _CRT_SECURE_NO_WARNINGS
    #endif

    #if !defined(_SCL_SECURE_NO_WARNINGS)
      #define _SCL_SECURE_NO_WARNINGS
    #endif
  #endif


#elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__FreeBSD__) || defined(__linux__)  // osx, linux and freebsd
  // for mmap and munmap
  // PROT_READ and PROT_WRITE  to allow reading and writing but not executing of the mapped memory pages
  // MAP_ANONYMOUS | MAP_SHARED for the anonymous shared memory we want
  // mmap is system call 2 on osx, freebsd, and linux
  // the apple docs for mmap say "BSD System Calls" so I guess they haven't changed them around
  #include <sys/mman.h>
  #include <sys/fcntl.h>
  #include <sys/errno.h>
  #include <sys/unistd.h>
  #include <sys/file.h>         // for flock
  #include <unistd.h>
#endif

#include <cstdint>
#include <cstring>
#include <atomic>
#include <mutex>
#include <memory>
#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <cassert>

using    i8   =   int8_t;
using    u8   =   uint8_t;
using   i64   =   int64_t;
using   u64   =   uint64_t;
using   i32   =   int32_t;
using   u32   =   uint32_t;
using   f32   =   float;
using   f64   =   double;
using  au64   =   std::atomic<u64>;
using  ai32   =   std::atomic<i64>;
using   ai8   =   std::atomic<i8>;
using  cstr   =   const char*;
using   str   =   std::string;             // will need C++ ifdefs eventually or just need to be taken out
//using   ui8   =   uint8_t;
//using  ui64   =   uint64_t;
//using  ui32   =   uint32_t;
//using aui32   =   std::atomic<ui32>;
//using aui64   =   std::atomic<u64>;

template<class T, class A=std::allocator<T> > using vec = std::vector<T, A>;  // will need C++ ifdefs eventually

#ifdef _WIN32                         // these have to be outside the anonymous namespace
  typedef void        *HANDLE;
  typedef HANDLE     *PHANDLE;
  typedef wchar_t       WCHAR;        // wc,   16-bit UNICODE character
  typedef UCHAR       BOOLEAN;        // winnt
  typedef unsigned long ULONG;
#endif

namespace {
  enum Match { MATCH_FALSE=0, MATCH_TRUE=1, MATCH_REMOVED=-1  };

  struct _u128
  {
    volatile u64 hi; volatile u64 lo; 
    //_u128& operator=(_u128 l){ hi = l.hi; lo = l.lo; return *this; };
  };

  template<class T>
  class lava_noop
  {
    void operator()(){}
  };

  template<class T, class Deleter=std::default_delete<T>, class Allocator=std::allocator<T> >
  class lava_vec
  {
  private:
    void* p;

    void       set_size(u64  s)
    { 
      *((u64*)clearBits(p) + 1) = s;
    }
    void  set_sizeBytes(u64 sb)
    {
      *((u64*)clearBits(p)) = sb;      // first 8 bytes should be the total size of the buffer in bytes
    } 

  public:
    static void*  setDestructorBit(void* p)
    {
      //return (void*)((u64)p ^ (((u64)1l)<<63));
      return (void*)((u64)p | (1llu<<63));
    }
    static bool   getDestructorBit(void* p)
    {
      return (((u64)p)>>63)!=0;
    }
    static void*         clearBits(void* p)
    {
      return (void*)( ((u64)p) & 0x0000FFFFFFFFFFFF);
    }
    static u64          sizeBytes(u64 count)  // sizeBytes is meant to take the same arguments as a constructor and return the total number of bytes to hold the entire stucture given those arguments 
    {
      return sizeof(u64)*2 + count*sizeof(T);
    }

    lava_vec(){}
    lava_vec(u64  count)
    {
      u64 sb = lava_vec::sizeBytes(count);
      p       = Allocator().allocate(sb);
      p       = setDestructorBit(p);
      set_size(count);
      set_sizeBytes(sb);
    }
    lava_vec(void*  addr, u64 count, bool owner=true) :
      p(addr)
    {
      if(owner){
        set_sizeBytes( lava_vec::sizeBytes(count) );
        set_size(count);
      }
    }
    lava_vec(void*  addr) :
      p(addr)
    {
      //u64 sb = lava_vec::sizeBytes(count);
      //set_size(count);
      //set_sizeBytes(sb);
      //
      //p = addr;
    }
    lava_vec(lava_vec const&) = delete;
    void operator=(lava_vec const&) = delete;
    lava_vec(lava_vec&& rval)
    {
      p      = rval.p;
      rval.p = nullptr;
    }
    ~lava_vec()
    {
      if(p && getDestructorBit(p)){
        Deleter().operator()((T*)clearBits(p));  //free(p);
        p = nullptr;
      }
    }

    T& operator[](u64 i)
    {
      return data()[i];
    }

    T*         data()
    {
      u64* maskptr = (u64*)clearBits(p); 
      return (T*)(maskptr+2);
    }
    u64   capacity() const
    {
      return (sizeBytes() - sizeof(u64)*2) / sizeof(T);
    }
    u64       size() const
    {
      return *((u64*)clearBits(p) + 1);   // second 8 bytes should be the number of elements
    } 
    u64  sizeBytes() const
    {
      return *((u64*)clearBits(p));   // first 8 bytes should be the total size of the buffer in bytes
    } 
    auto       addr() const -> void*
    {
      return p;
    }
  };

  inline u64 fnv_64a_buf(void const *const buf, u64 len)
  {
    // const u64 FNV_64_PRIME = 0x100000001b3;
    u64 hval = 0xcbf29ce484222325;    // FNV1_64_INIT;  // ((Fnv64_t)0xcbf29ce484222325ULL)
    u8*   bp = (u8*)buf;	           /* start of buffer */
    u8*   be = bp + len;		           /* beyond end of buffer */

    while(bp < be)                     // FNV-1a hash each octet of the buffer
    {
      hval ^= (u64)*bp++;             /* xor the bottom with the current octet */

      //hval *= FNV_64_PRIME; // does this do the same thing?  /* multiply by the 64 bit FNV magic prime mod 2^64 */
      hval += (hval << 1) + (hval << 4) + (hval << 5) +
              (hval << 7) + (hval << 8) + (hval << 40);
    }
    return hval;
  }
  
  inline bool compex128(
    volatile long long*  _Destination, 
    long long           _ExchangeHigh, 
    long long            _ExchangeLow, 
    long long*      _CompareAndResult)
  {
    return _InterlockedCompareExchange128(
     _Destination,
     _ExchangeHigh,
     _ExchangeLow,
     _CompareAndResult) == 1;
  }

  inline void prefetch1(char const* const p)
  {
    // if msvc or intel compilers
    _mm_prefetch(p, _MM_HINT_T1);
    // else 

    //endif
    //_m_prefetch((void*)p);
  }

  #ifdef _WIN32
    using  u128 = __declspec(align(128)) /*volatile*/ _u128;
  #else
    using  u128 = volatile _u128;
  #endif

  #ifdef _WIN32
    typedef struct _UNICODE_STRING {
      USHORT Length;
      USHORT MaximumLength;
      #ifdef MIDL_PASS
          [size_is(MaximumLength / 2), length_is((Length) / 2) ] USHORT * Buffer;
      #else // MIDL_PASS
          _Field_size_bytes_part_(MaximumLength, Length) PWCH   Buffer;
      #endif // MIDL_PASS
      } UNICODE_STRING;
    typedef UNICODE_STRING *PUNICODE_STRING;

    typedef struct _OBJECT_ATTRIBUTES {
        ULONG Length;
        HANDLE RootDirectory;
        PUNICODE_STRING ObjectName;
        ULONG Attributes;
        PVOID SecurityDescriptor;        // Points to type SECURITY_DESCRIPTOR
        PVOID SecurityQualityOfService;  // Points to type SECURITY_QUALITY_OF_SERVICE
    } OBJECT_ATTRIBUTES;
    typedef OBJECT_ATTRIBUTES *POBJECT_ATTRIBUTES;

    typedef long LONG;
    typedef LONG NTSTATUS;

    // the following is api poison and is a cancerous abomination, but it seems to be the only way to list the global anonymous memory maps in windows  
    #define DIRECTORY_QUERY              0x0001  
    #define STATUS_SUCCESS               ((NTSTATUS)0x00000000L)    // ntsubauth
    #define OBJ_CASE_INSENSITIVE         0x00000040L
    #define STATUS_NO_MORE_FILES         ((NTSTATUS)0x80000006L)
    #define STATUS_NO_MORE_ENTRIES       ((NTSTATUS)0x8000001AL)

    typedef struct _IO_STATUS_BLOCK {
		  union {
			  NTSTATUS Status;
			  PVOID    Pointer;
		  };
		  ULONG_PTR Information;
	  } IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;
  
    using NTOPENDIRECTORYOBJECT = NTSTATUS (WINAPI*)(
	    _Out_  PHANDLE DirectoryHandle,
	    _In_   ACCESS_MASK DesiredAccess,
	    _In_   POBJECT_ATTRIBUTES ObjectAttributes
	  );
    using NTOPENFILE = NTSTATUS (WINAPI*)(
      _Out_ PHANDLE               FileHandle,
      _In_  ACCESS_MASK        DesiredAccess,
      _In_  POBJECT_ATTRIBUTES ObjectAttributes,
      _Out_ PIO_STATUS_BLOCK   IoStatusBlock,
      _In_  ULONG                ShareAccess,
      _In_  ULONG                OpenOptions
    );
    using NTQUERYDIRECTORYOBJECT = NTSTATUS(WINAPI*)(
	    _In_       HANDLE DirectoryHandle,
	    _Out_opt_  PVOID Buffer,
	    _In_       ULONG Length,
	    _In_       BOOLEAN ReturnSingleEntry,
	    _In_       BOOLEAN RestartScan,
	    _Inout_    PULONG Context,
	    _Out_opt_  PULONG ReturnLength
	  );
    using RTLINITUNICODESTRING = VOID(*)(
      _Out_    PUNICODE_STRING DestinationString,
      _In_opt_ PCWSTR          SourceString
    );

    struct OBJECT_DIRECTORY_INFORMATION
    {
      UNICODE_STRING    name;
      UNICODE_STRING    type;
    };

    auto      GetLastErrorStdStr() -> std::string
    {
      DWORD error = GetLastError();
      if (error)
      {
        LPVOID lpMsgBuf;
        DWORD bufLen = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0, NULL );
        if (bufLen)
        {
          LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
          std::string result(lpMsgStr, lpMsgStr+bufLen);
      
          LocalFree(lpMsgBuf);

          return result;
        }
      }
      return std::string();
    }
    PVOID  GetLibraryProcAddress(PSTR LibraryName, PSTR ProcName)
    {
      return GetProcAddress(GetModuleHandleA(LibraryName), ProcName);
    }
  #endif
}

#ifdef _WIN32
  auto listDBs() -> std::vector<std::wstring>
  {
    //using namespace WINNT;

    static HMODULE _hModule = nullptr; 
    static NTOPENDIRECTORYOBJECT  NtOpenDirectoryObject  = nullptr;
    static NTOPENFILE             NtOpenFile             = nullptr;
    static NTQUERYDIRECTORYOBJECT NtQueryDirectoryObject = nullptr;
    static RTLINITUNICODESTRING   RtlInitUnicodeString   = nullptr;
    
    std::vector<std::wstring> ret;

    if(!NtOpenDirectoryObject){  
      NtOpenDirectoryObject  = (NTOPENDIRECTORYOBJECT)GetLibraryProcAddress( _T("ntdll.dll"), "NtOpenDirectoryObject");
    }
    if(!NtQueryDirectoryObject){ 
      NtQueryDirectoryObject = (NTQUERYDIRECTORYOBJECT)GetLibraryProcAddress(_T("ntdll.dll"), "NtQueryDirectoryObject");
    }
    if(!NtOpenFile){ 
      NtOpenFile = (NTOPENFILE)GetLibraryProcAddress(_T("ntdll.dll"), "NtOpenFile");
    }

    HANDLE   hDir = NULL;
    IO_STATUS_BLOCK  isb = { 0 };
    WCHAR* mempth = L"\\BaseNamedObjects";
    
    WCHAR buf[4096];
    UNICODE_STRING   pth = { 0 };
    pth.Buffer        = mempth;
    pth.Length        = (USHORT)lstrlenW(mempth) * sizeof(WCHAR);
    pth.MaximumLength = pth.Length;

    OBJECT_ATTRIBUTES oa = { 0 };
    oa.Length = sizeof( OBJECT_ATTRIBUTES );
    oa.RootDirectory      = NULL;
    oa.Attributes         = OBJ_CASE_INSENSITIVE;                               
    oa.ObjectName         = &pth;
    oa.SecurityDescriptor = NULL;                        
    oa.SecurityQualityOfService = NULL;               

    NTSTATUS status;
    status = NtOpenDirectoryObject(
      &hDir, 
      /*STANDARD_RIGHTS_READ |*/ DIRECTORY_QUERY, 
      &oa);

    if(status==STATUS_SUCCESS){ return ret; }

    BOOLEAN rescan = TRUE;
    ULONG      ctx = 0;
    ULONG   retLen = 0;
    do
    {
      status = NtQueryDirectoryObject(hDir, buf, sizeof(buf), TRUE, rescan, &ctx, &retLen);
      rescan = FALSE;
      auto info = (OBJECT_DIRECTORY_INFORMATION*)buf;

      if( lstrcmpW(info->type.Buffer, L"Section")!=0 ){ continue; }
      WCHAR wPrefix[] = L"simdb_";
      size_t pfxSz = sizeof(wPrefix);
      if( strncmp( (char*)info->name.Buffer, (char*)wPrefix, pfxSz)!=0 ){  continue; }

      std::wstring name =  std::wstring( (WCHAR*)info->name.Buffer );
      ret.push_back(name);
    }while(status!=STATUS_NO_MORE_ENTRIES);
    
    return ret;
  }
#else
  // gcc/clang/linux ?
  #include <alloca.h>
  #define STACK_VEC(TYPE, COUNT) lava_vec<TYPE>(_alloca(lava_vec<TYPE>::sizeBytes(COUNT)), COUNT, true);  
#endif

class     CncrLst
{
// Internally this is an array of indices that makes a linked list
// Externally indices can be gotten atomically and given back atomically
// | This is used to get free indices one at a time, and give back in-use indices one at a time
public:
  union Head
  {
    struct { u32 ver; u32 idx; };                      // ver is version, idx is index // todo: change cnt to version
    u64 asInt;
  };
  
  using     u32  =  uint32_t;                               // need to be i32 instead for the ConcurrentStore indices?
  using     u64  =  uint64_t;
  using ListVec  =  lava_vec<u32>;

  const static u32 LIST_END = 0xFFFFFFFF;

private:
  ListVec     m_lv;
  au64*        m_h;

public:
  static u64 sizeBytes(u32 size)
  {
    return ListVec::sizeBytes(size);
  }

  CncrLst(){}
  CncrLst(void* addr, u32 size, bool owner=true) :           // this constructor is for when the memory is owned an needs to be initialized
    m_lv(addr, size, owner)
  {                                                          // separate out initialization and let it be done explicitly in the simdb constructor?
    m_h = (au64*)addr;

    if(owner){
      for(u32 i=0; i<(size-1); ++i) m_lv[i] = i+1;
      m_lv[size-1] = LIST_END;

      ((Head*)m_h)->idx = 0;
      ((Head*)m_h)->ver = 0;
    }
                                          // uses the first 8 bytes that would normally store sizeBytes as the 64 bits of memory for the Head structure
  }

  auto        nxt() -> uint32_t           // moves forward in the list and return the previous index
  {
    /*prevHead,*/
    Head  curHead, nxtHead;

    curHead.asInt  =  m_h->load();        // std::atomic_load(m_h);  // m_h.load();
    do 
    {
      if(curHead.idx==LIST_END) return LIST_END;

      nxtHead.idx  =  m_lv[curHead.idx];
      nxtHead.ver  =  curHead.ver + 1;
    } while( !m_h->compare_exchange_strong(curHead.asInt, nxtHead.asInt) );

    return curHead.idx;
  }
  auto       free(u32 idx) -> uint32_t   // not thread safe yet when reading from the list, but it doesn't matter because you shouldn't be reading while freeing anyway?
  {
    Head curHead;
    Head nxtHead;
    uint32_t    retIdx;

    curHead.asInt = m_h->load();
    do 
    {
      retIdx = m_lv[idx] = curHead.idx;
      nxtHead.idx  =  idx;
      nxtHead.ver  =  curHead.ver + 1;
    } while( !m_h->compare_exchange_strong(curHead.asInt, nxtHead.asInt) );

    return retIdx;
  }
  auto      count() const -> u32
  {
    //return ((HeadUnion*)(&m_h))->cnt;
    //return ((Head*)(&m_h))->ver;
    return ((Head*)m_h)->ver;
  }
  auto        idx() -> u32
  {
    //return ((Head*)(&m_h))->idx;
    return ((Head*)m_h)->idx;
  }            // not thread safe
  auto       list() -> ListVec const* 
  {
    return &m_lv;
  }            // not thread safe
  u32      lnkCnt()                     // not thread safe
  {
    u32    cnt = 0;
    //auto      l = list();
    u32 curIdx = idx();
    while( curIdx != LIST_END ){
      //curIdx = l->at(curIdx).load();
      curIdx = m_lv[curIdx];   //  l->at(curIdx).load();
      ++cnt;
    }
    return cnt;
  }
};
class     CncrStr
{
public:
  union   VerIdx
  {
    //struct { u32 version; u32 idx; }; // declaring the version first and idx second puts the 
    struct { u32 idx; u32 version; }; // declaring the version first and idx second puts the 
    u64 asInt;

    VerIdx(){}
    VerIdx(u32 _idx, u32 _version) : idx(_idx), version(_version) {}
  };
  union   KeyAndReaders
  {
    struct{ u32 isKey : 1; i32 readers : 31; u32 version; };
    u64 asInt;
  };
  union   BlkLst
  {
    struct { KeyAndReaders kr; u32 idx; u32 len, klen, hash; };

    BlkLst() : idx(0), len(0), klen(0), hash(0)
    { 
      kr.isKey    = 0;
      kr.readers  = 0;
      kr.version  = 0;
    }
    BlkLst(bool isKey, i32 readers, u32 _idx, u32 ver, u32 _len, u32 _klen, u32 _hash=0) : 
      idx(_idx),
      hash(_hash)
    {
      kr.isKey    = isKey;
      kr.readers  = readers;
      kr.version  = ver;

      if(isKey){
        len  = _len;
        klen = _klen;
      }else{
        len  = 0;
        klen = 0;
      }
    } 
  };
  struct  BlkCnt { u32 end : 1; u32 cnt : 31; };                                       // this is returned from alloc() and may not be neccesary - it is the number of blocks allocated and if the end was reached

  //using IDX         =  i32;
  using ai32        =  std::atomic<i32>;
  using BlockLists  =  lava_vec<BlkLst>;                                               // only the indices returned from the concurrent list are altered, and only one thread will deal with any single index at a time 

  const static u32 LIST_END = CncrLst::LIST_END;

  static VerIdx      List_End()
  { 
    VerIdx vi; 
    vi.idx     = CncrLst::LIST_END; 
    vi.version = 0; 
    return vi; 
  }
  static bool       IsListEnd(VerIdx vi)
  {
    static const VerIdx empty = List_End();
    return empty.asInt == vi.asInt;
  }

  BlkLst    incReaders(u32 blkIdx, u32 version) const                   // BI is Block Index  increment the readers by one and return the previous kv from the successful swap 
  {

    KeyAndReaders cur, nxt;
    BlkLst* bl      = &s_bls[blkIdx];
    au64* areaders = (au64*)&(bl->kr.asInt);    
    cur.asInt       = areaders->load();
    do{
      if(cur.version!=version || cur.readers<0) return BlkLst(); // make_BlkLst(0,0,0,0,0,0);
      nxt = cur;
      nxt.readers += 1;
    }while( !areaders->compare_exchange_strong(cur.asInt, nxt.asInt) );
    
    return *bl;  // after readers has been incremented this block list entry is not going away. The only thing that would change would be the readers and that doesn't matter to the calling function.
  }
  bool      decReaders(u32 blkIdx, u32 version) const                   // BI is Block Index  increment the readers by one and return the previous kv from the successful swap 
  {
    KeyAndReaders cur, nxt;
    au64* areaders = (au64*)&(s_bls[blkIdx].kr.asInt);    
    cur.asInt = areaders->load();
    do{
      if(cur.version!=version) return false;
      nxt = cur;
      nxt.readers -= 1;
    }while( !areaders->compare_exchange_strong(cur.asInt, nxt.asInt) );
    
    if(cur.readers==0){ doFree(blkIdx); return false; }

    return true;
  }

private:   

  // On the thread's stack
  mutable CncrLst           s_cl;        // flat data structure - pointer to memory 
  mutable BlockLists       s_bls;        // flat data structure - pointer to memory - bl is Block Lists
  void*               s_blksAddr;        // points to the block space in the shared memory
  au64*                s_version;        // pointer to the shared version number

  u32                m_blockSize;
  u32               m_blockCount;
  u64                  m_szBytes;
  //mutable ai32      m_blocksUsed;       // todo: this is a mistake and does no good unless it is in the shared memory

  VerIdx       nxtBlock(u32  blkIdx)  const
  {
    BlkLst bl  = s_bls[blkIdx];
    VerIdx vi;
    vi.idx     = bl.idx;
    vi.version = bl.kr.version;

    prefetch1( (char const* const)blockFreePtr(bl.idx) );

    return vi;
  }
  u32     blockFreeSize()             const { return m_blockSize; }
  u8*      blockFreePtr(u32  blkIdx)  const { return ((u8*)s_blksAddr) + blkIdx*m_blockSize; }
  u8*            blkPtr(u32  blkIdx)  const { return ((u8*)s_blksAddr) + blkIdx*m_blockSize; }
  u32      blocksNeeded(u32     len, u32* out_rem=nullptr)
  {
    u32  freeSz   = blockFreeSize();
    u32  byteRem  = len % freeSz;
    u32  blocks   = len / freeSz + (byteRem? 1 : 0);    // should never be 0 if blocksize is greater than the size of the index type

    if(out_rem) *out_rem = byteRem;

    return blocks;
  }
  void           doFree(u32  blkIdx)  const        // frees a list/chain of blocks
  {
    u32   cur  =             blkIdx;          // cur is the current block index
    u32   nxt  =   s_bls[cur].idx;         //*stPtr(cur);              // nxt is the next block index
    for(; nxt>0; nxt=s_bls[cur].idx)
    { 
      //memset(blkPtr(cur), 0, m_blockSize);    // zero out memory on free, 
      //m_bls[cur].readers = 0;                 // reset the reader count
      
      s_bls[cur].kr.isKey   = false;          // make sure key is false;
      s_bls[cur].kr.readers = 0;              // reset the reader count
      
      s_cl.free(cur);
      //m_blocksUsed.fetch_add(-1);
      cur  =  nxt;
    }
    //memset(blkPtr(cur), 0, m_blockSize);       // 0 out memory on free, 
    //m_bls[cur].readers = 0;                  // reset the reader count
    s_bls[cur].kr.readers = 0;                 // reset the reader count
    s_cl.free(cur);
  }
  u32        writeBlock(u32  blkIdx, void const* const bytes, u32 len=0, u32 ofst=0)      // don't need to increment readers since write should be done before the block is exposed to any other threads
  {
    u32  blkFree  =  blockFreeSize();
    u8*        p  =  blockFreePtr(blkIdx);
    auto     nxt  =  nxtBlock(blkIdx);
    u32   cpyLen  =  len==0? blkFree : len;             // if next is negative, then it will be the length of the bytes in that block
    p      += ofst;
    memcpy(p, bytes, cpyLen);

    return cpyLen;
  }
  u32         readBlock(u32  blkIdx, u32 version, void *const bytes, u32 ofst=0, u32 len=0) const
  {
    BlkLst bl = incReaders(blkIdx, version);      if(bl.kr.version==0) return 0;
      u32   blkFree  =  blockFreeSize();
      u8*         p  =  blockFreePtr(blkIdx);
      u32       nxt  =  bl.idx;
      u32    cpyLen  =  len==0?  blkFree-ofst  :  len;
      //cpyLen        -=  ofst;
      memcpy(bytes, p+ofst, cpyLen);
    decReaders(blkIdx, version);

    return cpyLen;
  }

public:
  /* 
    The order of the shared memory is:
    Version
    CncrLst
    BlockLists
    Blocks
  */
  static u64    BlockListsOfst(){ return sizeof(u64); }
  static u64         CListOfst(u32 blockCount){ return BlockListsOfst() + BlockLists::sizeBytes(blockCount); }      // BlockLists::sizeBytes ends up being sizeof(BlkLst)*blockCount + 2 u64 variables
  static u64          BlksOfst(u32 blockCount){ return CListOfst(blockCount) + CncrLst::sizeBytes(blockCount); }
  static u64         sizeBytes(u32 blockSize, u32 blockCount){ return BlksOfst(blockCount) + blockSize*blockCount; }

  CncrStr(){}
  CncrStr(void* addr, u32 blockSize, u32 blockCount, bool owner=true) :
    m_blockSize(blockSize),
    m_blockCount(blockCount),
    //m_blocksUsed(0),
    s_blksAddr( (u8*)addr + BlksOfst(blockCount) ),
    s_cl(       (u8*)addr + CListOfst(blockCount), blockCount, owner),
    s_bls(      (u8*)addr + BlockListsOfst(),      blockCount, owner),
    s_version(  (au64*)addr ),
    m_szBytes( *((u64*)addr) )
  {
    if(owner){
      for(u32 i=0; i<m_blockCount; ++i){ s_bls[i] = BlkLst(); }
      s_version->store(1);                            // todo: redo this, with 32 bit integers, 0 shouldn't be a special value because it could loop around start at 1, use 0 as a special value - 
    }
    assert(blockSize > sizeof(i32));
  }

  //auto        alloc(u32    size, u32 klen, u32 hash, i32* out_blocks=nullptr) -> VerIdx     // have this output a struct with a 1 bit flag of whether it reached the LIST_END or not    // -todo: doesn't this need to give back the blocks if allocation fails? - it does
  auto        alloc(u32    size, u32 klen, u32 hash, BlkCnt* out_blocks=nullptr) -> VerIdx     // have this output a struct with a 1 bit flag of whether it reached the LIST_END or not    // -todo: doesn't this need to give back the blocks if allocation fails? - it does
  {
    u32 byteRem  =  0;
    u32  blocks  =  blocksNeeded(size, &byteRem);

    u32   st = s_cl.nxt();                                     // stBlk  is starting block
    SECTION(get the starting block index and handle errors)
    {
      if(st==LIST_END){
        if(out_blocks){ *out_blocks = {1, 0} ; } 
        return List_End(); // LIST_END; 
      }
    }

    u32  ver  =  (u32)s_version->fetch_add(1);
    u32  cur  =  st;
    u32  nxt  =  s_cl.nxt();
    //s_bls[st] =  BlkLst(true, 0, nxt, ver, size, klen, hash);
    u32  cnt  =  0;
    SECTION(loop for the number of blocks needed and get new block and link it to the list)
    {
      for(u32 i=0; i<blocks-1; ++i)
      {
        nxt    = s_cl.nxt();
        if(nxt==LIST_END){ free(st, ver); VerIdx empty={LIST_END,0}; return empty; }

        if(i==0) s_bls[cur] =  BlkLst(true,  0, nxt, ver, size, klen);  // make_BlkLst(true,  0, nxt, ver, size, klen);
        else     s_bls[cur] =  BlkLst(false, 0, nxt, ver, 0, 0);        // make_BlkLst(false, 0, nxt, ver, 0, 0);
        cur    =  nxt;
        ++cnt;
        //m_blocksUsed.fetch_add(1);
      }
    }

    SECTION(add the last index into the list, set out_blocks and return the start index with its version)
    {
      //u32 blockRemainder = byteRem? -byteRem : -blockFreeSize();
      //BlkLst  bl =  make_BlkLst(cur==st, 0, blockRemainder, ver, size, klen);

      //u32 blockRemainder = byteRem? byteRem : blockFreeSize();
      //BlkLst bl(cur==st, 0, blockRemainder, ver, size, klen, hash);
      //s_bls[cur] = bl;
      //s_bls[st].kr.isKey = true;

      //if(out_blocks){ *out_blocks = nxt==LIST_END? -((i32)cnt) : (i32)cnt; }     
      if(out_blocks){
        out_blocks->end = nxt==LIST_END;
        out_blocks->cnt = cnt;
      }     
      VerIdx vi(st, ver);
      return vi;
    }
  }
  bool         free(u32  blkIdx, u32 version)        // frees a list/chain of blocks
  {
    return decReaders(blkIdx, version);
  }
  void          put(u32  blkIdx, void const *const kbytes, u32 klen, void const *const vbytes, u32 vlen)  // don't need version because this will only be used after allocating and therefore will only be seen by one thread until it is inserted into the ConcurrentHash
  {
    using namespace std;
    
    u8*         b  =  (u8*)kbytes;
    bool   kjagged  =  (klen % blockFreeSize()) != 0;
    u32    kblocks  =  kjagged? blocksNeeded(klen)-1 : blocksNeeded(klen);
    u32   remklen   =  klen - (kblocks*blockFreeSize());
    
    u32   fillvlen  =  min(vlen, blockFreeSize()-remklen);
    u32   tailvlen  =  vlen-fillvlen;
    bool   vjagged  =  (tailvlen % blockFreeSize()) != 0;
    u32    vblocks  =  vjagged? blocksNeeded(tailvlen)-1 : blocksNeeded(tailvlen);
    u32    remvlen  =  max<u32>(0, tailvlen - (vblocks*blockFreeSize()) ); 

    u32       cur  =  blkIdx;
    for(u32 i=0; i<kblocks; ++i){
      b   +=  writeBlock(cur, b);
      cur  =  nxtBlock(cur).idx;
    }
    if(kjagged){
      writeBlock(cur, b, remklen);
      b    =  (u8*)vbytes;
      b   +=  writeBlock(cur, b, fillvlen, remklen);
      cur  =  nxtBlock(cur).idx;
    }
    for(u32 i=0; i<vblocks; ++i){
      b   +=  writeBlock(cur, b);
      cur  =  nxtBlock(cur).idx;
    }
    if(vjagged && remvlen>0){
      b   +=  writeBlock(cur, b, remvlen);
    }
  }
  u32           get(u32  blkIdx, u32 version, void *const bytes, u32 maxlen) const
  {
    using namespace std;

    if(blkIdx == LIST_END){ return 0; }

    BlkLst bl = incReaders(blkIdx, version);   
    
    u32 vlen = bl.len-bl.klen;
    if(bl.len==0 || vlen>maxlen ) return 0;

    auto   kdiv = div((i64)bl.klen, (i64)blockFreeSize());
    auto  kblks = kdiv.quot;
    u32    krem = (u32)kdiv.rem;
    auto vrdLen = 0;
    u32     len = 0;
    u32   rdLen = 0;
    u8*       b = (u8*)bytes;
    u8*      en = b + maxlen;
    i32     cur = blkIdx;
    VerIdx  nxt;
    for(int i=0; i<kblks; ++i){ 
      nxt = nxtBlock(cur);           if(nxt.version!=version){ goto read_failure; }
      cur = nxt.idx;
    }

    vrdLen =  min<u32>(blockFreeSize()-krem, vlen);
    rdLen  =  (u32)readBlock(cur, version, b, krem, vrdLen);
    b     +=  rdLen;
    len   +=  rdLen;
    nxt    =  nxtBlock(cur);         if(nxt.version!=version){ goto read_failure; }

    while(len<maxlen && !(nxt.idx<0) && nxt.idx!=LIST_END && nxt.version==version)
    {
      vrdLen =  min<u32>(blockFreeSize(), maxlen-len);
      cur    =  nxt.idx;
      rdLen  =  readBlock(cur, version, b, 0, vrdLen);  if(rdLen==0) break;        // rdLen is read length
      b     +=  rdLen;
      len   +=  rdLen;
      nxt    =  nxtBlock(cur);
    }

  read_failure:
    decReaders(blkIdx, version);

    return len;                                           // only one return after the top to make sure readers can be decremented - maybe it should be wrapped in a struct with a destructor
  }
  u32        getKey(u32  blkIdx, u32 version, void *const bytes, u32 maxlen) const
  {
    if(blkIdx == LIST_END){ return 0; }

    BlkLst bl = incReaders(blkIdx, version);   
    
    if(bl.len==0 || (bl.klen)>maxlen ) return 0;

    auto   kdiv = div((i64)bl.klen, (i64)blockFreeSize());
    auto  kblks = kdiv.quot;
    u32    krem = (u32)kdiv.rem;
    u32     len = 0;
    u32   rdLen = 0;
    u8*       b = (u8*)bytes;
    u32     cur = blkIdx;
    VerIdx  nxt = { blkIdx, version };

    if(krem>0) --kblks;
    int i=0;
    while( i<kblks && !(nxt.idx<0) && nxt.idx!=LIST_END && nxt.version==version)
    {
      cur    =  nxt.idx;
      rdLen  =  readBlock(cur, version, b);          if(rdLen==0) goto read_failure;        // rdLen is read length
      b     +=  rdLen;
      len   +=  rdLen;
      nxt    =  nxtBlock(cur);
    }
    rdLen  =  readBlock(cur, version, b, 0, krem);
    b     +=  rdLen;
    len   +=  rdLen;

  read_failure:
    decReaders(blkIdx, version);

    return len;                                           // only one return after the top to make sure readers can be decremented - maybe it should be wrapped in a struct with a destructor
    
    //for(int i=0; i<kblks; ++i){ 
    //  nxt    =  nxtBlock(cur);                 if(nxt.version!=version){ goto read_failure; }
    //  rdLen  =  readBlock(cur, version, b);
    //  b     +=  rdLen;
    //  len   +=  rdLen;
    //  cur    =  nxt.idx;
    //}
    //
    //rdLen  =  readBlock(cur, version, b, krem);
    //b     +=  rdLen;
    //len   +=  rdLen;
    //nxt    =  nxtBlock(cur);                  if(nxt.version!=version){ goto read_failure; }
    //
    ////while(true)
    //while( !(nxt.idx<0) && nxt.idx!=LIST_END && nxt.version==version)
    //{
    //  cur    =  nxt.idx;
    //  rdLen  =  readBlock(cur, version, b);  if(rdLen==0) break;        // rdLen is read length
    //  b     +=  rdLen;
    //  len   +=  rdLen;
    //  nxt    =  nxtBlock(cur);
    //  //if(nxt<0 || nxt==LIST_END) break;
    //}
  }
  Match   memcmpBlk(u32  blkIdx, u32 version, void const *const buf1, void const *const buf2, u32 len) const  // todo: eventually take out the inc and dec readers and only do them when dealing with the whole chain of blocks
  {
    if(incReaders(blkIdx, version).len==0) return MATCH_REMOVED;
      auto ret = memcmp(buf1, buf2, len);
    decReaders(blkIdx, version);

    if(ret==0) return MATCH_TRUE;

    return MATCH_FALSE;
  }
  Match     compare(u32  blkIdx, u32 version, void const *const buf, u32 len, u32 hash) const
  {
    using namespace std;
    
    if(s_bls[blkIdx].hash!=hash) return MATCH_FALSE;  // vast majority of calls should end here

    u32   curidx  =  blkIdx;
    VerIdx   nxt  =  nxtBlock(curidx);                            if(nxt.version!=version) return MATCH_FALSE;
    u32    blksz  =  (u32)blockFreeSize();  // todo: change this to u32
    u8*   curbuf  =  (u8*)buf;
    auto    klen  =  s_bls[blkIdx].klen;                          if(klen!=len) return MATCH_FALSE;
    auto  curlen  =  len;
    while(true)
    {
      auto p = blockFreePtr(curidx);
      if(blksz > curlen){
        return memcmpBlk(curidx, version, curbuf, p, curlen);
      }else{
        Match cmp = memcmpBlk(curidx, version, curbuf, p, blksz); if(cmp!=MATCH_TRUE){ return cmp; }
      }

      curbuf  +=  blksz;
      curlen  -=  blksz;
      curidx   =  nxt.idx;
      nxt      =  nxtBlock(curidx);                               if(nxt.version!=version) return MATCH_FALSE;
    }
  }
  u32           len(u32  blkIdx, u32 version, u32* out_vlen=nullptr) const
  {
    BlkLst bl = s_bls[blkIdx];
    if(version==bl.kr.version && bl.len>0){
      if(out_vlen) *out_vlen = bl.len - bl.klen;
      return bl.len;
    }else 
      return 0;
  }
  auto         list()      const -> CncrLst const&
  {
    return s_cl;
  }
  auto         data()      const -> const void*
  {
    return (void*)s_blksAddr;
  }
  u32    blockCount()      const
  {
    return m_blockCount; // m_cl.sizeBytes();
  }
  auto       blkLst(u32 i) const -> BlkLst
  {
    return s_bls[i];
  }

  friend class CncrHsh;
};
class     CncrHsh
{
public:
  using  VerIdx   = CncrStr::VerIdx;
  using  BlkLst   = CncrStr::BlkLst;

  struct VerIpd { u32 version, ipd; };                       // ipd is Ideal Position Distance

  static const i8   RM_OWNER         =     -1;               // keep this at 0 if INIT_READERS is changed to 1, then take out remove flag
  static const u8   LAST_READER      =      0;               // keep this at 0 if INIT_READERS is changed to 1, then take out remove flag
  static const u8   INIT_READERS     =      0;               // eventually make this 1 again? - to catch when readers has dropped to 0
  static const u8   FREE_READY       =      0;
  static const u8   MAX_READERS      =   0xFF;
  static const u32  KEY_MAX          =   0xFFFFFFFF; 
  static const u32  EMPTY_KEY        =   KEY_MAX;            // first 21 bits set 
  static const u32  DELETED_KEY      =   KEY_MAX - 1;        // 0xFFFFFFFE;       // 1 less than the EMPTY_KEY
  static const u32  EMPTY_HASH_IDX   =   0xFFFFFFFF;         // 32 bits set - hash indices are different from block indices 
  static const u32  LIST_END         =   CncrStr::LIST_END;

  static u32        nextPowerOf2(u32  v)
  {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;

    return v;
  }
  static u64           sizeBytes(u32 size)
  {
    //return lava_vec<VerIdx>::sizeBytes( nextPowerOf2(size) );
    return lava_vec<VerIdx>::sizeBytes(size);
  }
  static bool  DefaultKeyCompare(u32 a, u32 b)
  {
    return a == b;
  }
  static u32           HashBytes(const void *const buf, u32 len)
  {
    u64 hsh = fnv_64a_buf(buf, len);

    return (u32)( (hsh>>32) ^ ((u32)hsh));
  }
  static VerIdx         empty_kv(){ return VerIdx(EMPTY_KEY,0); }
  //{
  //  VerIdx empty;
  //  empty.idx      =  EMPTY_KEY;
  //  empty.version  =  0;
  //  return empty;
  //
  //  //empty.val      =  EMPTY_KEY;
  //  //empty.readers  =  0;
  //}
  static VerIdx       deleted_kv()
  {
    VerIdx empty;
    empty.idx      =  DELETED_KEY;
    empty.version  =  0;
    return empty;
  }
  static i64              vi_i64(VerIdx vi)
  {
    u64 iVi = vi.asInt;
    return *((i64*)(&iVi));                                              // interpret the u64 bits directly as a signed 64 bit integer instead    
  }
  static bool            IsEmpty(VerIdx kv)
  {
    static VerIdx emptykv = empty_kv();
    return emptykv.asInt == kv.asInt;
  }
  static u32                hi32(u64 n){ return (n>>32); }
  static u32                lo32(u64 n){ return (n<<32)>>32; }
  static u64               swp32(u64 n){ 
   return (((u64)lo32(n))<<32)  |  ((u64)hi32(n)); }
  static u64             incHi32(u64 n, u32 i){ return ((u64)hi32(n)+i)<<32 | lo32(n); }
  static u64             incLo32(u64 n, u32 i){ return ((u64)hi32(n))<<32 | (lo32(n)+i); }
  static u64          shftToHi64(u32 n){ return ((u64)n)<<32; }
  static u64              make64(u32 hi, u32 lo){ return (((u64)hi)<<32) | ((u64)lo); }

private:
  using Au32     =  std::atomic<u32>;
  using Au64     =  std::atomic<u64>;
  using VerIdxs  =  lava_vec<VerIdx>;
  using Mut      =  std::mutex;
  using UnqLock  =  std::unique_lock<Mut>;

          u32       m_sz;
  mutable VerIdxs   m_vis;           // m_vis is key value(s) - needs to be changed to versioned indices, m_vis
          CncrStr*  m_csp;           // csp is concurrent store pointer

  u32            nxtIdx(u32 i)                 const { return (i+1)%m_sz; }
  u32           prevIdx(u32 i)                 const { return std::min(i-1, m_sz-1); } // clamp to m_sz-1 for the case that hash==0, which will result in an unsigned integer wrap
  VerIdx        load_vi(u32 i)                 const
  {
    using namespace std;
    
    au64* avi = (au64*)(m_vis.data()+i);                            // avi is atomic versioned index
    u64   cur = swp32(avi->load());                                 // need because of endianess? // atomic_load<u64>( (au64*)(m_vis.data()+i) );              // Load the key that was there.

    //VerIdx ret;
    //if(i%2==1) ret.asInt = swp32(cur);
    //else       ret.asInt = cur;

    if(i%2==1) return VerIdx(lo32(cur), hi32(cur));
    else       return VerIdx(hi32(cur), lo32(cur));
  }
  VerIdx       store_vi(u32 i, u64 vi)         const
  {
    using namespace std;
        
    //u64 asInt = keyval.asInt;
    bool odd = i%2 == 1;
    VerIdx strVi;
    if(odd) strVi = VerIdx(lo32(vi), hi32(vi));            // the odd numbers need to be swapped so that their indices are on the outer border of 128 bit alignment - the indices need to be on the border of the 128 bit boundary so they can be swapped with an unaligned 64 bit atomic operation
    else    strVi = VerIdx(hi32(vi), lo32(vi));

    u64 prev = atomic_exchange<u64>( (au64*)(&m_vis[i]), *((u64*)(&strVi)) );

    if(odd) return VerIdx(lo32(prev), hi32(prev));
    else    return VerIdx(hi32(prev), lo32(prev));
  }
  //VerIdx       store_vi(u32 i, u64 vi)         const
  //{
  //  using namespace std;
  //      
  //  //u64 asInt = keyval.asInt;
  //  bool odd = i%2 == 1;
  //  if(odd) vi = swp32(vi);            // the odd numbers need to be swapped so that their indices are on the outer border of 128 bit alignment - the indices need to be on the border of the 128 bit boundary so they can be swapped with an unaligned 64 bit atomic operation
  //
  //  u64 prev = atomic_exchange<u64>( (au64*)(&m_vis[i]), vi);
  //
  //  VerIdx ret;
  //  if(odd) ret.asInt = swp32(prev);
  //  else    ret.asInt = prev;
  //
  //  return ret;
  //}
  bool         cmpex_vi(u32 i, VerIdx* expected, VerIdx desired) const
  {
    using namespace std;

    u64    desi = i%2? swp32(desired.asInt) : desired.asInt;                                // desi is desired int
    au64*  addr = (au64*)(m_vis.data()+i);
    return atomic_compare_exchange_strong(addr, (u64*)expected, desi);                      // The entry was free. Now let's try to take it using a CAS. 
  }
  void           doFree(u32 i)                 const
  {
    store_vi(i, empty_kv().asInt);
  }
  VerIpd            ipd(u32 i, VerIdx vi)      const  // ipd is Ideal Position Distance - it is the distance a CncrHsh index value is from the position that it gets hashed to 
  {
    BlkLst bl = m_csp->blkLst(vi.idx);
    u32    ip = bl.hash % m_sz;     // ip is Ideal Position
    //u32   ipd = vi.idx>ip?  vi.idx-ip  :  m_csp->blockCount() - ip + vi.idx;  // todo: change vi.idx to u32 so that there aren't sign mismatch warnings
    u32   ipd = i>ip?  i-ip  :  m_csp->blockCount() - ip + i;  // todo: change vi.idx to u32 so that there aren't sign mismatch warnings
    return {bl.kr.version, ipd};
  }
  bool          delDupe(u32 i)                 const                                 // delete duplicate indices - l is left index, r is right index - will do something different depending on if the two slots are within 128 bit alignment or not
  {
    if(i%2==0)
    {                                                                               // both indices are within a 128 bit boundary, so the 128 bit atomic can (and must) be used
      i64 rgtDel, lftDel;  _u128 viDbl;
      _u128* viDblAddr = (_u128*)&m_vis[i];                                         // find 128 bit offset address
      viDbl            = *viDblAddr;                                                // todo: should this use a 128 bit atomic load? if it isn't the same, the atomic compare exchange will load it atomically
      do{
        u32 l = hi32(viDbl.hi);
        u32 r = lo32(viDbl.lo);
        if(l==DELETED_KEY && r==EMPTY_KEY){
          lftDel = vi_i64( empty_kv() );
          rgtDel = *((i64*)(&viDbl.lo));
        }else if(l!=r || l>=DELETED_KEY){                                           // check if both the indices are the same and if they are, that they aren't both deleted or both empty 
          return false;                     
        }else{
          lftDel = *((i64*)(&viDbl.hi));                                            // if both the indices are the same, make a new right side VerIdx with the idx set to DELETED_KEY
          rgtDel = vi_i64( deleted_kv() );                                          // interpret the u64 bits directly as a signed 64 bit integer instead
        }
      }while( !compex128( (i64*)viDblAddr, lftDel, rgtDel, (i64*)&viDbl) );         // then compare and swap for a version with the new right side VerIdx // todo: does this need to be in a loop that only breaks when the two indices are not the same?
    }else
    {
      au64* idxDblAddr; u64 idxDbl, desired;
      u32* leftAddr = ((u32*)(&m_vis[i]))+1;                                        // if the two VerIdxs are not in a 128 bit boundary, then use a 64 bit compare and swap to set the right side index to DELETED_KEY
      idxDblAddr    = (au64*)leftAddr;                                              // increment the address by 4 bytes so that it lines up with the start of the two indices, then cast it to an atomic 64 bit unsigned integer for the compare and switch
      idxDbl        = idxDblAddr->load();
      do{
        u32  l = hi32(idxDbl);
        u32  r = lo32(idxDbl);
        if(l==DELETED_KEY && r==EMPTY_KEY){                                         // change the deleted key to empty if it is to the left of an empty slot and therefore at the end of a span
          desired = make64(EMPTY_KEY, EMPTY_KEY);
        }else if(l!=r || l>=DELETED_KEY){
          return false; 
        }else{                                                                      // if the indices are the same then do the compare and swap
          desired = make64(l, DELETED_KEY);                                         // make the new 64 bit integer with the right index set to DELETED_KEY
        }
      }while( !idxDblAddr->compare_exchange_strong(idxDbl, desired) );              // looping here would essentially mean that the indices change but are still identical to each other
    }

    return true;
  }
  bool    cleanDeletion(u32 i, u8 depth=0)     const
  {
    VerIdx curVi, nxtVi; VerIpd nxtVp; u32 nxtI;

    clean_loop: while( (nxtVi=load_vi(nxtI=nxtIdx(i))).idx <= DELETED_KEY )           // dupe_nxt stands for duplicate next, since we are duplicating the next VerIdx into the current (deleted) VerIdx slot
    {
      curVi = load_vi(i);
      //if(curVi.idx >= DELETED_KEY){ return false; }
      if(curVi.idx == EMPTY_KEY){ return false; }

      ////nxtVp = ipd(nxtIdx(i), nxtVi);
      //nxtVp = ipd(nxtI, nxtVi);
      //if(nxtVp.version!=nxtVi.version){ continue; /*goto clean_loop;*/ }             // the versions don't match, so start over on the same index and skip the compare exchange 
      //else if(nxtVp.ipd==0){ return true; }                                          // should this be converted to an empty slot since it is the end of a span? // next slot's versions match and its VerIdx is in its ideal position, so we are done 
      //else if( cmpex_vi(i, &curVi, nxtVi) ){ 
      //  delDupe(i);
      //  i = nxtIdx(i);
      //}

      //if(nxtVi.idx==EMPTY_KEY){ 
      //  if(delDupe(i)){ return true; }
      //  
      //  i = nxtIdx(i); continue;
      //}

      nxtVp = ipd(nxtI, nxtVi);
      if(nxtVp.version!=nxtVi.version){ continue; /*goto clean_loop;*/ }             // the versions don't match, so start over on the same index and skip the compare exchange 
      else if(nxtVp.ipd==0){ return true; }                                          // should this be converted to an empty slot since it is the end of a span? // next slot's versions match and its VerIdx is in its ideal position, so we are done 
      else if( cmpex_vi(i, &curVi, nxtVi) ){ 
        delDupe(i);
        i = nxtIdx(i);
      }

    }

    if(nxtVi.idx == DELETED_KEY){                                                    // if the next index is deleted, try to clean the next index, then come back and try to delete this one again
      if(depth<1){ cleanDeletion(nxtIdx(i), depth+1); }                              // could this recurse to the depth of the number of blocks?
      //i = nxtIdx(i);                                                               // this could mean the current slot has a deleted key and isn't cleanup by this function
      goto clean_loop;
    }else if(nxtVi.idx==EMPTY_KEY){
      delDupe(i);    
    }

    return true;
  }

  template<class MATCH_FUNC> 
  auto       checkMatch(u32 version, u32 key, MATCH_FUNC match) const -> Match //  decltype(match(empty_kv()))
  {
    //incReaders(i);  // todo: have incReaders return a VerIdx?
      Match ret = match(key, version);
    //decReaders(i);
    
    return ret;
  }

  template<class MATCH_FUNC, class FUNC> 
  bool       runIfMatch(u32 i, u32 version, u32 key, MATCH_FUNC match, FUNC f) const // const -> bool
  {
    //VerIdx kv = incReaders(i);    
      Match      m = match(key, version);
      bool matched = false;                                       // not inside a scope
      if(m==MATCH_TRUE){ matched=true; f(load_vi(i)); }          
    //decReaders(i);
    
    return matched;
  }

public:
  CncrHsh(){}
  CncrHsh(u32 size, CncrStr* cs)
  {
    init(size, cs);
  }
  CncrHsh(void* addr, u32 size, CncrStr* cs, bool owner=true) :
    m_sz(nextPowerOf2(size)),
    m_vis(addr, m_sz),
    m_csp(cs)
  {
    if(owner){
      init(size, cs);
      //VerIdx defKv = empty_kv();
      //for(u64 i=0; i<m_vis.size(); ++i)
      //  m_vis[i] = defKv;
    }
  }
  CncrHsh(CncrHsh const& lval) = delete;
  CncrHsh(CncrHsh&&      rval) = delete;
  
  CncrHsh& operator=(CncrHsh const& lval) = delete;
  CncrHsh& operator=(CncrHsh&&      rval) = delete;

  VerIdx  operator[](u32 idx) const
  {
    return m_vis[idx];
  }

  //template<class MATCH_FUNC> 
  //VerIdx   putHashed(u32 hash, VerIdx vi, MATCH_FUNC match)     const
  //{
  //  using namespace std;
  //  static const VerIdx empty   = empty_kv();
  //  static const VerIdx deleted = deleted_kv();
  //
  //  VerIdx desired   =  empty;
  //  desired.idx      =  vi.idx;
  //  desired.version  =  vi.version;
  //  u32           i  =  hash % m_sz;
  //  u32          en  =  prevIdx(i);   //min(hash%m_sz - 1, m_sz-1); // clamp to m_sz-1 for the case that hash==0, which will result in an unsigned integer wrap?   // % m_sz;   //>0? hash-1  :  m_sz
  //  for(;; i=nxtIdx(i) ) //++i)
  //  {
  //    VerIdx vi = load_vi(i);
  //    if(vi.idx>=DELETED_KEY)                                                               // it is either deleted or empty
  //    {          
  //      bool    success  =  cmpex_vi(i, m_vis.data()+i, desired);
  //      if(success) return vi;                                                //expected;  // continue; // WRONG!? // Another thread just stole it from underneath us.
  //      else{ i=prevIdx(i); continue; }  // retry the same loop again
  //    }                                                                                     // Either we just added the key, or another thread did.
  //    
  //    if( checkMatch(vi.version, vi.idx, match)!=MATCH_TRUE ) continue;
  //    bool success = cmpex_vi(i, m_vis.data()+i, desired);
  //    if(success) return vi;
  //    else{ i=prevIdx(i); continue; }                                            // todo: this doesn't do anything because it doesn't assign to i !! - come back and look this over
  //
  //    if(i==en) break;
  //  }
  //
  //  return empty;  // should never be reached
  //}

  VerIdx   putHashed(u32 hash, VerIdx lstVi, const void *const key, u32 klen)     const
  {
    using namespace std;
    static const VerIdx empty   = empty_kv();
    static const VerIdx deleted = deleted_kv();

    VerIdx desired   =  empty;
    desired.idx      =  lstVi.idx;
    desired.version  =  lstVi.version;
    u32           i  =  hash % m_sz;
    u32          en  =  prevIdx(i);
    for(;; i=nxtIdx(i) )
    {
      VerIdx vi = load_vi(i);
      if(vi.idx>=DELETED_KEY)                                                               // it is either deleted or empty
      {          
        bool    success  =  cmpex_vi(i, m_vis.data()+i, desired);
        if(success) return vi;
        else{ i=prevIdx(i); continue; }                                                     // retry the same loop again if a good slot was found but it was changed by another thread between the load and the compare-exchange
      }                                                                                     // Either we just added the key, or another thread did.
      
      //if( checkMatch(vi.version, vi.idx, match)!=MATCH_TRUE ){ continue; }
      if(m_csp->compare(vi.idx,vi.version,key,klen,hash)!=MATCH_TRUE ){ continue; }

      bool success = cmpex_vi(i, m_vis.data()+i, desired);
      if(success) return vi;
      else{ i=prevIdx(i); continue; }

      if(i==en) break;
    }

    return empty;  // should never be reached
  }

  template<class MATCH_FUNC, class FUNC> 
  bool      runMatch(u32 hash, MATCH_FUNC match, FUNC f)        const // -> decltype( f(VerIdx()) )
  {
    using namespace std;
    
    u32  i = hash % m_sz;
    u32 en = prevIdx(i);     // min(hash%m_sz - 1, m_sz-1); // clamp to m_sz-1 for the case that hash==0, which will result in an unsigned integer wrap?   // % m_sz;   //>0? hash-1  :  m_sz
    //for(;; ++i)
    for(;; i=nxtIdx(i) )
    {
      //i %= m_sz;
      VerIdx vi = load_vi(i);
      if(vi.idx == EMPTY_KEY){ return false;  }                                             // only EMPTY_KEY is the short circuit, since DELETED_KEY means you are still within a span and need to keep searching
      else if(vi.idx == DELETED_KEY){ continue; }
      else if( runIfMatch(i, vi.version, vi.idx, match, f) ){ return true; }
      else if(i==en){ return false; }
    }
  }
  template<class FUNC> 
  auto       runRead(u32  idx, u32 version, FUNC f)             const -> decltype( f(VerIdx()) )    // decltype( (f(empty_kv())) )
  {
    //VerIdx kv = incReaders(idx);
    //auto ret = f(vi);
    //decReaders(idx);

    auto  vi = load_vi(idx);        if(vi.version!=version) return false;
    return f(vi);
  }

  VerIdx   delHashed(const void *const key, u32 klen, u32 hash) const
  {  
    using namespace std;
    static const VerIdx   empty = empty_kv();
    static const VerIdx deleted = deleted_kv();

    u32  i = hash % m_sz;
    u32 en = prevIdx(i); 
    for(;; i=nxtIdx(i) )
    {
      VerIdx vi = load_vi(i);

      if(vi.idx==EMPTY_KEY){   return empty;   }
      if(vi.idx==DELETED_KEY){ return deleted; }

      Match m = m_csp->compare(vi.idx, vi.version, key, klen, hash);
      if(m==MATCH_TRUE){
        bool success = cmpex_vi(i, &vi, deleted);
        if(success){
          cleanDeletion(i);
          return vi;
        }else{ i=prevIdx(i); continue; }

        return vi;
      }

      if(m==MATCH_REMOVED || i==en){ return empty; }
    }

    return empty; 
  }

  bool          init(u32   sz, CncrStr* cs)
  {
    using namespace std;
    static const u64 iempty    =  empty_kv().asInt;
    static const u64 swpempty  =  swp32(iempty);

    u32 hi = hi32(iempty);
    u32 lo = lo32(iempty);
    
    m_csp   =  cs;
    m_sz    =  sz;
    new (&m_vis) lava_vec<VerIdx>(m_sz);                   // placement new because the copy constructor and assignment operator are deleted.  msvc doesn't care, but clang does
    
    //u64 ver0, ver1;
    //ver0         =  empty_kv().asInt;
    //ver1         =  swp32(empty_kv().asInt);
    //ver1.version  =  1;
    
    //for(u32 i=0; i<sz; i+=2) store_vi(i, iempty);            // evens 
    //for(u32 i=1; i<sz; i+=2) store_vi(i, iempty);            // odds

    //for(u32 i=0; i<sz; i+=2) *((u64*)(&m_vis[i])) = iempty;          // evens 
    //for(u32 i=1; i<sz; i+=2) *((u64*)(&m_vis[i])) = swpempty;        // odds

    for(u32 i=0; i<sz; i+=2) m_vis[i] = VerIdx(EMPTY_KEY,0);         // evens 
    for(u32 i=1; i<sz; i+=2) m_vis[i] = VerIdx(0,EMPTY_KEY);         // odds
    
    return true;
  }
  VerIdx          at(u32  idx)                  const
  {
    return load_vi(idx);
  }
  u32            nxt(u32  stIdx)                const
  {
    auto idx = stIdx;
    VerIdx empty = empty_kv();
    do{
      VerIdx kv = load_vi(idx);
      if(kv.idx != empty.idx) break;
      idx = (idx+1) % m_sz;                                             // don't increment idx above since break comes before it here

      if(idx==stIdx) return empty.idx;
    }while(true);

    return  idx;

    /* && kv.readers>=0 */
  }
  u32           size()                          const
  {
    return m_sz;
  }
  auto          data()                          const -> void* { return m_vis.data(); }
  u64      sizeBytes()                          const
  {
    return m_vis.sizeBytes();
  }
  i64        swapNxt(u32 idx)                   const
  {
    i64 retries = -1;
    if(idx%2==0)
    {                                                                 // if idx is even just use 128 bit atomic straight    
      u128*  idxAddr  =  (u128*)( ((u64*)m_vis.addr())+idx );
      u128   dblvi;                                                   // dblvi is double Version Index - it is used to point to two VerIdx structs at the same time 
      u128   swpvi;                                                   // swpvi is swapped version index - the two indices swapped - this is the desired value 
      do{           
        ++retries;                                                    // this will need to swap the side of VerIdx too
        dblvi = *idxAddr;                   
        swpvi = { swp32(idxAddr->lo), swp32(idxAddr->hi) };           // not needed? can use the values directly?
        //swpvi.hi = incLo32(swpvi.hi, 2);                              // swpvi.hi is the left VerIdx, actually ordered as IdxVer, so the lo 32 bits of that are the version number
        //swpvi.lo = incHi32(swpvi.lo, 2);                              // swpvi.lo is the right VerIdx, ordered as VerIdx since the versions are in the middle of the 128 bit alignments and the indices are on the outside
      }while( compex128( (i64*)(idxAddr), swpvi.hi, swpvi.lo, (i64*)(&dblvi) )==1 );
    }
    else                                                              // must be on an odd number, and so will need to use a 64 bit atomic to swap the indices in the middle
    {
      au64* idxAddr = (au64*)( ((u32*)m_vis.addr())+(idx*2+1) );      // offsets using u32, so idx needs to be double, then one more to point to the two indices that are on either side of the 128 bit atomic boundary    
      u64       cur = idxAddr->load();
      u64      swpd;
      do{
        ++retries;
        swpd = swp32(cur);
      }while( !idxAddr->compare_exchange_strong(cur, swpd) );           // compare and swap the hi and lo 32 bits
    }

    return retries;
  }
  i64            len(const void *const key, u32 klen, u32* out_vlen=nullptr, u32* out_version=nullptr) const
  {
    if(klen<1) return 0;

    u32       hash = HashBytes(key, klen);
    CncrStr*   csp = m_csp;
    auto matchFunc = [csp, key, klen, hash](u32 blkidx, u32 ver){
      return csp->compare(blkidx,ver,key,klen,hash);
    };

    //m_csp->compare(blkIdx, version, buf, len, hash);
    
    u32 len=0; u32 ver=0;
    auto runFunc = [csp, &len, &ver, out_vlen](VerIdx kv){
      len = IsEmpty(kv)?  0ull  :  csp->len(kv.idx, kv.version, out_vlen);
      ver = kv.version;
    };

    if(out_version){ *out_version = ver; }
    if( !runMatch(hash, matchFunc, runFunc) ) return 0;
    if(out_version){ *out_version = ver; }

    return len;
  }
  bool           get(const void *const key, u32 klen, void *const   out_val, u32 vlen) const
  {
    if(klen<1) return 0;

    //auto hash = CncrHsh::HashBytes(key, klen);
    ////auto  ths = this;
    //auto matchFunc = [ths, key, klen, hash](u32 blkidx, u32 ver){
    //  return CompareBlock(ths,blkidx,ver,key,klen,hash);
    //};

    u32       hash = HashBytes(key, klen);
    CncrStr*   csp = m_csp;
    auto matchFunc = [csp, key, klen, hash](u32 blkidx, u32 ver){
      return csp->compare(blkidx,ver,key,klen,hash);
    };
    
    u32  out_klen = 0;
    auto  runFunc = [csp, &out_klen, out_val, vlen](VerIdx kv){
      return csp->get(kv.idx, kv.version, out_val, vlen);
    };

    return runMatch(hash, matchFunc, runFunc);
  }
  i32            put(const void *const key, u32 klen, const void *const val, u32 vlen)
  {
    assert(klen>0);

    u32      hash = CncrHsh::HashBytes(key, klen);
        
    VerIdx lstVi = m_csp->alloc(klen+vlen, klen, hash);                       // lstVi is block list versioned index
    if(lstVi.idx==LIST_END){ return EMPTY_KEY; }

    m_csp->put(lstVi.idx, key, klen, val, vlen);

    VerIdx vi = putHashed(hash, lstVi, key, klen);
    if(vi.idx<DELETED_KEY){ m_csp->free(vi.idx, vi.version); }                          // putHashed returns the entry that was there before, which is the entry that was replaced. If it wasn't empty, we free it here. 

    return lstVi.idx;

    //CncrStr*  csp = m_csp;                                                            // this silly song and dance is because the this pointer can't be passed to a lambda
    //VerIdx     kv = putHashed(hash, vi,                                               // this returns the previous VerIdx at the position
    //  [csp, key, klen, hash](u32 blkidx, u32 ver){
    //    return csp->compare(blkidx,ver,key,klen,hash);
    //  });
  }
  bool           del(const void *const key, u32 klen)
  {
    CncrStr*  csp = m_csp;
    auto     hash = CncrHsh::HashBytes(key, klen);
    VerIdx     vi = delHashed(key, klen, hash);
    bool   doFree = vi.idx<DELETED_KEY;
    if(doFree){ m_csp->free(vi.idx, vi.version); }

    return doFree;
  }

};
struct  SharedMem       // in a halfway state right now - will need to use arbitrary memory and have other OS implementations for shared memory eventually
{
  static const int alignment = 0;
  
  #ifdef _WIN32
    void*      fileHndl;
  #elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__FreeBSD__) // || defined(__linux__) ?    // osx, linux and freebsd
    int        fileHndl;
  #endif

  void*       hndlPtr;
  void*           ptr;
  u64           size;
  bool          owner;

  static  bool file_exists(char const* filename)
  {
    if(FILE* file = fopen(filename, "r")){
      fclose(file);
      return true;
    }
    return false;
  }

public:
  static void        FreeAnon(SharedMem& sm)
  {
    #ifdef _WIN32
      if(sm.hndlPtr){
        UnmapViewOfFile(sm.hndlPtr);
      }
      if(sm.fileHndl){
        CloseHandle(sm.fileHndl);
      }
    #elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__FreeBSD__) // || defined(__linux__) ?    // osx, linux and freebsd
      if(sm.hndlPtr){
        munmap(sm.hndlPtr, sm.size);  // todo: size here needs to be the total size, and errors need to be checked
      }
      if(sm.fileHndl){
        close(sm.fileHndl); // todo: get close to work
        // todo: deal with errors here as well?
      }
    #endif

    sm.clear();
  }
  static SharedMem  AllocAnon(const char* name, u64 size)
  {
    using namespace std;
    
    SharedMem sm;
    sm.owner = false;
    sm.size  = alignment==0? size  :  alignment-(size%alignment);

    #ifdef _WIN32      // windows
      //char path[512] = "Global\\simdb_";
      char path[512] = "simdb_";
    //#elif defined(__APPLE__) || defined(__FreeBSD__) // || defined(__linux__) ?    // osx, linux and freebsd
    #elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__FreeBSD__) || defined(__linux__)  // osx, linux and freebsd
      char path[512] = "/tmp/simdb_15_";
      //char path[512] = "simdb_15_";
    #endif

    // todo: need to check that name and path are less than sizeof(path) here
    u64 len = strlen(path) + strlen(name);
    if(len > sizeof(path)-1){ /* todo: handle errors here */ }
    else{ strcat(path, name); }

    #ifdef _WIN32      // windows
      sm.fileHndl = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, path);
      if(sm.fileHndl==NULL)
      {
        sm.fileHndl = CreateFileMapping(
          INVALID_HANDLE_VALUE,
          NULL,
          PAGE_READWRITE,
          0,
          (DWORD)size,
          path);
        if(sm.fileHndl!=NULL) sm.owner=true;
      }
    
      if(sm.fileHndl==NULL){return move(sm);}

      sm.hndlPtr = MapViewOfFile(sm.fileHndl,   // handle to map object
        FILE_MAP_READ | FILE_MAP_WRITE, // FILE_MAP_ALL_ACCESS,   // read/write permission
        0,
        0,
        0);
      if(sm.hndlPtr==nullptr){ CloseHandle(sm.fileHndl); sm.clear(); return move(sm); }
      // END windows
    //#elif defined(__APPLE__) || defined(__FreeBSD__) // || defined(__linux__) ?    // osx, linux and freebsd
    #elif defined(__APPLE__) || defined(__MACH__) || defined(__unix__) || defined(__FreeBSD__) || defined(__linux__)  // osx, linux and freebsd
      //sm.fileHndl = open(path, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH ); // O_CREAT | O_SHLOCK ); // | O_NONBLOCK );
      sm.owner   = true; // todo: have to figure out how to detect which process is the owner

      FILE* fp = fopen(path,"rw");
      if(fp){
        fclose(fp);
        sm.fileHndl = open(path, O_RDWR);
        sm.owner = false;
      }else{
        sm.fileHndl = open(path, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR |S_IRGRP|S_IWGRP | S_IROTH|S_IWOTH ); // O_CREAT | O_SHLOCK ); // | O_NONBLOCK );
        if(sm.fileHndl == -1){
          printf("open failed, file handle was -1 \nFile name: %s \nError number: %d \n\n", path, errno); 
          fflush(stdout);
        }
        else{
          //flock(sm.fileHndl, LOCK_EX);   // exclusive lock  // LOCK_NB
        }
      }

      if(sm.owner){  // todo: still need more concrete race protection
        //fstore_t store = {F_ALLOCATECONTIG, F_PEOFPOSMODE, 0, (off_t)size};

        //struct flock lck = {0,0,0};
        fcntl(sm.fileHndl, F_GETLK, &flock);

        flock(sm.fileHndl, LOCK_EX);   // exclusive lock  // LOCK_NB
        fcntl(sm.fileHndl, F_PREALLOCATE); //  todo: try F_ALLOCATECONTIG at some point
        ftruncate(sm.fileHndl, size);   // todo: don't truncate if not the owner, and don't pre-allocate either ?
        flock(sm.fileHndl, LOCK_EX);
        // get the error number and handle the error
      }
      //sm.hndlPtr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, sm.fileHndl, 0);

      //auto zeromem = malloc(size);
      //memset(zeromem, 0, size);
      //write(sm.fileHndl, zeromem, size);
      //free(zeromem);
      sm.hndlPtr = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_SHARED , sm.fileHndl, 0); // MAP_PREFAULT_READ  | MAP_NOSYNC
      close(sm.fileHndl);
      sm.fileHndl = 0;
      // memset(sm.hndlPtr, 0, size);
 
      if(sm.hndlPtr==MAP_FAILED){
        printf("mmap failed\nError number: %d \n\n", errno);
        fflush(stdout);
        /*todo: handle this error*/ 
      }
    #endif       
  
    u64      addr = (u64)(sm.hndlPtr);
    u64 alignAddr = addr;
    if(alignment!=0) alignAddr = addr + ((alignment-addr%alignment)%alignment);       // why was the second modulo needed?
    sm.ptr         = (void*)(alignAddr);

    return move(sm);
  }

  SharedMem(){}
  SharedMem(SharedMem&)       = delete;
  SharedMem(SharedMem&& rval)
  {
    fileHndl       =  rval.fileHndl;
    hndlPtr        =  rval.hndlPtr;
    ptr            =  rval.ptr;
    size           =  rval.size;
    owner          =  rval.owner;

    rval.clear();
  }
  ~SharedMem()
  {
    SharedMem::FreeAnon(*this);
  }
  void clear()
  {
    fileHndl  =  (decltype(fileHndl))0;
    hndlPtr   =  nullptr;
    ptr       =  nullptr;
    size      =  0;
    owner     =  false;
  }
  auto  data() -> void*
  {
    return ptr;
  }
};
class       simdb
{
public:
  using BlkCnt = CncrStr::BlkCnt;
  using VerIdx = CncrHsh::VerIdx;

private:
  au64*      s_flags;
  au64*      s_blockSize;
  au64*      s_blockCount;
  CncrStr    s_cs;               // store data in blocks and get back indices
  CncrHsh    s_ch;               // store the indices of keys and values - contains a ConcurrentList

  // these variables are local to the stack where simdb lives, unlike the others, they are not simply a pointer into the shared memory
  SharedMem           m_mem;
  mutable u32    m_nxtChIdx;
  mutable u32    m_curChIdx;
  u64              m_blkCnt;
  u64               m_blkSz;

public:
  static const u32    EMPTY_KEY = CncrHsh::EMPTY_KEY;          // 28 bits set 
  static const u32  DELETED_KEY = CncrHsh::DELETED_KEY;        // 28 bits set 
  static const u32   FAILED_PUT = CncrHsh::EMPTY_KEY;          // 28 bits set 
  static const u32     LIST_END = CncrStr::LIST_END;
  static u64        OffsetBytes()
  {
    return sizeof(au64)*3;
  }
  static u64            MemSize(u64 blockSize, u64 blockCount)
  {
    auto  hashbytes = CncrHsh::sizeBytes((u32)blockCount);
    auto storebytes = CncrStr::sizeBytes((u32)blockSize, (u32)blockCount);
    return  hashbytes + storebytes + OffsetBytes();
  }
  static Match     CompareBlock(simdb const *const ths, i32 blkIdx, u32 version, void const *const buf, u32 len, u32 hash)
  { 
    return ths->s_cs.compare(blkIdx, version, buf, len, hash);
  }
  static bool           IsEmpty(VerIdx kv){return CncrHsh::IsEmpty(kv);}         // special value for CncrHsh
  static bool         IsListEnd(VerIdx vi){return CncrStr::IsListEnd(vi); }      // special value for CncrStr

public:
  simdb(){}
  simdb(const char* name, u32 blockSize, u32 blockCount) : 
    m_curChIdx(0)
  {
    new (&m_mem) SharedMem( SharedMem::AllocAnon(name, MemSize(blockSize,blockCount)) );

    s_blockCount =  ((au64*)m_mem.data())+2;
    s_blockSize  =  ((au64*)m_mem.data())+1;
    s_flags      =   (au64*)m_mem.data();

    if(isOwner()){
      s_blockCount->store(blockCount);
      s_blockSize->store(blockSize);
    }else{                                                       // need to spin until ready
      while(s_flags->load()==false){}
      m_mem.size = MemSize(s_blockSize->load(), s_blockCount->load());
    }

    //auto chSz = s_ch.sizeBytes();
    auto chSz = CncrHsh::sizeBytes(blockCount);
    new (&s_cs) CncrStr( ((u8*)m_mem.data())+chSz+OffsetBytes(), 
                                 (u32)s_blockSize->load(), 
                                 (u32)s_blockCount->load(), 
                                 m_mem.owner);                 // todo: change this to a void*

    new (&s_ch) CncrHsh( ((u8*)m_mem.data())+OffsetBytes(), 
                                (u32)s_blockCount->load(),
                                &s_cs,                        // the address of the CncrStr
                                m_mem.owner);

    m_blkCnt = s_blockCount->load();
    m_blkSz  = s_blockSize->load();

    // todo: initialized flag and reference count
    if(isOwner()) s_flags->store(1);                                        // set to 1 to signal construction is done
  }

  i64          len(const void *const key, u32 klen, u32* out_vlen=nullptr, u32* out_version=nullptr) const
  {
    return s_ch.len(key, klen, out_vlen, out_version);
  }
  bool         get(const void *const key, u32 klen, void *const   out_val, u32 vlen) const
  {
    return s_ch.get(key, klen, out_val, vlen);
  }
  i32          put(const void *const key, u32 klen, const void *const val, u32 vlen)
  {
    return s_ch.put(key, klen, val, vlen);
  }
  bool         del(const void *const key, u32 klen)
  {
    return s_ch.del(key, klen);
  }

  i32          put(char const* const key, const void *const val, u32 vlen)
  {
    assert(strlen(key)>0);
    return put(key, (u32)strlen(key), val, vlen);
  }
  bool         get(char const* const key, void *const val, u32 vlen) const // todo: should val not be a const pointer?
  {
    return get(key, (u32)strlen(key), val, vlen);
  }
  bool         len(u32 idx, u32 version, u32* out_vlen=nullptr, u32* out_version=nullptr) const  // todo: this needs to be redone to fit the functions as they stand now
  {
    auto  ths = this;
    bool   ok = s_ch.runRead(idx, version, 
    [ths, out_vlen, out_version](VerIdx kv)
    {
      u32 vlen = 0;
      auto tlen = ths->s_cs.len(kv.idx, kv.version, out_vlen);
      if(tlen>0){
        *out_vlen = tlen - *out_vlen;
        return true;
      }
      return false;
    });
  
    return ok;
  }
  void       flush() const
  {
    FlushViewOfFile(m_mem.hndlPtr, m_mem.size);
  }
  VerIdx       nxt() const                                   // this version index represents a hash index, not an block storage index
  {
    auto        st = m_nxtChIdx;
    VerIdx   empty = s_ch.empty_kv();
    u32    chNxt; // = empty.key;
    VerIdx     vi;
    do{
           chNxt = s_ch.nxt(m_nxtChIdx);      if(chNxt==empty.idx) return empty;             // can return the same index - it does not do the iteration after finding a non empty key
              vi = s_ch.at(chNxt);
      m_nxtChIdx = (chNxt + 1) % m_blkCnt;
    }while( IsEmpty(vi) );                               // m_nxtChIdx!=st && 

    m_curChIdx = chNxt;
    VerIdx ret = {chNxt, vi.version};
    
    return ret;
  }
  bool      getKey(u32 idx, u32 version, void *const out_buf, u32 klen) const
  {
    if(klen<1) return false;
    
    auto     ths = this;
    auto runFunc = [ths, klen, out_buf](VerIdx kv){
      if(IsEmpty(kv)) return false;
      auto getlen = ths->s_cs.getKey(kv.idx, kv.version, out_buf, klen);
      if(getlen<1) return false;
      
      return true;
    };
    return s_ch.runRead(idx, version, runFunc);
  }
  u32          cur() const { return m_curChIdx; }
  auto        data() const -> const void* const { return s_cs.data(); }
  u64         size() const { return CncrStr::sizeBytes( (u32)s_blockSize->load(), (u32)s_blockCount->load()); }
  bool     isOwner() const { return m_mem.owner; }
  u64       blocks() const { return s_blockCount->load(); }
  auto         mem() const -> void* { return m_mem.hndlPtr; }
  u64      memsize() const { return m_mem.size; }
  auto    hashData() const -> void const* const { return s_ch.data(); }

  // separated C++ functions - these won't need to exist if compiled for a C interface
  struct VerStr { 
    u32 v; str s; 
    bool  operator<(VerStr const& vs) const { if(s==vs.s) return v<vs.v; else return s<vs.s; }  
    bool  operator<(str const&    rs) const { return s<rs;    }
    bool operator==(VerStr const& vs) const { return s==vs.s && v==vs.v; } 
  };   

  i64          put(str    const& key, str const& value)
  {
    return put(key.data(), (u32)key.length(), value.data(), (u32)value.length());
  }
  bool         get(str    const& key, str*   out_value) const
  {
    u32   vlen = 0;
    auto  kvLen = len(key.data(), (u32)key.length(), &vlen);
    new (out_value) std::string(vlen,'\0');
    bool     ok = get(key.data(), (u32)key.length(), (void*)out_value->data(), vlen);

    return ok;
  }
  auto         get(str    const& key)                   const -> std::string
  {
    str ret;
    if(this->get(key, &ret)) return ret;
    else return str("");
  }
  VerStr    nxtKey(u64* searched=nullptr)               const
  {
    u32 klen, vlen;
    bool    ok = false;
    i64   prev = (i64)m_nxtChIdx;
    VerIdx nxt = this->nxt();

    if(searched){
      i64 sidx  = (i64)nxt.idx;       // sidx is signed index
      i64 sprev = (i64)prev;          // sprev is signed previous
      *searched = (sidx-sprev)>0?  sidx-sprev  :  (m_blkCnt-sprev-1) + sidx+1;
    }
    if(nxt.idx==EMPTY_KEY) 
      return {nxt.version, ""};
    
    ok         = this->len(nxt.idx, nxt.version, 
                           &klen, &vlen);               
    if(!ok)
      return {nxt.version, ""};
    
    str key(klen,'\0');
    ok         = this->getKey(nxt.idx, nxt.version, 
                              (void*)key.data(), klen); 
                              
    if(!ok || strlen(key.c_str())!=key.length() )
      return {nxt.version, ""};

    return { nxt.version, key };                    // copy elision 
  }
  auto  getKeyStrs() const -> vec<VerStr>            // vec<u32>* out_versions=nullptr
  {
    using namespace std;
    
    //unordered_set<str> keys;
    
    //template<> struct hash<VerStr>{
    //  size_t operator()(VerStr const& vs){ 
    //    return hash<str>()(vs.str);
    //  }  
    //};
    //unordered_set<VerStr> keys;

    set<VerStr> keys;

    //u32       i = 0;
    //str nxt = nxtKey();
    u64 srchCnt = 0;
    auto     nxt = nxtKey();                             
    while( srchCnt<m_blkCnt && keys.find(nxt)==keys.end() )
    {
      if(nxt.s.length()>0) keys.insert(nxt);
    
      u64 searched = 0;
      nxt = nxtKey(&searched);
      srchCnt += searched;
      //++i;
    }

    //if(out_versions) new (out_versions) vec<u32>()
    return vec<VerStr>(keys.begin(), keys.end());
  }
  bool         del(str const& key)
  {
    return this->del( (void const* const)key.data(), (u32)key.length() );
  }

  template<class T>
  i64          put(str    const& key, vec<T> const& val)
  {    
    return put(key.data(), (u32)key.length(), val.data(), (u32)(val.size()*sizeof(T)) );
  }
  // end separated C++ functions

};



#endif




//return m_mem.size;
//return s_cs.sizeBytes( (u32)s_blockSize->load(), (u32)s_blockCount->load());

//checkMatch(probedKv.version, probedKv.idx, match);
//
//}else{ i==0? (m_sz-1)  : (i-1); continue; }  // todo: look back at this, it shouldn't work!1!! - retry the same loop again

//i32  blkcnt = 0;    
//BlkCnt blkcnt;
// &blkcnt);
//
//auto     ths = this;

//i %= m_sz;
//
//VerIdx expected  =  vi; // vi.idx==EMPTY_KEY?  empty  :  deleted;
// 
// i==0? (m_sz-1)  : (i-1); 
// i==0? (m_sz-1)  : (i-1);

//static const u32  EMPTY_KEY        =  0x0000001FFFFF;   // first 21 bits set 
//static const u32  DELETED_KEY      =  0x0000001FFFFE;   // 1 less than the EMPTY_KEY
//static const  u64  EMPTY_KEY        =  0x000000000000001FFFFF;         // first 21 bits set 
//static const u64  EMPTY_KEY        =  0x000000000FFFFFFF;   // first 28 bits set 
//static const u64  EMPTY_KEY        =    0x0000000000200000;   // first 21 bits set 
//static const u64  EMPTY_KEY        =  2097151;         // first 21 bits set 

//u64 sb = lava_vec::sizeBytes(count);
//p       = addr;

//return _InterlockedCompareExchange128( (i64*)(idxAddr), 
//    swpvi.hi, swpvi.lo,
//    (i64*)(&dblvi) )==1;

//u64 pnum = 
// (u64*)( ((u64)p) & 0x0000FFFFFFFFFFFF);
//return (void*)((u64*)p+2);

//VerIdx keyval;
//keyval.asInt
//return keyval;   
//
//VerIdx       store_vi(u32 i, VerIdx  vi) const
//{
//  using namespace std;
//  
//  //atomic_store<u64>( (Au64*)&m_vis[i].asInt, _kv.asInt );
//  
//  u64 asInt = vi.asInt;
//  bool  odd = i%2 == 1;
//  if(odd) asInt = swp32(asInt);            // the even numbers need to be swapped so that their indices are in the lower address / higher bytes - the indices need to be on the border of the 128 bit boundary so they can be swapped with an unaligned 64 bit atomic operation
//
//  au64* avi = (au64*)(m_vis.data()+i);                            // avi is atomic versioned index
//  u64  prev = avi->exchange(asInt);          //atomic_exchange<u64>( (au64*)(&(m_vis[i].asInt)), asInt);
//
//  VerIdx ret;
//  if(odd) ret.asInt = swp32(prev);
//  else    ret.asInt = prev;
//
//  return ret;
//}
    
//m_sz      =  nextPowerOf2(sz);
//m_vis     =  lava_vec<VerIdx>(m_sz);
// 
//for(u64 i=0; i<m_vis.size(); ++i) m_vis[i] = defKv;

//static u64               swp32(u64 n){ 
//  return (((u64)hi32(n))<<32) & (u64)lo32(n);
//  }
//u64 nxtHi = (((u64)lo32(n))<<32);
//u64 nxtLo = ((u64)hi32(n));
//return nxtHi  |  nxtLo;

//if(out_version) *out_version = nxt.version;
//if(ok) 
//
//else   return { 0, "" };

//#include <winternl.h>
//namespace WINNT { 
//#include <Ntdef.h> 
//#include <Ntifs.h>
//typedef struct _OBJECT_ATTRIBUTES64 {
//    ULONG Length;
//    ULONG64 RootDirectory;
//    ULONG64 ObjectName;
//    ULONG Attributes;
//    ULONG64 SecurityDescriptor;
//    ULONG64 SecurityQualityOfService;
//} OBJECT_ATTRIBUTES64;
//typedef OBJECT_ATTRIBUTES64 *POBJECT_ATTRIBUTES64;
//
//}
//#include <ntstatus.h>
//
//#include <Wdm.h>
//#include <Ntstrsafe.h>

//#if defined(_CRT_SECURE_NO_WARNINGS)
//  #undef _CRT_SECURE_NO_WARNINGS
//  #define _CRT_SECURE_NO_WARNINGS
//#endif
//#undef _CRT_SECURE_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS 1       // msvc mandatory error nonsense when using some standard C functions like fopen 
//
//#if !defined(_CRT_SECURE_NO_WARNINGS)
//  #define _CRT_SECURE_NO_WARNINGS        // msvc mandatory error nonsense when using some standard C functions like fopen 
//#endif

//template<class MATCH_FUNC> 
//VerIdx   delHashed(const void *const key, u32 klen, u32 hash) const // MATCH_FUNC match)            const
//{  
//  using namespace std;
//  static const VerIdx   empty =   empty_kv();
//  static const VerIdx deleted = deleted_kv();
//
//  u32  i = hash;
//  u32 en = prevIdx(i); // min(hash%m_sz - 1, m_sz-1); // clamp to m_sz-1 for the case that hash==0, which will result in an unsigned integer wrap? 
//  for(;; ++i)
//  {
//    i %= m_sz;
//    VerIdx probedKv = load_kv(i);
//
//    if(probedKv.idx==EMPTY_KEY)   return empty;
//    if(probedKv.idx==DELETED_KEY) return deleted;
//
//    Match m = checkMatch(probedKv.version, probedKv.idx, match);
//    if(m==MATCH_TRUE){
//      bool success = cmpex_vi(i, &probedKv, deleted);
//      if(success){
//        cleanDeletion(i);
//        return probedKv;
//      }else{ i==0? (m_sz-1)  : (i-1); continue; }  // retry the same loop again
//
//      return probedKv;   
//    }
//
//    if(m==MATCH_REMOVED || i==en){ return empty; }
//  }
//
//  return empty; 
//}

// len()
//if(klen<1) return 0;
//
//auto hash = CncrHsh::HashBytes(key, klen);
//
//auto  ths = this;
//auto matchFunc = [ths, key, klen, hash](u32 blkidx, u32 ver){
//  return CompareBlock(ths,blkidx,ver,key,klen,hash);
//};
//
//u32 len=0;
//u32 ver=0;
//auto runFunc = [ths, &len, &ver, out_vlen](VerIdx kv){
//  len = IsEmpty(kv)?  0ull  :  ths->s_cs.len(kv.idx, kv.version, out_vlen);
//  ver = kv.version;
//};
//
//if( !s_ch.runMatch(hash, matchFunc, runFunc) ) return 0;
//
//if(out_version) *out_version = ver;
//return len;

// get()
//if(klen<1) return 0;
//
//auto hash = CncrHsh::HashBytes(key, klen);
//auto  ths = this;
//auto matchFunc = [ths, key, klen, hash](u32 blkidx, u32 ver){
//  return CompareBlock(ths,blkidx,ver,key,klen,hash);
//};
//
//u32  out_klen = 0;
//auto  runFunc = [ths, &out_klen, out_val, vlen](VerIdx kv){
//  return ths->s_cs.get(kv.idx, kv.version, out_val, vlen);
//};
//
//return s_ch.runMatch(hash, matchFunc, runFunc);

// put()
//assert(klen>0);
//
//u32   hash = CncrHsh::HashBytes(key, klen);
//
////i32  blkcnt = 0;    
////BlkCnt blkcnt;
//auto vi = s_cs.alloc(klen+vlen, klen, hash); // &blkcnt);                       // todo: use the VersionIdx struct // kidx is key index
//if(vi.idx==LIST_END) return EMPTY_KEY;
//
//s_cs.put(vi.idx, key, klen, val, vlen);
//
//auto     ths = this;                                                            // this silly song and dance is because the this pointer can't be passed to a lambda
//VerIdx    kv = s_ch.putHashed(hash, vi,                                         // this returns the previous VerIdx at the position
//  [ths, key, klen, hash](u32 blkidx, u32 ver){
//    return CompareBlock(ths,blkidx,ver,key,klen,hash);
//  });
//
//if(kv.idx<DELETED_KEY) s_cs.free(kv.idx, kv.version);                           // putHashed returns the entry that was there before, which is the entry that was replaced. If it wasn't empty, we free it here. 
//
//return vi.idx;

// del()
//auto hash = CncrHsh::HashBytes(key, klen);
//auto  ths = this;
//VerIdx kv = s_ch.delHashed(hash,
//  [ths, key, klen, hash](u32 blkidx, u32 ver){ return CompareBlock(ths,blkidx,ver,key,klen,hash); });
//
//bool doFree = kv.idx<DELETED_KEY;
//if(doFree) s_cs.free(kv.idx, kv.version);
//
//return doFree; //kv.idx!=EMPTY_KEY;

//i32          blockLen(i32  blkIdx)      // todo: change this to be either i64 or a 'BlkLen' struct that has the flag if nxt isn't valid?
//{
//  VerIdx nxt = nxtBlock(blkIdx);
//  if(nxt.idx < 0) return -(nxt.idx);
//
//  return blockFreeSize();
//}

//return sizeof(*s_version) + CncrLst::sizeBytes(blockCount) + BlockLists::sizeBytes(blockCount);
//
//return CncrLst::sizeBytes(blockCount) + BlockLists::sizeBytes(blockCount) + blockSize*blockCount;
//
//return sizeof(*s_version);

//u64 delkv = deleted_kv().asInt;                                         
//rgtDel    = *((i64*)(&delkv));                                          
//
//desired = (32<<((u64)l)) & DELETED_KEY;                                       
//
//desired = (32<<(u64)EMPTY_KEY) && EMPTY_KEY

//return ((u8*)stPtr(blkIdx)) + sizeof(IDX);
//
//return ((u8*)stPtr(blkIdx)) + sizeof(IDX);
//
//u32   cpyLen  =  nxt<0? -nxt : blkFree;             // if next is negative, then it will be the length of the bytes in that block

//u32 asInt; - from KeyAndReaders
//
//struct { KeyAndReaders kr; u32 version; i32 idx; u32 len, klen; };

// bl.idx, bl.kr.version };  // s_bls[blkIdx].kr.;
//
//return m_blockSize - sizeof(IDX);

//bool       delToEmpty(u32 i)                const
//{
//  if(i%2==0)                                                                      // both indices are within a 128 bit boundary, so the 128 bit atomic can (and must) be used
//  {                                                                               
//  }else
//  {
//  }
//}

//
// delDupe(prevIdx(i));                                    // now that the next VerIdx is duplicated into the current slot, compare the indices of both and if they are the same, set the right index (the original VerIdx) to DELETED_IDX

//loop_start: while( (nxtVi=load_kv(nxtIdx(i))).idx < DELETED_KEY )
//{
//  do{ 
//    curVi = load_kv(i);
//    if(curVi.idx != DELETED_KEY){ return false; }
//
//    nxtVp = ipd(nxtVi);
//    if(nxtVp.version!=nxtVi.version){ goto loop_start; }  // the versions don't match, so start over on the same index and skip the compare exchange 
//    else if(nxtVp.ipd==0){ return true; }                 // next slot's versions match and its VerIdx is in its ideal position, so we are done 
//  }while( !compexchange_kv(i, &curVi.asInt, nxtVi.asInt) );
//  
//  ++i;
//}

//u32 nxti = nxtIdx(i);
//nxtVi = load_kv(nxti);
//if(nxtVi.idx==DELETED_KEY || nxtVi.idx==EMPTY_KEY){ return true; }

//if(vp.version!=vi.version && vp.ipd>0){
//  //compexchange_kv(i, &curVi.asInt, vi.asInt);       // write next index's VerIdx to the current index if it is still deleted
//}

//using   i8     =  int8_t;
//using  u32     =  uint32_t;
//using  u64     =  uint64_t;
//using  u32     =  uint32_t;
//using  u64     =  uint64_t;

//bool  compexchange_kv(u32 i, u64* expected, u64 desired) const
//{
//  using namespace std;
//  
//  //kv    keyval;
//  //keyval.asInt    =  atomic_load<u64>( (Au64*)&m_kvs.data()[i].asInt );
//  //keyval.key      =  key;
//  //keyval.val      =  val;
//  //return success;
//
//  return atomic_compare_exchange_strong( (Au64*)&(m_kvs.data()[i].asInt), expected, desired);                      // The entry was free. Now let's try to take it using a CAS. 
//}

//HeadUnion  curHead;
//HeadUnion  nxtHead;
//
//return nxtHead.idx;

//new (&m_ch) CncrHsh( ((i8*)m_mem.data())+OffsetBytes(), m_blockCount->load(), m_mem.owner);
//new (&m_cs) ConcurrentStore( ((i8*)m_mem.data())+m_ch.sizeBytes(m_blockCount->load())+OffsetBytes(), m_blockSize->load(), m_blockCount->load(), m_mem.owner);                 // todo: change this to a void*

//new (&m_mem) SharedMem( SharedMem::AllocAnon(name, MemSize(blockSize,blockCount)) );
//new (&m_ch) CncrHsh( ( ((i8*)m_mem.data())+OffsetBytes(), blockCount, m_mem.owner) );
//new (&m_cs) ConcurrentStore(  ((i8*)m_mem.data())+m_ch.sizeBytes(blockCount)+OffsetBytes(), blockSize, blockCount, m_mem.owner);                 // todo: change this to a void*

//m_mem( SharedMem::AllocAnon(name, MemSize(blockSize,blockCount)) ),
//m_ch( ((i8*)m_mem.data())+OffsetBytes(), blockCount, m_mem.owner),
//m_cs( ((i8*)m_mem.data())+m_ch.sizeBytes(blockCount)+OffsetBytes(), blockSize, blockCount, m_mem.owner),                 // todo: change this to a void*
//m_blockCount( ((au64*)m_mem.data())+2 ),
//m_blockSize(  ((au64*)m_mem.data())+1 ),
//m_flags(       (au64*)m_mem.data() )

//static BlkLst   make_BlkLst(bool isKey, i32 readers, u32 idx, u32 ver, u32 len, u32 klen)
//{
//  BlkLst bl;
//  bl.kr.isKey    = isKey;
//  bl.kr.readers  = readers;
//  bl.idx         = idx;
//  bl.kr.version  = ver;
//
//  if(isKey){
//    bl.len  = len;
//    bl.klen = klen;
//  }else{
//    bl.len  = 0;
//    bl.klen = 0;
//  }
//
//  return bl;
//}

//i32      nxt  =  nxtBlock(curidx);
//
//if(curlen < blksz){ return MATCH_FALSE; }
//auto cmplen = min(curlen, (ui32)blksz);
//Match   cmp = memcmpBlk(curidx, curbuf, p, cmplen);
//}else if(-nxt != curlen){ return MATCH_FALSE; }
// return MATCH_TRUE; // never reached

//m_cl(m_blockCount)
//
//if(owner) *((u64*)addr) = blockCount;
//
//BlkLst def; 
//def.idx     = 0; 
//def.readers = 0; 
//for(u64 i=0; i<m_bls.size(); ++i) m_bls[i]=def;

//
//using BlockLists  =  lava_vec<IDX>;

//using ListVec  =  std::vector< std::atomic<ui32> >;  // does this need to be atomic? all the contention should be over the head
//
//using HeadInt  =  ui64;
//using    Head  =  std::atomic<ui64>;
//
//ui64   m_szBytes;
//
//ConcurrentList(ui32 size) : 
//  m_lv(size)
//{
//  for(uint32_t i=0; i<(size-1); ++i) m_lv[i]=i+1;
//  m_lv[size-1] = LIST_END;
//
//  m_h = 0;
//}
//
//ConcurrentList(void* addr) :           // this constructor is for memory that is not owned and so does not need to be initialized, just used
//  m_lv(addr)
//{
//  m_h = (aui64*)addr;
//  //m_h->asInt = 0;
//}
//
//ui64  sizeBytes() const
//{
//  return *((ui64*)addr);
//}

//dblVerIdx.hi  =  idxAddr->hi;
//dblVerIdx.hi  =  idxAddr->hi;
//
//auto tmp = dblVerIdx->hi;

//i32             stPtr(i32  blkIdx)  const
//{
  //return (i32*)( ((i8*)m_blksAddr) + blkIdx*m_blockSize );
  //return (i32*)&(m_bls.data()[blkIdx]);
  //return m_bls[blkIdx].idx;
  //return m_bls[blkIdx].idx;
//}

//auto      realloc(VerIdx st, i32 size, ui32 klen, i32* out_blocks=nullptr) -> VerIdx     // todo: doesn't this need to give back the blocks if allocation fails?
//{
//  i32  byteRem  =  0;
//  i32 blksNeed  =  blocksNeeded(size, &byteRem);
//
//  //ui32   st = s_cl.nxt();                                     // stBlk  is starting block
//  //SECTION(get the starting block index and handle errors)
//  //{
//  //  if(st==LIST_END){
//  //    if(out_blocks) *out_blocks = 0; 
//  //    return List_End();
//  //  }
//  //}
//
//  ui32    kvlen = len(st.idx, st.version);
//  i32  blksHave = blocksNeeded(size);
//  if(blksNeed > blksHave){
//    SECTION(add more blocks the current list)
//    {
//    }
//    SECTION(write )
//  }else{
//  }
//
//  //ui32 ver  =  (ui32)s_version->fetch_add(1);
//  //i32  cur  =  st;
//  //i32  nxt  =   0;
//  //i32  cnt  =   0;
//  //SECTION(loop for the number of blocks needed and get new block and link it to the list)
//  //{
//  //  for(i32 i=0; i<blocks-1; ++i)
//  //  {
//  //    nxt    = s_cl.nxt();
//  //    if(nxt==LIST_END){ free(st, ver); VerIdx empty={LIST_END,0}; return empty; }
//  //
//  //    if(i==0)  s_bls[cur] =  make_BlkLst(true,  0, nxt, ver, size, klen);
//  //    else      s_bls[cur] =  make_BlkLst(false, 0, nxt, ver, 0, 0);
//  //    cur        =  nxt;
//  //    ++cnt;
//  //    m_blocksUsed.fetch_add(1);
//  //  }
//  //}
//
//  SECTION(add the last index into the list, set out_blocks and return the start index with its version)
//  {
//    ui32 blockRemainder = byteRem? -byteRem : -blockFreeSize();
//    BlkLst  bl = make_BlkLst(cur==st, 0, blockRemainder, ver, size, klen);
//    s_bls[cur] = bl;
//    s_bls[st].kr.isKey = true;
//
//    if(out_blocks){ *out_blocks = nxt==LIST_END? -cnt : cnt; }
//    VerIdx vi = { st, ver };
//    return vi;
//  }
//}

//namespace WINNT { 
//  #include <Ntdef.h> 
////#include <Ntifs.h>
//}

//int s = (int)status;
//printf("\nstatus: %0xh error: %s\n", s, GetLastErrorStdStr().c_str() );
//if(status==STATUS_SUCCESS){
//  printf("status success");
//}

//wprintf(L"\n%s \n", mempth);
//buf;  // /*(WINNT::PWCH)*/ mempth;
//sizeof(buf); 

//typedef struct _RTLP_CURDIR_REF
//{
//	LONG RefCount;
//	HANDLE Handle;
//} RTLP_CURDIR_REF, *PRTLP_CURDIR_REF;
// typedef struct RTL_RELATIVE_NAME_U {
//	WINNT::UNICODE_STRING RelativeName;
//	HANDLE ContainingDirectory;
//	PRTLP_CURDIR_REF CurDirRef;
//} RTL_RELATIVE_NAME_U, *PRTL_RELATIVE_NAME_U;
//typedef BOOLEAN (NTAPI *RtlDosPathNameToNtPathName_U_t)(
//                          WINNT::PCWSTR DosName,
//                          WINNT::PUNICODE_STRING NtName,
//                          PCWSTR *PartName,
//                          PRTL_RELATIVE_NAME_U RelativeName);

/*
template<class T>
i64          get(vec<T> const& key, void*  out_buf) const     // todo: needs to be redone
{
  Reader r = read((void*)key.data(), (ui32)(key.size() * sizeof(T)));
  if(isEmpty(r.kv)) return -1;
  //if(r.kv.key == EMPTY_KEY || r.kv.readers <= 0){ return -1; }

  ui64 len = getFromBlkIdx(r.kv.val, out_buf);
  if(r.doRm()){ m_cs.free(r.kv.val); m_cs.free(r.kv.idx); }

  return len;
}
*/

// typedef NTSTATUS(WINAPI *NTOPENDIRECTORYOBJECT)(
//_Out_  PHANDLE DirectoryHandle,
//_In_   ACCESS_MASK DesiredAccess,
//_In_   POBJECT_ATTRIBUTES ObjectAttributes
//);
// 
//typedef NTSTATUS(WINAPI *NTQUERYDIRECTORYOBJECT)(
// _In_       HANDLE DirectoryHandle,
// _Out_opt_  PVOID Buffer,
// _In_       ULONG Length,
// _In_       BOOLEAN ReturnSingleEntry,
// _In_       BOOLEAN RestartScan,
// _Inout_    PULONG Context,
// _Out_opt_  PULONG ReturnLength
// );

//s = (int)status;
//printf("\nstatus: %0xh error: %s retlen: %llu \n", s, GetLastErrorStdStr().c_str(), retLen );
//wprintf(L"Buffer name: %s  type: %s\n\n", info->name.Buffer, info->type.Buffer );
//if(status==STATUS_SUCCESS){
//  printf("status success");
//}

//if(!_hModule){ LoadLibrary( _T("ntdll.dll") ); }
//if(!_hModule){ return ret; }
//if(!NtOpenDirectoryObject){  NtOpenDirectoryObject  = (NTOPENDIRECTORYOBJECT)GetProcAddress( _hModule, "NtOpenDirectoryObject");  }
//if(!NtQueryDirectoryObject){ NtQueryDirectoryObject = (NTQUERYDIRECTORYOBJECT)GetProcAddress(_hModule, "NtQueryDirectoryObject"); }
//
//printf("error: %s", GetLastErrorStdStr().c_str() );
//
//if(!RtlInitUnicodeString){
//  RtlInitUnicodeString = (RTLINITUNICODESTRING)GetLibraryProcAddress( _T("NtosKrnl.exe"), "RtlInitUnicodeString");
//}
//
// static RtlDosPathNameToNtPathName_U_t RtlDosPathNameToNtPathName_U;
//if(!RtlDosPathNameToNtPathName_U)
// if(!(RtlDosPathNameToNtPathName_U=(RtlDosPathNameToNtPathName_U_t) GetProcAddress(GetModuleHandleA("NTDLL.DLL"), "RtlDosPathNameToNtPathName_U")))
//  abort();

//RtlInitUnicodeString(&usDirectoryName, DIRECTORY_NAME);
//(WINNT::PUNICODE_STRING)
//oattr    
//WINNT::WCHAR* mempth = L"c:";
//
//printf("error: %s", GetLastErrorStdStr().c_str() ); 
//wprintf(L"\n%s \n", pth.Buffer);
//
//RtlDosPathNameToNtPathName_U(mempth, &pth, NULL, NULL);
//RtlInitUnicodeString(&UName, pszDir);
//
//oa.ObjectName         = NULL;                                
//
// status = NtOpenFile(
//   &hDir, 
//   FILE_LIST_DIRECTORY|SYNCHRONIZE, 
//   &oa, &isb, 
//   FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
	//0x01 /*FILE_DIRECTORY_FILE*/ | 0x20/*FILE_SYNCHRONOUS_IO_NONALERT*/ | 0x4000/*FILE_OPEN_FOR_BACKUP_INTENT*/);
//InitializeObjectAttributes(&objectAttributes, L("\BaseNamedObjects"), OBJ_CASE_INSENSITIVE, NULL, NULL);
//
// /*0x20001*/ /*SECTION_MAP_READ*/

//auto        alloc(i32    size, ui32 klen, i32* out_blocks=nullptr) -> VerIdx   // todo: doesn't this need to give back the blocks if allocation fails?
//{
//  i32 byteRem  =  0;
//  i32  blocks  =  blocksNeeded(size, &byteRem);
//  //if(out_blocks) *out_blocks = blocks;
//
//  ui32   st = s_cl.nxt();                                     // stBlk  is starting block
//  if(st==LIST_END){
//    if(out_blocks) *out_blocks = 0; 
//    return List_End(); // LIST_END; 
//  }
//
//  ui32 ver  =  (ui32)s_version->fetch_add(1);
//  i32  cur  =  st;
//  i32  cnt  =   0;
//  i32  nxt  =   0;
//  for(i32 i=0; i<blocks-1; ++i)
//  {
//    nxt    = s_cl.nxt();
//    if(nxt==LIST_END){ free(st, ver); VerIdx empty={LIST_END,0}; return empty; }
//
//    if(i==0)  s_bls[cur] =  make_BlkLst(true,  0, nxt, ver, size, klen);
//    else      s_bls[cur] =  make_BlkLst(false, 0, nxt, ver, 0, 0);
//    cur        =  nxt;
//    ++cnt;
//    m_blocksUsed.fetch_add(1);
//  }
//
//  BlkLst bl  = make_BlkLst(cur==st, 0, byteRem? -byteRem : -blockFreeSize(), ver, size, klen);
//  s_bls[cur] = bl;
//
//  if(out_blocks){ *out_blocks = nxt==LIST_END? -cnt : cnt; }     
//
//  s_bls[st].kr.isKey = true;
//
//  VerIdx vi = { st, ver };
//  return vi;
//}

//str       nxtKey(ui32* out_version=nullptr)         const
//{
//  ui32 klen, vlen;
//  bool    ok = false;
//  VerIdx nxt = this->nxt();                           if(nxt.idx==EMPTY_KEY) return "";
//  ok         = this->len(nxt.idx, nxt.version, 
//                         &klen, &vlen);               if(!ok) return "";
//  str key(klen,'\0');
//  ok         = this->getKey(nxt.idx, nxt.version, 
//                            (void*)key.data(), klen); if(!ok) return "";
//
//  if(out_version) *out_version = nxt.version;
//  return key;                    // copy elision 
//}

//template< template<class> class V, class T>
//using VAL_TYPE = V::value_type;
//vec<int>::value_type

//if(blkcnt<0){
//  s_cs.free(vi.idx, vi.version);
//  return EMPTY_KEY;
//}    

//template<class MATCH_FUNC> 
//VerIdx       checkMatch(ui32 i, ui32 key, MATCH_FUNC match) const -> Match //  decltype(match(empty_kv()))
//{
//  Match ret = match(key);
//  
//  return ret;
//}

// todo: WRONG? check needs to be run on each spin if the entry is different
//if( checkMatch(i, probedKv.version, probedKv.idx, match)==MATCH_TRUE ){
  //return store_vi(i, desired);
//}

//
//i  &=  m_sz - 1;


/*
open system call reference from http://www.unix.com/man-page/FreeBSD/2/open/

           O_RDONLY	   open for reading only
	   O_WRONLY	   open for writing only
	   O_RDWR	   open for reading and writing
	   O_EXEC	   open for execute only
	   O_NONBLOCK	   do not block on open
	   O_APPEND	   append on each write
	   O_CREAT	   create file if it does not exist
	   O_TRUNC	   truncate size to 0
	   O_EXCL	   error if create and file exists
	   O_SHLOCK	   atomically obtain a shared lock
	   O_EXLOCK	   atomically obtain an exclusive lock
	   O_DIRECT	   eliminate or reduce cache effects
	   O_FSYNC	   synchronous writes
	   O_SYNC	   synchronous writes
	   O_NOFOLLOW	   do not follow symlinks
	   O_NOCTTY	   don't assign controlling terminal
	   O_TTY_INIT	   restore default terminal attributes
	   O_DIRECTORY	   error if file is not a directory
	   O_CLOEXEC	   set FD_CLOEXEC upon open
*/


