#ifndef WXHEPATUS_DATABASE_H_
#define WXHEPATUS_DATABASE_H_

#include <string>
#include <memory>
#include <mysql/mysql.h>
#include <boost/cstdint.hpp>

namespace wxHepatus
{

class Database
{
public:
	Database(std::string const& configFile);
	~Database();

	bool validarUsuario(std::string const& usuario, std::string const& clave);
	
private:
	std::string const configFile;
    std::auto_ptr<MYSQL> mysql;
    
    class Connection
    {
    public:
    	Connection(Database& database);
    	~Connection();
    	
    private:
    	Database& database;
    };
    
    class MySqlResult
    {
	public:    	
    	MySqlResult(MYSQL* mysql);
    	~MySqlResult();
    	
    	MYSQL_ROW getRow();
    	
	private:	    	
    	MYSQL_RES * result;
    }; 
    
    MySqlResult execute(std::string const& query);
    void connect();
	void close();
};

}

#endif /*WXHEPATUS_DATABASE_H_*/
