#include "header.h"

//definition of global variables
int e_x,e_y;                //end coordinates
int s_v,e_v;                //start and end vertex
int visit_bfs[100];         //array to mark visited vertices in BFS traversal
int visit_dfs[100];         //array to mark visited vertices in DFS traversal
int f=-1,r=-1;              //front and rear pointers of the queue
int dfs_path[100][2];       //2-D array to store path flow for DFS traversal
int bfs_path[100][2];       //2-D array to store path flow for BFS traversal
int b=0,d=0;                //index for dfs_path and bfs_path
struct node *q[100];        //queue to store addresses of the nodes,used in bfs traversal


void creategraph(struct node **head,int data[100][100]){        //creates a graph (adjacency list)
    for(int i=1;i<=10;i++){
        head[i]=NULL;
    }
    int x,y;
    for(int i=9;i>=0;i--){                                      //numbering of rows and columns starts from 1
        for(int j=9;j>=0;j--){
            if(data[i][j]==0){
                //printf("%d %d",i,j);
                insert(head,i+1,j+1,data);
            }
        }
    }
    struct node * temp;
    int count=1;
    for(int i=1;i<=10;i++){
        temp=head[i];
        while(temp!=NULL){
            temp->vertex_id=count;
            count++;
            temp=temp->next;
            
        }
    }
}
void connect_nodes(struct node **head){
    //struct node *temp,*down,*right;
    // for(int i=0;i<10;i++){
    //     temp=head[i+1];
    //     for(int j=0;j<10;j++){
    //         while(temp!=NULL){
    //             if(data[i][j]==0 && data[i+1][j]==0 && i<9){
    //                 down=head[i+2];
    //                 for(int n=1;n<=10;n++){
    //                     while(down!=NULL && n!=j+1){
    //                         down=down->next;
    //                     }
    //                 }
    //                 temp->down=down;
    //             }
    //             else{
    //                 temp->down=NULL;
    //             }
    //             if(data[i][j]==0 && data[i][j+1]==0 && j<9){
    //                 for(int m=1;m<=10;m++){
    //                     right=head[i+1];
    //                     while(right!=NULL && m!=j+1){
    //                         right=right->next;
    //                     }
    //                 }
    //                 temp->right=right;
    //             }
    //             else{
    //                 temp->down=NULL;
    //             }
    //         }
    //     }
    // }
    struct node *temp,*down;
    for(int i=1;i<=10;i++){                    //to connect adjacent nodes on the right hand side
        temp=head[i];
        while(temp!=NULL){
            if(temp->r==temp->col_no+1){
                temp->right=temp->next;
            }
            else{
                temp->right=NULL;
            }
            temp=temp->next;
        }
    }
    for(int i=1;i<10;i++){                  //to connect adjacent nodes to the bottom
        temp=head[i];
        down=head[i+1];
        while(temp!=NULL && down!=NULL){
            if(temp->d==temp->row_no+1){
                while(down!=NULL && down->col_no!=temp->col_no){
                    down=down->next;
                }
                temp->down=down;
            }
            else{
                temp->down=NULL;
            }
            temp=temp->next;
        }
    }
}
void insert(struct node **head,int i,int j,int data[100][100]){         //inserts nodes into the graph
    struct node *temp;
    temp=(struct node *)malloc(sizeof(struct node));
    // temp->vertex_id=1;
    temp->row_no=i;
    temp->col_no=j;
    if(data[i-1][j]==0 && j<10){//to link nodes to the immediate right 
        temp->r=j+1;
    }
    else{
        temp->r=-1;
    }
    if(data[i][j-1]==0 && i<10){//to link nodes to the immediate bottom
        temp->d=i+1;
    }
    else{
        temp->d=-1;
    }
    temp->next=head[i];
    head[i]=temp;
}
int start_vertex(struct node **head,int x,int y){           //function to find the start vertex
    struct node *temp;
    int vertex;
    for(int i=1;i<=10;i++){
        temp=head[i];
        while(temp!=NULL){
            if(temp->row_no==x && temp->col_no==y){
                    vertex=temp->vertex_id;
                    return vertex;                          //returns start vertex
            }
            temp=temp->next;
        }
    }
}
int end_vertex(struct node **head,int x,int y){             //function to find the end vertex
    struct node *temp;
    int vertex;
    for(int i=1;i<=10;i++){
        temp=head[i];
        while(temp!=NULL){
            if(temp->row_no==x && temp->col_no==y){
                    vertex=temp->vertex_id;
                    return vertex;                          //returns end vertex
            }
            temp=temp->next;
        }
    }
}
void display(struct node **head){                           //displays the graph
    struct node * temp;
    printf("\nGraph : {vertex Number :(x-coordinate,y-coordinate)\n\n");
    for(int i=1;i<=10;i++){
        temp=head[i];
        printf("%d->\t",i);
        while(temp!=NULL){
            //printf("V:%d,C:(%d,%d),R:%d,D:%d\t",temp->vertex_id,temp->row_no,temp->col_no,temp->r,temp->d);
            //printf("%d ",temp->vertex_id);
            // printf("(%d,%d)->",temp->row_no,temp->col_no);
            printf("{%d:(%d,%d)}->",temp->vertex_id,temp->row_no,temp->col_no);
            temp=temp->next;
        }
        printf("\n");
    }
}
int bfs(int v,struct node *temp){                   //breath first search path flow traversal
    visit_bfs[v]=1;                                 //keeps track of visited nodes (1-visited,0-not visited)
    struct node *w,*right,*down,*adj[2],*u;
    // right=temp->right;
    // down=temp->down;
    // adj[0]=right;
    // adj[1]=down;
    //printf("%d->",temp->vertex_id);
    // printf("(%d,%d)->",temp->row_no,temp->col_no);
    printf("{%d:(%d,%d)}->",temp->vertex_id,temp->row_no,temp->col_no);
    //bfs_path[b]=temp->vertex_id;
    bfs_path[b][0]=temp->row_no;            //copying the path into the array
    bfs_path[b][1]=temp->col_no;
    b++;
    // if(visit_bfs[e_v]==1){
    //     return 0;
    // }
    qinsert(temp);
    while(!qempty()){
        if(visit_bfs[e_v]==1){
            return 0;
        }
        w=qdelete();
        right=w->right;         //stores address of immediate right node (stores NULL if its does not have an immediate right node)
        down=w->down;           //stores address of immediate bottom node (stores NULL if its does not have an immediate right node)
        adj[0]=right;           //storing immediate right node into the array at position 0
        adj[1]=down;            //storing immediate bottom node into the array at position 1

        // for(u=temp;u!=NULL;u=u->right){
        //     if(data[w][u]==0 && visit[u]==0){
        //         printf("%d ",u);
        //         visit[u]=1;
        //         qinsert(u);
        //         bfs(data,u);
        //     }
        // }
        // while(right!=NULL || down!=NULL){
        //     if(right!=NULL && v[right->vertex_id]==0){
        //         printf("%d->",right->vertex_id);
        //         visit[right->vertex_id]=1;
        //         qinsert(right);
        //         bfs(data,right->vertex_id,right);
        //     }
        // }
        for(int i=0;i<2;i++){           //this for loops iterates across both the nodes i.e right and down
            u=adj[i];
            if(u!=NULL && visit_bfs[u->vertex_id]==0){      //node is not null and not visited
                // printf("%d",u->vertex_id);
                visit_bfs[u->vertex_id]=1;
                qinsert(u); 
                bfs(u->vertex_id,u);   
            }
        }
    }
}
int qempty(){
    if(f==-1) return 1;
    return 0;
}
void qinsert(struct node *temp){
    r++;
    q[r]=temp;
    if(f==-1){
        f=0;
    }
}
struct node* qdelete(){
    struct node* w;
    w=q[f];
    if(f==r){
        f=r=-1;
    }
    else{
        f++;
    }
    return w;
}
int dfs(int v,struct node *temp)        //depth first search traversal to find path flow
{
    struct node *u,*adj[2],*p;
    visit_dfs[v]=1;                     //keeps track of visited nodes (1-visited,0-not visited)
    //printf("%d->",v);
    //printf("(%d,%d)->",temp->row_no,temp->col_no);

    printf("{%d:(%d,%d)}->",temp->vertex_id,temp->row_no,temp->col_no);
    // dfs_path[d]=v;

    dfs_path[d][0]=temp->row_no;        //copying the path into the array
    dfs_path[d][1]=temp->col_no;
    d++;
    // if(visit_dfs[56]==1){
    //     return 0;
    // }
    // if(temp->row_no==(e_x+1) && temp->col_no==(e_y+1)){
    //         return 0;
    // }
    adj[0]=temp->right;              //storing immediate right node into the array at position 0
    adj[1]=temp->down;               //storing immediate bottom node into the array at position 1
    for(int i=0;i<2;i++){
        if(visit_dfs[e_v]==1){
            return 0;
        }
        p=adj[i];
        if(p!=NULL){
            
            if(visit_dfs[p->vertex_id]==0)

                dfs(p->vertex_id,p);
        }
        
    }
}
int output_path(int result_bfs,int result_dfs){                      //to write the path flow of both methods into 2 seperate files
    FILE *fp1=fopen("outdfs.txt","w");
    FILE *fp2=fopen("outbfs.txt","w");
    
    if(fp1==NULL || fp2==NULL){
        printf("Eror: Could not access file");
        return 0;
    }

    if(!result_dfs){                                //writes the path flow into the file if it exits
        for(int i=0;i<d;i++){
            for(int j=0;j<2;j++){
                fprintf(fp1,"%d ",dfs_path[i][j]);
            }
            fprintf(fp1,"\n");                      //writes -1 if path does not exit
        }
    }
    else{
        fprintf(fp1,"%d",-1);
    }
    if(!result_bfs){                                //writes the path flow into the file if it exits
        for(int i=0;i<b;i++){
            for(int j=0;j<2;j++){
                fprintf(fp2,"%d ",bfs_path[i][j]);
            }
            fprintf(fp2,"\n");                      
        }
    }
    else{
        fprintf(fp2,"%d",-1);                       //writes -1 if path does not exit               
    }

    fclose(fp1);
    fclose(fp2);
}
