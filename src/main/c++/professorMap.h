#pragma once
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include "pubProfessor.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "createProfessor.h"


using namespace std;

#pragma once
template <class T>
class professorMap {
private:
	map<string, T*>* professors;
public:
	typedef typename map<string, T*>::iterator iterator;

	//Chelsea
	professorMap();
	professorMap(string fileName);
	//Really important to clean up dynamic memory because of the size of possible files
	virtual ~professorMap();

	/*
	Should import csv by creating 'virtualization' of
	2D array (vector<vector<string>>) then
	calling createProfessor() for each professor entry.
	*/
	void importCSV(string fileName);

	vector<string>* getProfessorNameList();
	int getProfessorCount();
	const T* getProfessor(string professorName);

	typename map<string, T*>::iterator begin();
	typename map<string, T*>::iterator end();

	void addProfessor(T& newProfessor);
	void removeProfessor(string professorName);
	vector<pair<string,vector<pair<string,int> > > > callMe();
};


template <class T>
professorMap<T>::professorMap() {
	this->professors = new map<string, T*>();
}

template <class T>
professorMap<T>::professorMap(string fileName){
	this->professors = new map<string, T*>();
	this->importCSV(fileName);
}

template <class T>
professorMap<T>::~professorMap(){
	for (map<string, T*>::iterator it = this->professors->begin(); it != this->professors->end(); ++it)
		delete (*it).second;
	delete professors;
}

/*
Should import csv by creating 'vitualization' of
2D array (vector<vector<string>>) then
calling createProfessor() for each professor entry.
*/

template <class T>
void professorMap<T>::importCSV(string fileName) {
	//read CSV file into 2D array
	vector<vector<string>*> myCSV;
	vector<string>* valueLine;
	ifstream inFile(fileName);
	string temp;

	//make 2D vector
	for (string line; getline(inFile, line);)
	{
		istringstream in(line);
		valueLine = new vector<string>();
		while (getline(in, temp, ','))
			valueLine->push_back(temp);

		myCSV.push_back(valueLine);
	}

	/*for (size_t i = 0; i < myCSV.size(); i++){
		cout << i;
		cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n";
		for (size_t j = 0; j < myCSV[i]->size(); j++){
			cout << myCSV[i]->at(j);
			cout << '\n';
		}
	}*/
	map<string, vector<vector<string> > >* orgCSV = new map<string, vector<vector<string> > >();
	for (size_t i = 0; i < myCSV.size(); i++) {
		//cout << "orgcsv: " + to_string(i) << "\n";

		if (!orgCSV->empty()){
			//cout << "if: " + to_string(i) << "\n";
			map<string, vector<vector<string> > >::iterator it = orgCSV->find((*myCSV[i])[0]);
			//cout << "past this line\n";
			//cout << (*myCSV[i])[0];
			//cout << "\n";
			/*if (!(*it).first.compare((*myCSV[i])[0])){
				cout << "asdfsadf: "<< "\n";
				(*it).second.push_back(*myCSV[i]);
			}*/
			if (it != orgCSV->end()) {
				(*it).second.push_back(*myCSV[i]);
			}
			else {
				vector<vector<string> > professorVector;
				professorVector.push_back(*myCSV[0]);
				professorVector.push_back(*myCSV[i]);
				orgCSV->insert(pair<string, vector<vector<string> > >((*myCSV[i])[0], professorVector));
			}
		}
		else {
			//cout << "else: " + to_string(i) << "\n";
			vector<vector<string> > professorVector;
			professorVector.push_back(*myCSV[0]);
			professorVector.push_back(*myCSV[i]);
			orgCSV->insert(pair<string, vector<vector<string> > >((*myCSV[i])[0], professorVector));
		}
	}
	//cout << "trythis";
	for (map<string, vector<vector<string> > >::iterator it = orgCSV->begin(); it != orgCSV->end(); ++it) {
		T* professor = createProfessor<pubProfessor>::createNewProfessor((*it).second);
		this->professors->insert(pair<string, T*>(professor->getName(),professor));
		//cout << "professors: " << professors->size();
	}
	for (size_t i = 0; i < myCSV.size(); i++)
		delete myCSV[i];
	delete orgCSV;
	int counter = 0;

	for (map<string, T*>::iterator it = professors->begin(); it != professors->end(); ++it)
	{
		counter++;
		cout << counter << " " << it->first << "\n";
	}
}

template <class T>
vector<string>* professorMap<T>::getProfessorNameList(){
	vector<string>* listOfProfs = new vector<string>;
	for (map<string, T*>::iterator it = professors.begin(); it != professors.end(); ++it)
		listOfProfs->push_back(it->first);
	return listOfProfs;
}

