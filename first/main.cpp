#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const int DEFAULT_BUFFER_LENGHT = 1000;

int count_lines(char* arr, char n, int value);

int count_lines(char* arr, char n, int value)
{
	int count = 1; //readable format
	for (int i = 0; i <= value; i++)
	{
		if (arr[i] == n)
		{
			count++;
		}
	}
	return count;
}

int find(char* pathToFile, char* textToFind)
{
	FILE* file;
	file = fopen(pathToFile, "r");
	if (!file)
	{
		printf("File wasn't found");
		return 1;
	}
	else
	{
		printf("File was opened successfully!\n");
		if (strlen(textToFind) == 0)
		{
			printf("Lenght of the string you want to find is 0! \n");
			system("pause");
			return 1;
		}
		else
		{
			int bufferLenth = 2 * strlen(textToFind);
			if (bufferLenth < DEFAULT_BUFFER_LENGHT)
			{
				bufferLenth = DEFAULT_BUFFER_LENGHT;
			}
			char* buffer = (char*)malloc(bufferLenth + 1);
			char* firstAppear;
			int bytesRead;
			int lineNumber = 0;
			bool isFound = false;
			int offset = 0;
			do
			{
				memset(buffer, '\0', bufferLenth + 1);
				bytesRead = fread(buffer, sizeof(char), bufferLenth, file);
				firstAppear = strstr(buffer, textToFind);
				if (firstAppear)
				{
					isFound = true;
					int front = firstAppear - buffer;
					int back = (buffer + bufferLenth) - (firstAppear + strlen(textToFind));
					front = front < 10 ? front : 10;
					back = back < 10 ? back : 10;
					char* dif = firstAppear - front;
					for (int i = 0; i <= (firstAppear - buffer); i++)
					{
						if (buffer[i] == '\n')
						{
							lineNumber++;
						}
					}
					printf("###FOUND AT %d row###\n", lineNumber + 1);
					fwrite(dif, sizeof(char), (front + strlen(textToFind) + back), stdout);
					printf("\n");
				
					offset = 0 - ((buffer + bufferLenth) - (firstAppear + strlen(textToFind)));
					fseek(file, offset, SEEK_CUR);
				}
				else
				{
					for (int i = 0; i <= bufferLenth; i++)
					{
						if (buffer[i] == '\n')
						{
							lineNumber++;
						}
					}
					offset = 0 - strlen(textToFind);
					fseek(file, offset, SEEK_CUR);
				}
				
	
			} while (bytesRead == bufferLenth);
			
			if (isFound != true)
			{
				printf("**** Wasn't found! **** \n");
				free(buffer);
				fclose(file);
				system("pause");
				return 1;
			}
			free(buffer);
			fclose(file);
			system("pause");
			return 0;
		}
	}
}


int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printf("You need specify more args for app \nExample: first.exe your_file \"Text to find\"\n");
		system("pause");
		return 1;
	}
	return find(argv[1], argv[2]);
}
