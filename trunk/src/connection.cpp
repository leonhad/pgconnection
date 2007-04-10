/**
 * $Header$
 *
 * Autor: Leonardo Alves - leonhad@gmail
 * Tamanho da tabula��o: 4
 * Codifica��o: ISO 8859-1
 * $Date$
 *
 * Implementa��o da classe que gerencia a conex�o com o banco de dados.
 *
 * $Revision$
 */
#include "resultset.h"
#include "connection.h"

/**
 * \brief Construtor.
 *
 * \param host			Nome ou IP da m�quina onde se encontra a base de dados.
 * \param port			N�mero da porta que receber� a conex�o.
 * \param database		Nome da base de dados.
 * \param login			Login do usu�rio.
 * \param password		Senha do usu�rio.
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
 * \brief Executa um comando de sele��o (SELECT).
 *
 * \param query		Comando SQL a ser executado.
 *
 * \return Retorna o resultado do comando como uma classe ResultSet.
 *
 * \exception NULL_PARAMETER	Ocorre quando resultado do comando for nulo.
 * \exception EMPTY_QUERY		Ocorre quando a string do comando enviado estava vazia.
 * \exception BAD_RESPONSE		Ocorre quando n�o foi poss�vel entender a resposta do servidor.
 * \exception NONFATAL_ERROR	Ocorre quando h� um erro n�o identificado, mas n�o fatal.
 * \exception FATAL_ERROR		Ocorre quando h� um erro n�o identificado e fatal.
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
 * \brief Executa um comando de atualiza��o (UPDATE, INSERT ou DELETE).
 *
 * \param update	Comando SQL a ser executado.
 *
 * \return Retorna a quantidade de linhas afetadas pelo comando.
 *
 * \exception NULL_PARAMETER	Ocorre quando resultado do comando for nulo.
 * \exception EMPTY_QUERY		Ocorre quando a string do comando enviado estava vazia.
 * \exception BAD_RESPONSE		Ocorre quando n�o foi poss�vel entender a resposta do servidor.
 * \exception NONFATAL_ERROR	Ocorre quando h� um erro n�o identificado, mas n�o fatal.
 * \exception FATAL_ERROR		Ocorre quando h� um erro n�o identificado e fatal.
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
