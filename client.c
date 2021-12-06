#include "PES1UG20CS008_H.h"
int main()
{
    struct node *head[10];
    int data[100][100];
    int i,j;
    int start_x,start_y,end_x,end_y;
    FILE *fp=fopen("input.txt","r");        //reading the input file to acces the adjacency matirx from which we can create a graph of adjacency list
    fscanf(fp,"%d",&start_x);               //copies start and end coordinates
    fscanf(fp,"%d",&start_y);
    fscanf(fp,"%d",&end_x);
    fscanf(fp,"%d",&end_y);
    e_x=end_x;
    e_y=end_y;

    // printf("%d %d %d %d\n",start_x,start_y,end_x,end_y);
    // printf("%d %d",e_x,e_y);

    for(i=0;i<10;i++){                              //reading the matric from the file
        for(j=0;j<10;j++){
            fscanf(fp,"%d",&data[i][j]);    
        }
    }
    fclose(fp);
    
    creategraph(head,data);
    display(head);
    connect_nodes(head);
    s_v=start_vertex(head,start_x+1,start_y+1);
    e_v=end_vertex(head,end_x+1,end_y+1);
    // printf("Start %d,End %d",s_v,e_v);
    int result_bfs,result_dfs;
    printf("\nBFS Search : {Vertex Number :(x-coordinate,y-coordinate)}\n");
    result_bfs=bfs(1,head[1]);
    printf("\n\nDFS Search : {Vertex Number :(x-coordinate,y-coordinate)}\n");
    result_dfs=dfs(1,head[1]);
    printf("\n");
    // for(int i=0;i<d;i++){
    //     printf("%d ",dfs_path[i]);
    // }
    //     printf("\n");

    // for(int i=0;i<b;i++){
    //     printf("%d ",bfs_path[i]);
    // }
    output_path(result_bfs,result_dfs);
}