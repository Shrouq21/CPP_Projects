#include<bits/stdc++.h>
using namespace std;
//Helper functions
void options(vector<string> opt)
{
	for (int i = 1; i <= (int)opt.size(); i++)
	{
		cout << "    " << i << "- " << opt[i - 1] << '\n';
	}
}


void WriteData(string& Path, string& d, bool append = true) {
	auto status = ios::out | ios::in | ios::app;
	if (append == false) {
		status = ios::out | ios::in | ios::trunc;
	}
	fstream file(Path.c_str(), status);
	if (file.fail()) {
		cout << "Error! . Can't open file\n";
		return;
	}

	file << d;

	file.close();
}
vector<string> ReadData(string& Path) {
	vector<string>Data;
	fstream file(Path.c_str());
	if (file.fail()) {
		cout << "Error! . Can't open file\n";
		return Data;
	}
	string lines;
	while (getline(file, lines)) {
		if (lines.empty())break;
		Data.push_back(lines);
	}
	file.close();
	return Data;
}
vector<string>SplitString(string& line) {
	vector<string>ans;
	int pos;
	while ((pos = line.find(',')) != -1) {
		string extracted = line.substr(0, pos);
		line.erase(0, pos + 1);
		ans.push_back(extracted);
	}
	return ans;
}
int toInt(string& target) {
	return stoi(target);
}
struct User
{
	string name, email, user_name, Pass;
	int age, UserId;
	bool IsAnonymous;
	//vector<int>QuestionFromMe;
};
struct UserService
{
	int NextUserId = 0;
	User currentUser;
	map<string, User>UserObjects;
	string UserPath{ "users.txt" };
	pair<User, bool> Register()
	{
		cout << "Enter Your Username: ";
		cin >> currentUser.user_name;
		if (UserObjects.count(currentUser.user_name))
			return { currentUser, false };
		cout << "Enter Your Name: ";
		cin >> currentUser.name;
		cout << "Enter Your Email: ";
		cin >> currentUser.email;
		cout << "Enter Your Age: ";
		cin >> currentUser.age;
		cout << "Enter Your Password: ";
		cin >> currentUser.Pass;
		cout << "If You accept Anonymous Questions Press 0 , Otherwise 1: ";
		cin >> currentUser.IsAnonymous;
		currentUser.UserId = ++NextUserId;
		UserObjects[currentUser.user_name] = currentUser;

		return { currentUser, true };
	}
	pair<User, bool> CheckExisting()
	{
		string Name, Password;
		cout << "Enter Your UserName && Password: ";
		cin >> Name >> Password;
		if (UserObjects.count(Name) and UserObjects[Name].Pass == Password)
			return{ UserObjects[Name],true };
		return { UserObjects[Name],false };
	}
	string Tostring() {
		// >> (cin) take data out of stream
		// << (cout) put data into the stream
		stringstream os;
		os << currentUser.UserId << "," << currentUser.age << "," <<currentUser.Pass << ","<<currentUser.IsAnonymous <<"," << currentUser.name << "," << currentUser.email
			<< "," << currentUser.user_name << ","<< '\n';
		return os.str();
	}
	void ListSystemUsers() {
		for (auto& user : UserObjects) {
			cout << "ID: " << user.second.UserId << "               " << "Name: " << user.second.name << '\n';
		}
	}
	void SystemUpdated() {
		string line = Tostring();
		if (UserObjects.empty()) {
			WriteData(UserPath, line, false); //truncate
		}
		else
		WriteData(UserPath, line,true); //append
	}
	void SaveAllDataToFile() {
		for (auto& pair : UserObjects) {
			currentUser = pair.second;
			SystemUpdated();
		}
	}
	void UserRepository() {
		vector<string>UserData = ReadData(UserPath);
		for (auto& i : UserData) {
			vector<string>parts = SplitString(i);
			string UserName = parts[6];
			UserObjects[UserName].UserId = toInt(parts[0]);
			NextUserId = max(NextUserId, toInt(parts[0]));
			UserObjects[UserName].name = parts[4];
			UserObjects[UserName].email = parts[5];
			UserObjects[UserName].user_name = parts[6];
			UserObjects[UserName].Pass = parts[2];
			UserObjects[UserName].age = toInt(parts[1]);
			UserObjects[UserName].IsAnonymous = toInt(parts[3]);
		}
	}
};
struct Question
{
	string name, question, answer;
	int QuestionId, FromId, ToId;
	//bool IsParent = false;
	bool IsAnonymous = 0;
	pair<bool, int>IsParent{ false,-1 };
};
struct QuestionBank
{
	int NextQuestionId = 0;
	map<int, Question>QuestionObjects;
	map<int, vector<int>>ThreadQuestions;
	string QuestionPath{ "questions.txt" };
	void PrintQuestionsFromMe(string& name, UserService& AskedUser)
	{
		User user = AskedUser.UserObjects[name];
		bool found = 0;
		for (auto& q : QuestionObjects) {
			if (q.second.FromId == user.UserId) {
				Print(q.second);
				found = 1;
			}
		}
	
		if (found == 0)cout << "No Questions Yet\n";
	}
	void PrintQuestionsToMe(string& name, UserService& AskedUser)
	{
		User user = AskedUser.UserObjects[name];
		bool found = 0;
		for (auto& q : QuestionObjects) {
			if (q.second.ToId == user.UserId) {
				Print(q.second,false);
				found = 1;
			}
		}
		if (found == 0)cout << "No Questions Yet\n";
	}
	void Print(Question current,bool From = true,bool Thread=false, bool ShowAnswer=true)
	{
		string prefix{};
		if (From)
		{
			cout << "QuestionId (" << current.QuestionId << ")";
			if (current.IsAnonymous == 0)cout << " !AQ";
			cout<<" To UserId(" << current.ToId << ")    Question: " << current.question << '\n';
		}
		else {
			if (Thread == true)prefix = "Thread question: ";
			if (current.IsAnonymous)cout << "(AQ): ";
			cout << prefix << "QuestionId ("
			<< current.QuestionId << ") ";
			if (!current.IsAnonymous)
				cout << "From UserId(" << current.FromId << ") ";
			cout << current.question << '\n';
		}
		PrintAnswer(current);

	}
	void PrintAnswer(Question current)
	{
		if (current.answer.empty())
			cout << " Answer: No Answer yet\n";
		else cout << "Answer: " << current.answer << '\n';
	}
	bool CheckAnonymous(User& user)
	{
		if (user.IsAnonymous == 0)return false;
		return true;
	}
	void AskQuestion(string& name, UserService& AskedUser)
	{
		int Id;
		string username;
		User ToUser;
		User& user = AskedUser.UserObjects[name];
		string question;
		Question current;
		cout << "Enter Username or -1 To Cancel: ";
		cin >> username;
		if (username == "-1")return;
		else
		{
			if (!AskedUser.UserObjects.count(username))
			{
				cout << "No such a user\n";
				return;
			}
			ToUser = AskedUser.UserObjects[username];
			if (!(CheckAnonymous(ToUser)))
				cout << "Note: Anonymous questions are not allowed for this user\n";
			else
			{
				cout << "Anonymous question?0/1: ";
				cin >> current.IsAnonymous;
			}
			cout << "For thread question: Enter question id or -1 for new question: ";
			cin >> Id;
			cout << "Enter question text: ";
			getline(cin, current.question);
			getline(cin, current.question);
			current.FromId = user.UserId;
			current.ToId = ToUser.UserId;
			current.QuestionId = ++NextQuestionId;
			//user.QuestionFromMe.push_back(CurrentQuestion.QuestionId);  //
			if (Id == -1) {
				current.IsParent.first = 1;
				current.IsParent.second = current.QuestionId;
				ThreadQuestions[current.QuestionId].push_back(current.QuestionId);
			}
			else {
				current.IsParent.first = 0; //not a parent
				current.IsParent.second = Id; //parent id 
				ThreadQuestions[Id].push_back(current.QuestionId);
			}
			QuestionObjects[current.QuestionId] = current;
		}
		if(QuestionObjects.size()==1)
		SystemUpdated(current,false);
		else SystemUpdated(current);
	}
	void Feed(Question& question,bool IsParent=true) {
		string prefix = "Parent ";
		if (!IsParent)prefix = "Thread ";
			cout << prefix<<"question Id (" << question.QuestionId << ") from user id ("
			<< question.FromId << ") to user id (" << question.ToId << ") Question: " << question.question << '\n';
		
			if (question.answer.empty())cout << "No answer yet";
			else cout << question.answer;
			cout << '\n';

		
	}
	void PrintUnansweredQuestions(string& name, UserService& AskedUser) {
		User& user = AskedUser.UserObjects[name];
		bool found = 0;
		for (auto& q : QuestionObjects) {
			if (user.UserId==q.second.ToId and q.second.answer.empty()) {
				Print(q.second);
				found = 1;
			}
		}
		if (!found)cout << "No unanswered questions.\n";
	}
	bool CheckPermission(int QuestionId,UserService&AskedUser,string username, bool from = true) {
		Question q = QuestionObjects[QuestionId];
		User u = AskedUser.UserObjects[username];
		if (from) return q.FromId == u.UserId;
		return q.ToId == u.UserId;
	}
	void EditAnswer(string username,UserService&AskedUser) {
		User user = AskedUser.UserObjects[username];
		cout << "Enter Question Id\n";
		int id; cin >> id;
		if (!CheckPermission(id, AskedUser, username,false))
		 {
			cout << "You don't have permission\n";
			return;
		}
       cout << "Enter your new answer: ";
		getline(cin, QuestionObjects[id].answer); // for cin>>id
		getline(cin, QuestionObjects[id].answer);

	}
	void EditQuestion(string username, UserService& AskedUser) {
		User user = AskedUser.UserObjects[username];
		cout << "Enter Question Id: ";
		int id; cin >> id;
		if (!CheckPermission(id, AskedUser, username, true)) {
			cout << "You don't have a permission\n";
			return;
		}
		cout << "Enter your new question: ";
		getline(cin, QuestionObjects[id].question); // for cin>>id
		getline(cin, QuestionObjects[id].question);

	}
	void search_keyword() {
		string keyword;
		cout << "Enter a keyword: ";
		cin >> keyword;
		int count = 0;
		for (auto& question : QuestionObjects) {
			if (question.second.question.find(keyword) != string::npos) {
				cout << "Question Id (" << question.second.QuestionId << ") from user id ("
					<< question.second.FromId << ") to user id (" << question.second.ToId << ") Question: "
					<<question.second.question << '\n';
				++count;
			}
			if (question.second.answer.find(keyword) != string::npos) {
				cout << "Answer for question id(" << question.second.QuestionId << ") from user id ("
					<< question.second.FromId << ") to user id (" << question.second.ToId << ") :";
				cout << question.second.answer << '\n';
	            ++count;
			}
		}
		if (count == 0)cout << "No results found\n";
		else cout << "Total results: " << count << '\n';
	}
	void ListFeed() {
		for(auto &Parent:ThreadQuestions){
			vector<int>Threads = ThreadQuestions[Parent.first];
			for (int thread = 0; thread < Threads.size(); thread++) {
				if (Threads[thread] == Parent.first)
					Feed(QuestionObjects[Threads[thread]]);
				else Feed(QuestionObjects[Threads[thread]],false);
			}
	}
	}
	int CheckExistingQuestion() {
		int QuestionId;
		cout << "Enter Question id or -1 to cancel: ";
		cin >> QuestionId;
		if (QuestionId == -1)return -1;
		if (!(QuestionObjects.count(QuestionId))) {
			cout << "No such QuestionId. Try Again\n";
			CheckExistingQuestion();
		}
		return QuestionId;
	}
	void AnswerQuestion(string& name, UserService& AskedUser) {
		User& user = AskedUser.UserObjects[name];
		string Answer;
		int id = CheckExistingQuestion();
		if (id == -1)return;
		if (!CheckPermission(id, AskedUser, name, false))
		{
			cout << "You don't have permission\n";
			return;
		}
		Print(QuestionObjects[id],false);
		if (!QuestionObjects[id].answer.empty())
			cout << "Warning: Already answered. Answer will be updated\n";
		cout << "Enter answer: ";
		getline(cin, QuestionObjects[id].answer);
		getline(cin, QuestionObjects[id].answer);
	}
	void DeleteQuestion(string& name, UserService& AskedUser) {
		int id = CheckExistingQuestion();
		if (id == -1)return;
		if (!CheckPermission(id, AskedUser,name, true))
		{
			cout << "You don't have permission\n";
			return;
		}
		if (QuestionObjects[id].IsParent.first) // if iam a parent
		{
			vector<int>& threads = ThreadQuestions[id];
			for (auto& i : threads) {
				QuestionObjects.erase(i);
			}//thread from vector
			ThreadQuestions.erase(id);
		}
		
		
		else { //not a parent
			int ParentId = QuestionObjects[id].IsParent.second;
			vector<int>&threads = ThreadQuestions[ParentId];
			 //thread
			threads.erase(remove(threads.begin(), threads.end(), id), threads.end()); //thread from vector
			QuestionObjects.erase(id);
		}
	

	}
	string ToString(Question current) {
		stringstream os;
		os << current.QuestionId << "," << current.IsParent.first << "," <<
			current.IsParent.second << "," << current.FromId << ","
			<< current.ToId << "," << current.IsAnonymous << ","
			<< current.question << "," << current.answer << "," << "\n";
		return os.str();
	}
	void SystemUpdated(Question current,bool sign = true) {
		string line = ToString(current);
		WriteData(QuestionPath, line, sign);
	}
	void SaveAllDataToFile() {
		bool FirstTime =true;
		for (auto& pair : QuestionObjects) {
			Question current = pair.second;
			if (FirstTime) {
				SystemUpdated(current, false);
				FirstTime = false;
			}
			else SystemUpdated(current);
		}
	}
	void QuestionRepository() {
		vector<string>Data = ReadData(QuestionPath); //lines
		for (auto& line : Data) {
			vector<string>parts = SplitString(line);
			int id = toInt(parts[0]);
			QuestionObjects[id].QuestionId = id;
			NextQuestionId = max(id, NextQuestionId);
			QuestionObjects[id].IsParent.first = toInt(parts[1]);
			QuestionObjects[id].IsParent.second = toInt(parts[2]);
			QuestionObjects[id].FromId = toInt(parts[3]);
			QuestionObjects[id].ToId = toInt(parts[4]);
			QuestionObjects[id].IsAnonymous = toInt(parts[5]);
			QuestionObjects[id].question = parts[6];
			QuestionObjects[id].answer = parts[7];
			ThreadQuestions[toInt(parts[2])].push_back(id);
		}
	}
};
struct System
{
	QuestionBank Q;
	UserService U;
	pair<User, bool>Check;
	vector<string>menu;
	int choice;
	void Start()
	{
		Q.QuestionRepository();
		U.UserRepository();
		// fstream User("users.txt", ios::app);
		while (true) {
			menu.clear();
			cout << "Menu:\n";
			options({ "Login","Signup" });
			int choice; cout << "Enter Your Choice: ";
			cin >> choice;
			if (!(choice >= 1 and choice <= 2))
			{
				cout << "Error! try Again\n"; Start();
			}
			if (choice == 1)
			{
				Check = U.CheckExisting();
				if (!Check.second)
				{
					cout << "Error! try Again\n";
					continue;
				}

			}
			else
			{
				Check = U.Register();
				if (!Check.second) {
					cout << "Error! try Again\n";
					continue;
				}

				U.SystemUpdated();

			}
			menu.push_back("Print Questions To Me");
			menu.push_back("Print Questions From Me");
			menu.push_back("Answer Question");
			menu.push_back("Delete Question");
			menu.push_back("Ask Question");
			menu.push_back("List System Users");
			menu.push_back("Feed");
			menu.push_back("Show UnansweredQuestions To Me");
			menu.push_back("SearchKeyword");
			menu.push_back("EditAnswer");
			menu.push_back("EditQuestion");
			menu.push_back("Logout");
			while (true) {
				cout << "Menu:\n";
				options(menu);
				cout << "Enter Your Choice: ";
				cin >> choice;
				if (choice == 1) {
					Q.PrintQuestionsToMe(Check.first.user_name, U);
				}
				else if (choice == 2) {
					Q.PrintQuestionsFromMe(Check.first.user_name, U);
				}
				else if (choice == 3) {
					Q.AnswerQuestion(Check.first.user_name, U);
					Q.SaveAllDataToFile();
				}
				else if (choice == 4) {
					Q.DeleteQuestion(Check.first.user_name, U);
					Q.SaveAllDataToFile();
				}
				else if (choice == 5) {
					Q.AskQuestion(Check.first.user_name, U);
				}
				else if (choice == 6) U.ListSystemUsers();
				else if (choice == 7)Q.ListFeed();
				else if (choice == 8) Q.PrintUnansweredQuestions(Check.first.user_name, U);
				else if (choice == 9)Q.search_keyword();
				else if (choice == 10) Q.EditAnswer(Check.first.user_name, U);
				else if (choice == 11) Q.EditQuestion(Check.first.user_name, U);
				else if (choice == 12)break;

			}
		}
	}
};

int main()
{
	System system;
	system.Start();
}