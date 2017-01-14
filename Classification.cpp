
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Classification.cpp
 * Author: razak_ajayi
 * 
 * Created on 25 October 2016, 19:10
 */

#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <random>



#include "Classification.h"

using namespace std;
namespace knearest {

    /*
     *Implementation of PIMPL Idiom of Classification class
     */
    class Classification::Impl {
    public:
        Table learningData, learningDataLabels, data, dataLabels, correctDataLabels;
        unsigned int k;

    };

    Classification::Classification(string learning_data, string learningdataLabels, string data, unsigned int k) throw (invalid_argument) {

        cImpl = new Impl();
        // populate the table learning data with values read from csv file
        cImpl->learningData.populate_Table(learning_data);
        // populate the table learning data labels with values read from csv file
        cImpl->learningDataLabels.populate_Table(learningdataLabels);
        // populate the table data  with values read from csv file
        cImpl->data.populate_Table(data);
        // Get value of k
        cImpl->k = k;

        // check validity that columns of learningData and data match
        if (cImpl->learningData.getNumOfCols() != cImpl->data.getNumOfCols())
            throw invalid_argument("The number of columns of learningData and data must match");

        // check validity that number of rows of learningData and data match
        if (cImpl->learningData.getNumOfRows() != cImpl->learningDataLabels.getNumOfRows())
            throw invalid_argument("The number of rows of learningData and learning data labels must match");

        // check validity that learningDataLabels has only one column
        if (cImpl->learningDataLabels.getNumOfCols() != 1)
            throw invalid_argument("The learningDataLabels must have only one column");
        
        // check validity that value of k is not larger than the number of rows in learningData
        if (cImpl->k > cImpl->learningData.getNumOfRows())
            throw invalid_argument("The value of k cannot be larger than the number of rows in learningData");



    }

    Classification::~Classification() {
        delete cImpl;
    }

    /*
     * Get euclidean distance for classification
     */
    void Classification::euclidean() {

        vector<double>frequency;
        vector<int>labels;
        vector<double> eDistances;
        double sub;
        double distance = 0.0;

        int mode;
        int counter;
        // Calculate the Euclidean distances between each row of table data
        // and all rows of table learning data
        for (unsigned int x = 1; x <= cImpl->data.getNumOfRows(); x++) {
            map<double, int> my_map;
            map<double, int> ::iterator it;
            for (unsigned int p = 1; p <= cImpl->learningData.getNumOfRows(); p++) {
                // Calculate the difference between column y of table data 
                // and table learning data
                for (unsigned int y = 1; y <= cImpl->learningData.getNumOfCols(); y++) {
                    sub = cImpl->data.getValue(x, y) - cImpl->learningData.getValue(p, y);
                    distance += pow(sub, 2.0);
                }
                eDistances.push_back(sqrt(distance));
                distance = 0.0;
            }
            // Pair each distance with their matching learning data Label
            for (unsigned int j = 1; j <= cImpl->learningDataLabels.getNumOfRows(); j++)
                my_map.insert(pair<double, int>(eDistances.at(j - 1), cImpl->learningDataLabels.getValue(j, 1)));
            //sort the distances in ascending order
            sort(eDistances.begin(), eDistances.end());
            // Get the K lowest value of distances
            eDistances.resize(cImpl->k);

            // Find the k distance in the map and store the
            // matching learning data labels in vector labels
            for (int i = 0; i < eDistances.size(); i++) {
                double m = eDistances.at(i);
                it = my_map.find(m);
                if (it != my_map.end()) {
                    labels.push_back(it->second);
                }
            }
            // Get label with the highest frequency 
            int max = 0;
            for (int n = 0; n < labels.size(); n++) {
                int count = 0;
                for (int m = n; m < labels.size(); m++) {
                    if (labels.at(n) == labels.at(m)) {
                        count++;
                    }
                }
                // If label have equal frequency 
                // store in vector frequency
                if (count == max) {
                    frequency.push_back(labels.at(n));
                } else if (count > max) {
                    max = count;
                    frequency.clear();
                    mode = labels.at(n);
                    frequency.push_back(mode);
                }
                // If labels with equal frequency are greater 
                // Than one, select one at random
                if (frequency.size() > 1) {
                    random_device rd;
                    int randVal = rd();
                    if (randVal % 2 != 0) {
                        mode = labels.at(n);
                    }
                    frequency.clear();
                    frequency.push_back(mode);
                }

            }
            cImpl->dataLabels.addRow(frequency);

            labels.clear();
            eDistances.clear();
        }

    }

    /**
     * Get accuracy of a classification
     */
    double Classification::getAccuracy(string correctdataLabels) throw (invalid_argument) {
        // populate the table correct data labels with values read from csv file
        cImpl->correctDataLabels.populate_Table(correctdataLabels);

        // check validity that correctDataLabels has only one column
        if (cImpl->correctDataLabels.getNumOfCols() != 1)
            throw invalid_argument("The correctDataLabels must have only one column");
        // check validity that both learningDataLabels and correctDataLabels have equal number of rows
        if (cImpl->data.getNumOfRows() != cImpl->correctDataLabels.getNumOfRows())
            throw invalid_argument("Both data and correctDataLabels must have equal number of rows");

        double equal = 0.0;
        for (int i = 1; i <= cImpl->dataLabels.getNumOfRows(); i++) {
            if (cImpl->dataLabels.getValue(i, 1) == cImpl->correctDataLabels.getValue(i, 1))
                equal += 1.0;
        }

        double accuracy = (equal / cImpl->dataLabels.getNumOfRows()) * 100;

        return accuracy;
    }

}