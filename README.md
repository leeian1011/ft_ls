# ft\_ls

A recreation of the POSIX-compliant requirement and GNU coreutils command, `ls`.

## Design

### Parsing

Parsing options & list of directories to crawl through `char **argc`.
Options will be handled with bitwise operations for memory-optimization.
(I am doing this not because I have to but because I want to, just to mess around with bitwise operators).

## Understanding & Research

### ACL

Access Control List (ACL)

Files in linux are able to be configured for security via the command `setfacl`.<br></br>
These configurations to security allows users to specify who is allowed to access a file (hence access control).<br></br>
The configurations set by `setfacl` is stored in the file's extended attributes. These extended attributes (and therefore ACLs) are
accessible via the `getxattr` function provided by libc.

Note that `ls` only tracks POSIX ACL extended attribute, and nothing else.

Using `setfacl` on a file will add a new '+' char to the ACL attributes output from `ls`.
i.e:
```
rwxrwxrwx+ file1 # this file has extended attributes for ACL
rwxrwxrwx  file2 # this file does not
```

## Bonuses

- ACL and extended attributes
- Options -o -g -d

### Log
> This section is a devlog that will not be formatted properly, it's purpose is to note/jot down my progress.

[16/8/2026]<br></br>
- Converted manual arg parsing approach (strchr + checking arg[0] == '-') to using getopt (provided by libc).
- manual arg parsing had issues handling '--' and plain '-'
- Handled --help partially.
- Added linked list sorting using merge sort (easiest sorting algo for linkedlist data structure) to accomodate
- default ls listing (lexicographically ordered).
- Added reverse linked list function to accomodate '-r' option.
- introduce github repo for tracking. 

 [17/8/2026]<br></br>
 - theres no valgrind on mac lmao
 - rediscovered strlcat and memset to not have to allocate string when recursively checking directories.
 - created an abomination `t_llist *directories` where `directories->data` is a `t_llist *`.
 - after recursively appending all directories in -R option mode, program aborts, unable to identify why due to valgrind being missing on macOS.

 [18/8/2026]
- found out retaining pointers of `struct dirent *` is not safe as mentioned in the ![unix docs](https://www.unix.com/man-page/posix/3p/readdir/)
mentioned in the description, the pointers may be invalidated by calls to `readdir`, thus I will employ a different approach to managing the data.








