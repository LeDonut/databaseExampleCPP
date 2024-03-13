#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <memory>

int main() {
    const string server = "tcp://localhost:3306";
    const string user = "root";
    const string password = "";
    const string database = "Local instance MySQL80";

    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

        std::unique_ptr<sql::Connection> conn(driver->connect(server, user, password));
        conn->setSchema(database);

        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        stmt->execute("DROP TABLE IF EXISTS schueler");
        stmt->execute("CREATE TABLE schueler (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), klasse VARCHAR(255))");

        std::unique_ptr<sql::PreparedStatement> pstmt;
        pstmt.reset(conn->prepareStatement("INSERT INTO schueler (name, klasse) VALUES (?, ?)"));

        string schuelerDaten[2][2] = {
                {"Max Mustermann", "10A"},
                {"Erika Mustermann", "10B"}
        };


        for (int i = 0; i < 2; ++i) {
            pstmt->setString(1, schuelerDaten[i][0]);
            pstmt->setString(2, schuelerDaten[i][1]);
            pstmt->executeUpdate();
        }

        pstmt.reset(conn->prepareStatement("SELECT id, name, klasse FROM schueler"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            cout << "ID: " << res->getInt("id") << " | Name: " << res->getString("name") << " | Klasse: " << res->getString("klasse") << endl;
        }

        conn->close();
    } catch (sql::SQLException& e) {
        cout << "SQLException: " << e.what() << endl;
        cout << "SQLState: " << e.getSQLState() << endl;
    }


    return 0;
}
