#include<bits/stdc++.h>
#include <sstream> 
#include <vector>
using namespace std;

//! class for creating an edge of the graph.
class Edge{
    public:
	char source;
	char dest;
	int weight;
};
//! compare function used in sorting the edges according to their weights.
bool compare(Edge e1, Edge e2);
//! Recursive function to find the parent of a node.
int findParent(int i, int *parent);
//! method to find minimum spanning tree of given graph.
void kruskals( Edge* input , int n , int e);
//! main function.
int main(){

    fstream file ;
    file.open("input1.csv", ios :: in);
    string temp;
    int count =0;
    while(!file.eof()){
    	getline(file, temp);
    	count++;
    }
    file.close();
    fstream file1;
    file1.open("input1.csv", ios :: in);
    int e = count -1;
	Edge* edges = new Edge[e];  //! Array which contains all the edges of graph.
	string line, word;
	int max = 0;
	for (int i=0;i<e ;i++)
	{
		getline(file1, line);
		stringstream s(line);
		vector <char> vect;
		while (getline (s,word,',')){
            vect.push_back(word[0]);
		}
		edges[i].source = vect[0];
		edges[i].dest = vect[1];
		edges[i].weight = (int)vect[2]-48;
		if ((int)edges[i].dest > max){
			max = edges[i].dest;
		}
		vect.clear();
	}
	int n = max - 64;
	cout << "Edge representation of given graph :" << endl;
	cout << "Source  "<< "Destination  "<< "Weight"<< endl;
	for (int i=0;i<e;i++){
		cout<< edges[i].source << "       "<< edges[i].dest << "            "<< edges[i].weight<< endl;
	}
	kruskals(edges , n , e );
	system("dot -Tpdf Krushkal.dot -o Krushkal.pdf");
    return 0;
}
//! compare function used in sorting the edges according to their weights.
bool compare(Edge e1, Edge e2){
	return (e1.weight < e2.weight);
}
//! Recursive function to find the parent of a node.
int findParent(int i, int *parent){
	if (parent[i] == i )
		return i;
	return findParent(parent[i],parent);
}
//! method to find minimum spanning tree of given graph.
void kruskals( Edge* input , int n , int e){

	sort(input , input + e, compare);
	Edge* output = new Edge[n-1];
	int * parent = new int [n];
	for (int i=0;i<n;i++){
		parent[i] = i;
	} 
	int count =0; 
	int i=0;
	int min_sum=0;
	while (count != (n-1)){

		Edge currentedge = input[i];

		int sParent = findParent((int)currentedge.source -65 , parent);
		int dParent = findParent((int)currentedge.dest - 65, parent);

        if(sParent != dParent){
        	min_sum += currentedge.weight;
        	output[count] = currentedge;
        	count++;
        	parent[sParent] = dParent;
        }
        i++;
	}
	cout << "Edge representation of Minimum Spanning Tree of the given graph :"<< endl;
	cout << "Source  "<< "Destination  "<< "Weight"<< endl;
	for (int i=0;i<n-1;i++){
		if(output[i].source < output[i].dest){
			cout << output[i].source << "       "<<output[i].dest << "            "<< output[i].weight<< endl;
		}
		else {
			cout << output[i].dest << "       "<<output[i].source << "            "<< output[i].weight<< endl;
		}
	}
	cout << "The minimum sum of the spanning tree is : "<< min_sum << endl;
	   
	    ofstream file;        //! file for making dot file to use graphviz.
		file.open("Krushkal.dot");

		if (file.is_open())
		{
			file << "graph MST {" << endl;
			file << "\tgraph [ dpi = 1200 ];" << endl;

			for (int i =0;i<n-1 ;i++)
			{
				file << "\t" << output[i].source << " -- " << output[i].dest << " [label=" << output[i].weight << "];" << endl; 
			}

			file << "}" << endl;

			file.close();
		}

}