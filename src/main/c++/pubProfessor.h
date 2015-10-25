#pragma once
#include <string>
#include <vector>

using namespace std;

class pubProfessor {
private:
    string memberName;	//Member Name
    string primaryDomain;	//Primary Domain
    int numberOfPublications;	//Number of entries in all vectors
    
    //All vectors can be identifed by array operations (ex. getType()[i];)
    vector<string>* publicationStatus;
    vector<string>* type;
    vector<string>* role;
    vector<string>* publicationName;
    vector<string>* authors;
    vector<string>* title;

    int numberOfBookChapters;
    int numberOfBooks;
    int numberOfBookEdits;
    int numberOfCaseReports;
    int numberOfClinicalCareGuides;
    int numberOfCommentaries;
    int numberOfConferences;
    int numberOfEditorials;
    int numberOfInvitedArticles;
    int numberOfJournalArticles;
    int numberOfLetters;
    int numberOfMagazine;
    int numberOfManuals;
    int numberOfMonographs;
    int numberOfMultimedia;
    int numberOfNewsletterArticles;
    int numberOfNewspaperArticles;
    int numberOfAbstracts;
    int numberOfStudentPubs;
    int numberOfWebVids;
    int numberOfWorkingPapers;
public:
    pubProfessor();
    pubProfessor(string memberName, string primaryDomain);
    virtual ~pubProfessor();
    
    const string getName();
    const string getDomain();
    int getNumberOfBookChapters();
    const int getNumberOfBooks();
    const int getNumberOfBookEdits();
    const int getNumberOfCaseReports();
    const int getNumberOfClinicalCareGuides();
    const int getNumberOfCommentaries();
    const int getNumberOfConferences();
    const int getNumberOfEditorials();
    const int getNumberOfInvitedArticles();
    const int getNumberOfJournalArticles();
    const int getNumberOfLetters();
    const int getNumberOfMagazine();
    const int getNumberOfManuals();
    const int getNumberOfMonographs();
    const int getNumberOfMultimedia();
    const int getNumberOfNewsletterArticles();
    const int getNumberOfNewspaperArticles();
    const int getNumberOfAbstracts();
    const int getNumberOfStudentPubs();
    const int getNumberOfWebVids();
    const int getNumberOfWorkingPapers();
    const vector<string>* getPublicationStatus();
    const vector<string>* getType();
    const vector<string>* getRole();
    const vector<string>* getPublicationName();
    const vector<string>* getAuthors();
    const vector<string>* getTitle();
    
    void addEntry(string publicationStatus, string type, string role, string publicationName, string authors, string title);
    void removeEntry(int indexToRemove);
};
