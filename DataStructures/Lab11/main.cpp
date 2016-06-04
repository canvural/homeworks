



#include <iostream>

#include <sstream>



#include <queue>

#include <stack>



using namespace std;



struct elem{int index;double weight;elem* next;};

enum colour{WHI,GRE};



struct vertexList{elem* SENT;colour COLUR;};



struct Graph

{

    int size;

    vertexList *v;

};



void insertEdge(Graph &g, int u, int v, double weight)

{

    if(u> (g.size-1) || v> (g.size-1)) return;

    if(u<0 || v<0) return;



    elem* p=g.v[u].SENT;



    while (p->next!=NULL && p->next->index < v )

    {

        if(p->index==v)

        {

            p->weight=weight;

            return;

        }

        p=p->next;

    }

    elem *addedElem= new elem;

    addedElem->index=v;

    addedElem->weight=weight;

    addedElem->next=p->next;



    p->next=addedElem;



}



void loadGraph(Graph &g, int n, int m)

{

    g.size=n;

    g.v= new vertexList[n];



    for(int i=0; i< n; i++)

    {



        g.v[i].SENT= new elem;

        g.v[i].SENT->index=i;

        g.v[i].SENT->next=NULL;

    }



    int idxStart;

    int idxEnd;

    double weight;



    for(int i=0; i < m ;i++)

    {

        cin>> idxStart;

        cin>> idxEnd;

        cin>> weight;



        insertEdge(g, idxStart, idxEnd, weight);

    }

}



bool findEdge(Graph &g, int u, int v, double &weight)

{

    if(u> g.size || v> g.size) return false;

    if(u<0 || v<0) return false;



    elem* p= g.v[u].SENT->next;



    while (p != NULL)

    {

        if(p->index==v)

        {

            weight= p->weight;

            return true;

        }

        p=p->next;

    }

    return false;

}

void showAsMatrix(Graph &g)

{

    elem* temp;



    for(int i=0; i < g.size; i++)

    {

        temp= g.v[i].SENT->next;

        for (int j=0; j < g.size; j++)

        {

            if(temp==NULL || temp->index > j)

            {

                if(i==j) cout <<"0,";

                else cout <<"-,";

            }

            else if(temp->index == j)

            {

                cout <<temp->weight<<',';

                temp=temp->next;

            }

        }

    cout<< endl;

    }

}



void showAsArrayOfLists(Graph &g)

{

    elem* temp;

     for(int i=0; i < g.size; i++)

     {

        temp= g.v[i].SENT->next;

        cout<< i <<':';



        while(temp != NULL)

        {

            cout<< temp->index <<"("<< temp->weight <<"),";

            temp=temp->next;

        }



        cout <<endl;

     }

}





void BFS(Graph &g, int s)

{

    for(int i=0; i< g.size; i++)

        g.v[i].COLUR=WHI;



    queue<int> q;



    q.push(s);

    int next;



    while (!q.empty())

    {

        next=q.front();

        q.pop();



        elem* p=g.v[next].SENT->next;

        g.v[next].COLUR=GRE;



        while( p != NULL )

        {

            if(g.v[p->index].COLUR != GRE){

                q.push(p->index); // if not discovered push to queue

                g.v[p->index].COLUR= GRE;

            }

            p=p->next;

        }

        cout<< next <<',';

    }

    cout<< endl;



}



void DFSvisit (Graph &g, int s)

{

    g.v[s].COLUR=GRE; //once visited

    cout << s <<',';



    elem* p=g.v[s].SENT->next;

    while (p != NULL)

    {

        if(g.v[p->index].COLUR==WHI)

            DFSvisit(g, p->index);

        p=p->next;

    }



}

void DFS (Graph &g, int s)

{

    for(int i=0; i< g.size; i++)

        g.v[i].COLUR=WHI;



    DFSvisit(g, s);

    cout <<endl;

}







void showBool(bool val){

    if(val)

        cout << "true" << endl;

    else

        cout << "false" << endl;

}



bool isCommand(const string command,const char *mnemonic){

    return command==mnemonic;

}



int main()

{

    string line;

    string command;

    Graph *gra=0;

    int currentL=0;

    int variab1=0;

    int variab2=0;

    cout << "START" << endl;



    while(true)

    {

        getline(cin,line);

        std::stringstream stream(line);

        stream >> command;

        if(line=="" || command[0]=='#')

        {

            // ignore empty line and comment

            continue;

        }



        // copy line on output with exclamation mark

        cout << "!" << line << endl;;



        // change to uppercase

        command[0]=toupper(command[0]);

        command[1]=toupper(command[1]);



        // zero-argument command

        if(isCommand(command,"HA")){

            cout << "END OF EXECUTION" << endl;

            break;

        }



        if(isCommand(command,"SM")) //*

        {

            showAsMatrix(gra[currentL]);

            continue;

        }



        if(isCommand(command,"SA")) //*

        {

            showAsArrayOfLists(gra[currentL]);

            continue;

        }



        // read next argument, one int value

        stream >> variab1;

        if(isCommand(command,"GO"))

        {

            gra=new Graph[variab1];

            continue;

        }





        if(isCommand(command,"CH"))

        {

            currentL=variab1;

            continue;

        }

        if(isCommand(command,"BF"))

        {

            BFS(gra[currentL], variab1);

            continue;

        }

        if(isCommand(command,"DF"))

        {

            DFS(gra[currentL], variab1);

            continue;

        }





        stream >> variab2;



        if(isCommand(command,"LG"))

        {

            loadGraph(gra[currentL], variab1, variab2);

            continue;

        }



        if(isCommand(command,"FE"))

        {

            double edgeWeight;

            bool ret= findEdge(gra[currentL], variab1, variab2, edgeWeight);

            if(ret)

                cout << edgeWeight <<endl;

            else

                showBool(ret);

            continue;

        }



        if(isCommand(command,"IE"))

        {

            float weight;

            stream >> weight;

            insertEdge(gra[currentL], variab1, variab2, weight);

            continue;



        }





        cout << "wrong argument in test: " << command << endl;

    }

    return 0;

}
