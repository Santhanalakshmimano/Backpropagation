#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <climits>
#include <tuple>
using namespace std;

vector<vector<double>>Data ;
vector<vector<int>>class_Target_Output;
// vector<int>class_Target_Output;

vector<double **>weights;
vector<vector<double>>Each_Layer_input;
vector<double>Layer_input;
vector<int>Target_Output;

void Read_data(){
	ifstream ifs("Irisdata.txt");
	string line;
	double in;
	char ch;
	
	//pushing dataset into Vector 
	while (getline(ifs, line)) 
	{
		vector<double> data_store;
		stringstream iss(line);
		//cout<< "line "<< line << endl;
		while (iss >> in)
		{ 
			//cout<< in << "  ";
			data_store.push_back(in);
			iss >> ch;
		}

		Data.push_back(data_store);

	}
}
void Read_class_Target_Data(){
	ifstream ifs("Output.txt");
	string line;
	double in;
	
	//pushing dataset into Vector Data
	while (getline(ifs, line)) 
	{
		vector<int> data;
		stringstream iss(line);
		//cout<< "line "<< line << endl;
		while (iss >> in)
		{ 
			//cout<< in << "  ";
			data.push_back(in);
		}

		class_Target_Output.push_back(data);
	}
}
void Read_Target_Data(){
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
void Print_Dataset(){
	cout<<"rows : "<< Data.size()<<endl;
	// for(int i=0; i<Data.size();  i++){
	// 	cout<<"cols : "<< Data[i].size()<<endl;
	// 	for(int j=0; j<Data[0].size(); j++){
	// 		cout<<"\t"<<Data[i][j];
	// 	}
	// 	cout<<endl;
	// }
}
void Print_Target_Data(){
	for(int i=0; i<Target_Output.size();  i++){
		cout<<"\t"<<Target_Output[i];
	}
}
void weight(int layers, vector<int> &nodes){
	double **matrix;
	int x, y;
	for(int i=0; i<layers; i++){
		x = nodes[i];
		y = nodes[i+1];
		matrix = (double **)malloc(x * sizeof(double *));
		for(int j=0; j<x; j++){
			matrix[j] = (double*)malloc(y * sizeof(double));
		}
		for(int k=0; k<x; k++){
			for(int l=0; l<y; l++){
				matrix[k][l] = (double)rand()/(double)RAND_MAX;
			}
		}
		cout<<"The initial weight elements are"<<endl;
		for(int a=0; a<x; a++){
			for(int b=0; b<y; b++){
				cout<<"\t"<<matrix[a][b];
			}
			cout<<endl;
		}
	 	weights.push_back(matrix);
	 	//free(matrix);
	 	
	}

}

//Forward propagation
vector<double> calculate(int layers, vector<int> &nodes, vector<double> &p){
	int x,y;
	double sum,bias, *softmax_element, individual_exponential;
	vector<double>softmax;
	for(int i=0; i<layers; i++){
		x = nodes[i];
		y = nodes[i+1];
		double sum_of_exponential=0;
		softmax_element = (double*)malloc(y * sizeof(double));
		bias = (double)rand()/(double)RAND_MAX;
		cout<<"Bias is "<<bias<<endl;
		for(int j=0; j<y; j++){
			sum = 0;
			for(int k=0; k<x; k++){
				sum += p[k] * weights[i][k][j];
			}
			sum = sum + bias;
			individual_exponential = exp(sum);
			sum_of_exponential += individual_exponential;
			softmax.push_back(individual_exponential);
			//cout<<"The sigmoid of "<<j<<" "<<sigmoid[j]<<endl;
			//Layer_input.push_back(sigmoid[j]);
		}
		// for(int g=0; g<softmax.size(); g++){
		// 	sum_of_exponential += softmax[g];
		// }
		for(int h=0; h<softmax.size(); h++){
			softmax_element[h] = (softmax[h] / sum_of_exponential);
			Layer_input.push_back(softmax_element[h]);
		}
		Each_Layer_input.push_back(Layer_input);
		softmax.clear();
		Layer_input.clear();
		p.clear();
		for(int l=0; l<y; l++){
			p.push_back(softmax_element[l]);
		}
	}
	// cout<<"The output elements are"<<endl;
	// for(int i=0; i<p.size(); i++){
	// 	cout<<"\t"<<p[i];
	// }
	return p;
}

double sum;
tuple<double,double> Update_Output_weight(int layers, vector<int> &nodes, vector<double> &p, int n){
			
			double TotalError = 0, Update_weight, learning_rate = 0.5,deltaoutput,sum=0;
			int index = layers - 1;
			// int x = nodes.size()-1;
			// x = nodes[x];
			int y = nodes.size()-2;
			y = nodes[y];
			//Updating weights (Output layer)
			for(int j=0; j<p.size(); j++){
					deltaoutput = p[j] * (1 - p[j]) * (class_Target_Output[n][j] - p[j]); //error value of each neuron
					TotalError += pow((class_Target_Output[n][j] - p[j]), 2); 
				
				// for(int k=0; k<x; k++){
					for(int l=0; l<y; l++){
						Update_weight = learning_rate * deltaoutput * p[j];
						weights[index][l][j] += Update_weight;
						sum += weights[index][l][j] * deltaoutput;
					}
					
				// }
			}
			//cout<<"Total Error is   "<<(TotalError/2)<<endl;
			//cout<<"The summation of weights is    "<<sum<<endl;
			return make_tuple((TotalError/2), sum);
}

void Update_Hidden_weight(int layers, vector<double> &p, vector<int> &nodes, double sum_of_weights){
			int y;
			double Update_weight, learning_rate = 0.5,deltaerror, ssum=0;
			//cout <<"\n"<<"The layer value is "<<layers<<endl;
			y = nodes[layers];
			//cout<<"Y value "<<y<<endl;
			for(int j=0; j<p.size(); j++){
				deltaerror = p[j] * (1-p[j]) * sum_of_weights; //error value 
				//cout<<" The value of sum in hidden is    "<<sum_of_weights<<endl;
				for(int k=0; k<y; k++){
					Update_weight = learning_rate * deltaerror * p[j];
					weights[layers][k][j] += Update_weight;
					ssum += weights[layers][k][j] * deltaerror;
				}
				//cout<<"ssum is    "<<ssum<<endl;	
			}
			sum_of_weights = ssum;				//for proceeding to next layer
}

void Updated_weight_matrix(int layers, vector<int> &nodes){
	int x, y;
	for(int i=0; i<layers; i++){
		x = nodes[i];
		y = nodes[i+1];
		cout<<"\n";
		cout<<"The updated weight elements are "<<"\n";
		for(int j=0; j<x; j++){
			for(int k=0; k<y; k++){
				cout<<"\t"<<weights[i][j][k];
			}
			cout<<endl;
		}
	}
}

void Train(){

	
	int x,y,count =0;
	double sum_of_weights,Error,initial_error = 1;
	vector<double>Output_Layer;
	vector<int>v;
	v.push_back(Data[0].size()); 		//no.of nodes in input layer
	v.push_back(3); 					//no.of nodes in hidden layer
	v.push_back(2);						//no.of nodes in output layer
	// for(int i=0; i<v.size(); i++){
	// 	cout<<"\t"<<v[i];
	// }
	int layers = v.size()-1;					// layers - no.of layers - excluding input layer				
	weight(layers, v);	
	vector<double>input;
	// int p=1;
	// while(1){
		cout<<"Initial error is    "<<initial_error<<endl;
		cout<<"\n";
		// cout<<"Iteration number: "<<p<<endl;
		for(int i=0; i<Data.size(); i++){
			for(int j=0; j<Data[0].size(); j++){
				input.push_back(Data[i][j]);
			}
			// Each_Layer_input.push_back(input);
			Output_Layer = calculate(layers, v, input);
			
			tie(Error,sum_of_weights) = Update_Output_weight(layers, v, Output_Layer, Target_Output[i]);
			vector<int> Value;
			for(int h=0; h<Output_Layer.size(); h++){
				cout<<"The Output is  "<<Output_Layer[h]<<"\t";
				if(Output_Layer[h] < 0.5){
					Value.push_back(0);
				}
				else{
					Value.push_back(1);
				}
			}
			for(int a=0; a<class_Target_Output.size(); a++){
				if(class_Target_Output[a] == Value){
					cout<<"The label is  "<<a<<"\t";
				}
			}
			Value.clear();
			cout<<"Error  "<<Error<<"\t"<<"Target Output is   "<<Target_Output[i]<<endl;
				//cout<<"Total Error is "<< (initial_error - Error)<<endl;
				vector<double> hid;
				for(int k=Each_Layer_input.size()-2; k>=0; k--){
					for(int l=0; l<Each_Layer_input[k].size(); l++){
					 	hid.push_back(Each_Layer_input[k][l]);
					}
					 	Update_Hidden_weight(k, hid, v, sum_of_weights);
					 	hid.clear();
				}
				
				if(Error < 0.2){
					Updated_weight_matrix(layers, v);
					break;
				}
				input.clear();
				Each_Layer_input.clear();

			//}
			
		}
		// cout<<"Initial Error  "<<initial_error<<endl;
		// if(p > 10 && (initial_error - Error) < 0.5){
		// 	count++;
		// }
		// else{
		// 	count =0;
		// }

		// if(count >= 20){
		// 	cout<<"Error difference is   "<<(initial_error - Error)<<endl;
		// 	cout<<"Final Error is   "<<Error<<endl;
		// 	exit(0);
		// }
		// initial_error = Error;
		// p++;
	// }	
}

int main(){
	
	
	Read_data();
	Read_class_Target_Data();
	Read_Target_Data();
	cout<<"Dataset are"<<endl;
	Print_Dataset();
	cout<<"Target data"<<endl;
	Print_Target_Data(); 
	cout<<endl;
	Train();
		// cout<<"The input of each layer are";
		// for(int i=0; i<Each_Layer_input.size(); i++){
		// 	for(int j=0; j<Each_Layer_input[i].size(); j++){
		// 		cout<<"\t"<<Each_Layer_input[i][j];
		// 	}
		// 	cout<<endl;
		// }
	
	

	 return 0;

}

