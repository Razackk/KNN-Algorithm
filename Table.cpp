/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Table.cpp
 * Author: razak_ajayi
 * 
 * Created on 20 October 2016, 17:04
 */
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "Table.h"

using namespace std;
namespace knearest {

    /*
     *Implementation of PIMPL Idiom of Table class
     */
    class Table::Impl {
    public:
        /*2D vector of double*/
        vector<vector<double> > data;
        

        /*
         *round to a precision of four decimal places
         */
        inline double precision(double val) {

            double fourD = pow(10.0, 4);
            val = ceil((val * fourD * 1.0)) / (fourD * 1.0);

            return val;
        }

        /*
         *Gets user's index  for table
         *concealed vector container is zero based
         */
        int getIndex(int index) {
            return index - 1;
        }

        /*
         *converts a given string to its corresponding double
         * in a precision of four decimal places
         */
        double stringToDouble(string strValue) {
            //c str returns a pointer to an array that contains characters
            //represent the value of the string passed to stod;
            double value = stod(strValue.c_str());

            return this->precision(value);
        }

        /*
         *splits strings separated by commas
         *into a vector as double
         */
        void split(string& line, vector<double>& dataRow) {
            double data_Val;
            int pos = 0;
            //string npos(no position) is a constant integral value which
            //is defined to be -1.
            //so far as the line contains a comma, split and
            //store in dataRow vector till there are no more commas.
            while ((pos = line.find_first_of(",")) != string::npos) {
                data_Val = stringToDouble(line.substr(0, pos));
                dataRow.push_back(data_Val);
                line = line.substr(pos + 1);
            }
            //after which there are no more commas, line holds value
            //of the last number in the file
            if (!line.empty()) {
                data_Val = stringToDouble(line);
                dataRow.push_back(data_Val);
            }
        }

        /*
         *Number of the rows in Table
         *Size of data's vector
         */
        unsigned int numRows() {
            if (this->data.size() > 0) {
                return this->data.size();
            } else
                return 0;
        }

        /*
         *Number of the columns in Table
         *Size of first row in data's vector
         */
        unsigned int numCols() {

            if (this->data.size() > 0) {
                return this->data.at(0).size();
            } else
                return 0;
        }

        /*
         *Average of a given column 
         */
        double colAvg(int col_index) {
            col_index = this->getIndex(col_index);

            double sum = 0.0;
            for (int i = 0; i < this->data.size(); i++) {
                sum += this->data.at(i).at(col_index); //sum of a column
            }
            sum /= this->numRows();

            return sum;

        }

        /*
         *Corrected sample standard deviation of a column specified by user
         */
        double correctedColSampleStddev(int col_index) {

            double x, y, z;
            x = 0.0;
            double stddev;
            for (int i = 0; i < this->data.size(); i++) {
                y = this->data.at(i).at(this->getIndex(col_index)) - this->colAvg(col_index);
                x += pow(y, 2); //sum of the difference between each cell value and mean
            }

            z = (1.0 / (this->numRows() - 1)) * x;
            stddev = sqrt(z);

            return stddev;
        }

    };

    Table::Table() {

        mImpl = new Impl();
    }

    Table::~Table() {
        delete mImpl;
    }

    /* populates table with values read from csv file */
    void Table::populate_Table(string filename) throw (invalid_argument) {
        //reads line from file
        ifstream Value(filename.c_str());
        string csvLine;
        //validates that the file can open
        if (!Value) {
            throw invalid_argument("Cannot open file");
        }
        //get line from file
        while (getline(Value, csvLine)) {
            vector <double> myVector;

            mImpl->split(csvLine, myVector);
            mImpl->data.push_back(myVector);
        }
        Value.close();


    }

    /*
     *Get the number of rows in table
     */
    unsigned int Table::getNumOfRows() {

        return mImpl->numRows();
    }

    /*
     *Get the number of columns in table
     */
    unsigned int Table::getNumOfCols() {

        return mImpl->numCols();
    }

    /*
     *Get the average of a column specified by the user
     */
    double Table::getColAvg(int col_index) throw (runtime_error) {
        //checks validity of column 
        //throws error if column index is invalid
        if (col_index > 0 && col_index <= mImpl->numCols()) {
            return mImpl->colAvg(col_index);
        } else {
            throw runtime_error("column value is invalid");
        }

    }

