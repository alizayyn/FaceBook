#include<iostream>
#include<fstream>

using namespace std;
const int MaxFriends = 10;
const int MaxLikedPages = 10;
const int MaxLikes = 10;
const int MaxComments = 10;

class Helper;
class Users;
class Page;
class FaceBook;
class Object;
class Comment;
class Posts;
class Date;
class Activity;
class Memory;


class Helper
{
public:
	static int strlength(const char* str)
	{
		int count = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			count++;
		}
		return count;
	}
	static void StringCopy(char* dest, const char* src)
	{

		int i = 0;

		for (; src[i] != '\0'; i++)
		{
			dest[i] = src[i];
		}
		dest[i] = '\0';

	}
	static char* GetStringFromBuffer(char* str)
	{
		int l = strlength(str);
		char* String = new char[l + 1];
		StringCopy(String, str);
		return String;
	}
	static	int FirstIndexOfSubString(char* myStr, char* strToFind)
	{
		bool check = false;
		int index = 0;
		int l = strlength(myStr);
		int l2 = strlength(strToFind);

		for (int i = 0; i < l || myStr[i] != '\0'; i++)
		{
			int k = i;
			if (myStr[i] != ' ') {

				if (check != true)
				{
					for (int j = 0; j < l2; j++)
					{

						if (myStr[i] == strToFind[j])
						{
							index = k;
							check = true;
							i++;
						}
						else
						{
							check = false;
							index = -1;
							break;
						}
					}
				}
				else break;
			}
		}
		return index;
	}
	static int stringcmp(char* str1, const char* str2)
	{
		int i = 0;
		while (str1[i] != '\0' && str2[i] != '\0')
		{
			if (str1[i] > str2[i])
			{
				return 1;
			}
			else if (str1[i] < str2[i])
			{
				return -1;
			}
			else if (str1 == str2)
			{
				return 0;
			}
			i++;
		}
	}


};

class Date
{
private:
	int Day;
	int Month;
	int Year;
public:
	static Date CurrentDate;
	static void SetCurrentDate(Date d)
	{

		CurrentDate = d;
		cout << "Command\t\t SetCurrentDate" << CurrentDate.getDay() << " " << CurrentDate.getMonth() << " " << CurrentDate.getYear() << endl;
		cout << "System Date:\t\t "; CurrentDate.print(); cout << "\n\n";
	}
	static Date getCurrentDate()
	{
		return CurrentDate;
	}
	void Yesteday()
	{
		Day = Day - 1;
	}
	Date()
	{

		Day = 0;
		Month = 0;
		Year = 0;
	}
	Date(int d, int m, int y)
	{

		Day = d;
		Month = m;
		Year = y;
	}
	void print()
	{
		cout << Day << "/" << Month << "/" << Year;
	}

	void ReadDataFromFile(ifstream& fin)
	{
		fin >> Day;
		fin >> Month;
		fin >> Year;
	}
	int getDay()
	{
		return Day;
	}
	int getMonth()
	{
		return Month;
	}
	int getYear()
	{
		return Year;
	}
	int Compare(Date d2)
	{
		int d1Day = Day;
		int d1Month = Month;
		int d1Year = Year;

		int d2Day = d2.Day;
		int d2Month = d2.Month;
		int d2Year = d2.Year;

		if (d1Day > d2Day || d1Month > d2Month || d1Year > d2Year)
		{
			if (d1Day > d2Day && d1Month >= d2Month && d1Year >= d2Year)
			{
				return 1;
			}
			else if (d1Day >= d2Day && d1Month > d2Month && d1Year >= d2Year)
			{
				return 1;

			}
			else if (d1Day >= d2Day && d1Month >= d2Month && d1Year > d2Year)
			{
				return 1;
			}
			else if (d1Day >= d2Day && d1Month <= d2Month && d1Year > d2Year) {
				return 1;
			}
			else if (d1Day < d2Day && d1Month >= d2Month && d1Year >= d2Year)
			{
				return -1;
			}
			else if (d1Day >= d2Day && d1Month < d2Month && d1Year >= d2Year)
			{
				return -1;

			}
			else if (d1Day >= d2Day && d1Month >= d2Month && d1Year < d2Year)
			{
				return -1;
			}


		}
		else if (d1Day == d2Day && d1Month == d2Month && d1Year == d2Year)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	int operator-(Date d)
	{
		int result = Year - d.Year;
		return result;
	}
};
Date Date::CurrentDate = Date(); //initialization of static member 

class Object
{
public:
	char* iD;
public:
	Object()
	{
		iD = 0;
	}

