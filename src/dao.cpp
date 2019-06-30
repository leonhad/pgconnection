/*
 * Implementação da classe que representa os objetos para acesso direto (DAO - Direct Acess Object).
 */
#include "dao.h"

/**
 * \brief Construtor.
 *
 * \param conn		Conexão com a base de dados.
 *
 * \exception NULL_PARAMETER	Ocorre quando conn é um ponteiro nulo.
 */
DAO::DAO(Connection *conn) throw (SQLException)
{
	if (!conn)
    {
		throw SQLException("DAO::DAO(): invalid connection", NULL_PARAMETER);
    }

	this->conn = conn;
}

/**
 * \brief Converte a string dada para sequ�ncia de escape compat�vel com o banco de dados.
 *
 * \param str	String a ser convertida.
 *
 * \return A string resultante da convers�o.
 */
string DAO::escape(string str)
{
    if (str.empty()) {
        return "NULL";
    }

    char *u = new char[str.size() * 2 + 1];
    PQescapeString(u, str.c_str(), str.size());
    string temp = "'";
    temp += u;
    temp += "'";
    delete [] u;
    return temp;
}

// $Source$
