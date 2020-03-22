# **Basic C++ implementation of Backpropagation**

## **Backpropagation.cpp** 
1. Compile Backpropagation.cpp file using the command:
> g++ -std=c++11 Backpropagation.cpp -o obj
2. Run obj executable
> gdb ./obj
    
## **Random_selection.cpp**
  Compile this cpp file to get train, test and validation files.
  
## **Input**
Train_data/Irisdata.txt 
Source: https://archive.ics.uci.edu/ml/datasets/iris
#Label is in separate file 
Train_data/Whole_label.txt

## **Note:** 
- Only first 100 instances are taken from the dataset. i.e Iris Setosa and Iris Versicolour
- Labels can be placed along with Irisdata.txt file

## **Output**
Binary classification: 0 or 1 
- Iris Setosa
- Iris Versicolour
