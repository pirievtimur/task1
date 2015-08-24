#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static const int DEFAULT_BUFFER_LENGHT = 1000;

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
			int buf_len = 2 * strlen(textToFind);
			if (buf_len < DEFAULT_BUFFER_LENGHT)
			{
				buf_len = DEFAULT_BUFFER_LENGHT;
			}
			char* buffer = (char*)malloc(buf_len + 1); //creating of the array of chars to keep characters with BUFFER_LENTH value
			char* firstAppear; //pointer for strstr function
			int bytes_read = 0;
			do
			{
				memset(buffer, '\0', buf_len);
				bytes_read = fread(buffer, sizeof(char), buf_len , file);
				buffer[bytes_read] = '\0';
				firstAppear = strstr(buffer, textToFind);
				if (firstAppear)
				{
					int front = firstAppear - buffer;
					front = front < 10 ? front : 10;
					int back = (buffer + buf_len) - (firstAppear + strlen(textToFind));
					back = back < 10 ? back : 10;

					char* dif = firstAppear - front;
					printf("**** Found! **** \n");
					fwrite(dif, sizeof(char), (front + back + strlen(textToFind)), stdout);
					printf("\n");
													
				}
				fseek(file, (0 - strlen(textToFind)), SEEK_CUR);
			} while (bytes_read == buf_len);

			free(buffer);
			fclose(file);
			system("pause");

			if (!firstAppear)
			{
				printf("**** Wasn't found! **** \n");
				free(buffer);
				system("pause");
				return 1;
			}
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