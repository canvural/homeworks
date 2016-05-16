#include <iostream>
#include <string>
#include <sstream>

// DSF - disjoint sets forest

using namespace std;

// element of array
struct Element{
	int rank;
	int parent;
};

// DSF - disjoint sets forest
struct DSF{
	Element *arr;
	int size;
};

void init(DSF & dsf, int size){
    dsf.arr = new Element[size];
    dsf.size = size;
}

void makeSet(DSF &dsf, int val)
{
    dsf.arr[val].rank = 0;
    dsf.arr[val].parent = val;
}

void makeOneElementSets(DSF & dsf){
    for(int i = 0; i < dsf.size; i++) {
        makeSet(dsf, i);
    }
}

int find(DSF & dsf, int index){
    if(dsf.arr[index].parent != index) {
        dsf.arr[index].parent = find(dsf, dsf.arr[index].parent);
    }

    return dsf.arr[index].parent;
}

void link(DSF & dsf, int index1, int index2){
    if(index1 == index2) {
        return;
    }

    if(dsf.arr[index1].rank > dsf.arr[index2].rank) {
        dsf.arr[index2].parent = index1;
    } else {
        dsf.arr[index1].parent = index2;
        if(dsf.arr[index1].rank == dsf.arr[index2].rank) {
            dsf.arr[index2].rank++;
        }
    }
}

void makeUnion(DSF & dsf, int index1, int index2){
    link(dsf, 
         find(dsf, index1),
         find(dsf, index2)
    );
}

int parent(DSF & dsf, int index){
	return dsf.arr[index].parent;
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

int main(){
	string line;
	string command;
	DSF *dsf=NULL;
	int currentF=0;
	int value;
	cout << "START" << endl;
	while(true){
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

		if(isCommand(command,"MO"))
		{
			makeOneElementSets(dsf[currentF]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"IN"))
		{
			init(dsf[currentF],value);
			continue;
		}


		if(isCommand(command,"FD"))
		{
			cout << find(dsf[currentF],value) << endl;
			continue;
		}

		if(isCommand(command,"PA"))
		{
			cout << parent(dsf[currentF],value) << endl;
			continue;
		}

		if(isCommand(command,"UN"))
		{
			int value2;
			stream >> value2;
			makeUnion(dsf[currentF],value,value2);
			continue;
		}


		if(isCommand(command,"CH"))
		{
			currentF=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			dsf=new DSF[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;

	}
	return 0;
}
