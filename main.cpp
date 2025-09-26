#include <iostream>
#include <string>
using namespace std;

//Lab #2
//By Kateryna Taranenko

class Node {
private:
	int data;
	Node* next;

public:
	Node(int d)
	{
		data = d;
		next = nullptr;
	}
};

struct Commit {
	int hash;
	string message;
	Commit* next;

	Commit(int h, const string& msg) : hash(h), message(msg), next(nullptr)
	{
		Node* newNode = new Node(h);
	}
};

class CommitHistory {
private:
	Commit* head;
public:
	CommitHistory() : head(nullptr)
	{

	}
	void commit(const string& message) // append
	{
		int hash = rand() % 1000; // Simulated hash
	}
	void log() const// display all
	{
		//display all commits with the arrow between them: commit1 <-commit2<-
		if (!head)//if there is no variables in linked list
		{
			return;
		}
		const Commit* current = head;
		while (current != nullptr)  // Fixed condition
		{
			cout << "[" << current->hash << ": " << current->message << "]";
			if (current->next)
			{
				cout << " <- ";
			}
			current = current->next;  // Move to next commit
		}
		cout << '\n';
	}


	void reset()// Delete last commit
	{

		if (!head) //if there is no variables in linked list
		{
			return;
		}

		//Head - The Most Recent Commit
		//Tail - Oldest Commit

		Commit* temp = head; //creating temp value to hold info
		//that is going to be deleted

		head = head->next; // without losing connection to LL, moving head to next
		delete temp; //deleting the temp value

		cout << "Last commit removed" << endl; // Displaying message
	}

	//*****

	static CommitHistory merge(const CommitHistory& branch1, const CommitHistory& branch2)
	{
		CommitHistory merged;

		//Copying from branch 1 to merged
		const Commit* current1 = branch1.head;
		while (current1 != nullptr)
		{
			Commit* newCommit = new Commit(current1->hash, current1->message);
			newCommit->next = merged.head;
			merged.head = newCommit;
			current1 = current1->next;
		}


		//****

		//Copying from branch 2 to merged
		const Commit* current2 = branch2.head;
		while (current2 != nullptr)
		{
			Commit* newCommit = new Commit(current2->hash, current2->message);
			newCommit->next = merged.head;
			merged.head = newCommit;
			current2= current2->next;
		}

		cout << "Branches merged when done!" << endl;
		return merged;
	}


	~CommitHistory() //Destructor 
	{
		while (head)
		{
			Commit* temp = head;
			head = head->next;
			delete temp;
			//Deleting one by one
			//Because if we delete head, or somethere in the middle
			//We will lose connection to out Linked List
		}
	}
};

//***


int main() //Main from materials
{
	srand(time(0)); // For random hash generation
	

	CommitHistory master;

	master.commit("Initial commit");
	master.commit("Add README");
	master.commit("Implement login system");

	CommitHistory featureBranch;
	featureBranch.commit("Start feature X");
	featureBranch.commit("Fix bug in feature X");
	cout << "\n== Master Branch ==";
	master.log();

	cout << "\n== Feature Branch ==";
	featureBranch.log();
	cout << "\n== Reset last commit on master ==";
	master.reset();

	master.log();


	cout << "\n== Merged History ==";
	CommitHistory merged = CommitHistory::merge(master, featureBranch);
	merged.reset();
	merged.log();


	cout << "\n== Master Branch Unchanged after merge==";
	master.log();


	cout << "\n== Feature Branch Unchanged after merge==";
	featureBranch.log();

	return 0;
}

/*


== Master Branch ==
== Feature Branch ==
== Reset last commit on master ==
== Merged History ==Branches merged when done!

== Master Branch Unchanged after merge==
== Feature Branch Unchanged after merge==



*/
