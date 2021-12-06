#ifndef HEADER
#define HEADER
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
struct node
{
    int vertex_id;
    int row_no;
    int col_no;
    int r;
    int d;
    struct node* next;
    struct node *right;
    struct node* down;
};

//declaration of global variables using extern

extern int e_x,e_y; //end coordinates
extern int s_v,e_v; //start and end vertex
extern int visit_bfs[100];
extern int visit_dfs[100];
extern int f,r;
extern int dfs_path[100][2];
extern int bfs_path[100][2];
extern int b,d;
extern struct node *q[100];

void creategraph(struct node **,int data[100][100]);
void insert(struct node **head,int i,int j,int data[100][100]);
void display(struct node **head);
void connect_nodes(struct node **head);
int start_vertex(struct node **head,int x,int y);
int end_vertex(struct node **head,int x,int y);
int bfs(int v,struct node *temp);
int qempty();
void qinsert(struct node *v);
struct node * qdelete();
int dfs(int v,struct node *temp);
int output_path();

#endif