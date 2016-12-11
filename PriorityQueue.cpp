//
//Christian Hill
//HW7 _ 11/8/16
//CSCi 2270 - Boese
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "PatientQueue.hpp"
using namespace std;
//Constructor
PatientQueue::PatientQueue()
{
    lastIndex = 0;
}

//Destructor
PatientQueue::~PatientQueue()
{
	cout<<"We're CLOSING! Deleting patient queue!" <<endl;
	for(int i=1;i<=lastIndex;i++)
	{
		cout<<"Removing "<<waitlist[i]->name<<" from the queue."<<endl;
		delete waitlist[i];
	}
}

bool PatientQueue::isEmpty(){
	if (lastIndex == 0){
        return true;
    }
    else{
		return false;
	}
}

//Returns Total amount of patients left
	int PatientQueue::size(){
	return lastIndex;
	}

//Enqueue function that adds people to the queue and sorts them by priority.
	void PatientQueue::enqueue(int priority, std::string name){
	int parent;
	cout << "Adding " << priority << " " << name << endl;
	if(isEmpty() == true)
    {
	lastIndex++;
    waitlist[lastIndex]= new Patient(priority, name);
	}

	else{
	++lastIndex;
	waitlist[lastIndex]= new Patient(priority, name);
	int child=lastIndex;	
	parent = child/2;

    while(waitlist[child]->priority < waitlist[parent]->priority && parent!=1){
		
		swap(parent,child);
		child = parent;
		parent = child/2;
	}
	if(parent==1 && waitlist[parent]->priority>waitlist[child]->priority)
	swap(parent,child);
	
}
printList();
}

//Swap function that swaps two array names/priority
	void PatientQueue::swap(int index1, int index2){
		string temp = waitlist[index1]->name;
		int temp1 = waitlist[index1]->priority;
		waitlist[index1]->priority = waitlist[index2]->priority;
		waitlist[index1]->name = waitlist[index2]->name;
		waitlist[index2]->priority = temp1;
		waitlist[index2]->name = temp;
}

//Removes top priority from the array and re-heaps
	Patient* PatientQueue::dequeue()
{
		cout<<"Processing "<<waitlist[1]->priority<<" "<<waitlist[1]->name<<endl;		// returns pointer to patient record and removes from array
		if(isEmpty()==true){
			cout<<"No patients"<<endl;
				return waitlist[1];
}
	else if (lastIndex == 1) {
	lastIndex--;
	return waitlist[1];
}
	else{
		int parent=1;
		int child=2;
		swap(1,lastIndex);
		while(waitlist[parent]->priority > waitlist[child]->priority && child!=lastIndex)
		{
			if(waitlist[child+1]->priority>waitlist[child]->priority)
			swap(parent,child);
			else
			swap(parent,child+1);
			parent=child;
			child=child*2;
		}
		lastIndex--;
		return waitlist[lastIndex+1];
		
	}
}

// prints the array using indexes
	void PatientQueue::printList(){
		int i=1;
		cout<<"==="<<endl;				
	if(isEmpty()==true){
		cout<<"Patients Waiting"<<endl;
		cout<<"No one waiting!"<<endl;
		cout<<"==="<<endl;
	}
	else{
		cout<<"Patients Waiting"<<endl;
		while(i!=lastIndex+1){
			cout<<"["<<waitlist[i]->priority<<"] "<<waitlist[i]->name<<endl;
			i++;
		}
		cout<<"==="<<endl;
	}
}