	//pure virtual functions
	virtual void AddpostTotimeline(Posts* p) = 0;
	virtual void PrintlistView() = 0;
	virtual void printlistView(bool) = 0;


	char* getiD()
	{
		return iD;
	}
	void setiD(char* id)
	{
		iD = Helper::GetStringFromBuffer(id);
	}
	virtual ~Object()
	{
		if (iD)
		{
			delete[]iD;
		}
	}
};

class Comment
{
private:
	char* id;
	Object* commentby;
	char* text;
public:
	static int TotalComments;
	Comment()
	{
		id = 0;
		commentby = 0;
		text = 0;
	}
	void SetValues(char* ID, char* Text, Object* CommentBy)
	{
		id = Helper::GetStringFromBuffer(ID);
		text = Helper::GetStringFromBuffer(Text);
		commentby = CommentBy;
	}
	void printComment()
	{
		commentby->printlistView(0); cout << " wrote: \"" << text << " \"\n";
	}

	char* NewId()
	{
		id = new char[4];
		int F = 0;
		int L = 0;
		Comment::TotalComments++;
		F = Comment::TotalComments / 10;
		L = Comment::TotalComments % 10;
		id[0] = 'c';
		id[1] = F + '0';
		id[2] = L + '0';
		id[3] = '\0';
		return id;
	}
	char* GetID()
	{
		return id;
	}
	~Comment()
	{

		if (id)
		{
			delete[]id;
		}
		if (text)
		{
			delete[]text;
		}
	}
};
int Comment::TotalComments = 0;



class Activity
{
private:
	int Type;
	char* value;
public:
	Activity()
	{
		Type = 0;
		value = 0;
	}

	void ReadDataFromFile(ifstream& fin)
	{
		fin >> Type;
		char temp[100];
		fin.getline(temp, 100);
		value = Helper::GetStringFromBuffer(temp);
	}

	void printActivity()
	{
		if (Type == 1)
		{
			cout << " is Feeling" << value << endl;
		}
		else if (Type == 2)
		{
			cout << " is Thinking about" << value << endl;
		}
		else if (Type == 3)
		{
			cout << " is Making" << value << endl;
		}
		else if (Type == 4)
		{
			cout << " is Celebrating" << value << endl;
		}
	}
	~Activity()
	{
		if (value)
		{
			delete[] value;
		}
	}
};


class Posts
{
private:
	char* Text;
	Date SharedDate;
	Activity* activity;
	Object* SharedBy;
	Object** LikedBy;
	Comment** comments;
	char* PostID;
	int PostType;
	int noOfLikedPosts;
	int noOfcomments;
public:
	static int  TotalPosts;
	Posts()
	{
		Text = 0;
		activity = 0;
		SharedBy = 0;
		LikedBy = new Object * [MaxLikes];
		for (int i = 0; i < MaxLikes; i++)
		{
			LikedBy[i] = 0;
		}
		comments = new Comment * [MaxComments];
		for (int i = 0; i < MaxComments; i++)
		{
			comments[i] = 0;
		}
		PostID = 0;
		PostType = 0;
		noOfLikedPosts = 0;
		noOfcomments = 0;
	}
	void AddComment(Comment* com)
	{
		if (noOfcomments < MaxComments)
		{
			comments[noOfcomments++] = com;
		}
		else
		{
			cout << "Comments limit reached !\n";
		}
	}

	void ReadDataFromFile(ifstream& fin)
	{
		char Temp[200];
		fin >> PostType;
		fin >> Temp;
		PostID = Helper::GetStringFromBuffer(Temp);
		SharedDate.ReadDataFromFile(fin);
		fin.ignore();

		fin.getline(Temp, 200);

		Text = Helper::GetStringFromBuffer(Temp);
		if (PostType == 2)
		{
			activity = new Activity;
			activity->ReadDataFromFile(fin);
		}

	}

	void setShareBy(Object* s)
	{
		SharedBy = s;
	}

	Object* getShareBy()
	{
		return SharedBy;
	}

