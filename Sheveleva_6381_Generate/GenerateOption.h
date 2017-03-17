/*
 * Функция генерирования параметров.
 * Входные данные: процент появления команд типа (int).
 * Выходные данные: номер команды типа (int).
 */
int GenerateOption (int percent_command_1,
					int percent_command_2,
					int percent_command_3,
					int percent_command_4)
{
	int option = rand() % 100 + 1;
	if (option < (percent_command_1 + 1)) {
		return 1;
	}
	if ((option > (percent_command_1 - 1)) && (option < (percent_command_1 + percent_command_2 + 1))) {
		return 2;
	}
		if ((option > (percent_command_1 + percent_command_2 - 1)) && (option < (percent_command_1 + percent_command_2 + percent_command_3 + 1))) {
		return 3;
	}
		if (option > (percent_command_1 + percent_command_2 + percent_command_3 - 1)) {
		return 4;
	}	
}
