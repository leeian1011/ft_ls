#ifndef FT_LS_H
#define FT_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>
#include <getopt.h>
#include "linkedlist.h"

#define OPT_RECURSIVE 1
#define OPT_REVERSE 2
#define OPT_ALL_INFO 4
#define OPT_LISTING 8
#define OPT_G_LISTING 32
#define OPT_O_LISTING 64
#define OPT_TIME_ORDERED 16
#define OPT_DIRECTORIES_ONLY 128
#define OPT_PASSED_PATH 256
#define OPT_MULTI_PP 512
#define OPT_IDENTS "Rralgotd"
#define OPT_RECURSIVE_IDENT 'R'
#define OPT_REVERSE_IDENT 'r'
#define OPT_ALL_INFO_IDENT 'a'
#define OPT_LISTING_IDENT 'l'
#define OPT_G_LISTING_IDENT 'g'
#define OPT_O_LISTING_IDENT 'o'
#define OPT_TIME_ORDERED_IDENT 't'
#define OPT_DIRECTORIES_ONLY_IDENT 'd'

#define BUILD_RESET(replace, dest, src, dlen, ...) {\
	if ((replace)) {\
		printf("hello inside\n");\
		strlcpy((dest), (src), PATH_MAX);\
		__VA_ARGS__\
		getcwd((dest), PATH_MAX);\
	} else {\
		strlcat((dest), "/", PATH_MAX);\
		strlcat((dest), (src), PATH_MAX);\
		__VA_ARGS__;\
		memset((dest) + (dlen), 0, PATH_MAX - (dlen));\
	}\
}

typedef uint16_t t_opt;

typedef struct t_arguments {
	t_opt options;
	t_llist *dirs;
	bool execute_list;
} t_arguments;

typedef struct t_fsinfo {
} t_fsinfo;

typedef struct t_rls_ctx {
	int options;
	char *dirp;
	size_t cwd_len;
} t_rls_ctx;

typedef struct t_rls_dispatch {
	void (*recurse_list)(t_rls_ctx *context);
	t_rls_ctx context;
} t_rls_dispatch;

typedef struct t_dirdata {
	struct dirent *dirent;
	struct stat *stat;
} t_dirdata;

t_arguments parse_arguments(int argc, char *const *argv);
void temp_list_all(t_arguments args);
int handle_errno_parsing(char *dir, t_llist **non_dir);
void handle_errno_listing(t_rls_ctx *ctx);
void output_dirlist(t_rls_ctx *ctx, t_llist *dir_list, bool first_invoc);

int compare_dirstr(t_llist *a, t_llist *b);
int compare_dirent(t_llist *a, t_llist *b);
int compare_time(t_llist *a, t_llist *b);


#endif