	virtual void printPost(bool date = 1, bool cmnt = 1)
	{
		if (PostType == 2)
		{
			SharedBy->printlistView(1);  activity->printActivity();

			cout << "    \"" << Text;
			if (date == 1)
			{
				cout << "\" ...("; SharedDate.print(); cout << ")\n\n";
			}
			else
			{
				cout << " \"\n";
			}

			if (cmnt == 1)
			{
				for (int i = 0; i < noOfcomments; i++)
				{
					cout << "\t\t ";
					if (comments[i] != 0)
					{
						comments[i]->printComment();
					}

				}
				cout << "\n\n";
			}
		}
		else
		{
			SharedBy->printlistView(1); cout << " shared \" "  << Text;
			if (date == 1)
			{
				cout << "\" ...("; SharedDate.print(); cout << ")\n\n";
			}
			else
			{
				cout << " \"\n";
			}

			if (cmnt == 1)
			{
				for (int i = 0; i < noOfcomments; i++)
				{
					cout << "\t\t ";
					if (comments[i] != 0)
					{
						comments[i]->printComment();
					}
				}
				cout << "\n\n";
			}

		}
	}

	Date getSharedDate()
	{
		return SharedDate;
	}

	void LikePost(Object* o)
	{
		if (noOfLikedPosts < MaxLikes)
		{
			LikedBy[noOfLikedPosts++] = o;
		}
		else
		{
			cout << "liked limit reached";
		}
	}
	void likePost(Object* o)
	{
		cout << "Command:\t\t LikePost(" << Posts::getiD() << ")\n";
		if (noOfLikedPosts < MaxLikes)
		{
			LikedBy[noOfLikedPosts++] = o;
		}
		else
		{
			cout << "liked limit reached";
		}
	}
	void viewPost()
	{
		cout << "Command:                   ViewPost((" << Posts::getiD() << ")\n\n";
		printPost();
		cout << "---------------------------------------------------------------------------------------------------------------------\n";

	}
	void viewLikedlist()
	{
		cout << "---------------------------------------------------------------------------------------------------------------------\n";

		cout << "Command:                   ViewLikedList(" << PostID << ")\n\n";
		cout << "Post Liked By: \n";
		if (LikedBy[0] != 0)
		{
			for (int i = 0; i < noOfLikedPosts; i++)
			{
				LikedBy[i]->PrintlistView();
			}
		}

		else
		{
			cout << "no likes";
		}
		cout << "---------------------------------------------------------------------------------------------------------------------\n";

	}
	char* getiD()
	{
		return PostID;
	}

	int GetDay()
	{
		return SharedDate.getDay();
	}
	int GetMonth()
	{
		return SharedDate.getMonth();
	}
	void SetValues(Object* Optr, char* txt)
	{
		SharedBy = Optr;
		SharedDate = Date::CurrentDate;
		Text = Helper::GetStringFromBuffer(txt);
	}
	char* getText()
	{
		return Text;
	}
	virtual ~Posts()
	{
		if (Text)
		{
			delete[]Text;
		}
		if (PostID)
		{
			delete[]PostID;
		}
		if (LikedBy)
		{
			delete[]LikedBy;
		}
		if (comments)
		{
			for (int i = 0; i < noOfcomments; i++)
			{
				delete comments[i];
			}
			delete comments;
		}

	}

};
int Posts::TotalPosts = 0;

class Memory :public Posts
{
private:
	Posts* originalPost;

public:
	Memory(Posts* p, char* t)
	{
		originalPost = p;
		SetValues(originalPost->getShareBy(), t);
	}
	void printPost(bool date = 1, bool cmnt = 1)
	{
		cout << "~~~ ";
		getShareBy()->printlistView(0);
		cout << " shared a memory ~~~ ...("; Date::CurrentDate.print(); cout << ")\n";
		cout << "  \" " << getText() << " \"\n";
		cout << "\t\t\t(" << Date::CurrentDate - originalPost->getSharedDate() << " Years Ago)\n";
		originalPost->printPost(1, 0);
	}

};

class Page :public Object
{

private:
	char* Title;
	Posts** timeline;
	int noOfPostinTimeline;
public:
	static int TotalPages;
	Page()
	{
		Title = 0;
		timeline = new Posts * [10];
		for (int i = 0; i < 10; i++)
		{
			timeline[i] = 0;
		}
		noOfPostinTimeline = 0;
	}
	void PrintlistView()
	{
		cout << getiD() << " --" << Title << "\n";
	}
	void printlistView(bool ch=1)
	{
		if(ch==1)
		{
			cout << "---" << Title;
		}
		else if (ch == 0)
		{
			cout << Title;
		}
	}

