/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Classification.h
 * Author: razak_ajayi
 *
 * Created on 25 October 2016, 19:10
 */

#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <string>
#include <iostream>
#include <stdexcept>

#include "Table.h"

using namespace std;
namespace knearest {

    /**
     * @brief Classify the data table
     * 
     * @since 1.0
     */
    class Classification {
    public:

        /**
         * @brief Constructor of the Classification class
         * @param learningData The name CSV file containing learning data
         * @param learningDataLabels The name of CSV file containing the label
         * @param data The name of CSV file containing the data to be classified
         * @param k A constant integer value
         * 
         * @warning Throws invalid_argument if:
         * @li The number of columns of learningData and data don't match
         * @li The number of rows of learningData and learningDataLabels don't match
         * @li The learningDataLabels doesn't have only one column
         * @li The value of k is greater than the number of rows in learningData
         * @li The value of k is not a positive integer
         * 
         * @since 1.0
         */
        Classification(std::string learning_data, std::string learningdataLabels, std::string data, unsigned int k)throw (invalid_argument);
        /**
         * @brief Destructor of the Classification class
         * 
         * @since 1.0
         */
        virtual ~Classification();
        /**
         * @brief Get accuracy of a classification
         * @param correctDataLabelsThe name of CSV file containing the data to compare and get accuracy
         * @return The accuracy as double
         * 
         * @warning Throws invalid_argument if:
         * @li The correctDataLabels doesn't have only one column
         * @li Both data and correctDataLabels don't have equal number of rows
         * 
         * @since 1.0
         */
        double getAccuracy(std::string correctdataLabels) throw (invalid_argument);
        /**
         * @brief Get euclidean distances for classification
         * 
         * @since 1.0
         */
        void euclidean();

    private:
        /**
         * @brief Pointer to implementation
         * @since 1.0
         */
        class Impl;
        Impl *cImpl;

    };
}
#endif /* CLASSIFICATION_H */
