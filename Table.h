/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Table.h
 * Author: razak_ajayi
 *
 * Created on 20 October 2016, 17:04
 */

#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;
namespace knearest {

    /**
     * @brief Create table from CSV file
     * 
     * @since 1.0
     */
    class Table {
    public:
        /**
         * @brief Constructor of the Table class
         * 
         * @since 1.0
         */
        Table();
        /**
         * @brief Destructor of the Table class
         * 
         * @since 1.0
         */
        ~Table();

        /**
         * @brief Populate table with values from file
         * @param filename The name of the csv file to read from
         * 
         * @warning Throws invalid_argument if
         * @li The file cannot be opened
         * 
         * @since 1.0
         */
        void populate_Table(string filename)throw (invalid_argument);
        /**
         * @brief Get the average of a column specified by the user
         * @param col_index The column of which average would be calculated
         * @return The Column average as double
         * 
         * @warning Throws invalid_argument if
         * @li The column index is incorrect
         * 
         * @since 1.0
         */
        double getColAvg(int col_index)throw (runtime_error);
        /**
         * @brief Get corrected sample standard deviation of a column specified by the user
         * @param col_index The column of which the corrected sample standard deviation would be calculated
         * @return The corrected sample standard deviation as double
         * 
         * @warning Throws runtime_error if
         * @li The column index is incorrect
         * 
         * @since 1.0
         */
        double getCorrectedColSampleStddev(int col_index)throw (runtime_error);
        /**
         * @brief Get the number of rows in table
         * @return The number of rows as unsigned integer
         * 
         * @since 1.0
         */
        unsigned int getNumOfRows();
        /**
         * @brief Get the number of columns in table
         * @return The number of columns as unsigned integer
         * 
         * @since 1.0
         */
        unsigned int getNumOfCols();
        /**
         * @brief Get the value of a specific cell in table
         * @param row_index The row number of the cell 
         * @param col_index The column number of the cell 
         * @return The specific value as double
         * 
         * @warning Throws runtime_error if
         * @li The column index is incorrect
         * @li The row index is incorrect
         * 
         * @since 1.0
         */
        double getValue(int row_index, int col_index)throw (runtime_error);
        /**
         * @brief Change value of a specific cell in table
         * @param row_index The row number of the specific cell 
         * @param col_index The column number of the specific cell 
         * @param New_Val The new value for the cell 
         * 
         * @warning Throws runtime_error if
         * @li The column index is incorrect
         * @li The row index is incorrect
         * 
         * @since 1.0
         */
        void changeVal(int row_index, int col_index, double New_Val)throw (runtime_error);
        /**
         * @brief standardization of data in table
         * @since 1.0 
         */
        void dataStandardization();
        /**
         * @brief Remove a specific row from table
         * @param row_index The row which is to be removed
         * 
         * @warning Throws runtime_error if
         * @li The row index is incorrect
         * 
         * @since 1.0
         */
        void removeRow(int row_index)throw (runtime_error);
        /**
         * @brief Remove a specific column from table
         * @param col_index The column which is to be removed
         * 
         * @warning Throws runtime_error if
         * @li The column index is incorrect
         * 
         * @since 1.0
         */
        void removeCol(int col_index)throw (runtime_error);
        /**
         * @brief Add a row containing numbers to the table
         * @param row_val The values for the new row 
         * @param size The size of array of double
         * 
         * @warning Throws invalid_argument if
         * @li The row values does not match number of columns in table
         * 
         * @since 1.0
         */
        void addRow(double *row_val, int size)throw (invalid_argument);
        /**
         * @brief Add a vector containing numbers as row to the table
         * @param newRow The vector containing the new rows
         * @since 1.0
         */
        void addRow(vector <double> newRow);
        /**
         * @brief add a column containing numbers to the table
         * @param col_val The values for the new column
         * @param size The size of array of double
         * 
         * @warning Throws invalid_argument if
         * @li The column size does not match number of rows in table
         * 
         * @since 1.0
         */
        void addCol(double *col_val, int size)throw (invalid_argument);
        /** 
         *@brief Output the whole content of the table without using cout
         * Overloading the insertion operator (<<)
         * @since 1.0
         */
        friend ostream& operator<<(ostream &stream, Table &t);

    private:
        /**
         * @brief Pointer to implementation
         * @since 1.0
         */
        class Impl;
        Impl *mImpl;
        
    };
}


#endif /* TABLE_H */

