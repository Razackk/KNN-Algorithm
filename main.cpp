/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: razak_ajayi
 *
 * Created on 19 October 2016, 13:37
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <exception>
#include <algorithm>

#include "Classification.h"
//#include "Classification_Ref.h"
#include "Table.h"
using namespace std;
using namespace knearest;

/*
 * 
 */
int main() {
    //Table class test
    Table *tab;
    tab = new Table();
    tab->populate_Table("Learning_Data.csv");
   try{ 

   /*
    cout << *tab;
    cout << "Number of rows: " << tab->getNumOfRows() << "\n";
    cout << "Number of columns: " << tab->getNumOfCols() << "\n";
    cout << "Column Average: " << tab->getColAvg(1) << "\n";
    cout << "standard deviation: " << tab->getCorrectedColSampleStddev(1) << "\n";
    tab->dataStandardization();
    
    cout << "Value: " << tab->getValue(2, 3) << "\n";
    tab->changeVal(1, 3, 0.0558888);
    tab->removeRow(5);
    tab->removeCol(2);
    
    double input[] = {0.002, 0.034, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343,0.2343, 0.3243, 0.34343, 0.24242};
    int inputsize = sizeof (input) / sizeof (input[0]);
    tab->addRow(input, inputsize);
    
    double values[] = {0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.23437, 0.3248, 0.34340, 
        0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.2343, 0.3243, 0.34343, 0.24242,
        0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.2343, 0.3243, 0.34343, 0.24242,
        0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.2343, 0.3243, 0.34343, 0.24242,
        0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.2343, 0.3243, 0.34343, 0.24242,
        0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.2343, 0.3243, 0.34343, 0.24242,
        0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.2343, 0.3243, 0.34343, 0.24242,
        0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.2343, 0.3243, 0.34343, 0.24242,
        0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.2343, 0.3243, 0.34343, 0.24242,
        0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.2343, 0.3243, 0.34343, 0.24242,
        0.002, 0.035, 0.8273, 0.2242, 0.2232, 0.2445, 0.1324, 0.4343, 0.1343, 0.2343, 0.3243, 0.24247, 0.34343};
    int valSize = sizeof (values) / sizeof (values[0]);
    tab->addCol(values, valSize);
    */
    //Classification class test
    //Classification cat("Learning_Data.csv", "Learning_Data_Labels.csv", "Data.csv", -1 );
    //cat.euclidean();
    //cout << "Accuracy: " << cat.getAccuracy("Correct_Data_Labels.csv") << "%";
    
    //Distance selection test
    //Classification_Ref cat("Learning_Data.csv", "Learning_Data_Labels.csv", "Data.csv", 4);
    //cout<<cat.selection("manhattan", "Correct_Data_Labels.csv")<<"%";
    
    delete tab;
    return 0;
}catch(invalid_argument e){
    cerr<<e.what();
}
   catch(runtime_error e){
    cerr<<e.what();
}
    
}


