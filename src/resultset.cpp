/*
 * Implementação da classe que interpreta os possíveis resultados de um comando SQL.
 */
#include "resultset.h"
#include <cstdlib>

/**
 * \brief Construtor.
 *
 * \param result	Resultado de um comando SQL.
 *
 * \exception NULL_PARAMETER	Ocorre quando result é um ponteiro nulo.
 * \exception EMPTY_QUERY		Ocorre quando a string do comando enviado estava vazia.
 * \exception BAD_RESPONSE		Ocorre quando não foi possível entender a resposta do servidor.
 * \exception NONFATAL_ERROR	Ocorre quando há um erro não identificado, mas não fatal.
 * \exception FATAL_ERROR		Ocorre quando há um erro não identificado e fatal.
 */
ResultSet::ResultSet(PGresult *result) throw (SQLException)
{
	_result = result;
	_cursor = -1;
	_columns = 0;

	if (!_result) {
        throw SQLException("ResultSet::ResultSet(): Invalid result: null pointer", NULL_PARAMETER);
    } else {
		enum exceptionCode code;

        switch(PQresultStatus(_result)) {
            // insert, delete e update
            case PGRES_COMMAND_OK:
                _lines = atoi(PQcmdTuples(_result));
                return;
            // select
            case PGRES_TUPLES_OK:
                _lines = PQntuples(_result);
                _columns = PQnfields(_result);
                return;
			case PGRES_EMPTY_QUERY:
				code = EMPTY_QUERY;
				break;
			case PGRES_BAD_RESPONSE:
				code = BAD_RESPONSE;
				break;
			case PGRES_NONFATAL_ERROR:
				code = NONFATAL_ERROR;
				break;
            default:
                code = FATAL_ERROR;
				break;
        }

		SQLException e = SQLException(PQresultErrorMessage(_result), code);
		PQclear(_result);
		throw e;
    }
}


/**
 * \brief Destrutor.
 */
ResultSet::~ResultSet()
{
    PQclear(_result);
}

/**
 * \brief Move o cursor de leitura para a próxima linha.
 *
 * \return 	Retorna <b>false</b> caso não exista uma próxima linha.
 */
bool ResultSet::next()
{
    _cursor++;
    if (_cursor < _lines) {
        return true;
    }

    return false;
}

/**
 * \brief Verifica se uma dada coluna � nula.
 *
 * \param index		�ndice da coluna a ser verificada.
 * 
 * \return	Retorna <b>true</b> se a coluna � nula, <b>false</b> caso contr�rio.
 * 
 * \exception INDEX_OUT_OF_BOUNDS		Ocorre quando o �ndice indicado aponta para uma
 *										coluna inexistente.
 */
bool ResultSet::isNull(int index) throw (SQLException)
{
	try {
    	checkColumn(index);
	} catch (const SQLException& e) {
		throw e;
	}

    return PQgetisnull(_result, _cursor, index);
}

/**
 * \brief Verifica se uma dada coluna � nula.
 *
 * \param columnName		Nome da coluna a ser verificada.
 * 
 * \return	Retorna <b>true</b> se a coluna � nula, <b>false</b> caso contr�rio.
 * 
 * \exception INVALID_COLUMN			Ocorre quando o nome dado n�o indica uma coluna v�lida.
 */
bool ResultSet::isNull(string columnName) throw (SQLException)
{
    int index = checkColumn(columnName);

    return PQgetisnull(_result, _cursor, index);
}

/**
 * \brief Obt�m o valor de uma dada coluna como string.
 *
 * \param columnName		Nome da coluna.
 * 
 * \return	Retorna o valor da coluna como string.
 * 
 * \exception INVALID_COLUMN			Ocorre quando o nome dado n�o indica uma coluna v�lida.
 */
string ResultSet::stringValue(string columnName) throw (SQLException)
{
    string value;

	try {
		int index = checkColumn(columnName);
		value = stringValue(index);
	} catch (SQLException& e) {
		throw e;
	}

	return value;
}

/**
 * \brief Obt�m o valor de uma dada coluna como string.
 *
 * \param columnIndex		�ndice da coluna.
 * 
 * \return	Retorna o valor da coluna como string.
 * 
 * \exception INDEX_OUT_OF_BOUNDS		Ocorre quando o �ndice indicado aponta para uma
 *										coluna inexistente.
 */
string ResultSet::stringValue(int columnIndex) throw (SQLException)
{
	bool nullColumn;

	try {
		nullColumn = isNull(columnIndex);
	} catch (SQLException& e) {
		throw e;
	}

	if (nullColumn)
		return "";
	else
		return PQgetvalue(_result, _cursor, columnIndex);
}

/**
 * \brief Obt�m o valor de uma dada coluna como int.
 *
 * \param columnName		Nome da coluna.
 * 
 * \return	Retorna o valor da coluna como int.
 * 
 * \exception INVALID_COLUMN			Ocorre quando o nome dado n�o indica uma coluna v�lida.
 */
int ResultSet::intValue(string columnName) throw (SQLException)
{	
	string value;

	try {
		value = stringValue(columnName);
	} catch (SQLException& e) {
		throw e;
	}

	// TODO verificar os poss�veis erros na convers�o string - int
	if (value == "")
		return 0;
	else
    	return atoi(value.c_str());
}

/**
 * \brief Obt�m o valor de uma dada coluna como int.
 *
 * \param columnIndex		�ndice da coluna.
 * 
 * \return	Retorna o valor da coluna como int.
 * 
 * \exception INDEX_OUT_OF_BOUNDS		Ocorre quando o �ndice indicado aponta para uma
 *										coluna inexistente.
 */
int ResultSet::intValue(int columnIndex) throw (SQLException)
{
    string value;

	try {
		value = stringValue(columnIndex);
	} catch (SQLException e) {
		throw e;
	}

	// TODO verificar os poss�veis erros na convers�o string - int
	if (value == "")
		return 0;
	else	
		return atoi(value.c_str());
}

/**
 * \brief Obt�m o valor de uma dada coluna como float.
 *
 * \param columnName		Nome da coluna.
 * 
 * \return	Retorna o valor da coluna como float.
 * 
 * \exception INVALID_COLUMN			Ocorre quando o nome dado n�o indica uma coluna v�lida.
 */
float ResultSet::floatValue(string columnName) throw (SQLException)
{
    string value;
	
	try {
		value = stringValue(columnName);
	} catch (SQLException e) {
		throw e;
	}

	// TODO verificar os poss�veis erros na convers�o string - float
	if (value == "")
		return 0.0f;
	else
		return atof(value.c_str());
}

/**
 * \brief Obt�m o valor de uma dada coluna como float.
 *
 * \param columnIndex		�ndice da coluna.
 * 
 * \return	Retorna o valor da coluna como float.
 * 
 * \exception INDEX_OUT_OF_BOUNDS		Ocorre quando o �ndice indicado aponta para uma
 *										coluna inexistente.
 */
float ResultSet::floatValue(int columnIndex) throw (SQLException)
{
    string value;
	
	try {
		value = stringValue(columnIndex);
	} catch (SQLException e) {
		throw e;
	}

	// TODO verificar os poss�veis erros na convers�o string - float
	if (value == "")
		return 0.0f;
	else
		return atof(value.c_str());
}

// $Source$
