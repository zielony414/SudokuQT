#pragma once
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace sql;

class MySQL
{
private:
	Driver* driver;
	Connection* con;

	Statement* stmt;
	ResultSet* res;

	string IP = "localhost:3306";
	string user = "root";
	string password = "";
	string database = "sudoqt";

public:
	MySQL();
	~MySQL();
	bool verify_account(string login, string passw);
	bool add_account(string login, string passw);
	bool is_in_database(string login);
	ResultSet* return_score(const int level_id);
	bool export_score(string login, int level_id, int score);
};

