/*
 * $Header$
 *
 * Autor: Leonardo Alves - leonhad@gmail
 * Tamanho da tabula��o: 4
 * Codifica��o: ISO 8859-1
 * $Date$
 *
 * Declara��o da classe que interpreta os poss�veis resultados de um comando SQL.
 *
 * $Revision$
 */
#ifndef RESULTSET_H
#define RESULTSET_H

#include <string>
#include <libpq-fe.h>
#include "sqlexception.h"

using std::string;

/// Classe que interpreta os poss�veis resultados de um comando SQL.
class ResultSet {
private:
    // ResultSet do comando SQL
    PGresult *_result;
    // N�mero de linhas afetadas/retornadas
    int _lines;
    // Linha atual do resultado
    int _cursor;
    // N�mero de colunas
    int _columns;
    
public:
	ResultSet(PGresult *result) throw (SQLException);
	~ResultSet();

	inline int lines() const;
	inline int columns() const;
	bool next();
	bool isNull(int index) throw (SQLException);
	bool isNull(string columnName) throw (SQLException);
	
	string stringValue(string columnName) throw (SQLException);
	string stringValue(int index) throw (SQLException);
	int intValue(string columnName) throw (SQLException);
	int intValue(int columnIndex) throw (SQLException);
	float floatValue(string coluna) throw (SQLException);
	float floatValue(int coluna) throw (SQLException);

	// TODO Acrescentar retorno para os tipos data e hora

private:
    inline void checkColumn(int index) throw (SQLException);
	inline int checkColumn(string columnName) throw (SQLException);
};

/**
 * \brief Obt�m a quantidade de linhas afetadas pelo comando.
 *
 * \return A quantidade de linhas afetadas pelo comando.
 */
inline int
ResultSet::lines() const
{
	return _lines;
}

/**
 * \brief Obt�m a quantidade de colunas afetadas pelo comando.
 *
 * \return A quantidade de colunas afetadas pelo comando.
 */
inline int
ResultSet::columns() const
{
	return _columns;
}

inline void 
ResultSet::checkColumn(int index) throw (SQLException)
{
    if (index < 0 || index > _columns) {
        throw SQLException("ResultSet::checkColumn: Index is out of bounds", INDEX_OUT_OF_BOUNDS);
    }
}

inline int 
ResultSet::checkColumn(string columnName) throw (SQLException)
{
	int index = PQfnumber(_result, columnName.c_str());

	if (index == -1) {
		string msg = "Column ";
		msg += columnName + " not exists";
		throw SQLException(msg, INVALID_COLUMN);
	}

	return index;
}

#endif // RESULTSET_H

// $Source$
