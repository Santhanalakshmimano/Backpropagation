#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;
int co=0;

vector<vector<double> >Data;
vector<int> Index;
// vector<int> Random_Index;
vector<double> Target_Output;

void Read_Data(){
	ifstream ifs("Irisdata.txt");
	string line;
	double num;
	char ch;
	while(getline(ifs, line)){
		vector<double> data_value;
		stringstream s(line);
		while(s >> num){
			data_value.push_back(num);
			s >> ch;
		}
		Data.push_back(data_value);
	}
}

void Training_file(){
	ofstream trainfile;
	trainfile.open("training.txt");
	for(int i=0; i<(Index.size()/2); i++){
		for(int j=0; j<Data[0].size(); j++){
			int x = Index[i];
			trainfile << Data[x][j];
			trainfile <<"\t";
		}
		trainfile << "\n";
	}
	trainfile.close();
}

void Testing_file(){
	ofstream testfile;
	testfile.open("testing.txt");
	for(int i=(Index.size()-20); i< Index.size(); i++){
		for(int j=0; j<Data[0].size(); j++){
			int x = Index[i];
			testfile << Data[x][j];
			testfile <<"\t";
		}
		testfile <<"\n";
	}
	testfile.close();
}

void Validation_file(){
	ofstream validfile;
	validfile.open("Validation.txt");
	for(int i=(Index.size()/2); i< (Index.size()-20); i++){
		for(int j=0; j<Data[0].size(); j++){
			int x = Index[i];
			validfile << Data[x][j];
			validfile <<"\t";
		}
		validfile <<"\n";
	}
	validfile.close();
}

void Read_Output(){
	string line;
	int n;
	//pushing labels into Vector output
	ifstream op("output.txt");
	while(getline(op, line)){
		stringstream iss(line);
		while(iss >> n){
			Target_Output.push_back(n);
		}
		
	}
}

void Train_Out(){
	ofstream trainfile;
	trainfile.open("Train_Output_file.txt");
	for(int i=0; i< (Index.size()/2); i++){
			int x = Index[i];
			trainfile << Target_Output[x]<<"\n";
	}
		
	trainfile.close();
}

void Test_Out(){
	ofstream testfile;
	testfile.open("Test_Output_file.txt");
	for(int i=(Index.size()-20); i< (Index.size()); i++){
			int x = Index[i];
			testfile << Target_Output[x]<<"\n";
	}
		
	testfile.close();
}

void Valid_Out(){
	ofstream validfile;
	validfile.open("Valid_Output_file.txt");
	for(int i=(Index.size()/2); i< (Index.size()-20); i++){
			int x = Index[i];
			validfile << Target_Output[x]<<"\n";
	}
		
	validfile.close();
}
int main(){
	int temp, *number;
	
	Read_Data();
	for(int index =0; index < Data.size(); index++){
		Index.push_back(index);
	}
	random_shuffle(Index.begin(), Index.end());
	// for(int i=0; i<Index.size(); i++){
	// 	// Random_Index.push_back(Index[i]);
	// 	cout<<Index[i]<<"\t";
	// }

	Training_file();
	Testing_file();
	Validation_file();
	Read_Output();
	Train_Out();
	Valid_Out();
	Test_Out();
	
	return 0;
	}