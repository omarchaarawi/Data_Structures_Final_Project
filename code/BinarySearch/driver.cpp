#include <iostream>
#include <string>
#include <fstream>
#include "IdTree.hpp"
#include <sstream>
#include <chrono>
#include <cstdlib>


using namespace std;

int* readData(string filename);

int main (int argc, char* argv[]){
    if(argc != 2) {
        cout << "Please include a data_in file" << endl;
        return 1;
    }

    string DATAFILE = argv[1];

    // Binary Search Tree
    IdTree Tree;  // initialize a BST
    float insert[400] = {};  // array for time cost averages in microseconds of insert
    float search[400] = {}; // array for time coast in averages in microseconds of search
    int* testData = readData(DATAFILE);  // reads the data into an array 
    int index = 0;
    for (int i = 0; i < 400; i++ ){
        // first let's time insertion
        auto start = chrono::high_resolution_clock::now();  // get start time
        // ios_base::sync_with_stdio(false);
        for (int j = 0; j < 100; j++){
            Tree.addNode(testData[index]);  // add tracking IDs 100 at a time
            index++;
        }
        auto stop = chrono::high_resolution_clock::now();  // get end time
        auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
        float timeTaken = duration.count()*1e-3;  // get timeTaken in microseconds
        insert[i] = timeTaken/100; // add average time taken for insertion of 100 tracking IDs
        
        // next let's time search
        // use the same method as in timing insertion
        start = chrono::high_resolution_clock::now();
        // ios_base::sync_with_stdio(false);
        for (int j = 0; j < 100; j++){
            int ind = rand() % ((i + 1) * 100); // generate a random number between 0 and i+1*100
            Tree.search(testData[ind]);
        }
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
        timeTaken = duration.count()*1e-3;
        search[i] = timeTaken/100;
    }


    delete [] testData;  // delete array when finished with it

    // read data into a csv file
    for(int i = 0; i < 4; ++i)
        DATAFILE.pop_back(); // drop ".csv" from file being read
    ofstream outFile("insert_search_performance_BST_" + DATAFILE + ".csv");
    outFile << "Iteration,Avg insertion times,Avg search times\n";
    for (int i = 0; i < 400; ++i){
        outFile << i << "," << insert[i] << "," << search[i] << "," << "\n";
    }
    outFile.close();
    return 0;
}

// reads the data into an array on the heap
// don't forget to delete the array when finished with it
int* readData(string filename){
    int index = 0;
    int* testData = new int[40000];
    // read the csv file and grab each serial number
    ifstream trackingIDs(filename);
    if(!trackingIDs.is_open()){
        cerr << "Could not open " << filename << endl;
        return NULL;
    }
    else{
        string line, ID;
        while(getline(trackingIDs, line)){
            stringstream x(line);
            while(getline(x, ID, ',')){
                int key = stoi(ID);
                testData[index] = key;
                index++;
            }
        }
    }
    trackingIDs.close();
    return testData;
}
