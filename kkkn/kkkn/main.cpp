#include "Application.h"
#include "windows.h"
#include "locale.h"
int main() {

	system("chcp 1251>nul");
	setlocale(0, "rus");

	return(Application::get().exec());
}