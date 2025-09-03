#include "MyForm handler.cpp"

using namespace System;
using namespace System::Windows::Forms;

[System::STAThreadAttribute()]
int main(array<String^>^ argc)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Application::Run(gcnew MyNotebook::MyForm);

	return 0;
}