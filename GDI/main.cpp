#include <windows.h>
#include <wingdi.h>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::wstring> vec;

BOOL CALLBACK speichereFenster(HWND hwnd, LPARAM substring) {
	const DWORD TITLE_SIZE = 1024;
	TCHAR windowTitle[TITLE_SIZE];
	GetWindowText(hwnd, windowTitle, TITLE_SIZE);
	int length = ::GetWindowTextLength(hwnd);
	std::wstring temp(&windowTitle[0]);
	if (!IsWindowVisible(hwnd) || length == 0 ) {
		return TRUE;
	}
	vec.push_back(temp);
	return TRUE;
}

int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	std::vector<std::wstring> titles;
	EnumWindows(speichereFenster, NULL);
	std::cout << "Select window below" << std::endl;

	for (int i = 0; i < vec.size(); i++)
	{
		wprintf(L"%d) %s\n", i + 1, vec.at(i).c_str());
	}

	int program = 0;
	std::cin >> program;

	if (program > vec.size())
	{
		std::cerr << "Не тот выбор!";
	}

	HWND hwnd = FindWindow(NULL,vec.at(program-1).c_str()); 

	if (hwnd == nullptr)
	{
		return 1;
	}

	HDC hdc = GetDC(hwnd);

	if (hdc == nullptr)
	{
		return 1;
	}

	int pixelCounter = 0;
	std::wstring wstr;

	while (true)
	{
		std::getline(std::wcin, wstr);

		if (wstr == L"exit") {
			ReleaseDC(nullptr, hdc);
			return 0;
		
		}
		else
		{
			COLORREF bg = RGB(0, 0, 0);
			COLORREF fg = RGB(255, 255, 255);
			SetTextColor(hdc, fg);
			SetBkColor(hdc, bg);
			const wchar_t* message = wstr.c_str();
			TextOut(hdc, 0, pixelCounter, message, wcslen(message));
			TextOut(hdc, -15, 0, L" ", 1);
			pixelCounter += 16;
		}
	}
	return 0;
}
