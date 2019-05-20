#include "stdafx.h"
#define HAVE_STRUCT_TIMESPEC
#include <my_global.h> 
#include <mysql.h> 
#include <iostream>
#include "Baza.h"


Baza::Baza()
{

}


Baza::~Baza()
{
	mysql_close(con);
}


void Baza::finish_with_error(MYSQL *con)
{
	fprintf(stderr, "%s\n", mysql_error(con));
	mysql_close(con);
	exit(1);
}

void Baza::connect()
{
	con = mysql_init(NULL);

	if (con == NULL)
	{
		fprintf(stderr, "mysql_init() failed\n");
		//exit(1);
	}

	if (mysql_real_connect(con, "localhost", "root", "aX#>:&^443@dR", "po_db", 3306, NULL, 0) == NULL)
	{
		finish_with_error(con);
	}
}

void Baza::logger(char login[], char pass[], bool &cookie)
{
	cout << "Zaloguj sie!" << endl;
	cout << "Login:" << endl;
	cin >> login;
	cout << "Haslo:" << endl;
	cin >> pass;

	

	sprintf_s(query, "SELECT id\
                   FROM student \
                   WHERE imie='%s'\
                   AND nazwisko='%s'"
		, login, pass);

	if (mysql_query(con, query))
	{
		finish_with_error(con);
	}

	result = mysql_store_result(con);
	if (mysql_num_rows(result) == 1)
	{
		cout << "Zalogowano" << endl;
		MYSQL_ROW row = mysql_fetch_row(result);
		mysql_free_result(result);
		cookie = TRUE;
	}

	else
	{
		cout << "Zle haslo" << endl;
		mysql_free_result(result);
		cookie = FALSE;
	}
}

void Baza::zad23( bool cookie)
{
	if (cookie == FALSE)
	{
		cout << "Blad weryfikacji" << endl;
	}
	else
	{


		if (mysql_query(con, "SELECT * FROM student"))
		{
			finish_with_error(con);
		}


		cout << "Wszyscy studenci:" << endl;



		result = mysql_store_result(con);

		if (result == NULL)
		{
			finish_with_error(con);
		}

		int num_fields = mysql_num_fields(result);
		MYSQL_ROW row;

		while ((row = mysql_fetch_row(result)))
		{
			for (int i = 0; i < num_fields; i++)
			{
				printf("%s ", row[i] ? row[i] : "NULL");
			}
			printf("\n");
		}
		mysql_free_result(result);
	}
}

void Baza::zad4(bool cookie)
{
	if (cookie == FALSE)
	{
		cout << "Blad weryfikacji" << endl;
	}
	else
	{
		unsigned int nr_przedmiotu = 0;
		cout << "Podaj nr przedmiotu:";
		cin >> nr_przedmiotu;
		cout << "Wszyscy studenci uczeszczajacy na przedmiot o numerze " << nr_przedmiotu << ":" << endl;



		sprintf_s(query, "SELECT student.imie,student.nazwisko,\
                 przedmioty.nazwa_przedmiotu,\
                 student_przedmioty.ocena_z_przedmiotu \
                 FROM student_przedmioty \
                 LEFT JOIN student \
                 ON student.id = student_przedmioty.id_student\
                 LEFT JOIN przedmioty\
                 ON przedmioty.id = student_przedmioty.id_przedmioty\
                 WHERE student_przedmioty.id_przedmioty = %i"
			, nr_przedmiotu);

		if (mysql_query(con, query))
		{
			finish_with_error(con);
		}


		result = mysql_store_result(con);

		if (result == NULL)
		{
			finish_with_error(con);
		}

		int num_fields = mysql_num_fields(result);
		MYSQL_ROW row;

		while ((row = mysql_fetch_row(result)))
		{
			for (int i = 0; i < num_fields; i++)
			{
				printf("%s ", row[i] ? row[i] : "NULL");
			}
			printf("\n");
		}
		mysql_free_result(result);

	}
}

