/*
 * $Header$
 *
 * Autor: Leonardo Alves - leonhad@gmail
 * Tamanho da tabulação: 4
 * Codificação: ISO 8859-1
 * $Date$
 *
 * Declaração da classe que interpreta os possíveis resultados de um comando SQL.
 *
 * $Revision$
 */
#ifndef RESULTSET_H
#define RESULTSET_H

#include <string>
#include <libpq-fe.h>
#include "sqlexception.h"

using std::string;

/// Classe que interpreta os possíveis resultados de um comando SQL.
class ResultSet {
private:
    // ResultSet do comando SQL
    PGresult *_result;
    // Número de linhas afetadas/retornadas
    int _lines;
    // Linha atual do resultado
    int _cursor;
    // Número de colunas
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
 * \brief Obtém a quantidade de linhas afetadas pelo comando.
 *
 * \return A quantidade de linhas afetadas pelo comando.
 */
inline int
ResultSet::lines() const
{
	return _lines;
}

/**
 * \brief Obtém a quantidade de colunas afetadas pelo comando.
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
