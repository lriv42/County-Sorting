/*
	Name:		Liam Rivers
	Due Date:	10/11/23
	Purpose:	Sorting counties by descending population
*/

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include "County.h"
#include "list.h"
//include your list header here--done

using namespace std;

int main()
{
	ifstream file;
	stringstream temp;
	string line, county, state;
	int index, pop;
	//file.open("counties_list.csv", ios::in); //comment out one csv file or the other for whatever purpose is needed
	file.open("counties_ten.csv", ios::in);

	//create a new list of county pointers -- done
	
	DblLinkedList <County *> countyList; //the new double linked list that holds all county data

	County* newCounty;

	if(file.good()) {
	while(getline(file, line, ','))
	{
		temp.clear();
		temp.str(line);
		temp >> index;

		getline(file, line, ',');
		county = line;

		getline(file, line, ',');
		state = line;

		getline(file, line, '\n');
		temp.clear();
		temp.str(line);
		temp >> pop;

		newCounty = new County(index, county, state, pop);
		//append newCounty to your list-- done
		countyList.appendNode(newCounty);
		
	}}

	file.close();

	//call mergesort-- done
	countyList.mergesort();

	//print the list-- done
	countyList.printList();

	//countyList.selectionSort(); unable to get working, left in case you want to see outputs of each try for yourself

	//countyList.printList();

	return 0;
}

//TO FIX
//DOES NOT PRINT FULL LIST
// LIST.H - DESTRUCTOR - DOES NOT DEALLOCATE FULL LIST
//LIST.H - PRINTLIST - SHOULD CREATE ANOTHER NODE TO TRAVERSE THE LIST
//... DOES NOT PRINT THE FULL LIST
//LIST.H - MERGESORT(PUBLIC) - SHOULD ASSIGN HEAD TO MERGESORT(HEAD, TAIL) 