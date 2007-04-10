/**
 * $Header$
 *
 * Autor: Edson Alves - edsomjr@gmail.com
 * Tamanho da tabulação: 4
 * Codificação: ISO 8859-1
 * $Date$
 *
 * Teste da biblioteca conn.
 *
 * $Revision$
 */
#include <iostream>
#include "connection.h"

using namespace std;

int main()
{
	Connection *conn = NULL;
	int lines = 0;

	try {
		conn = new Connection("", "", "Teste", "postgres", "");
		lines = conn->executeUpdate("INSERT INTO Teste (code) VALUES (123)");
	} catch (const SQLException& e) {
		cerr << e.message() << endl;
		cerr << e.code() << endl;
	}

	cout << "Lines affected = " << lines << endl;

	delete conn;

	return 0;
}

// $Source$
