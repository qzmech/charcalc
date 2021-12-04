#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 25

int main(int num_args, const char* _args[])
{
	if (num_args == 1)
	{
		printf_s("ERROR: no parameters found");
		return 0;
	}

	FILE *_text_file = NULL;

	fopen_s(&_text_file,_args[1], "rb");

	if (_text_file == NULL)
	{
		printf_s("ERROR: this path is not correct");
		return 0;
	}


	fseek(_text_file, 0, SEEK_END);
	unsigned long _size_file = ftell(_text_file);
	rewind(_text_file);

	if (_size_file == 0)
	{
		printf_s("MESSAGE: this file have not data");
		fclose(_text_file);
		return 0;
	}


	char *_buffer = (char*)malloc(_size_file * sizeof(char));

	if (_buffer == NULL)
	{
		printf_s("\nERROR: the data is not able to store in buffer\n");
		free(_text_file);
		fclose(_text_file);
		return 0;
	}

	if (!fread(_buffer, sizeof(char), _size_file, _text_file))
	{
		printf_s("\n# ERROR: this file can not be read");
		free(_buffer);
		fclose(_text_file);
		return 0;
	}

	fclose(_text_file);


	printf_s("TEXT:\n");

	unsigned long _array_length[MAX_WORD_LENGTH] = { 0 };
	unsigned long _length_word = 0;

	for (unsigned long iterator = 0; iterator < _size_file; iterator++)
	{
		printf_s("%c", _buffer[iterator]);

		char _current_char = _buffer[iterator];

		if ((_current_char != ' ') &&
			(_current_char != '!') &&
			(_current_char != '?') &&
			(_current_char != '(') &&
			(_current_char != ')') &&
			(_current_char != '.') &&
			(_current_char != ',') &&
			(_current_char != ':') &&
			(_current_char != ';') &&
			(_current_char != '"') &&
			(_current_char != '#') &&
			(_current_char != '№') &&
			(_current_char != '%') &&
			(_current_char != '+') &&
			(_current_char != '=') &&
			(_current_char != '&') &&
			(_current_char != '*') &&
			(_current_char != '^') &&
			(_current_char != '$') &&
			(_current_char != '@') &&
			(_current_char != '\n') &&
			(_current_char != '\t') &&
			(_current_char != '\v') &&
			(_current_char != '\r') &&
			(_current_char != '\f'))
		{
			_length_word++;
		}
		else if (((_current_char == ' ') || (_current_char == '\n')) &&
			(_length_word != 0) && (_length_word <= MAX_WORD_LENGTH))
		{
			_array_length[(_length_word - 1)]++;
			_length_word = 0;
		}

		if (((iterator + 1) == _size_file) && (_length_word != 0) && (_length_word <= MAX_WORD_LENGTH))
		{
			_array_length[(_length_word - 1)]++;
		}
	}

	free(_buffer);

	printf_s("\nSIZE: %li symbol(s)", _size_file);

	unsigned long _total_words = 0;
	char _words_exist = 0;

	for (unsigned long iterator = 0; iterator < MAX_WORD_LENGTH; iterator++)
	{
		if (_array_length[iterator] != 0)
		{
			_words_exist = 1;
			printf_s("\nLength %li: %li occurrence(s)", (iterator + 1), _array_length[iterator]);
			_total_words += _array_length[iterator];
		}
	}

	if (_words_exist == 1)
	{
		printf_s("\n");
		printf_s("TOTAL: %li word(s)", _total_words);
	}
	else
	{
		printf_s("\nMESSAGE: this file have not words");
	}

	return 0;
}