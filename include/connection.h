/**
 * $Header$
 *
 * Autor: Leonardo Alves - leonhad@gmail
 * Tamanho da tabula��o: 4
 * Codifica��o: ISO 8859-1
 * $Date$
 *
 * Declara��o da classe que gerencia a conex�o com o banco de dados.
 *
 * $Revision$
 */
#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <libpq-fe.h>
#include "sqlexception.h"

class ResultSet;
using std::string;

/**
 * \brief Classe que gerencia a conex�o com o banco de dados.
 */
class Connection
{
private:
    PGconn *_conn;
    
public:
	Connection(string host, string port, string database, string login, string password) throw (SQLException);
	inline ~Connection();

	ResultSet * executeQuery(string query) throw (SQLException);
	int executeUpdate(string update) throw (SQLException);
};

/**
 * \brief Destrutor.
 */
inline
Connection::~Connection()
{
	PQfinish(_conn);
}

#endif // CONNECTION_H

// $Source$
