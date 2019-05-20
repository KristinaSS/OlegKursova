#define _CRT_SECURE_NO_WARNINGS
#define NAME 31
#define LINE_LENGHT 120

#define ALL_KEYWORDS  7

const char* KEYWORD_STRING[ALL_KEYWORDS] = { "char ","double ","float ","int ","long ","short ","void " };

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//test


//read functions
void readFromFile(char fName[NAME + 1]);
int readFromKeyboard(char fName[NAME + 1]);

//write functions
void writeToFile(int maxSymbolsLineNumber, int numberIdentifiers);
void writeToScreen(int maxSymbolsLineNumber, int numberIdentifiers);

//support functions
void menu();
int checkFileExtension(char fNameIn[]);
char *fNameDirect();
char *getSubstr(const char currentLine[LINE_LENGHT], const char keywordString[LINE_LENGHT], char keyword[LINE_LENGHT]);
int doesContainKeyword(const char checkedStr[LINE_LENGHT]);


//program functions
int lineWithMostSymbols(char fName[]);
int numberOfIdentifiers(char fName[]);

//**********************************************************

int main() {

    SetConsoleOutputCP(1251);
    menu();

    return 0;
}

//read functions
void readFromFile(char fName[NAME + 1]) {
    FILE *fp;

    fp = fopen(fName, "r");

    if (fp == NULL)
    {
        printf("Ãðåøêà ñ ôàéëà!\n");
        perror(fName);
    }
    fclose(fp);
}
int readFromKeyboard(char fName[NAME + 1]) {
    FILE *fp = NULL;
    char ch;

    fp = fopen(fName, "w");

    if (fp == NULL)
        return -1;

    printf("\n×åòåíå îò êëàâèàòóðà...\n Ïèøåòå:\n");
    printf("çà êðàé: ctrl+z\n");

    while ((ch = (char)getchar()) != EOF)
        fprintf(fp, "%c", ch);

    fclose(fp);

    return 0;
}