	void ReadDataFromFile(ifstream& fin)
	{
		char Temp[50];
		fin >> Temp;
		setiD(Temp);

		fin.getline(Temp, 50);
		Title = Helper::GetStringFromBuffer(Temp);

	}
	void AddpostTotimeline(Posts* p)
	{
		if (noOfPostinTimeline < 10)
		{
			timeline[noOfPostinTimeline++] = p;
		}
		else
		{
			cout << "Time Lint limit reached";
		}
	}
	void printTimeline()
	{
		for (int i = 0; i < noOfPostinTimeline; i++)
		{
			timeline[i]->printPost();
		}
	}
	void ViewRecent()
	{
		Date d = Date::getCurrentDate();
		d.Yesteday();
		for (int i = 0; i < noOfPostinTimeline; i++)
		{
			if (timeline[i]->getSharedDate().Compare(Date::getCurrentDate()) == 0 || timeline[i]->getSharedDate().Compare(d) == 0)
			{
				timeline[i]->printPost(0);
			}
		}
	}
	void viewPages()
	{
		cout << "---------------------------------------------------------------------------------------------------------------------\n";
		cout << "Command:                   ViewPost((" << Object::getiD() << ")\n\n";
		printlistView(0); cout << "\n ";
		printTimeline();
		cout << "---------------------------------------------------------------------------------------------------------------------\n";

	}
	~Page()
	{
		if (Title)
		{
			delete[] Title;

		}
		if (timeline)
		{
			for (int i = 0; i < noOfPostinTimeline; i++)
			{
				delete timeline[i];
			}
			delete timeline;
		}
	}
};
int Page::TotalPages = 0;

class Users :public Object
{
private:

	char* Fname;
	char* Lname;

	Page** LikedPages;
	Users** friendList;
	Posts** timeline;


	int fcount;
	int pcount;


	int noOfPostsInTimeline;

public:
	static int TotalUsers;

	Users()
	{
		Fname = 0;
		Lname = 0;

		LikedPages = new Page * [MaxLikedPages];
		for (int i = 0; i < MaxLikedPages; i++)
		{
			LikedPages[i] = 0;
		}

		friendList = new Users * [MaxFriends];
		for (int i = 0; i < MaxFriends; i++)
		{
			friendList[i] = 0;
		}

		timeline = new Posts * [10];
		for (int i = 0; i < 10; i++)
		{
			timeline[i] = 0;
		}


		fcount = 0;
		pcount = 0;

		noOfPostsInTimeline = 0;
	}

	void LikedPage(Page* ptr)
	{

		int count = 0;

		for (int i = 0; i < MaxLikedPages; i++)
		{
			if (LikedPages[i] != 0)
			{
				count++;
			}
		}

		if (count == MaxLikedPages)
		{
			cout << "Liked Pages LIMIT REACHED! \n";
		}

		else
		{
			bool check = false;
			if (check != true)
			{
				for (int i = 0; i < MaxLikedPages; i++)
				{
					if (LikedPages[i] == 0)
					{
						LikedPages[i] = ptr;
						pcount++;
						break;
					}
				}
			}
		}
	}

	void AddFriend(Users* u)
	{

		int count = 0;
		for (int i = 0; i < MaxFriends; i++)
		{
			if (friendList[i] != 0)
			{
				count++;
			}
		}
		if (count == MaxFriends)
		{
			cout << " FRIEND LIMIT REACHED! \n";

		}
		else
		{
			bool check = false;
			if (check != true)
			{
				for (int i = 0; i < MaxFriends; i++)
				{
					if (friendList[i] == 0)
					{
						friendList[i] = u;
						fcount++;
						break;
					}
				}
			}
		}
	}


	void ViewFriendlist()
	{
		cout << "Command:\t\tView Friend List\n";
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << Fname << " " << Lname << "- Friend List\n\n";
		if (friendList[0] != 0)
		{
			for (int i = 0; i < fcount - 1; i++)
			{
				friendList[i]->PrintlistView();
			}
		}

		else
		{
			cout << "You have no friends \n";
		}
	}
	void ViewLikedPages()
	{
		cout << "\nCommand:\t\tView Liked Pages\n";
		cout << "------------------------------------------------------------------------------------------------------------\n";
		cout << Fname << " " << Lname << "- Liked Pages\n\n";
		if (LikedPages[0] != 0)
			for (int i = 0; i < pcount - 1; i++)
			{
				LikedPages[i]->PrintlistView();
			}

		else
		{
			cout << "You have no liked Pages";
		}
	}

