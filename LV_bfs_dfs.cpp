

/*
Represent a given graph using adjacency matrix/list to perform DFS and using adjacency list to perform 
BFS. Use the map of the area around the college as the graph. Identify thr prominent land marks as nodes and perform DFS and BFS
on that.*/
#include<iostream>
#include <istream>
#include<stack>
#include<queue>

using namespace std;

class graph_list{
    int n;
    struct Node{
        int data;
        Node* next;  
    };
    Node* head[10];

    stack<int> s;
    queue<int> q;

public:
    graph_list(){
        cout << "Enter number of nodes : ";
        cin >> n;
        for (int i=0; i<n; i++) head[i] = nullptr;
    }

    void create();
    void dfs();
    void bfs();

};

void graph_list::create(){
    Node* curr, *temp;
    int m;
    for(int i=0; i<n; i++){
        head[i] = new Node;
        head[i]->next = nullptr;
        cout << "\nEnter data for vertex: ";
        cin >> head[i]->data;
        curr = head[i];
        cout << "Enter no. of adjacency nodes : ";
        cin >> m;
        for(int j=0; j<m; j++){
            temp = new Node;
            temp->next = nullptr;
            cout << "Enter data for adjacency node : ";
            cin >> temp->data;
            curr->next = temp;
            curr = temp;
        }
    }
}

void graph_list::dfs(){
    int sv, visited[10], num;
    cout << "\nEnter starting vertex : ";
    cin >> sv;
    for(int i=0; i<n; i++){
        visited[i] = 0;
    }
    s.push(sv);
    while(!s.empty()){
        num = s.top();
        s.pop();
        if(visited[num]==0){
            cout << num << " ";
            visited[num] = 1;
            Node* t = head[num];
            while(t!=nullptr){
                if(visited[t->data]==0) s.push(t->data);
                t = t->next;
            }
        }
    }
}

void graph_list::bfs(){
    int sv, visited[10], num;
    cout << "\nEnter starting vertex : ";
    cin >> sv;
    for(int i=0; i<n; i++){
        visited[i] = 0;
    }
    q.push(sv);
    while(!q.empty()){
        num = q.front();
        q.pop();
        if(visited[num]==0){
            cout << num << " ";
            visited[num] = 1;
            Node* t = head[num];
            while(t!=nullptr){
                if(visited[t->data]==0) q.push(t->data);
                t = t->next;
            }
        }
    }
}

int main(){
    graph_list g;
    g.create();
    cout << "\n\nDFS : ";
    g.dfs();
    cout << "\n\nBFS : ";
    g.bfs(); 
    return 0;
}

/*Enter number of nodes : 4

Enter data for vertex: 0
Enter no. of adjacency nodes : 2
Enter data for adjacency node : 1
Enter data for adjacency node : 2

Enter data for vertex: 1
Enter no. of adjacency nodes : 3
Enter data for adjacency node : 0
Enter data for adjacency node : 2
Enter data for adjacency node : 3

Enter data for vertex: 2
Enter no. of adjacency nodes : 3
Enter data for adjacency node : 0
Enter data for adjacency node : 1
Enter data for adjacency node : 3

Enter data for vertex: 3
Enter no. of adjacency nodes : 2
Enter data for adjacency node : 1
Enter data for adjacency node : 2


DFS :
Enter starting vertex : 0
0 2 3 1

BFS :
Enter starting vertex : 0
0 1 2 3
*/