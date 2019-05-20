#pragma once

#include "stdafx.h"
#define HAVE_STRUCT_TIMESPEC
#include <my_global.h> 
#include <mysql.h> 
#include <iostream>

using namespace std;

class Baza
{
public:
	MYSQL *con;
	MYSQL_RES * result;
	char query[2048];

	Baza();
	~Baza();

	void finish_with_error(MYSQL *con);
	void connect();
	void logger(char[], char[], bool &cookie);
	void zad23(bool cookie);
	void zad4(bool cookie);







};
