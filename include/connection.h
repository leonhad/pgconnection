/**
 * $Header$
 *
 * Autor: Leonardo Alves - leonhad@gmail
 * Tamanho da tabulação: 4
 * Codificação: ISO 8859-1
 * $Date$
 *
 * Declaração da classe que gerencia a conexão com o banco de dados.
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
 * \brief Classe que gerencia a conexão com o banco de dados.
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