	void ViewHome()
	{
		cout << "\n\n\nCommand:\t\t ViewHome\n";
		cout << "---------------------------------------------------------------------------------------------------------------\n";
		cout << Fname << " " << Lname << " -- Home Page\n\n";
		if (friendList[0] != 0)
		{
			for (int i = 0; i < fcount - 1; i++)
			{
				friendList[i]->ViewRecent();
			}
		}
		if (LikedPages[0] != 0)
		{
			for (int i = 0; i < pcount - 1; i++)
			{
				LikedPages[i]->ViewRecent();
			}
		}
		else
		{
			cout << "No post to Show as you have no friends and Liked Pages";
		}
		cout << "---------------------------------------------------------------------------------------------------------------\n";
	}

	void ViewRecent()
	{
		Date d = Date::getCurrentDate();
		d.Yesteday();
		for (int i = 0; i < noOfPostsInTimeline; i++)
		{
			if (timeline[i]->getSharedDate().Compare(Date::getCurrentDate()) == 0 || timeline[i]->getSharedDate().Compare(d) == 0)
			{
				timeline[i]->printPost(0);
			}
		}
	}

	void ViewTimeline()
	{
		cout << "\nCommand:\t\t ViewTimeline\n\n";

		cout << Fname << " " << Lname << " -- Time Line\n\n";
		if (timeline[0] != 0)
		{
			for (int i = 0; i < noOfPostsInTimeline; i++)
			{
				timeline[i]->printPost();
			}
		}
		else
		{
			cout << "You have not shared any Post\n";
		}

	}
	void printTimeline()
	{
		for (int i = 0; i < noOfPostsInTimeline; i++)
		{
			timeline[i]->printPost();
		}
	}

	void CurrentUser()
	{
		cout << "\nCommand:\t\tSet current user \"" << Object::getiD() << "\"\n\n";
		if (Fname != 0 && Lname != 0)
		{
			cout << " \"" << Fname << " " << Lname << "\" " << " successfully set as Current User\n\n";
		}
		else
		{
			cout << "NO USER FOUND";
		}
	}
	void PrintlistView()
	{
		cout << getiD() << " -- " << Fname << " " << Lname << "\n";
	}
	void printlistView(bool ch=1)
	{
		if(ch==1)
		{
			cout << " --- " << Fname << " " << Lname;
		}
		else if (ch == 0)
		{
			cout << Fname << " " << Lname;
		}
	}
	void SeeMemories()
	{
		cout << "Command:			SeeYouMemories()\n\n";
		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n\n";

		for (int i = 0; i < noOfPostsInTimeline; i++)
		{
			int n = Date::CurrentDate - timeline[i]->getSharedDate();
			if (timeline[i]->GetDay() == Date::CurrentDate.getDay() && timeline[i]->GetMonth() == Date::CurrentDate.getMonth() && n != 0)
			{
				cout << "On this Day\n" << n << " Years ago\n";
				timeline[i]->printPost();
			}
		}
		cout << "---------------------------------------------------------------------------------------------------------------------\n";

	}

	void ShareMemory(Posts* P, char* t)
	{
		cout << "Command\t\t Share Memory(" << P->getiD() << "," << t << ")";
		timeline[noOfPostsInTimeline] = new Memory(P, t);
		noOfPostsInTimeline++;
	}

	void ReadDataFromFile(ifstream& fin)
	{
		char Temp[50];
		fin >> Temp;
		setiD(Temp);
		fin >> Temp;
		Fname = Helper::GetStringFromBuffer(Temp);
		fin >> Temp;
		Lname = Helper::GetStringFromBuffer(Temp);

	}

	void AddpostTotimeline(Posts* p)
	{
		if (noOfPostsInTimeline < 10)
		{
			timeline[noOfPostsInTimeline++] = p;
		}
		else
		{
			cout << "Post can not be add to the time line as limit reached\n";
		}
	}

