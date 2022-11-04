#pragma once
#include<iostream>
#include<fstream>
#include<map>
#include<stdlib.h>
#include<vector>
#include<bitset>
#include<queue>
using namespace std;

//Definition of the Node
struct Tree {
	char letter;
	int freq;
	Tree* left;
	Tree* right;
};
struct Order 
{
	bool operator()(Tree* l, Tree* r) // changes the priority queues comparison algorithm to the smallest first 
	{
		return l->freq > r->freq;
	}
};
//Functions
void fillMap(priority_queue<Tree*, vector<Tree*>, Order>& p1); 
void createTree(priority_queue<Tree*, vector<Tree*>, Order>& p1);
void createCode(priority_queue<Tree*, vector<Tree*>, Order> p1);
void printByAsciiCode(map<char, string>& huffmanCode);
void printByHuffmanCode(map<char, string>& huffmanCode);
void recursiveCreateCode(Tree* temp, string code, map<char, string>& huffmanCode);



void printByAsciiCode(map<char, string>& huffmanCode) { 
	ofstream out; 
	ifstream in;
	
	char ch;
	in.open("text.txt");
	if (!in)
		cout << "File couldn't be found!\n";
	out.open("asciicode.txt");
	if (!out)
		cout << "File couldn't be found!\n";
	in >> noskipws;  //takes the space as a character 
	while (in >> ch) {  //time space complexity is O(n)


		out << bitset<8>(ch).to_string()<<" ";  // converts  string to char and print each letter as a bit
		
	};
	out.close();
	in.close();
}
void printByHuffmanCode(map<char, string>& huffmanCode) {    
	ofstream out;
	ifstream in;
	
	char ch;
	in.open("text.txt");
	if (!in)
		cout << "File couldn't be found!\n";
	out.open("huffmancode.txt");
	if (!out)
		cout << "File couldn't be found!\n";  // prints the codes into the file 
	in >> noskipws; //takes the space as a character 
	while (in >> ch) {

	
		out << huffmanCode[ch]<<"  ";  //prints the code corresponding to each letter into file 
	};


	out.close();
	in.close();

}
void createCode(priority_queue<Tree*, vector<Tree*>, Order> p1) {
	Tree* temp = new Tree; 
	map<char, string> huffmanCode;
	temp = p1.top();
	recursiveCreateCode(temp, "", huffmanCode); // sends the root for filling huffman code map with letter code
	cout << "\n \nCode Table Is >>\n___________________\n"; 
	map<char, string>::iterator it;    
	for (it = huffmanCode.begin(); it != huffmanCode.end(); it++) {  //prints the table with the codes corresponding to each letter
		if (it->first == ' ')
			cout << "|Space" << it->first << "  =  " << it->second << "  |" << endl;


		else
			cout << "|     " << it->first << "  =  " << it->second << "  |" << endl;
	}
	printByHuffmanCode(huffmanCode);  //prints  huffman code as text  file
	printByAsciiCode(huffmanCode);    //prints  ASCII code of every character as  text file
}

void recursiveCreateCode(Tree* temp, string code, map<char, string>& huffmanCode) {  //time space complexity is O(logn)
	if (temp->letter != NULL) { // until the next node is leaf node
		huffmanCode[temp->letter] = code;   //update string value according to letter for each recursive operation 
	}
	else {
		recursiveCreateCode(temp->left, code + "0", huffmanCode);  // traverse  until the leftmost of tree and put code all each branches 
		recursiveCreateCode(temp->right, code + "1", huffmanCode); //traverse  until the rightmost of tree and put code all each branches
	}


}
void createTree(priority_queue<Tree*, vector<Tree*>, Order>& p1) { 

	while (p1.size() != 1) { 

		Tree* node = new Tree;

		node->left = p1.top(); //get smallest value 
		p1.pop();
		node->right = p1.top();  // get second smallest value  
		p1.pop();  // values must be pop so we can traverse in priority queue

		node->freq = node->left->freq + node->right->freq;
		node->letter = NULL;
		p1.push(node); //new node is added to priority queue
	}
}


void fillMap(priority_queue<Tree*, vector<Tree*>, Order>& p1) { //The function transfer the  information in the text file, to the map
	ifstream in;
	map<char, int> freqMap;
	char ch;
	in.open("text.txt");
	in >> noskipws; //takes the space as a character 
	if (!in)
		cout << "File couldn't be found!\n";
	else {
		while (in >> ch) { 

			freqMap[ch]++;  //character counter

		}
	}
	in.close();

	map<char, int>::iterator it;
	
	for (it = freqMap.begin(); it != freqMap.end(); it++) { //iterates each character in the  map     

		Tree* node = new Tree;   //nodes that hold information inside the map 
		node->freq = it->second;    // fills in nodes to be added to the priority queue
		//cout << it->first << "  ";
		node->letter = it->first;
		//cout << it->second;

		node->left = NULL;
		node->right = NULL;
	    p1.push(node);  //adds each node to priority queue for creating tree

	}


}