/*
 * $Header$
 *
 * Autor: Leonardo Alves - leonhad@gmail
 * Tamanho da tabula��o: 4
 * Codifica��o: ISO 8859-1
 * $Date$
 *
 * Declara��o da classe que representa os objetos para acesso direto (DAO - Direct Acess Object).
 *
 * $Revision$
 */
#ifndef DAO_H
#define DAO_H

#include "connection.h"

/**
 * \brief Classe que representa os objetos para acesso direto (DAO - Direct Acess Object).
 */
class DAO
{
protected:
    Connection *conn;
    
public:
	DAO(Connection *conn) throw (SQLException);

	string escape(string str);
	string getSQLData(string data);
};

#endif

// $Source$