//support functions
void menu() {
    int i, maxSymbolsLineNumber = 0, numberIdentifiers = 0;
    int k;
    int checkExtension;

    //for name
    char *pName, fName[NAME + 1];
    char defName[NAME] = "default.c";

    //mode
    char mode;

    char *menu[] = {
            "Ìåíþ",
            "1.×åòåíå îò ôàéë/Çàïèñ â ôàéë",
            "2.×åòåíå îò ôàéë/Èçâåæäàíå íà åêðàí",
            "3.Ïèñàíå îò êîíçîëà/Çàïèñ â ôàéë",
            "4.Ïèñàíå îò êîçîëà/Èçâåæäàíå íà åêðàí",
            "5.Èçõîä"
    };

    do {
        system("cls");

        for (i = 0;i < 6;i++)
            printf("\n%s\n", menu[i]);
        printf("\n Èçáåðåòå îò 1 äî 5\n");

        mode = (char)fgetc(stdin);

        switch (mode)
        {
            case '1':
                printf("Òè èçáðà:1.×åòåíå îò ôàéë/Çàïèñ â ôàéë");

                //for file name:
                do {
                    pName = fNameDirect();

                    for (k = 0;k < NAME;k++)
                        fName[k] = *(pName + k);

                    checkExtension = checkFileExtension(fName);

                    if (checkExtension != 0)
                    {
                        printf("Íàïèñàõòå íå âàëèäíî èìå íà ôàéë!\n");
                        continue;
                    }
                    else
                        break;
                } while (1);

                //task
                readFromFile(fName);

                maxSymbolsLineNumber = lineWithMostSymbols(fName);
                if (maxSymbolsLineNumber == -1)
                {
                    printf("\nÃðåøêà ïî âðåìå íà ÷åòåíå íà ôàéëà!\n");
                    break;
                }

                numberIdentifiers = numberOfIdentifiers(fName);
                if (numberIdentifiers == -1)
                {
                    printf("\nÃðåøêà ïî âðåìå íà ÷åòåíå íà ôàéëà!\n");
                    break;
                }

                numberIdentifiers = numberOfIdentifiers(fName);
                writeToFile(maxSymbolsLineNumber, numberIdentifiers);

                system("pause");
                break;

            case '2':
                printf("Èçáðàõòå 2:×åòåíå îò ôàéë/Èçâåæäàíå íà åêðàí\n");

                //for file name:
                do {
                    pName = fNameDirect();

                    for (k = 0;k < NAME;k++)
                        fName[k] = *(pName + k);

                    checkExtension = checkFileExtension(fName);

                    if (checkExtension != 0)
                    {
                        printf("Íàïèñàõòå íå âàëèäíî èìå íà ôàéë!\n");
                        continue;
                    }
                    else
                        break;
                } while (1);

                //task
                readFromFile(fName);

                maxSymbolsLineNumber = lineWithMostSymbols(fName);
                if (maxSymbolsLineNumber == -1)
                {
                    printf("\nÃðåøêà ïî âðåìå íà ÷åòåíå íà ôàéëà!\n");
                    break;
                }

                numberIdentifiers = numberOfIdentifiers(fName);
                if (numberIdentifiers == -1)
                {
                    printf("\nÃðåøêà ïî âðåìå íà ÷åòåíå íà ôàéëà!\n");
                    break;
                }
                writeToScreen(maxSymbolsLineNumber, numberIdentifiers);

                system("pause");
                break;

            case '3':
                printf("Èçáðàõòå 3:Ïèñàíå îò êîíçîëà/Çàïèñ â ôàéë\n");
                //for file name:

                //task
                if ((readFromKeyboard(defName)) != 0)
                {
                    printf("\nÃðåøêà ïî âðåìå íà ÷åòåíå íà ôàéëà!\n");
                    break;
                }
                maxSymbolsLineNumber = lineWithMostSymbols(defName);
                if (maxSymbolsLineNumber == -1)
                {
                    printf("\nÃðåøêà ïî âðåìå íà ÷åòåíå íà ôàéëà!\n");
                    break;
                }
                numberIdentifiers = numberOfIdentifiers(defName);
                if (numberIdentifiers == -1)
                {
                    printf("\nÃðåøêà ïî âðåìå íà ÷åòåíå íà ôàéëà!\n");
                    break;
                }
                writeToFile(maxSymbolsLineNumber, numberIdentifiers);

                system("pause");
                break;
            case '4':
                printf("Èçáðàõòå 4: Ïèñàíå îò êîçîëà/Èçâåæäàíå íà åêðàí\n");
                //for file name:

                //task
                if ((readFromKeyboard(defName)) != 0)
                {
                    printf("\nÃðåøêà ïî âðåìå íà ÷åòåíå íà ôàéëà!\n");
                    break;
                }
                maxSymbolsLineNumber = lineWithMostSymbols(defName);
                if (maxSymbolsLineNumber == -1)
                {
                    printf("\nÃðåøêà ïî âðåìå íà ÷åòåíå íà ôàéëà!\n");
                    break;
                }
                numberIdentifiers = numberOfIdentifiers(defName);
                if (numberIdentifiers == -1)
                {
                    printf("\nÃðåøêà ïî âðåìå íà ÷åòåíå íà ôàéëà!\n");
                    break;
                }
                writeToScreen(maxSymbolsLineNumber, numberIdentifiers);
                system("pause");
                break;

            case '5':
                //break;
                return;
            default:
                printf("Íàïèñàõòå íå âàëèäíî îò ìåíþòî!\n");
                system("pause");
                break;
        }
    } while (1);
}
char *fNameDirect() {
    char fName[NAME + 1], *pName;

    printf("Íàïèøåòå èìåòî íà ôàéëà, êîéòî æåëàåòå äà ÷åòåòå:"
           "\nìîëÿ íàïèøåòå '.c' â êðàÿ\n");
    getchar();

    fgets(fName, NAME, stdin);
    int i;
    for (i = 0;i < NAME;i++)
    {
        if (fName[i] == '\n')
        {
            fName[i] = '\0';
            break;
        }
    }
    pName = fName;

    return pName;
}
int checkFileExtension(char fNameIn[]) {

    int fNameLength = strlen(fNameIn);

    if (fNameIn[fNameLength - 2] != '.' || fNameIn[fNameLength - 1] != 'c')
    {
        return 1;
    }
    return 0;
}
int doesContainKeyword(const char checkedStr[]) {

    int i, j, k, l;
    int mini = -1, minj = LINE_LENGHT + 1;

    for (i = 0;i < ALL_KEYWORDS; i++)
    {
        int checkedStrLen = strlen(checkedStr);
        int keywordStrLen = strlen(KEYWORD_STRING[i]);

        if (strlen(checkedStr) >= strlen(KEYWORD_STRING[i]))
        {
            for (j = 0;j < checkedStrLen - keywordStrLen;j++)
            {
                l = 1;

                for (k = 0;k < keywordStrLen;k++)
                {
                    if (checkedStr[j + k] != *(KEYWORD_STRING[i] + k)) //contains substring
                    {
                        l = 0;
                        k = keywordStrLen + 1; //exit
                    }
                }
                if (l == 1)
                {
                    if (j < minj)
                    {
                        mini = i;//keyword
                        minj = j;//beginning
                    }
                    j = checkedStrLen + 1;
                }
            }
        }
    }
    return mini;
}
char *getSubstr(const char currentLine[], const char keywordString[], char keyword[]) {

    int curLineLen = strlen(currentLine);
    int keywordStrLen = strlen(keywordString);

    if (curLineLen < keywordStrLen)
    {
        return NULL; //stops fun
    }

    keyword[0] = '\0';

    int i, k, l;

    for (i = 0;i < curLineLen - keywordStrLen;i++)
    {
        int j;
        l = 1;

        for (j = 0;j < keywordStrLen;j++)
        {
            if (currentLine[j + i] != keywordString[j])
            {
                l = 0;
                break;
            }
        }
        if (l == 1)
        {
            for (j = 0, k = i + keywordStrLen;k < curLineLen;j++, k++)
            {
                keyword[j] = currentLine[k];
            }
            keyword[curLineLen - keywordStrLen - i] = '\0';
            return; //todo check
        }
    }
}

