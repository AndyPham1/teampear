#include "stdafx.h"
#include "pubProfessor.h"
#include "modelExceptions.h"

using namespace std;

pubProfessor::pubProfessor(){
	this->memberName = "";	//Member Name
	this->primaryDomain = "";	//Primary Domain
	this->numberOfPublications = 0;	//Number of entries in all vectors
	this->publicationStatus = new vector<string>();
	this->type = new vector<string>();
	this->role = new vector<string>();
	this->publicationName = new vector<string>();
	this->authors = new vector<string>();
	this->title = new vector<string>();
	this->date = new vector<int>();
}
pubProfessor::pubProfessor(string memberName, string primaryDomain){
	this->memberName = memberName;	//Member Name
	this->primaryDomain = primaryDomain;	//Primary Domain
	this->numberOfPublications = 0;	//Number of entries in all vectors
	this->publicationStatus = new vector<string>();
	this->type = new vector<string>();
	this->role = new vector<string>();
	this->publicationName = new vector<string>();
	this->authors = new vector<string>();
	this->title = new vector<string>();
	this->date = new vector<int>();
}
pubProfessor::~pubProfessor(){
	delete this->publicationStatus;
	delete this->type;
	delete this->role;
	delete this->publicationName;
	delete this->authors;
	delete this->title;
	delete this->date;
}

const string pubProfessor::getName()						{ return this->memberName; }
const string pubProfessor::getDomain()						{ return this->primaryDomain; }
const int pubProfessor::getNumberOfPubs()					{ return this->numberOfPublications; }
const vector<string>* pubProfessor::getPublicationStatus()	{ return this->publicationStatus; }
const vector<string>* pubProfessor::getType()				{ return this->type; }
const vector<string>* pubProfessor::getRole()				{ return this->role; }
const vector<string>* pubProfessor::getPublicationName()	{ return this->publicationName; }
const vector<string>* pubProfessor::getAuthors()			{ return this->authors; }
const vector<string>* pubProfessor::getTitle()				{ return this->title; }
const vector<int>*	  pubProfessor::getDate()				{ return this->date; }

//Add an entry to all vectors
void pubProfessor::addEntry(string publicationStatus, string type, string role, string publicationName,
		string authors, string title, int date){
	this->numberOfPublications++;
	this->publicationStatus->push_back(publicationStatus);
	this->type->push_back(type);
	this->role->push_back(role);
	this->publicationName->push_back(publicationName);
	this->authors->push_back(authors);
	this->title->push_back(title);
	this->date->push_back(date);
}

//Remove an entry, based on given index value (0 indexed)
void pubProfessor::removeEntry(int indexToRemove){
	if (indexToRemove >= this->numberOfPublications)
		throw new indexOutOfBoundsException();

	this->numberOfPublications--;
	this->publicationStatus->erase(this->publicationStatus->begin() + indexToRemove);
	this->type->erase(this->type->begin() + indexToRemove);
	this->role->erase(this->role->begin() + indexToRemove);
	this->publicationName->erase(this->publicationName->begin() + indexToRemove);
	this->authors->erase(this->authors->begin() + indexToRemove);
	this->title->erase(this->title->begin() + indexToRemove);
	this->date->erase(this->date->begin() + indexToRemove);
}