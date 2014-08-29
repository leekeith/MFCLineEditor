// LineGraphEditor.h
// Model:		Program parses CSV file and creates a table of values
//				Modified table of values is saved back to the CSV file 
//
// View:		The table of values is displayed to the user as a line graph
//				The line graph actively reflects changes to data
//				The numerical data is displayed in editable databoxes
//
// Controller:	The user can manipulate the databoxes within the window
//				The user can save the current file
#pragma once
#include "stdafx.h"

#include "resource.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;
//****************Data*Model*********************************//
// The following classes are used to model the information   //
//contained in a CSV file.  This flexible platform allows    //
//for tables of various sizes where the first two entries of //
//row 1 are the X and Y labels.  the remaining labels can be //
//blank                                                      //
/*************************************************************/

//DataPoint class: Represents a row of data in the CSV
class DataPoint
{
private:
	//Each value in this vector is a cell in the row
	vector<float> elements;
protected:
	int n_elements;
public:
	//Constructors
	DataPoint();
	DataPoint(int n_elements, float* elements);
	//Setters
	virtual void addElement(float value);
	virtual void setElement(int index, float value);
	//Getters
	virtual float getElement(int index);
	int numElements();
	void clear();
};

//Special subclass of DataPoint.
//Holds Row of strings to use as labels
class Headings : public DataPoint
{
private:
	vector<string> elements;
public:
	//Constructors
	Headings();
	Headings(int n_elements, string* elements);
	//Setters
	void addElement(string value);
	void setElement(int index, string vaule);
	//Getters
	string getHeading(int index);
};

//Table class
//stores and maintains the values from the CSV files
//Updates the file
class Table
{
private:
	string path;
	Headings heads;
	vector<DataPoint> data;
	bool valid;
public:
	//Constructors
	Table();
	Table(string path);
	bool initialize(string path);
	//Validator
	bool isValidTable();
	//File Manipulation
	bool loadTable();
	bool saveTable();
	//Setters
	void addDataPoint(DataPoint data);
	void setDataPoint(int index, DataPoint data);
	//Getters
	DataPoint getDataPoint(int index);
	string getHeading(int index);
	int numElements();
	int numPoints();
	string getPath();
};