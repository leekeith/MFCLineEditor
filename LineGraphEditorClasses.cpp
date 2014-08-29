#include "stdafx.h"
#include "LineGraphEditor.h"
#include <sstream>


//********************DataPoint Class***************//

//Default constructor
DataPoint::DataPoint()
{
	n_elements=0;
}

//Constructor:
//INPUT: An array of floats of size n_elements
//OUTPUT: New DataPoint
DataPoint::DataPoint(int n_elements, float* elements)
{
	this->n_elements=n_elements;
	for(int i=0;i<n_elements;i++)
	{
		this->elements.push_back(elements[i]);
	}
}


//addElement
//INPUT: a float value to add to the DataPoint
//MODIFIES: n_elements, elements<float> vector

void DataPoint::addElement(float value)
{
	this->n_elements++;
	this->elements.push_back(value);
}


//getElement
//INPUT: Index of desired element
//OUTPUT: value of desired element
float DataPoint::getElement(int index)
{
	if(index<this->n_elements)
		return this->elements[index];
	else return 0.0;
}

//setElement
//INPUT: Index of element to modify and new value
//MODIFIES: elements[index] value
void DataPoint::setElement(int index, float value)
{
	if(index<this->n_elements)
		this->elements[index]=value;
}

//numElements
//OUTPUT: Number of elements added to DataPoint
int DataPoint::numElements()
{
	return n_elements;
}

//clear
//MODIFIES: n_elements and elements
//Resets datapoint to empty
void DataPoint::clear()
{
	this->n_elements=0;
	this->elements.clear();
}

//********************Headings Class***************//

//Default constructor
Headings::Headings()
{
	DataPoint();
}

//Constructor
//INPUT: Array of strings of size n_elements
//OUTPUT: new Headings object
Headings::Headings(int n_elements, string* elements)
{
	this->n_elements=n_elements;
	for(int i=0;i<n_elements;i++)
		this->elements.push_back(elements[i]);
}

//addElement
//Overrides DataPoint::addElement to accept strings
void Headings::addElement(string value)
{
	this->n_elements++;
	this->elements.push_back(value);
}

//getHeading
//Replaces DataPoint::getElement, returning string value
string Headings::getHeading(int index)
{
	if(index<this->n_elements)
		return this->elements[index];
	else return NULL;
}

//setElement
//Overrides DataPoint::setElement to accept strings
void Headings::setElement(int index, string value)
{
	if(index<this->n_elements)
		this->elements[index]=value;
}


//********************Table Class***************//

//Default constructor
Table::Table()
{
	valid=false;
}
//Constructor
//INPUT: The path and filename of the CSV file to parse
//OUTPUT:  Fully populated Table of values
Table::Table(string path)
{
	this->path=path;
	if(bool value=this->loadTable())
		valid=true;
	else valid=false;
	
}

//initialize
//INPUT: Path and filename of CSV file to parse
//OUTPUT: Returns TRUE if file opens and FALSE otherwise
//MODIFIES: this->path
bool Table::initialize(string path)
{
	this->path=path;
	if(this->loadTable())
		valid=true;
	else valid=false;
	return valid;
}
//loadTable
//OUTPUT: Returns true if file opens and FALSE otherwise
//MODIFIES: this->data<DataPoint> && this ->heads<Headings>
bool Table::loadTable()
{
	fstream file;
	string buffer,elem;
	DataPoint* dp;
	float* vals;
	int ne;
	this->data.clear();
	this->heads.clear();
	//Open file read-only
	file.open(path,ios::in);
	if(file.is_open())
	{
		//Get Headings
		getline(file,buffer);
		stringstream ss(buffer);
		//Parse for all comma-separated values
		while(getline(ss,elem,','))
			this->heads.addElement(elem);
		ne=this->heads.numElements();
		vals=(float*)malloc(sizeof(float)*ne);
		//Get Data
		while(!file.eof())
		{
			//Parse each row of doc
			getline(file,buffer);
			ss.str(buffer);
			ss.clear();
			ss.seekg(0,ios::beg);
			for(int i=0;i<ne;i++)
			{
				//Get Each value from row
				getline(ss,elem,',');
				vals[i]=atof(elem.c_str());
			}
			//Insert row of values into blank dp
			dp=new DataPoint(ne,vals);
			//add dp to Table
			this->addDataPoint(*dp);
			delete dp;
		}
		file.close();
		return true;
	}
	else return false;
}

//saveTable
//OUTPUT: Returns TRUE if file opens for writing, false otherwise
//MODIFIES: The file located at this->path
bool Table::saveTable()
{
	fstream file;
	string line,buffer;
	int i,j;
	int ne=heads.numElements();
	//Open file for overwrite
	file.open(this->path,ios::out|ios::trunc);
	if(file.is_open())
	{
		file.clear();
		file.seekg(0,file.beg);
		//Insert all headings in first row of file
		for(i=0;i<ne-1;i++)
			file<<heads.getHeading(i)<<",";
		file<<heads.getHeading(ne-1)<<"\n";
		
		//Add datapoints to the file
		for(i=0;i<this->numPoints();i++)
		{
			for(j=0;j<ne-1;j++)
				file<<this->data[i].getElement(j)<<",";
			file<<this->data[i].getElement(ne-1)<<"\n";
		}
		
		file.close();
		return true;
	}
	else return false;
}


//addDataPoint
//INPUT: DataPoint object
//MODIFIES: this->data<DataPoint>
void Table::addDataPoint(DataPoint data)
{
	int j;
	int i=0;
	if(this->data.size()>0)
	{

		//Insert Element in order by X-Value
		while(i<this->data.size() && data.getElement(0)>this->data[i].getElement(0) )
			i++;

		if(i<this->data.size())
		{
			if(data.getElement(0)==this->data[i].getElement(0))
			{
				//Replace if X-Value exists
				for(j=1;j<data.numElements();j++)
				{
					this->data[i].setElement(j,data.getElement(j));
				}
			}
			else
			{
				//Shift tail back by 1
				this->data.push_back(this->data[this->data.size()-1]);
				for(j=this->data.size()-2;j>i;j--)
				{
					this->data[j+1]=this->data[j];
				}
				this->data[i]=data;
			}
		}
		else this->data.push_back(data);
	}
	else this->data.push_back(data);
}

//getDataPoint
//INPUT: index of datapoint ot retrieve
//OUTPUT: Copy of selected datapoint from this->data
DataPoint Table::getDataPoint(int index)
{
	if(index<this->numPoints())
		return this->data[index];
	else return *(new DataPoint());
}


//setDataPoint
//INPUT: index of DataPoint to replace and DataPoint to use
//MODIFIES this->data<DataPoint>
void Table::setDataPoint(int index, DataPoint data)
{
	if(index<this->numPoints())
		this->data[index]=data;
}

//getHeading
//INPUT: Index of requested heading
//OUTPUT: copy of string contained in this->heads[index]
string Table::getHeading(int index)
{
	if(index<this->numElements())
		return this->heads.getHeading(index);
	else return "";
}

//numElements
//OUTPUT: Number of headings in Table
int Table::numElements()
{
	return this->heads.numElements();
}

//numPoints
//OUTPUT: size of data<DataPoint>
int Table::numPoints()
{
	return this->data.size();
}

//isValidTable
//OUTPUT: Returns TRUE if Table successfully initialized,
//		FALSE otherwise
bool Table::isValidTable()
{
	return valid;
}

//getPath
//OUTPUT: Copy of this->path
string Table::getPath()
{
	return this->path;
}