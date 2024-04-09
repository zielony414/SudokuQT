#include "MySQL.h"

MySQL::MySQL() {
    try {
        driver = get_driver_instance();
        con = driver->connect(IP, user, password);
        con->setSchema(database);
        stmt = con->createStatement();
        res = nullptr;
    }
    catch (SQLException& e) {
        cout << "SQLException: " << e.what() << endl;
    }
    catch (std::runtime_error& e) {
        cout << "RuntimeError: " << e.what() << endl;
    }
}

MySQL::~MySQL() {
    delete stmt;
    delete con;
    if (res != nullptr) {
        delete res;
    }
}


bool MySQL::verify_account(string login, string passw)
{
    stringstream query;
    query << "SELECT COUNT(*) FROM Users WHERE login =  '" << login << "' AND password = '"<< passw <<"'";

    // Wykonanie zapytania
    res = stmt->executeQuery(query.str());

    // Sprawdzenie, czy wynik zapytania jest poprawny
    if (res && res->next()) {
        int count = res->getInt(1); 
        
        if (count == 1) {
            delete res;
            return true;
        }
        else {
            delete res;
            return false;
        }
    }
    else {
        delete res; 
        return false;
    }
}

bool MySQL::add_account(string login, string passw)
{
    try {
        // Tworzenie zapytania INSERT INTO
        stringstream query;
        query << "INSERT INTO `users` (`login`, `password`) VALUES ('" << login << "', '" << passw << "')";

        stmt->executeUpdate(query.str());

        return true; // Powodzenie operacji
    }
    catch (SQLException& e) {
        cout << "SQLException: " << e.what() << endl;
        return false;
    }
    catch (std::runtime_error& e) {
        cout << "RuntimeError: " << e.what() << endl;
        return false;
    }

    return false;
}

bool MySQL::is_in_database(string login)
{
    stringstream query;
    query << "SELECT COUNT(*) FROM Users WHERE login =  '" << login << "'";

    res = stmt->executeQuery(query.str());

    if (res && res->next()) {
        int count = res->getInt(1);

        if (count != 0) {
            delete res;
            return true;
        }
        else {
            delete res;
            return false;
        }
    }
    else {
        delete res;
        return false;
    }
}

ResultSet* MySQL::return_score(const int level_id) {
    
    stringstream query;

    switch (level_id) {
    case 1:
        query << "SELECT `users`.`login`, `scores`.`Score`, `scores`.`Difficulty_level`, `scores`.`Date` FROM `users` LEFT JOIN `scores` ON `scores`.`User_ID` = `users`.`ID` WHERE `scores`.`Difficulty_level` = '1' ORDER BY `scores`.`Score` DESC; ";
        res = stmt->executeQuery(query.str());
        break;

    case 2:
        query << "SELECT `users`.`login`, `scores`.`Score`, `scores`.`Difficulty_level`, `scores`.`Date` FROM `users` LEFT JOIN `scores` ON `scores`.`User_ID` = `users`.`ID` WHERE `scores`.`Difficulty_level` = '2' ORDER BY `scores`.`Score` DESC; ";
        res = stmt->executeQuery(query.str());
        break;

    case 3:
        query << "SELECT `users`.`login`, `scores`.`Score`, `scores`.`Difficulty_level`, `scores`.`Date` FROM `users` LEFT JOIN `scores` ON `scores`.`User_ID` = `users`.`ID` WHERE `scores`.`Difficulty_level` = '3' ORDER BY `scores`.`Score` DESC; ";
        res = stmt->executeQuery(query.str());
        break;

    case 4:
        query << "SELECT `users`.`login`, `scores`.`Score`, `scores`.`Difficulty_level`, `scores`.`Date` FROM `users` LEFT JOIN `scores` ON `scores`.`User_ID` = `users`.`ID` ORDER BY `scores`.`Score` DESC; ";
        res = stmt->executeQuery(query.str());
        break;

    default:
        query << "SELECT `users`.`login`, `scores`.`Score`, `scores`.`Difficulty_level`, `scores`.`Date` FROM `users` LEFT JOIN `scores` ON `scores`.`User_ID` = `users`.`ID` ORDER BY 'scores' DESC; ";
        res = stmt->executeQuery(query.str());
        break;
    }

    return res;
}

bool MySQL::export_score(string login, int level_id, int score)
{
    int player_id{};
    stringstream select_query;
    select_query << "SELECT ID FROM Users WHERE login = '" << login << "'";

    res = stmt->executeQuery(select_query.str());

    if (res->next()) {
        player_id = res->getInt("ID");
    }

    std::time_t czas = std::time(nullptr);
    std::tm* dataCzas = std::localtime(&czas);

    // Wyświetlenie daty w formacie "DD.MM.RRRR"
    const int dzien = dataCzas->tm_mday;
    const int miesiac = dataCzas->tm_mon + 1; // tm_mon liczy miesiące od 0 do 11
    const int rok = dataCzas->tm_year + 1900;

    const std::string Czas = std::to_string(rok) + "-" + std::to_string(miesiac) + "-" + std::to_string(dzien);

    try {
        // Tworzenie zapytania INSERT INTO
        stringstream insert_query;
        insert_query << "INSERT INTO `scores` (`Score`, `Difficulty_level`, `User_ID`, `Date`) VALUES ('"<< score << "','" << level_id << "', '" << player_id << "','" << Czas << "')";

        // Wykonanie zapytania
        stmt->executeUpdate(insert_query.str());

        return true; // Powodzenie operacji
    }
    catch (SQLException& e) {
        cout << "SQLException: " << e.what() << endl;
        return false;
    }
    catch (std::runtime_error& e) {
        cout << "RuntimeError: " << e.what() << endl;
        return false;
    }
}
