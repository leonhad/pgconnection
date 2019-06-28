/*
 * $Header$
 *
 * Autor: Leonardo Alves - leonhad@gmail
 * Tamanho da tabulação: 4
 * Codificação: ISO 8859-1
 * $Date$
 *
 * Declaração da classe que representa as exceções referentes ao banco de dados.
 *
 * $Revision$
 */
#ifndef SQLEXCEPTION_H
#define SQLEXCEPTION_H

#include <string>

using std::string;

/// Possíveis códigos de exceção
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

/// \brief Classe que representa as exceções referentes ao banco de dados.
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
 * \param code		Código da exceção.
 * \param message	Mensagem associada à exceção.
 */
inline 
SQLException::SQLException(string message, enum exceptionCode code)
{
	_code = code;
	_message = message;
}

/**
 * \brief Obtém o código da exceção.
 *
 * \return O código da exceção.
 */
inline int 
SQLException::code() const
{
	return _code;
}

/**
 * \brief Obtém a mensagem associada à exceção.
 *
 * \return A mensagem associada à exceção.
 */
inline string
SQLException::message() const
{
	return _message;
}

#endif // SQLEXCEPTION_H

// $Source$
