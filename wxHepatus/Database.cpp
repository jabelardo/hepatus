#include <wxHepatus/Database.h>
#include <wxHepatus/GetPot>
#include <fstream>
#include <stdexcept>
#include <sstream>

namespace wxHepatus
{

Database::Database(std::string const& configFile)
	: configFile(configFile)
{
	std::ifstream file;
    file.open(configFile.c_str());
    if (!file) {
        throw std::runtime_error("can't open file " + configFile);      
    }
}

Database::~Database()
{
	close();
}

void
Database::close()
{
	if (mysql.get()) {
		mysql_close(mysql.get());
	}
}

Database::Connection::Connection(Database& database)
	: database(database)
{
	database.connect();
}

Database::Connection::~Connection()
{
	database.close();
}
    	
Database::MySqlResult
Database::execute(std::string const& query)
{		
	if (query.empty()) {
		throw std::runtime_error("Empty query");
	}
	Connection connection(*this);	    			
	int const ER_LOCK_WAIT_TIMEOUT = 1205;
	int const ER_LOCK_DEADLOCK = 1213;
	int const MAX_TRIES = 100;	
	for (int i = 0; i < MAX_TRIES; ++i) {
        if (mysql_query(mysql.get(), query.c_str()) == 0) {
            return MySqlResult(mysql.get());            
        }
        int err = mysql_errno(mysql.get());
        if (err == ER_LOCK_WAIT_TIMEOUT || err == ER_LOCK_DEADLOCK) {
            timespec t;
            t.tv_sec = 0;
            t.tv_nsec = 100000000;
            nanosleep(&t, NULL);
        } else {
        	break; 
	    }
    }
    std::ostringstream oss;
    oss << "MySQL Error(" << mysql_errno(mysql.get()) << "): " << mysql_error(mysql.get());  
    throw std::runtime_error(oss.str());
}

Database::MySqlResult::MySqlResult(MYSQL* mysql)
	: result(mysql_store_result(mysql))
{
}

Database::MySqlResult::~MySqlResult()
{
	if (result) {
		mysql_free_result(result);
	}
}

MYSQL_ROW 
Database::MySqlResult::getRow()
{
	return mysql_fetch_row(result);
}
    	
bool 
Database::validarUsuario(std::string const& usuario, std::string const& clave)
{
	std::ostringstream oss;
	oss << "SELECT * FROM Usuarios WHERE Login = '" << usuario 
	    << "' AND Password = MD5('" << clave << "') AND IdAgente = 1";
	
	MySqlResult result = execute(oss.str());	

	return result.getRow();
}

void
Database::connect()
{
	GetPot config(configFile.c_str());
    unsigned short const databasePort = config("Database/port", 3306);
    std::string const databaseHost = config("Database/host", "127.0.0.1");
    std::string const databaseUser = config("Database/user", "user");
    std::string const databasePassword = config("Database/password", "password");
    std::string const databaseName = config("Database/name", "database");
    
	std::auto_ptr<MYSQL> mysqlPtr(new MYSQL);
    mysql_init(mysqlPtr.get());
    if (!mysql_real_connect(mysqlPtr.get(), 
                            databaseHost.c_str(), 
                            databaseUser.c_str(), 
                            databasePassword.c_str(), 
                            databaseName.c_str(), 
                            databasePort, 
                            NULL, 
                            0)) {
        throw std::runtime_error(mysql_error(mysqlPtr.get()));      
    }
    close();
    mysql = mysqlPtr;
}

}