//program files
int lineWithMostSymbols(char fName[]) {

    FILE *fp;

    char currentChar, lastChar = '\0';
    int characters = 0, mostLineCharacters = 0;
    int line = 1, lineMaxChar = 1;

    //flags
    int multi = 0, single = 0;

    fp = fopen(fName, "r");

    if (fp == NULL)
        return -1;

    do
    {
        currentChar = (char)fgetc(fp);

        //single line comment
        if (lastChar == '/' && currentChar == '/')
        {
            single = 1; // single on

            if (characters != 0)
                characters--; // not count beg of single line

            if (characters > mostLineCharacters)
            {
                mostLineCharacters = characters;
                lineMaxChar = line;
            }
            characters = 0; // because new line

            line++;
            lastChar = currentChar; //because its a single line comment
            continue;
        }

        if (single == 1)
        {
            if (currentChar == '\n' || currentChar == EOF)
            {
                single = 0; // next line will not be a comment
            }
            continue;
        }

        //multi line comment

        if (lastChar == '/'&& currentChar == '*')
        {
            multi = 1; //multi on

            if (characters != 0) // not count beg of multi line
                characters--;

            continue;
        }

        if (multi == 1)
        {
            if (currentChar == '\n' || currentChar == EOF)
            {
                if (characters > mostLineCharacters)
                {
                    mostLineCharacters = characters;
                    lineMaxChar = line;
                }

                characters = 0;

                line++;
                continue;
            }

            if (lastChar == '*'&& currentChar == '/')
            {
                multi = 0; //multi off
            }

            lastChar = currentChar;
            continue;
        }

        lastChar = currentChar;

        //to see if its a new line

        if (currentChar == '\n' || currentChar == EOF) //what if this is in a comment? this needs to be in an if
        {
            // cause new line is a character

            if (characters > mostLineCharacters)
            {
                mostLineCharacters = characters;
                lineMaxChar = line;
            }
            characters = 0;

            line++;

            continue;
        }



        characters++;

    } while (currentChar != EOF);

    fclose(fp);

    return lineMaxChar - 1;
}
int numberOfIdentifiers(char fName[]) {

    FILE *fp;

    int numberIdentifiers = 0;
    int currentLineLength = 0;
    int i;

    char keyword[LINE_LENGHT];
    char currentLine[LINE_LENGHT + 1], currentChar;
    // new
    char lastChar ='\0';
    int single =0, multi=0, aFlag =0;

    fp = fopen(fName, "r");


    //**************************************

    int isEOF = 0;

    while (!isEOF)
    {
        for (i = 0;1;i++)
        {
            currentChar = (char)fgetc(fp);
            //dddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
            if (lastChar == '/' && currentChar == '/')
            {
                single = 1; // single on

                lastChar = currentChar; //because its a single line comment
                continue;
            }

            if (single == 1)
            {
                if (currentChar == '\n' || currentChar == EOF)
                {
                    single = 0; // next line will not be a comment
                }
                continue;
            }

            //multi line comment

            if (lastChar == '/'&& currentChar == '*')
            {
                multi = 1; //multi on

                continue;
            }

            if (multi == 1)
            {
                if (currentChar == '\n' || currentChar == EOF)
                {
                    continue;
                }

                if (lastChar == '*'&& currentChar == '/')
                {
                    multi = 0; //multi off
                }
                lastChar = currentChar;

                continue;
            }
            if(aFlag==0 && (currentChar=='"'||currentChar=='\'')){
                aFlag++;
                lastChar = currentChar;
                continue;

            }
            if(aFlag!=0)
            {
                aFlag++;
                if(currentChar=='"' || currentChar =='\''||aFlag>100)
                    aFlag = 0;
                lastChar = currentChar;
                continue;
            }

            lastChar = currentChar;
//dddaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

            if (currentChar == '\n' || currentChar == EOF) {
                currentLine[i] = '\0';
                if (currentChar == EOF)
                {
                    isEOF = 1;
                }
                break;
            }
            currentLine[i] = currentChar;
            currentLineLength++;
        }

        int l = 1;

        while (l == 1)
        {
            keyword[0] = '\0'; //making empty

            int numKeyword = doesContainKeyword(currentLine);

            if (numKeyword != -1)
            {
                numberIdentifiers++;
                getSubstr(currentLine, KEYWORD_STRING[numKeyword], keyword);

                int size = strlen(keyword);

                for (i = 0;i <= size;i++)
                {
                    currentLine[i] = keyword[i];
                }

            }
            else //if one keyword
            {
                l = 0;

                for (i = 0;i < (int)strlen(currentLine);i++)
                {
                    if (currentLine[i] == ',')
                    {
                        numberIdentifiers++;
                    }
                }

            }
        }

    }
    fclose(fp);
    return numberIdentifiers;
}

//write files
void writeToScreen(int maxSymbolsLineNumber, int numberIdentifiers) {

    printf("Ðåäúò ñ íàé-ìíîãî çíà÷åùè ñèìâîëè å %d\n", maxSymbolsLineNumber);
    printf("Áðîÿ èíäåíòèôèêàòîðè: %d\n", numberIdentifiers);
}
void writeToFile(int maxSymbolsLineNumber, int numberIdentifiers) {

    char outputFName[NAME + 1];

    FILE *fp = NULL;

    printf("\nÌîëÿ âúâåäåòå ôàéëà â êîéòî èñêàòå äà äà çàïàçèòå ðåçóëòàòèòå â:\n");

    scanf("%s", outputFName);
    getchar();

    fp = fopen(outputFName, "w");

    if (fp == NULL) {
        printf("\nÃðåøêà âúâ ôàéëà!\n");
        perror(outputFName);
    }

    printf("\nÏèñàíå...\n");
    fprintf(fp, "%s%d \n", "\nÐåäúò ñ íàé-ìíîãî çíà÷åùè ñèìâîëè å:", maxSymbolsLineNumber);
    fprintf(fp, "Áðîé èíäåíòèôèêàòîðè: %d\n", numberIdentifiers);

    fclose(fp);
}