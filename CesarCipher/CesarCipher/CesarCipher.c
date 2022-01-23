#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stddef.h> 
#include <locale.h> 
#include <Windows.h>

char s[MAX_PATH]; //путь к файлу, который необходимо набрать с клавиатуры

int Deshyfr(int n) //функция дешифрования текста, в которую поступает найденный ключ 
{
	FILE* Ffr, * Ffw; //файлы: для чтения и записи 
	char c; //"ловим" символы из файла 
	int Res, Res1, Res2, Res3;

	Ffr = fopen(s, "r");
	if (Ffr == NULL) //если файл не открыт 
	{
		return 1;
	}

	Ffw = fopen("output.txt", "w");
	if (Ffw == NULL) //если файл не открыт 
	{
		return 2;
	}

	Res = fgetc(Ffr);
	if ((Res == EOF) && (!feof(Ffr)))
	{
		return 3;
	}
	c = Res;

	while (!feof(Ffr)) //пока не конец файла 
	{

		int k = n;
		if ((c >= 'A') && (c <= 'Z'))
		{
			c = c - (k % 26);
			if ('A' > c) //если вышли за границы доступного 
				c = 'Z' - ('A' - c) + 1;
		}
		if ((c >= 'a') && (c <= 'z'))
		{
			c = c - (k % 26);
			if ('a' > c) //если вышли за границы доступного 
				c = 'z' - ('a' - c) + 1;
		}

		Res3 = fprintf(Ffw, "%c", c);
		if (Res3 < 0)
		{
			return 4;
		}

		Res = fgetc(Ffr);
		if ((Res == EOF) && (!feof(Ffr)))
		{
			return 3;
		}
		c = Res;
	}

	Res1 = fclose(Ffr);
	if (Res1 != 0) //если файл не закрыт 
	{
		return 5;
	}

	Res2 = fclose(Ffw);
	if (Res2 != 0) //если файл не закрыт 
	{
		return 6;
	}

	return 0;
}

int MaxSymbol(int* MostUsed)
{
	FILE* Ffr;
	int Res, Res1, Res2, Res3, Res4;
	char c;
	int HowOften[26] = { 0 };
	int Max = 0;
	int a = 0;
	size_t i;

	if (MostUsed == NULL)
	{
		return 1;
	}

	Res = setlocale(LC_ALL, "");
	if (Res == NULL)
	{
		return 2;
	}

	Res1 = printf("Введите путь к файлу:\n");
	if (Res1 < 0)
	{
		return 3;
	}

	Res2 = scanf("%s", s); //читаем строку, то бишь-путь к файлу
	if (Res2 != 1)
	{
		return 4;
	}
	
	Ffr = fopen(s, "r");
	if (Ffr == NULL) //если файл не открыт 
	{
		return 5;
	}

	while (!feof(Ffr)) //подсчёт символов 
	{
		Res3 = fgetc(Ffr);
		if ((Res3 == EOF) && (!feof(Ffr)))
		{
			return 6;
		}
		c = Res3;

		if ((c >= 'A') && (c <= 'Z'))
			HowOften[c - 'A']++;
		if ((c >= 'a') && (c <= 'z'))
			HowOften[c - 'a']++;
	}

	for (i = 0; i < 26; i++) //нахождение самого частого символа
	{
		if (HowOften[i] > Max)
		{
			a = i + 97;
			Max = HowOften[i];
		}
	}

	Res4 = fclose(Ffr);
	if (Res4 != 0) //если файл не закрыт 
	{
		return 7;
	}

	*MostUsed = a;

	return 0;
}

int Key(int* MostUsed) //функция поиска ключа и начала дешифровки текста 
{
	char MostFrequent = 'e'; //всем известная буква 'e', как наиболее часто встречающаяся буква в английских текстах 

	if (MostUsed == NULL)
	{
		return 1;
	}

	*MostUsed = *MostUsed - MostFrequent;

	return 0;
}

int main()
{
	int Res, Res1, Res2, Res3, Res4;
	int MostUsed;
	int Errors1 = 0, Errors2 = 0, Errors3 = 0;

	Res = setlocale(LC_ALL, "");
	if (Res == NULL)
	{
		printf("Error!\n");
		return 1;
	}

	Res1 = printf("Добро пожаловать в программу, следуйте пожалуйста дальнейшим инструкциям на экране:\n");
	if (Res1 < 0)
	{
		printf("Error!\n");
		return 2;
	}

	Errors1 = MaxSymbol(&MostUsed);
	switch (Errors1)
	{
	case 1:
	{
		printf("Не выделено адресное пространство!\n");
		return 1;
	}break;
	case 2:
	{
		printf("Не найдена новая локаль!\n");
		return 2;
	}break;
	case 3:
	{
		printf("Ошибка вывода!\n");
		return 3;
	}break;
	case 4:
	{
		printf("Ошибка ввода!\n");
		return 4;
	}break;
	case 5:
	{
		printf("Файл не открыт для нахождения частотности!\n");
		return 5;
	}break;
	case 6:
	{
		printf("Ошибка с получением символов из файла!\n");
		return 6;
	}break;
	case 7:
	{
		printf("Файл не закрыт!\n");
		return 7;
	}break;
	default: Res2 = printf("Максимально часто встречающийся элемент найден!\n");
		if (Res2 < 0)
		{
			return 3;
		}break;
	}

	Errors2 = Key(&MostUsed);
	switch (Errors2)
	{
	case 1:
	{
		printf("Не выделено адресное пространство!\n");
		return 1;
	}break;
	default: Res3 = printf("Ключ найден!\n");
		if (Res3 < 0)
		{
			return 4;
		}break;
	}

	Errors3 = Deshyfr(MostUsed);
	switch (Errors3)
	{
	case 1:
	{
		printf("Не открыт файл для чтения!\n");
		return 1;
	}break;
	case 2:
	{
		printf("Не открыт файл для записи!\n");
		return 2;
	}break;
	case 3:
	{
		printf("Ошибка с получением символов из файла!\n");
		return 3;
	}break;
	case 4:
	{
		printf("Ошибка с записью символов в файл!\n");
		return 4;
	}break;
	case 5:
	{
		printf("Не закрыт файл для чтения!\n");
		return 5;
	}break;
	case 6:
	{
		printf("Не закрыт файл для записи!\n");
		return 6;
	}break;
	default: Res4 = printf("Программа успешно выполнена!\n");
		if (Res4 < 0)
		{
			return 5;
		}break;
	}
	return 0;
}