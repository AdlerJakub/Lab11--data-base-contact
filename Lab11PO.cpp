#include "stdafx.h"
#define HAVE_STRUCT_TIMESPEC
#include <my_global.h> 
#include <mysql.h> 
#include <iostream>
#include "Baza.h"

using namespace std;


int main(int argc, char **argv) 
{ 
	

	char login[100];
	char pass[100];
	bool cookie; // tworze cookie
	
	Baza db;
	db.connect();

	db.logger(login, pass, cookie);
	db.zad23(cookie);
	db.zad4(cookie);
	
	return 0;
}