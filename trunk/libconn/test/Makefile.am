## $Header$
##
## Autor: Edson Alves - edsomjr@gmail.com
## Tamanho da tabulação: 4
## Codificação: ISO 8859-1
## $Date$
##
## Arquivo alvo para a construção do programa de testes.
##
## $Revision$
##

# Descrição do programa de testes
check_PROGRAMS = test

# Arquivos necessários para a construção do programa de testes
test_SOURCES = test.cpp

# Bibliotecas usadas na construção do programa de testes
test_LDADD = ../src/libconn.la -lpq

# Includes adicionais
INCLUDES = -I/usr/include/postgresql

# Flags de compilação
AM_CFLAGS = -ggdb -pedantic -Wall -fPIC
