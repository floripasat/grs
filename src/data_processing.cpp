/*
 * data_processing.cpp
 * 
 * Copyright (C) 2017, Universidade Federal de Santa Catarina
 * 
 * This file is part of FloripaSat-GRS.
 * 
 * FloripaSat-GRS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-GRS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-GRS.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \file data_processing.cpp
 * 
 * \brief Data validation functions implementation.
 * 
 * \author Elder Dominghini Tramontin <elderdtramontin@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 09/10/2017
 * 
 * \addtogroup data_processing
 * \{
 */

#include <iostream>
#include "data_processing.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

#define MAX_COLUNMS 100

DataProcessing::DataProcessing(std::string fileName)
{    
    std::ifstream inputFile;
    std::string line, term;
    double value;
    int j = 0;
    cols = 0;
    rows = 0;
    dataFileName = fileName;

    inputFile.open(fileName.c_str());

    if(std::getline(inputFile, line))
    {
        cols = 1;
    }
    else
    {
        return;
    }

    for (int i = 0; i < line.size(); i++)
        if (line[i] == ',')
            cols++; 

    max   = new double[MAX_COLUNMS];   //maximum value
    min   = new double[MAX_COLUNMS];   //minimum value
    avg   = new double[MAX_COLUNMS];   //average value

    for (int i = 0; i <= line.size(); i++)
    {
        if (line[i] == ',' || line[i] == '\0'){
            std::stringstream temp(term);
            temp >> max[j];
            min[j] = max[j];
            avg[j] = max[j];
            j++;
            term = "";
        }
        else
        {
            term += line[i];
        }        
    }
    rows = 1;    
    

    while(std::getline(inputFile, line))
    {           
        j = 0;  
        for (int i = 0; i <= line.size(); i++)
        {            
            if (line[i] == ',' || line[i] == '\0'){
                std::stringstream temp(term);
                temp >> value;
                if(value < min[j])
                    min[j] = value;
                
                if(value > max[j])
                    max[j] = value;
                
                avg[j] += value;
                j++;
                term = "";
            }
            else
            {
                term += line[i];
            }            
        }
        if(j > cols)
        {
            cols = j;
        }
        
        rows++;
    }

    for (int j = 0; j < cols; j++)
    {
        avg[j] /= rows;
    }   

    inputFile.close();
    //stdev = new double[cols];   //standart deviation
}

DataProcessing::~DataProcessing()
{
    delete max;
    delete min;
    delete avg;
}

double DataProcessing::GetMax(int index)
{
    return max[index-1];
}

double DataProcessing::GetMin(int index)
{
    return min[index-1];
}

double DataProcessing::GetAverage(int index)
{
    return avg[index-1];
}
int DataProcessing::GetColumns(void)
{
    return cols;
}

int DataProcessing::GetRows(void)
{
    return rows;
}

std::string DataProcessing::Validate(std::string fileName)
{
    std::ifstream inputFile;
    std::ifstream validationFile;
    //std::ofstream outputFile;
    std::stringstream outputFile;
    std::string line, term;
    double value;
    double *maxValidation, *minValidation;
    int j,k;
    int fail_count = 0;

    maxValidation = new double[MAX_COLUNMS];
    minValidation = new double[MAX_COLUNMS];

    inputFile.open(dataFileName.c_str());

    validationFile.open(fileName.c_str());

    //std::string outputFileName = fileName.substr(0, fileName.length() - 4) + "_validation.log";
    //outputFile.open(outputFileName.c_str());

    //read the maximum and minimum allowed values
    k = j = 0;
    while(std::getline(validationFile, line))
    {
        for (int i = 0; i <= line.size(); i++)
        {
            if (line[i] == ',')
            {
                std::stringstream temp(term);
                temp >> minValidation[j];
                term = "";
            }
            else
            {
                if (line[i] == '#' || line[i] == '\0')
                {
                    std::stringstream temp(term);
                    temp >> maxValidation[j];
                    j++;
                    term = "";
                    break;
                }

                else
                {
                    term += line[i];
                }        
            }
        }
    }


    outputFile << cols << " data fields.\n";
    outputFile << rows << " data packets.\n";
    outputFile << cols*rows << " values.\n\n";

    /* validation based on max and min
    for (j = 0; j < cols; j++)
    {
        if(maxValidation[j] < max[j])
        {
            outputFile << "\tValue not allowed in the column "<<j+1<<":  \t"<<max[j]<< ".        Max allowed: "<<maxValidation[j]<<"\n";            
            fail_count++;
        }

        if(minValidation[j] > min[j])
        {
            outputFile << "\tValue not allowed in the column "<<j+1<<":  \t"<<min[j]<< ".        Min allowed: "<<minValidation[j]<<"\n";
            fail_count++;
        }
    }
    */
    outputFile << "Values not allowed:\n";

    while(std::getline(inputFile, line))
    {           
        j = 0;  
        for (int i = 0; i <= line.size(); i++)
        {            
            if (line[i] == ',' || line[i] == '\0'){
                std::stringstream temp(term);
                temp >> value;
                if(value < minValidation[j])
                {
                    outputFile << "\trow " << k+1 << ", column " << j+1 << ":\t" << setfill(' ') << setw(12) << value << "\t\tMin. allowed: " << minValidation[j] << "\n";
                    fail_count++;
                }
                
                if(value > maxValidation[j])
                {
                    outputFile << "\trow "<< k+1 << ", column " << j+1 << ":\t" << setfill(' ') << setw(12) << value << "\t\tMax. allowed: " << maxValidation[j] << "\n";            
                    fail_count++;
                }
                j++;
                term = "";
            }
            else
            {
                term += line[i];
            }
            
        }
        k++;
    }

    outputFile << "\nUnexpected values: " << fail_count << "\n";
    outputFile << "Error: " << 100*fail_count / double(cols*rows) << "%\n";

    inputFile.close();
    validationFile.close();
    //outputFile.close();
    
    return outputFile.str();
}
//! \} End of data_processing group implementation
