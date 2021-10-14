#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int keyGen(string line, int C, int p);

int main (int argc , char *argv[])
{
  // initialize features
  bool queryMode = (argc == 4);
  int inputSize = 0;
  int inputWordsCnt = 0;
  int primaryArrSize = 0;
  int maxCollision =0;
  int hashSize[21] = {0};
  int popularKey = 0;
  string pFileName = argv[1];
  string dFileName = argv[2];
  if(queryMode){
    string qFilename = argv[3];
  }

  // load figures
  string line; //temp reading string
  ifstream parameterFile(pFileName);
  getline(parameterFile,line);
  const int p = stoi(line);
  primaryArrSize = p;
  getline(parameterFile,line);
  const int C = stoi(line);
  //cout<<p<<"  "<<C;
  parameterFile.close();

  // first pass
  int chainSize[p] = {0};
  int tempKey = -1;
  ifstream dataFile(dFileName);
  while(getline(dataFile,line)){
    tempKey = keyGen(line, C, p);
    //cout<<tempKey; 
    chainSize[tempKey]++;
    inputSize++;
  }
  dataFile.close();

  //generating array according to chainsize
  string* primaryArr[p];
  maxCollision = chainSize[0];
  for(int i = 0; i < p; i++){
    if(chainSize[i] > maxCollision){
      maxCollision = chainSize[i];
    }
    string* tempPtr = new string[chainSize[i]]();
    primaryArr[i] = tempPtr;
  }
  if(maxCollision > 0){
    maxCollision--;
  }
  

  // second pass
  int tempKey2 = -1;
  ifstream dataFile2(dFileName);
  while(getline(dataFile2,line)){
    tempKey2 = keyGen(line, C, p);
    //cout<<tempKey; 
    int tempPosition = 0;
    bool duplicate = false;
    while(primaryArr[tempKey2][tempPosition] != ""){
      if(primaryArr[tempKey2][tempPosition] == line){
        duplicate = true;
        chainSize[tempKey2]--;
        break;
      }
      tempPosition++;
      
    }
    if(duplicate){
        duplicate = false;
        continue;
    }else{
      primaryArr[tempKey2][tempPosition] = line;
      inputWordsCnt++;
    }
  }
  dataFile2.close();

  // iterate through the table and collect buckets information
  int popularKeySize = chainSize[0];
  for(int i = 0; i < p; i ++){
    if(chainSize[i] <= 20){
      hashSize[chainSize[i]]++;
    }
    if(chainSize[i] > popularKeySize){
      popularKeySize = chainSize[i];
      popularKey = i;
    }
  }

  //print results
  
  cout<<"Size of input: "<<inputSize<<endl;
  cout<<"Number of words in table: "<<inputWordsCnt<<endl;
  cout<<"Primary array size: "<<primaryArrSize<<endl;
  cout<<"Maximum number of collisions in a hashbucket: "<<maxCollision<<endl;

  cout<<"The number of hashbuckets b with x elements:"<<endl;
  for(int i = 0; i < 21; i++){
    cout<<"x="<<i<<" : b="<<hashSize[i]<<endl;
  }
  cout<<"Keys in most populated bucket:";
  for(int i = 0; i < popularKeySize; i++){
    cout<<" "<<primaryArr[popularKey][i];
  }
  cout<<endl;

  cout<<"Queries"<<endl;
  if(queryMode){
    string qFilename  = argv[3];
    ifstream queryFile(qFilename);
    while(getline(queryFile,line)){
      int key = keyGen(line,C,p);
      bool foundFlag = false;
      for(int i = 0; i < chainSize[key]; i++){
        if(primaryArr[key][i] == line){
          cout<<"Key \""<<line<<"\" exists at ("<<key<<", "<<i<<")."<<endl;
          foundFlag = true;
        }
      }
      if(!foundFlag){
        cout<<"Key \""<<line<<"\" does not exist."<<endl;
      }
    }
  }
}




int keyGen(string line, int C, int p){
  //cout<<p<<"  "<<C<<"  "<<line<<endl;
  int len = line.length();
  int d[len];
  for(int i = 0; i < len; i++){
    d[i] = int(line[i]);
    //cout<<d[i]<<"  ";
  }
  //cout<<endl;
  int k = len - 1;
  int recB = d[k];
  while(k > 0){
    recB = recB % p;
    recB = (recB * C) % p;
    recB = recB + d[k-1] % p;
    recB = recB % p;
    k = k - 1;
  }

  //cout<<"final:  "<<recB<<endl;
  return recB % p;
}
