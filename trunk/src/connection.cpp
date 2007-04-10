/**
 * $Header$
 *
 * Autor: Leonardo Alves - leonhad@gmail
 * Tamanho da tabulação: 4
 * Codificação: ISO 8859-1
 * $Date$
 *
 * Implementação da classe que gerencia a conexão com o banco de dados.
 *
 * $Revision$
 */
#include "resultset.h"
#include "connection.h"

/**
 * \brief Construtor.
 *
 * \param host			Nome ou IP da máquina onde se encontra a base de dados.
 * \param port			Número da porta que receberá a conexão.
 * \param database		Nome da base de dados.
 * \param login			Login do usuário.
 * \param password		Senha do usuário.
 *
 * \exception 
 */
Connection::Connection(string host, string port, string database, string login, string password) throw (SQLException)
{
	_conn = PQsetdbLogin(host.c_str(), port.c_str(), NULL, NULL, database.c_str(), login.c_str(), password.c_str());
	if (PQstatus(_conn) == CONNECTION_BAD) {
        throw SQLException(PQerrorMessage(_conn), BAD_CONNECTION);
    }
}

/**
 * \brief Executa um comando de seleção (SELECT).
 *
 * \param query		Comando SQL a ser executado.
 *
 * \return Retorna o resultado do comando como uma classe ResultSet.
 *
 * \exception NULL_PARAMETER	Ocorre quando resultado do comando for nulo.
 * \exception EMPTY_QUERY		Ocorre quando a string do comando enviado estava vazia.
 * \exception BAD_RESPONSE		Ocorre quando não foi possível entender a resposta do servidor.
 * \exception NONFATAL_ERROR	Ocorre quando há um erro não identificado, mas não fatal.
 * \exception FATAL_ERROR		Ocorre quando há um erro não identificado e fatal.
 */
ResultSet *
Connection::executeQuery(string query) throw (SQLException)
{
    PGresult *result = PQexec(_conn, query.c_str());
	ResultSet *rs = NULL;

	try {
		rs = new ResultSet(result);
	} catch (const SQLException& e) {
		if (rs)	delete rs;
		throw e;
	}
    
	return rs;
}

/**
 * \brief Executa um comando de atualização (UPDATE, INSERT ou DELETE).
 *
 * \param update	Comando SQL a ser executado.
 *
 * \return Retorna a quantidade de linhas afetadas pelo comando.
 *
 * \exception NULL_PARAMETER	Ocorre quando resultado do comando for nulo.
 * \exception EMPTY_QUERY		Ocorre quando a string do comando enviado estava vazia.
 * \exception BAD_RESPONSE		Ocorre quando não foi possível entender a resposta do servidor.
 * \exception NONFATAL_ERROR	Ocorre quando há um erro não identificado, mas não fatal.
 * \exception FATAL_ERROR		Ocorre quando há um erro não identificado e fatal.
 */
int 
Connection::executeUpdate(string update) throw (SQLException)
{
    PGresult *result = PQexec(_conn, update.c_str());
    ResultSet *rs = NULL;

	try {
		rs = new ResultSet(result);
	} catch (const SQLException& e) {
		if (rs) delete rs;
		throw e;
	}

	int lines = rs->lines();
	if (rs) delete rs;

    return lines;
}

// $Source$
