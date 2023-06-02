#include <iostream>

using namespace std;

class Database 
{
protected:
	Database() 
	{
		// ...
	}

	int data = 0;

public:
	static Database& get() 
	{
		// c++ 11 이상 버전에서는 쓰레드 세이프 함.
		static Database db;
		cout << "DB 객체 생성!" << endl;
		return db;
	}

	// 복사 생성자 삭제
	Database(Database const&) = delete;
	// 이동 생성자 삭제
	Database(Database&&) = delete;
	// 복사 연산자 삭제
	Database& operator=(Database const&) = delete;
	// 이동 연산자 삭제
	Database& operator=(Database&&) = delete;

	int getDataValue()
	{
		return data;
	}
	void increaseDataValue() 
	{
		data++;
	}
};

int main()
{
	
	Database& db = Database::get();
	db.increaseDataValue();
	cout << db.getDataValue() << endl;

	Database& db2 = Database::get();
	cout << db2.getDataValue() << endl;
}
