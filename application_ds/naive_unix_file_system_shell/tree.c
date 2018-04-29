#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "common.h"

TreePtr tree_create_node()
{
        TreePtr node = Malloc(sizeof(Tree));
        node->file_name = Malloc(MAX_FILE_NAME_LENGTH);
        node->parent = NULL;
        node->child = NULL;
        node->sibling = NULL;

        return node;
}

TreePtr file_system_init()
{
        TreePtr root_dir = tree_create_node();
        root_dir->file_name[0] = '/';
        root_dir->file_name[1] = '\0';

        return root_dir;
}

void tree_destroy(TreePtr root)
{
        if (root) {
                tree_destroy(root->child);
                tree_destroy(root->sibling);
                free(root);
        }
}

// insert a new node under current node
void tree_insert(NodePtr node, char *file_name, enum FileType file_type)
{
        // init the new node
        NodePtr new_node = tree_create_node();
        new_node->parent = node;
        new_node->file_type = file_type;
        strcpy(new_node->file_name, file_name);

        if (node->child == NULL) {
                node->child = new_node;
        } else {
                NodePtr p = node->child->sibling;
                NodePtr q = p;
                while (p) {
                        q = p;
                        p = p->sibling;
                }
                q->sibling = new_node;
        }
}

NodePtr find_previous_sibling(NodePtr current_node)
{
        NodePtr p = current_node->parent;
        if (p == NULL) {  // root
                return NULL;
        } else if (p->child == current_node) {
                return NULL;
        } else {
                NodePtr q = p->child;
                NodePtr t = p->child;
                while (q && q != current_node) {
                        t = q;
                        q = q->sibling;
                }
                return t;
        }
}

NodePtr find_last_sibling(NodePtr current_node)
{
        if (current_node == NULL) {
                return NULL;
        } else {
                NodePtr p = current_node->sibling;
                NodePtr q = NULL;
                while (p) {  // break when p = NULL
                        q = p;
                        p = p->sibling;
                }
                return q;
        }
}

void tree_delete(NodePtr current_node)
{
        if (current_node == NULL) {
                return ;
        } else if (current_node->parent == NULL) {  // root
                if (current_node->child == NULL) {
                        free(current_node);
                } else {
                        if (current_node->child->sibling == NULL) {
                                current_node->parent = NULL;  // become the root
                                free(current_node);
                        } else {
                                if (current_node->child->child != NULL) {
                                        current_node->child->sibling = current_node->child->sibling;
                                        NodePtr q = current_node->child->child;
                                        while (q) {
                                                q->parent = current_node->child;
                                        }
                                        free(current_node);
                                } else {
                                        current_node->child->child = current_node->child->sibling;
                                        NodePtr q = current_node->child->child;
                                        while (q) {
                                                q->parent = current_node->child;
                                        }
                                        free(current_node);
                                }
                        }
                }
        } else {  // command node
                NodePtr previous_sibling = find_previous_sibling(current_node);
                if (previous_sibling == NULL) {  // current_node is the big brother
                        NodePtr p = current_node->parent;
                        if (current_node->child == NULL && current_node->sibling == NULL) {
                                free(current_node);
                                p->child = NULL;
                        } else if (current_node->child != NULL && current_node->sibling == NULL) {
                                p->child = current_node->child;
                                NodePtr q = current_node->child;
                                while (q) {
                                        q->parent = current_node->sibling;
                                        q = q->sibling;
                                }
                                free(current_node);
                        } else if (current_node->child == NULL && current_node->sibling !=NULL) {
                                p->child = current_node->sibling;
                                free(current_node);
                        } else {
                                NodePtr last_sibling = find_last_sibling(current_node->sibling->child);
                                if (current_node->sibling->child == NULL) {
                                        current_node->parent->child = current_node->sibling;
                                        current_node->sibling->child = current_node->child;
                                } else {
                                        last_sibling->sibling = current_node->child;
                                }
                                NodePtr q = current_node->child;
                                while (q) {
                                        q->parent = current_node->sibling;
                                        q = q->sibling;
                                }
                                free(current_node);
                        }
                } else {  // current_node is not the big brother
                        if (current_node->child == NULL) {
                                previous_sibling->sibling = current_node->sibling;
                                free(current_node);
                        } else {
                                previous_sibling->sibling = current_node->sibling;
                                if (previous_sibling->child == NULL) {
                                        previous_sibling->child = current_node->child;
                                } else {
                                        NodePtr last_cousin = find_last_sibling(previous_sibling->child);
                                        last_cousin->sibling = current_node->child;
                                }
                                NodePtr q = current_node->child;
                                while (q) {
                                        q->parent = previous_sibling;
                                        q = q->sibling;
                                }
                                free(current_node);
                        }
                }
        }
}


char* tree_path(NodePtr current_node)
{
        NodePtr array_node_ptrs[MAX_PATH_LENGTH];
        NodePtr p = current_node;
        int i = 0;
        while (p) {
                array_node_ptrs[i++] = p;
                p = p->parent;
        }
        char* s = Malloc(sizeof(char) * 1024);
        strcpy(s, array_node_ptrs[i - 1]->file_name);  // root directory
        for (int j = 1; j < i; j++) {
                strcpy(s, array_node_ptrs[j]->file_name);
                strcpy(s, "/");
        }
        return s;
}