	void postComment(Posts* p, char* txt)
	{
		cout << "Command:                   PostComment(" << p->getiD() << "," << txt << ")\n";
		Comment* c = new Comment;
		char* a = Helper::GetStringFromBuffer(c->NewId());
		//cout << c->GetID();
		c->SetValues(a, txt, this);
		p->AddComment(c);
	}

	~Users()
	{
		if (Lname)
		{
			delete[] Lname;
			Lname = 0;
		}
		if (Fname)
		{
			delete[] Fname;
			Fname = 0;
		}
		if (friendList)
		{
			delete[] friendList;
			friendList = 0;
		}
		if (LikedPages)
		{
			delete[] LikedPages;
			LikedPages = 0;
		}
		if (timeline)
		{
			for (int i = 0; i < noOfPostsInTimeline; i++)
				delete timeline[i];
			delete timeline;
		}
	}
};
int Users::TotalUsers = 0;
class FaceBook {

private:
	Page** pages;
	Users** users;
	Posts** posts;
public:

	FaceBook()
	{
		pages = 0;
		users = 0;
		posts = 0;
	}

	Page* SearchPageByID(char* p)
	{
		bool check = 0;
		for (int i = 0; i < Page::TotalPages; i++)
		{
			int z = Helper::FirstIndexOfSubString(pages[i]->getiD(), p);
			if (z == 0)
			{
				check = 1;
				return pages[i];
			}
		}
		if (check == 0)
		{
			return 0;
		}
	}

	Users* SearchUserByID(char* u)
	{
		bool check = 0;
		for (int i = 0; i < Users::TotalUsers; i++)
		{
			int z = Helper::FirstIndexOfSubString(users[i]->getiD(), u);
			if (z == 0)
			{
				check = 1;
				return users[i];
			}
		}
		if (check == 0)
		{
			return 0;
		}

	}
	Posts* SearchPostByID(char* p)
	{
		bool check = 0;
		for (int i = 0; i < Posts::TotalPosts; i++)
		{
			int z = Helper::FirstIndexOfSubString(posts[i]->getiD(), p);
			if (z == 0)
			{
				check = 1;
				return posts[i];
			}
		}
		if (check == 0)
		{
			return 0;
		}
	}

	Object* SearchObjectByID(char* Optr)
	{
		Page* Pptr = SearchPageByID(Optr);
		Users* Uptr = SearchUserByID(Optr);
		if (Uptr != 0)
		{
			return Uptr;
		}
		else if (Pptr != 0)
		{
			return Pptr;
		}
	}
	void  LoadPagesFromFile()
	{
		ifstream fin("pages.txt");

		if (!fin.is_open())
		{
			cout << "file is not open";
		}

		else
		{
			fin >> Page::TotalPages;
			pages = new Page * [Page::TotalPages];

			for (int i = 0; i < Page::TotalPages; i++)
			{
				pages[i] = new Page;
				pages[i]->ReadDataFromFile(fin);
			}
			fin.close();
		}
	}
	void  LoadUsersFromFile()
	{
		ifstream fin("users.txt");
		if (!fin.is_open())
		{
			cout << "file is not open";
		}
		else
		{
			fin >> Users::TotalUsers;
			users = new Users * [Users::TotalUsers];

			char*** TempUsersID;
			TempUsersID = new char** [Users::TotalUsers];

			int i = 0;

			while (i < Users::TotalUsers)
			{
				TempUsersID[i] = new char* [MaxFriends];
				users[i] = new Users;
				users[i]->ReadDataFromFile(fin);
				char Temp[20];
				Temp[0] = ' ';
				int z = 0;
				while (Temp[0] != '-')
				{
					fin >> Temp;
					TempUsersID[i][z] = Helper::GetStringFromBuffer(Temp);

					z++;
				}
				TempUsersID[i][z] = 0;
				Temp[0] = ' ';
				while (Temp[0] != '-')
				{
					fin >> Temp;
					Page* pageptr;
					pageptr = SearchPageByID(Temp);
					users[i]->LikedPage(pageptr);
				}
				i++;
			}

			for (int i = 0; i < Users::TotalUsers; i++)
			{
				int z = 0;
				while (TempUsersID[i][z] != 0)
				{
					Users* uPtr = SearchUserByID(TempUsersID[i][z]);
					users[i]->AddFriend(uPtr);
					delete[]TempUsersID[i][z];
					z++;
				}
				delete[] TempUsersID[i];
			}
			delete[] TempUsersID;
			fin.close();
		}
	}

