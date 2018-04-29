#pragma once 

#include "common.h"

#define MAX_FILE_NAME_LENGTH 64
#define MAX_PATH_LENGTH 128

enum FileType {
        DIRECTORY,
        REGULAR
};

struct Tree {
        char *file_name;
        enum FileType file_type;
        struct Tree *parent;
        struct Tree *child;
        struct Tree *sibling;
};

typedef struct Tree Tree;
typedef struct Tree Node;
typedef struct Tree* TreePtr;
typedef struct Tree* NodePtr;

void print_prompt(char *s);

TreePtr file_system_init();

NodePtr tree_create_node();

void tree_destroy(TreePtr);

void tree_insert(NodePtr, char*, enum FileType);

void tree_delete(NodePtr);

NodePtr previous_sibling(NodePtr);

NodePtr find_last_sibling(NodePtr);

char* tree_path(NodePtr);

int node_depth(NodePtr);

int node_height(NodePtr);

int tree_depth(NodePtr);

int tree_height(NodePtr);

int is_leaf(NodePtr);  // Macro is ok

#define IS_LEAF(node) \
        (!(node->child) && !(node->sibling))

NodePtr command_ls(NodePtr);

NodePtr command_pwd(NodePtr);

NodePtr command_cd(NodePtr, char*);

NodePtr command_lsfs(NodePtr);

NodePtr command_mkdir(NodePtr, char*);

NodePtr command_touch(NodePtr, char*);

NodePtr command_rm(NodePtr, char*);
