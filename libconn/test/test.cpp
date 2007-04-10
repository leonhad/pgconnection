/**
 * $Header$
 *
 * Autor: Edson Alves - edsomjr@gmail.com
 * Tamanho da tabula��o: 4
 * Codifica��o: ISO 8859-1
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
