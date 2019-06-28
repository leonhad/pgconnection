/*
 * $Header$
 *
 * Autor: Leonardo Alves - leonhad@gmail
 * Tamanho da tabula��o: 4
 * Codifica��o: ISO 8859-1
 * $Date$
 *
 * Declara��o da classe que representa as exce��es referentes ao banco de dados.
 *
 * $Revision$
 */
#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include <string>

using std::string;

/// Poss�veis c�digos de exce��o
enum exceptionCode {
	NULL_PARAMETER,
	INDEX_OUT_OF_BOUNDS,
	EMPTY_QUERY,
	BAD_RESPONSE,
	NONFATAL_ERROR,
	FATAL_ERROR,
	INVALID_COLUMN,
	BAD_CONNECTION,
	COMMAND_PROCESSED
};

/// \brief Classe que representa as exce��es referentes ao banco de dados.
class SQLException {
private:
	enum exceptionCode _code;
	string _message;

public:
	inline SQLException(string message, enum exceptionCode code);
	inline int code() const;
	inline string message() const;
};

/**
 * \brief Construtor.
 *
 * \param code		C�digo da exce��o.
 * \param message	Mensagem associada � exce��o.
 */
inline 
SQLException::SQLException(string message, enum exceptionCode code)
{
	_code = code;
	_message = message;
}

/**
 * \brief Obt�m o c�digo da exce��o.
 *
 * \return O c�digo da exce��o.
 */
inline int 
SQLException::code() const
{
	return _code;
}

/**
 * \brief Obt�m a mensagem associada � exce��o.
 *
 * \return A mensagem associada � exce��o.
 */
inline string
SQLException::message() const
{
	return _message;
}

#endif // SQLEXCEPTION_H

// $Source$