    /*
     *Get corrected sample standard deviation of a column specified by the user
     */
    double Table::getCorrectedColSampleStddev(int col_index)throw (runtime_error) {
        //checks validity of column 
        //throws error if column index is invalid
        if (col_index > 0 && col_index <= mImpl->numCols()) {
            return mImpl->correctedColSampleStddev(col_index);
        } else {
            throw runtime_error("Column value is invalid");
        }

    }

    /*
     *standardize data in table
     */
    void Table::dataStandardization() {
        //modifies data into new values
        //with an average of zero
        double datastd;
        for (int r = 0; r < mImpl->numRows(); r++) {
            for (int c = 0; c < mImpl->numCols(); c++) {
                //column average subtracted from cell value divided by column standard deviation
                datastd = mImpl->data.at(r).at(c) - mImpl->colAvg(c + 1);
                datastd /= mImpl->correctedColSampleStddev(c + 1);
                mImpl->data.at(r).at(c) = datastd;
            }
        }
    }

    /*
     *Get the value of a specific cell in table
     */
    double Table::getValue(int row_index, int col_index)throw (runtime_error) {
        //checks validity of row and column 
        //throws error if column or row  index is invalid
        if (col_index > 0 && col_index <= mImpl->numCols()) {
            if (row_index > 0 && row_index <= mImpl->numRows())
                return mImpl->data.at(mImpl->getIndex(row_index)).at(mImpl->getIndex(col_index));
        } else {
            throw runtime_error("Invalid Parameter");
        }

    }

    /*
     *Change value of a specific cell in table
     */
    void Table::changeVal(int row_index, int col_index, double New_Val)throw (runtime_error) {
        //checks validity of row and column 
        //throws error if column or row  index is invalid
        if (col_index > 0 && col_index <= mImpl->numCols()) {
            if (row_index > 0 && row_index <= mImpl->numRows())
                mImpl->data.at(mImpl->getIndex(row_index)).at(mImpl->getIndex(col_index)) = New_Val;
        } else {
            throw runtime_error("Invalid Parameter");
        }

    }

    /*
     *Remove a specific row from table
     */
    void Table::removeRow(int row_index)throw (runtime_error) {
        //checks validity of row  
        //throws error if row  index is invalid
        if (row_index > 0 && row_index <= mImpl->numRows()) {
            row_index = mImpl->getIndex(row_index);
            mImpl->data.erase(mImpl->data.begin() + row_index);
        } else {
            throw runtime_error("Row value is invalid");
        }

    }

    /*
     *Remove a specific column from table
     */
    void Table::removeCol(int col_index)throw (runtime_error) {
        //checks validity of column  
        //throws error if column  index is invalid
        if (col_index > 0 && col_index <= mImpl->numCols()) {
            col_index = mImpl->getIndex(col_index);
            for (int i = 0; i < mImpl->data.size(); i++) {
                mImpl->data.at(i).erase(mImpl->data.at(i).begin() + col_index);
            }
        } else {
            throw runtime_error("Column value is invalid");
        }

    }

    /*
     *Add a row containing numbers to the table
     */
    void Table::addRow(double *row_val, int size)throw (invalid_argument) {

            vector <double> newRow;
            for (int i = 0; i < size; i++)
                newRow.push_back(row_val[i]);

            //checks validity of row  
            //throws error if row  values are incomplete 
            if (mImpl->numCols() == newRow.size()) {
                
                mImpl->data.push_back(newRow);
            } else {
                throw invalid_argument("Row values must match number of columns in table");
            }
    }

    /**
     * Add a vector containing numbers as row to the table
     */
    void Table::addRow(vector <double> newRow) {
        mImpl->data.push_back(newRow);
    }

    /*
     *Add a column containing numbers to the table
     */
    void Table::addCol(double *col_val, int size)throw (invalid_argument) {
        //check validity that the column size of input 
        //is equal to the number of rows in the table
        if (mImpl->numRows() == size) {
            for (int i = 0; i < mImpl->data.size(); i++) {
                //Add column
                mImpl->data.at(i).push_back(col_val[i]);
            }
        } else {
            //throw error if not equal
            throw invalid_argument("Size must match number of rows in table");
        }

    }

    /*
     *Output the whole content of the table without using cout
     *Overload the insertion operator (<<)
     */
    ostream& operator<<(ostream &stream, Table &t) {
        /*iterator for the row in data*/
        vector<vector<double> >::iterator row;
        /*iterator for the column in data*/
        vector<double>::iterator col;
        for (row = t.mImpl->data.begin(); row != t.mImpl->data.end(); ++row) {
           for (col = (*row).begin(); col != (*row).end(); ++col)
                stream << *col << " ";
                stream << endl;
                
        }

        return stream;
    }

}

