#ifndef FT_LS_H
#define FT_LS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
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

typedef uint16_t t_opt;

typedef struct t_arguments {
	t_opt options;
	t_llist *dirs;
	bool execute_list;
} t_arguments;

typedef struct t_fsinfo {
} t_fsinfo;

typedef struct t_rls_ctx {
	t_llist **directories;
	int options;
	char *dirp;
	size_t cwd_len;
} t_rls_ctx;

typedef struct t_rls_dispatch {
	void (*recurse_list)(t_rls_ctx *context);
	t_rls_ctx context;
} t_rls_dispatch;

t_arguments parse_arguments(int argc, char *const *argv);
void temp_list_all(t_arguments args);
void handle_errno_parsing(char *dir, t_llist **non_dir);
void handle_errno_listing(t_rls_ctx *ctx);


#endif
