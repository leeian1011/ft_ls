# ft_ls

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
[16/8/2026]
- Converted manual arg parsing approach (strchr + checking arg[0] == '-') to using getopt (provided by libc).
- manual arg parsing had issues handling '--' and plain '-'
- Handled --help partially.
- Added linked list sorting using merge sort (easiest sorting algo for linkedlist data structure) to accomodate
- default ls listing (lexicographically ordered).
- Added reverse linked list function to accomodate '-r' option.