	void LoadPosts()
	{
		ifstream fin("posts.txt");
		if (!fin.is_open())
		{
			cout << "file is not open";
		}
		else
		{
			fin >> Posts::TotalPosts;
			posts = new Posts * [Posts::TotalPosts];
			for (int i = 0; i < Posts::TotalPosts; i++)
			{
				posts[i] = new Posts;
				posts[i]->ReadDataFromFile(fin);

				char temp[20];
				char* ID;
				fin >> temp;
				ID = Helper::GetStringFromBuffer(temp);
				Object* sharedBy = SearchObjectByID(ID);
				posts[i]->setShareBy(sharedBy);
				sharedBy->AddpostTotimeline(posts[i]);

				if (ID)
				{
					delete[]ID;
				}
				//______________liked by________________
				Object* like;
				while (1)
				{
					fin >> temp;
					if (Helper::stringcmp(temp, "-1") == 0)
					{
						break;
					}
					like = SearchObjectByID(temp);
					posts[i]->LikePost(like);
				}
			}
			fin.close();
		}
	}

	void LoadComment()
	{
		ifstream fin("comments.txt");
		if (!fin.is_open())
		{
			cout << "file is not open";
		}
		else
		{
			fin >> Comment::TotalComments;
			for (int i = 0; i < Comment::TotalComments; i++)
			{
				Comment* comment = new Comment;
				char temp[100];
				fin >> temp;
				char* ID;
				char* postID;
				char* commentby;
				char* Text;
				ID = Helper::GetStringFromBuffer(temp);
				fin >> temp;
				postID = Helper::GetStringFromBuffer(temp);
				Posts* postPtr = SearchPostByID(postID);
				postPtr->AddComment(comment);
				fin >> temp;
				commentby = Helper::GetStringFromBuffer(temp);
				Object* CmntBy = SearchObjectByID(commentby);
				fin.getline(temp, 100);
				Text = Helper::GetStringFromBuffer(temp);
				comment->SetValues(ID, Text, CmntBy);
				if (ID)
				{
					delete[]ID;
				}
				if (postID)
				{
					delete[]postID;
				}
				if (commentby)
				{
					delete[]commentby;
				}
				if (Text)
				{
					delete[]Text;
				}
			}
			fin.close();
		}
	}
	void Load()
	{
		LoadPagesFromFile();
		LoadUsersFromFile();
		LoadPosts();
		LoadComment();
	}
	void Run()
	{
		Date d(15, 11, 2017);
		Date::SetCurrentDate(d);
		char ID[5] = "u7";
		Users* user;
		user = SearchUserByID(ID);
		if (user != 0)
		{
			user->CurrentUser();
			user->ViewFriendlist();
			user->ViewLikedPages();
			user->ViewHome();
			user->ViewTimeline();

			char p1[] = "post5";

			Posts* post1;
			post1 = SearchPostByID(p1);
			post1->viewLikedlist(); cout << endl;

			post1->likePost(user);
			post1->viewLikedlist();



			char p2[] = "post4";
			char cmt[] = "Good luck for your result";
			Posts* post2;
			post2 = SearchPostByID(p2);
			user->postComment(post2, cmt);
			post2->viewPost();



			char p3[] = "post8";
			char cm[] = "Thanks for wishes";


			Posts* post3;
			post3 = SearchPostByID(p3);
			user->postComment(post3, cm);
			post3->viewPost();


			char pid[] = "post10";
			char txt[] = "Never thought I will be specialist in this field...";
			Posts* pp = SearchPostByID(pid);
			user->SeeMemories();
			user->ShareMemory(pp, txt);

			user->ViewTimeline();


			char page[] = "p1";
			Page* p = SearchPageByID(page);
			p->viewPages();

		}
		else
		{
			cout << "\n\t\t\t\t\t\tNo Such User Found!\n\n";
		}
	}

	~FaceBook()
	{
		if (pages)
		{
			for (int i = 0; i < Page::TotalPages; i++)
			{
				delete pages[i];
			}
			delete[] pages;
			pages = 0;
		}

		if (users)
		{
			for (int i = 0; i < Users::TotalUsers; i++)
			{
				delete users[i];

			}
			delete[] users;

		}

		if (posts)
		{
			delete[] posts;
		}

	}
};
int main()
{
	FaceBook fb;
	fb.Load();
	fb.Run();
	system("pause");
	return 0;
}