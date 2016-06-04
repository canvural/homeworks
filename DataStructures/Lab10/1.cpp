


#include <iostream>

#include <stdlib.h>

#include <sstream>

#include <limits>



#define infinity 10000

using namespace std;



struct vertice

{

    int index;

    double *arrOfWeights;

};



struct Graph

{

    int size;

    vertice *v;

};

void insertEdge(Graph &g, int u, int v, double weight)

{

    if(u> (g.size-1) || v> (g.size-1)) return;

    if(u<0 || v<0) return;



    g.v[u].arrOfWeights[v]=weight;

}



void loadGraph(Graph &g, int n, int m)

{

    g.size=n;

    g.v=new vertice[n];



    for(int i = 0; i < n; i++){

        g.v[i].arrOfWeights = new double[n];

        for(int j=0; j < n; j++)

        {

        if(i==j) g.v[i].arrOfWeights[j]=0;

        else  g.v[i].arrOfWeights[j]=infinity;

        }

    }

    int idxStart;

    int idxEnd;

    float weight;



    for(; m>0; m--)

    {

        cin>> idxStart;

        cin>> idxEnd;

        cin>> weight;



        insertEdge(g, idxStart, idxEnd, weight);

    //  g.v[idxStart].arrOfWeights[idxEnd]= weight;

    }

}





bool findEdge(Graph &g, int u, int v, double &weight)

{

    if(u> g.size || v> g.size) return false;

    if(u<0 || v<0) return false;



    weight= g.v[u].arrOfWeights[v];                     //why double= INT_MAX+1

    if (weight==0 || weight >= infinity) return false;



    return true;

}

void showAsMatrix(Graph &g)

{

    for(int i=0; i < g.size; i++)

    {

        for (int j=0; j < g.size; j++)

        {

            if (g.v[i].arrOfWeights[j] == infinity) cout <<"-,";

            else cout<< g.v[i].arrOfWeights[j] <<',';

        }

    cout<< endl;

    }

}

void showAsArrayOfLists(Graph &g)

{

     for(int i=0; i < g.size; i++)

     {

        cout<< i <<':';

        for (int j=0; j < g.size; j++)

        {

            if(g.v[i].arrOfWeights[j] != 0 && g.v[i].arrOfWeights[j]!=infinity)

            cout<<j<<"("<<g.v[i].arrOfWeights[j] <<"),";

        }

        cout <<endl;

     }

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