void print_prompt(char *s)
{
        printf("huaizhi@xtp-UU:%s$ ", s);
        return ;
}

NodePtr command_ls(NodePtr current_node)
{
        if (current_node->child == NULL) {
                print_prompt(current_node->file_name);
        } else {
                NodePtr p = current_node->child;
                while (p) {
                        printf("%s  ", p->file_name);
                        p = p->sibling;
                }
                printf("\n");
                print_prompt(current_node->file_name);
        }
        return current_node;
}

NodePtr command_pwd(NodePtr current_node)
{
        char *s = tree_path(current_node);
        printf("%s\n", s);
        print_prompt(current_node->file_name);
        return current_node;
}

NodePtr command_cd(NodePtr current_node, char *dir_name)
{
        if (strcmp(dir_name, ".") == 0) {
                print_prompt(current_node->file_name);
                return current_node;
        }
        if (strcmp(dir_name, "..") == 0) {
                NodePtr parent_node = current_node->parent;
                if (parent_node != NULL) {
                        print_prompt(parent_node->file_name);
                        return parent_node;
                } else {
                        print_prompt(current_node->file_name);
                        return current_node;
                }
        }
        // find the directory
        NodePtr node = current_node->child;
        while (node && strcmp(node->file_name, dir_name) != 0) {
                node = node->sibling;
        }

        if (node == NULL) {
                printf("no such file or directory\n");
                print_prompt(current_node->file_name);
                return current_node;
        }

        if (node->file_type == REGULAR) {
                printf("%s is not directory\n", node->file_name);
                print_prompt(current_node->file_name);
                return current_node;
        }

        print_prompt(node->file_name);
        return node;
}


NodePtr command_mkdir(NodePtr current_node, char *s)
{
        NodePtr new_node = tree_create_node();
        new_node->parent = current_node;
        strcpy(new_node->file_name, s);
        new_node->file_type = DIRECTORY;
        if (current_node->child == NULL) {
                current_node->child = new_node;
                new_node->parent = current_node;
        } else {
                NodePtr p = current_node->child;
                while (p->sibling != NULL) {
                        p = p->sibling;
                }
                p->sibling = new_node;
                p->parent = current_node;
        }
        print_prompt(current_node->file_name);
        return current_node;
}

NodePtr command_touch(NodePtr current_node, char *s)
{
        NodePtr new_node = tree_create_node();
        new_node->parent = current_node;
        strcpy(new_node->file_name, s);
        char *p = new_node->file_name;
        while (*p != '\0') {
                p++;
        }
        *p++ = '*';
        *p = '\0';
        new_node->file_type = REGULAR;
        if (current_node->child == NULL) {
                current_node->child = new_node;
                new_node->parent = current_node;
        } else {
                NodePtr p = current_node->child;
                while (p->sibling != NULL) {
                        p = p->sibling;
                }
                p->sibling = new_node;
                p->parent = current_node;
        }
        print_prompt(current_node->file_name);
        return current_node;
}

int is_leaf(NodePtr current_node)
{
        if (current_node->child == NULL &&
                        current_node->sibling == NULL) {
                return 1;
        } else {
                return 0;
        }
}

int node_depth(NodePtr current_node)
{
        if (current_node->parent == NULL) {  // root
                return 0;
        } else {  // tail recursion
                return 1 + tree_depth(current_node->parent);
        }
}

int node_height(NodePtr current_node)
{
        if (is_leaf(current_node)) {
                return 0;
        } else if (current_node->child == NULL) {
                return node_height(current_node->sibling);
        } else if (current_node->sibling == NULL) {
                return 1 + node_height(current_node->child);
        } else {
                return MAX((1 + node_height(current_node->child)),
                                node_height(current_node->sibling));
        }
}

int tree_depth(NodePtr root)
{
        return node_depth(root);
}

int tree_height(NodePtr root)
{
        return node_height(root);
}

static void print_name(NodePtr current_node, int depth)
{
        for (int i = 0; i < depth; i++) {
                printf("        ");
        }
        printf("%s\n", current_node->file_name);
}

static void list_dir(NodePtr current_node, int depth)
{
        if (current_node != NULL) {  // legitimate entry
                print_name(current_node, depth);
                if (current_node->file_type == DIRECTORY) {
                        NodePtr node = current_node->child;
                        while (node) {
                                list_dir(node, depth + 1);
                                node = node->sibling;
                        }
                }
        }
}

NodePtr command_lsfs(NodePtr current_node)
{
        if (current_node == NULL) {
                return NULL;
        }
        list_dir(current_node, 0);
        print_prompt(current_node->file_name);
        return current_node;
}

NodePtr command_rm(NodePtr current_node, char *s)
{
        NodePtr node = current_node->child;
        while (node && strcmp(node->file_name, s) != 0) {
                node = node->sibling;
        }
        if (node == NULL) {
                printf("no such file or directory\n");
                print_prompt(current_node->file_name);
                return current_node;
        } else {  // file is found
                tree_delete(node);
                print_prompt(current_node->file_name);
                return current_node;
        }
}