template <class T>
int professorMap<T>::getProfessorCount() {
	return this->professors->size();
}

template <class T>
const T* professorMap<T>::getProfessor(string professorName){
	std::map<string, T*>::iterator it = this->professors->find(professorName);
	if ((*it).first == professorName)
		return (*it).second;
	throw new professorNotFoundException();
}

template <class T>
typename std::map<string, T*>::iterator professorMap<T>::begin() { return this->professors->begin(); }

template <class T>
typename std::map<string, T*>::iterator professorMap<T>::end() { return this->professors->end(); }

template <class T>
void professorMap<T>::addProfessor(T& newProfessor) { this->professors->insert(newProfessor.getName(), newProfessor); }

template <class T>
void professorMap<T>::removeProfessor(string professorName){
	map<string, T*>::iterator it = this->professors->find(professorName);
	if ((*it).first == professorName)
		this->professors->erase(it);
	else
		throw new professorNotFoundException();
}

template <class T>
vector<pair<string, vector<pair<string, int> > > > professorMap<T>::callMe(){
//	T* prof;
	vector<pair<string, vector<pair<string, int> > > > mainVector;

	vector<pair<string, int> >* vBookChapters = new vector<pair<string, int>>;
	vector<pair<string, int> >* vBooks = new vector<pair<string, int>>;
	vector<pair<string, int> >* vBookEdits = new vector<pair<string, int>>;
	vector<pair<string, int> >* vCaseReports = new vector<pair<string, int>>;
	vector<pair<string, int> >* vClinicalCareGuides = new vector<pair<string, int>>;
	vector<pair<string, int> >* vCommentaries = new vector<pair<string, int>>;
	vector<pair<string, int> >* vConferences = new vector<pair<string, int>>;
	vector<pair<string, int> >* vEditorials = new vector<pair<string, int>>;
	vector<pair<string, int> >* vInvitedArticles = new vector<pair<string, int>>;
	vector<pair<string, int> >* vJournalArticles = new vector<pair<string, int>>;
	vector<pair<string, int> >* vLetters = new vector<pair<string, int>>;
	vector<pair<string, int> >* vMagazine = new vector<pair<string, int>>;
	vector<pair<string, int> >* vManuals = new vector<pair<string, int>>;
	vector<pair<string, int> >* vMonograph = new vector<pair<string, int>>;
	vector<pair<string, int> >* vMultimedia = new vector<pair<string, int>>;
	vector<pair<string, int> >* vNewsletterArt = new vector<pair<string, int>>;
	vector<pair<string, int> >* vNewspaperArt = new vector<pair<string, int>>;
	vector<pair<string, int> >* vAbstracts = new vector<pair<string, int>>;
	vector<pair<string, int> >* vStudentPubs = new vector<pair<string, int>>;
	vector<pair<string, int> >* vWebVids = new vector<pair<string, int>>;
	vector<pair<string, int> >* vWorkingPapers = new vector<pair<string, int>>;

	const char* args[] = { "Book Chapters", "Books", "Books Edited", "Case Reports", "Clinical Case Guidelines", \
	"Commentaries", "Conference Proceedings", "Editorials", "Invited Articles", "Journal Articles", \
	"Letters to Editor", "Magazine Entries", "Manuals", "Monographs", "Multimedia", "Newsletter Articles", \
	"Newspaper Articles", "Published Abstracts", "Supervised Student Publications", "Websites / Videos", \
	"Working Papers" };

	vector<string> type(args, args + sizeof(args) / sizeof(args[0]));
	//cout << "chelsea";
	map<string, T*>::iterator it;
	for (it = professors->begin(); it != professors->end(); ++it){ // iterate through the professor objects
		//cout << " is a girl";
		const vector <string>* pubTypes = it->second->getType();
		string profName = it->first;
		int countBookChapters = 0;
		int countBooks = 0;
		int countBookEdits = 0;
		int countCaseReports = 0;
		int countClinicalCareGuides = 0;
		int countCommentaries = 0;
		int countConferences = 0;
		int countEditorials = 0;
		int countInvitedArticles = 0;
		int countJournalArticles = 0;
		int countLetters = 0;
		int countMagazine = 0;
		int countManuals = 0;
		int countMonographs = 0;
		int countMultimedia = 0;
		int countNewsletterArticles = 0;
		int countNewspaperArticles = 0;
		int countAbstracts = 0;
		int countStudentPubs = 0;
		int countWebVids = 0;
		int countWorkingPapers = 0;

		for (vector<string>::const_iterator it2 = pubTypes->begin(); it2 != pubTypes->end(); ++it2){ // iterate through the publication types
			if (!(*it2).compare(type[0]))
				countBookChapters++;
			else if (!(*it2).compare(type[1]))
				countBooks++;
			else if (!(*it2).compare(type[2]))
				countBookEdits++;
			else if (!(*it2).compare(type[3]))
				countCaseReports++;
			else if (!(*it2).compare(type[4]))
				countClinicalCareGuides++;
			else if (!(*it2).compare(type[5]))
				countCommentaries++;
			else if (!(*it2).compare(type[6]))
				countConferences++;
			else if (!(*it2).compare(type[7]))
				countEditorials++;
			else if (!(*it2).compare(type[8]))
				countInvitedArticles++;
			else if (!(*it2).compare(type[9]))
				countJournalArticles++;
			else if (!(*it2).compare(type[10]))
				countLetters++;
			else if (!(*it2).compare(type[11]))
				countMagazine++;
			else if (!(*it2).compare(type[12]))
				countManuals++;
			else if (!(*it2).compare(type[13]))
				countMonographs++;
			else if (!(*it2).compare(type[14]))
				countMultimedia++;
			else if (!(*it2).compare(type[15]))
				countNewsletterArticles++;
			else if (!(*it2).compare(type[16]))
				countNewspaperArticles++;
			else if (!(*it2).compare(type[17]))
				countAbstracts++;
			else if (!(*it2).compare(type[18]))
				countStudentPubs++;
			else if (!(*it2).compare(type[19]))
				countWebVids++;
			else if (!(*it2).compare(type[20]))
				countWorkingPapers++;
		}

		//make pairs and push into vectors
		pair<string, int>* temp;

		temp = new pair<string, int>(profName, countBookChapters);
		//cout << temp->first;
		//cout << "jas;ldfkjadsf";
		vBookChapters->push_back(*temp);
		
		temp = new pair<string, int>(profName, countBooks);
		vBooks->push_back(*temp);

		temp = new pair<string, int>(profName, countCaseReports);
		vCaseReports->push_back(*temp);

		temp = new pair<string, int>(profName, countClinicalCareGuides);
		vClinicalCareGuides->push_back(*temp);

		temp = new pair<string, int>(profName, countCommentaries);
		vCommentaries->push_back(*temp);

		temp = new pair<string, int>(profName, countConferences);
		vConferences->push_back(*temp);

		temp = new pair<string, int>(profName, countEditorials);
		vEditorials->push_back(*temp);

		temp = new pair<string, int>(profName, countInvitedArticles);
		vInvitedArticles->push_back(*temp);

		temp = new pair<string, int>(profName, countJournalArticles);
		vJournalArticles->push_back(*temp);

		temp = new pair<string, int>(profName, countLetters);
		vLetters->push_back(*temp);

		temp = new pair<string, int>(profName, countMagazine);
		vMagazine->push_back(*temp);

		temp = new pair<string, int>(profName, countManuals);
		vManuals->push_back(*temp);

		temp = new pair<string, int>(profName, countMonographs);
		vMonograph->push_back(*temp);

		temp = new pair<string, int>(profName, countMultimedia);
		vMultimedia->push_back(*temp);

		temp = new pair<string, int>(profName, countNewsletterArticles);
		vNewsletterArt->push_back(*temp);

		temp = new pair<string, int>(profName, countNewspaperArticles);
		vNewspaperArt->push_back(*temp);

		temp = new pair<string, int>(profName, countAbstracts);
		vAbstracts->push_back(*temp);

		temp = new pair<string, int>(profName, countStudentPubs);
		vStudentPubs->push_back(*temp);

		temp = new pair<string, int>(profName, countWebVids);
		vWebVids->push_back(*temp);

		temp = new pair<string, int>(profName, countWorkingPapers);
		vWorkingPapers->push_back(*temp);
		}

	//push 15 publication type vectors into pairs

	pair<string, vector<pair<string, int> > >* temporary;

	temporary = new pair<string, vector<pair<string, int> > >(type[0], *vBookChapters);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[1], *vBooks);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[2], *vBookEdits);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[3], *vCaseReports);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[4], *vClinicalCareGuides);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[5], *vCommentaries);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[6], *vConferences);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[7], *vEditorials);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[8], *vInvitedArticles);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[9], *vJournalArticles);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[10], *vLetters);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[11], *vMagazine);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[12], *vManuals);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[13], *vMonograph);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[14], *vMultimedia);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[15], *vNewsletterArt);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[16], *vNewspaperArt);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[17], *vAbstracts);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[18], *vStudentPubs);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[19], *vWebVids);
	mainVector.push_back(*temporary);

	temporary = new pair<string, vector<pair<string, int> > >(type[20], *vWorkingPapers);
	mainVector.push_back(*temporary);

	return mainVector;
}
