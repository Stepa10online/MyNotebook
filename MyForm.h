

#include "InformationForm.h"
#include "FolderForm.h"
#include "ColorChangeForm.h"
#include <string>
#include <vector>
#include <fstream> 


struct ButtonColor {
	int r;
	int g;
	int b;
};
std::vector<ButtonColor> colors;
bool color_copied = false;
namespace MyNotebook {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			SetSettings();
			openFileDialog1->Filter = "Text files(*.txt)|*.txt|Json files(*.json)|*.json|RTF files (*.rtf)|*.rtf|All files (*.*)|*.*";
			saveFileDialog1->Filter = "Text files(*.txt)|*.txt|Json files(*.json)|*.json|RTF files (*.rtf)|*.rtf|All files (*.*)|*.*";
			//UpdateColors();

		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			SaveSettings();
			if (components)
			{
				delete components;
			}
		}


		int checkDataFromJson()
		{
			setlocale(LC_ALL, "ru");
			// Открываем файл
			FILE* fp;
			fopen_s(&fp, "settings.json", "r");
			if (!fp) {
				//std::cerr << "Не удалось открыть файл!" << std::endl;
				MessageBox::Show("Не удалось открыть settings.json!");
				colors = std::vector<ButtonColor>{};
				return 1;
			}

			// Чтение файла в буфер
			char readBuffer[65536];
			FileReadStream is(fp, readBuffer, sizeof(readBuffer));

			// Парсинг JSON
			Document document;
			document.ParseStream(is);
			fclose(fp);

			// Проверка на наличие ошибок
			if (document.HasParseError()) {
				//std::cerr << "Ошибка парсинга JSON!" << std::endl;
				colors = std::vector<ButtonColor>{};
				return 1;
			}

			// Проверка, что это объект
			if (!document.IsObject()) {
				//std::cerr << "Ожидался объект JSON!" << std::endl;
				colors = std::vector<ButtonColor>{};
				return 1;
			}

			// Проверка наличия массива "btns open save"
			if (document.HasMember("btns open save") && document["btns open save"].IsBool()) {
				this->кнопкиОткрытьСохранитьToolStripMenuItem->Checked = document["btns open save"].GetBool();
			}
			// Проверка наличия массива "btns open save"
			if (document.HasMember("file opening format") && document["file opening format"].IsInt()) {
				filter_selected = document["file opening format"].GetInt();
			}
			// Проверка наличия массива "save folder"
			if (document.HasMember("save folder") && document["save folder"].IsString()) {
				folder_save = document["save folder"].GetString();
				if(standart_open_folder)
					this->openFileDialog1->InitialDirectory = gcnew String(folder_save.c_str());
			}
			// Проверка наличия массива "edit color"
			if (document.HasMember("edit color") && document["edit color"].IsBool()) {
				this->показыватьНастройкуЦветаToolStripMenuItem->Checked = document["edit color"].GetBool();
			}
			// Проверка наличия массива "show save popup"
			if (document.HasMember("show save popup") && document["show save popup"].IsBool()) {
				show_save_popup = document["show save popup"].GetBool();
				this->ShowSavePopUpToolStripMenuItem->Checked = show_save_popup;
			}
			// Проверка наличия массива "color"
			if (document.HasMember("colors") && document["colors"].IsArray()) {
				const Value& colorArray = document["colors"];


				// Итерация по элементам массива
				for (rapidjson::SizeType i = 0; i < colorArray.Size(); i++) {
					const Value& colorValue = colorArray[i];

					// Проверка, что это объект
					if (colorValue.IsObject()) {
						ButtonColor person;

						// Извлечение красного
						if (colorValue.HasMember("r") && colorValue["r"].IsInt()) {
							person.r = colorValue["r"].GetInt();
						}

						// Извлечение зеленого
						if (colorValue.HasMember("g") && colorValue["g"].IsInt()) {
							person.g = colorValue["g"].GetInt();
						}

						// Извлечение синего
						if (colorValue.HasMember("b") && colorValue["b"].IsInt()) {
							person.b = colorValue["b"].GetInt();
						}

						// Добавление в вектор
						colors.push_back(person);
					}
				}

				//return colors;
				//// Вывод данных
				//for (const auto& person : colors) {
				//}
			}
			else {
				//std::cerr << "Массив 'colors' не найден!" << std::endl;
			}
		}
		void SaveDataToJson(const std::string& filename) {
			setlocale(LC_ALL, "ru");
			// Создаем JSON документ
			Document document;
			document.SetObject();

			// Создаем аллокатор
			Document::AllocatorType& allocator = document.GetAllocator();

			Value s;
			s.SetString(StringRef(folder_save.c_str()));

			// Добавляем другие поля
			document.AddMember("btns open save", this->кнопкиОткрытьСохранитьToolStripMenuItem->Checked, allocator);
			document.AddMember("edit color", this->показыватьНастройкуЦветаToolStripMenuItem->Checked, allocator);
			document.AddMember("file opening format", filter_selected, allocator);
			document.AddMember("save folder", s, allocator);
			document.AddMember("show save popup", show_save_popup, allocator);
			//save_folder.SetString(cbuffer, len, allocator);

			// Создаем массив для цветов
			Value colorArray(kArrayType);

			// Заполняем массив цветами
			for (const auto& color : colors) {
				Value colorObject(kObjectType);
				colorObject.AddMember("r", color.r, allocator);
				colorObject.AddMember("g", color.g, allocator);
				colorObject.AddMember("b", color.b, allocator);
				colorArray.PushBack(colorObject, allocator);
			}

			// Добавляем массив цветов в документ
			document.AddMember("colors", colorArray, allocator);

			// Создаем строковый буфер для записи
			StringBuffer buffer;
			Writer<StringBuffer> writer(buffer);
			document.Accept(writer);

			// Записываем в файл
			std::ofstream outFile(filename);
			if (!outFile) {
				MessageBox::Show("Не удалось открыть файл для записи!");
				//std::cerr << "Не удалось открыть файл для записи!" << std::endl;
				return;
			}
			outFile << buffer.GetString();
			outFile.close();
			//std::cout << "Данные успешно сохранены в " << filename << std::endl;
		}
		void UpdateColors()
		{
			this->Color_button_1->BackColor = System::Drawing::Color::FromArgb(colors[0].r, colors[0].g, colors[0].b);
			this->Color_button_2->BackColor = System::Drawing::Color::FromArgb(colors[1].r, colors[1].g, colors[1].b);
			this->Color_button_3->BackColor = System::Drawing::Color::FromArgb(colors[2].r, colors[2].g, colors[2].b);
			this->Color_button_4->BackColor = System::Drawing::Color::FromArgb(colors[3].r, colors[3].g, colors[3].b);
			this->Color_button_5->BackColor = System::Drawing::Color::FromArgb(colors[4].r, colors[4].g, colors[4].b);
			this->Color_button_6->BackColor = System::Drawing::Color::FromArgb(colors[5].r, colors[5].g, colors[5].b);
			this->Color_button_7->BackColor = System::Drawing::Color::FromArgb(colors[6].r, colors[6].g, colors[6].b);
			this->Color_button_8->BackColor = System::Drawing::Color::FromArgb(colors[7].r, colors[7].g, colors[7].b);
			this->Color_button_9->BackColor = System::Drawing::Color::FromArgb(colors[8].r, colors[8].g, colors[8].b);
		}
		void SetSettings()
		{
			checkDataFromJson();
			UpdateColors();
			updateBottomButtons();
			updateRichBoxSize();

			this->openFileDialog1->InitialDirectory = gcnew String(folder_save.c_str());
			this->saveFileDialog1->InitialDirectory = gcnew String(folder_save.c_str());
		}
		void SaveSettings()
		{
			colors.clear();
			colors.push_back({ this->Color_button_1->BackColor.R,this->Color_button_1->BackColor.G, this->Color_button_1->BackColor.B });
			colors.push_back({ this->Color_button_2->BackColor.R,this->Color_button_2->BackColor.G, this->Color_button_2->BackColor.B });
			colors.push_back({ this->Color_button_3->BackColor.R,this->Color_button_3->BackColor.G, this->Color_button_3->BackColor.B });
			colors.push_back({ this->Color_button_4->BackColor.R,this->Color_button_4->BackColor.G, this->Color_button_4->BackColor.B });
			colors.push_back({ this->Color_button_5->BackColor.R,this->Color_button_5->BackColor.G, this->Color_button_5->BackColor.B });
			colors.push_back({ this->Color_button_6->BackColor.R,this->Color_button_6->BackColor.G, this->Color_button_6->BackColor.B });
			colors.push_back({ this->Color_button_7->BackColor.R,this->Color_button_7->BackColor.G, this->Color_button_7->BackColor.B });
			colors.push_back({ this->Color_button_8->BackColor.R,this->Color_button_8->BackColor.G, this->Color_button_8->BackColor.B });
			colors.push_back({ this->Color_button_9->BackColor.R,this->Color_button_9->BackColor.G, this->Color_button_9->BackColor.B });
			SaveDataToJson("settings.json");
		}

		String^ file_name = "";
	protected:


	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ создатьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ переименоватьToolStripMenuItem;

	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::StatusStrip^ statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^ toolStripStatusLabel1;

	private: System::Windows::Forms::ToolStripMenuItem^ найтиToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;

	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::Button^ open_button;
	private: System::Windows::Forms::Button^ save_button;


	private: System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
	private: System::Windows::Forms::TextBox^ filename_textBox;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ buttonRenameSave;
	private: System::Windows::Forms::ToolStripMenuItem^ системаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ выйтиИзСистемыToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ справкаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ оПрограммеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ открытьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ сохранитьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
	private: System::Windows::Forms::ContextMenuStrip^ richTextBox_contextMenuStrip;

	private: System::Windows::Forms::ToolStripMenuItem^ очиститьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ копироватьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ вырезатьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ вставитьToolStripMenuItem;



	private: System::Windows::Forms::TextBox^ find_textBox;
	private: System::Windows::Forms::Label^ find_label2;
	private: System::Windows::Forms::Button^ find_button;
	private: System::Windows::Forms::FontDialog^ fontDialog1;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^ настроитьТекстToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ шрифтToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ папкаСохраненийToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ настройкиToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ показыватьИмяФайлаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ кнопкиОткрытьСохранитьToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ активированныеРежимыToolStripMenuItem;
	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Button^ Color_button_1;
	private: System::Windows::Forms::Label^ label__Color__;
	private: System::Windows::Forms::Button^ Color_button_2;
	private: System::Windows::Forms::Button^ Color_button_4;
	private: System::Windows::Forms::Button^ Color_button_3;
	private: System::Windows::Forms::ContextMenuStrip^ Color_contextMenuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^ ChangeColorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ добавитьВИзбранноеToolStripMenuItem;
	private: System::Windows::Forms::Button^ EditColors;
	private: System::Windows::Forms::ColorDialog^ colorDialog1;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator4;
	private: System::Windows::Forms::ToolStripMenuItem^ размерToolStripMenuItem;
	private: System::Windows::Forms::ToolStripComboBox^ toolStripComboBox1;
	private: System::Windows::Forms::ToolStripMenuItem^ показыватьНастройкуЦветаToolStripMenuItem;
	private: System::Windows::Forms::Button^ Color_button_5;
	private: System::Windows::Forms::Button^ Color_button_7;
	private: System::Windows::Forms::Button^ Color_button_6;
	private: System::Windows::Forms::Button^ Color_button_9;
	private: System::Windows::Forms::Button^ Color_button_8;
	private: System::Windows::Forms::ToolStripMenuItem^ копироватьЦветToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator3;
	private: System::Windows::Forms::Button^ Color_button_10;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator5;
	private: System::Windows::Forms::ToolStripMenuItem^ выделитьЖирнымToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ выделитьКурсивомToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ выделитьПодчеркиваниемToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ выделитьЗачеркиваниемToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ очиститьВыделениеToolStripMenuItem;
private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator6;
private: System::Windows::Forms::ToolStripMenuItem^ ShowSavePopUpToolStripMenuItem;
	protected:
		Control last_hovered_control;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->создатьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->открытьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->сохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->переименоватьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->найтиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->настроитьТекстToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->шрифтToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->размерToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripComboBox1 = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->папкаСохраненийToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->настройкиToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->кнопкиОткрытьСохранитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->показыватьНастройкуЦветаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ShowSavePopUpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->активированныеРежимыToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->показыватьИмяФайлаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->справкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->оПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->системаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выйтиИзСистемыToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox_contextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->копироватьЦветToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->копироватьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->вырезатьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->вставитьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->очиститьToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->очиститьВыделениеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выделитьЖирнымToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выделитьКурсивомToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выделитьПодчеркиваниемToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->выделитьЗачеркиваниемToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->open_button = (gcnew System::Windows::Forms::Button());
			this->save_button = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->filename_textBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->buttonRenameSave = (gcnew System::Windows::Forms::Button());
			this->find_textBox = (gcnew System::Windows::Forms::TextBox());
			this->find_label2 = (gcnew System::Windows::Forms::Label());
			this->find_button = (gcnew System::Windows::Forms::Button());
			this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->Color_button_10 = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->Color_button_1 = (gcnew System::Windows::Forms::Button());
			this->Color_contextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->ChangeColorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->добавитьВИзбранноеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label__Color__ = (gcnew System::Windows::Forms::Label());
			this->Color_button_2 = (gcnew System::Windows::Forms::Button());
			this->Color_button_4 = (gcnew System::Windows::Forms::Button());
			this->Color_button_3 = (gcnew System::Windows::Forms::Button());
			this->EditColors = (gcnew System::Windows::Forms::Button());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->Color_button_5 = (gcnew System::Windows::Forms::Button());
			this->Color_button_7 = (gcnew System::Windows::Forms::Button());
			this->Color_button_6 = (gcnew System::Windows::Forms::Button());
			this->Color_button_9 = (gcnew System::Windows::Forms::Button());
			this->Color_button_8 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1->SuspendLayout();
			this->statusStrip1->SuspendLayout();
			this->richTextBox_contextMenuStrip->SuspendLayout();
			this->Color_contextMenuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->файлToolStripMenuItem,
					this->настройкиToolStripMenuItem, this->справкаToolStripMenuItem, this->системаToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(496, 24);
			this->menuStrip1->TabIndex = 2;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^>(10) {
				this->создатьToolStripMenuItem,
					this->toolStripSeparator4, this->открытьToolStripMenuItem, this->сохранитьToolStripMenuItem, this->toolStripSeparator1, this->переименоватьToolStripMenuItem,
					this->найтиToolStripMenuItem, this->toolStripSeparator2, this->настроитьТекстToolStripMenuItem, this->папкаСохраненийToolStripMenuItem
			});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(48, 20);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// создатьToolStripMenuItem
			// 
			this->создатьToolStripMenuItem->Name = L"создатьToolStripMenuItem";
			this->создатьToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+N";
			this->создатьToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->создатьToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->создатьToolStripMenuItem->Text = L"Создать";
			this->создатьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::создатьToolStripMenuItem_Click);
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(199, 6);
			// 
			// открытьToolStripMenuItem
			// 
			this->открытьToolStripMenuItem->Name = L"открытьToolStripMenuItem";
			this->открытьToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+O";
			this->открытьToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->открытьToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->открытьToolStripMenuItem->Text = L"Открыть";
			this->открытьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::open_button_Click);
			// 
			// сохранитьToolStripMenuItem
			// 
			this->сохранитьToolStripMenuItem->Name = L"сохранитьToolStripMenuItem";
			this->сохранитьToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+S";
			this->сохранитьToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->сохранитьToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->сохранитьToolStripMenuItem->Text = L"Сохранить";
			this->сохранитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::save_button_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(199, 6);
			// 
			// переименоватьToolStripMenuItem
			// 
			this->переименоватьToolStripMenuItem->CheckOnClick = true;
			this->переименоватьToolStripMenuItem->Name = L"переименоватьToolStripMenuItem";
			this->переименоватьToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+R";
			this->переименоватьToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::R));
			this->переименоватьToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->переименоватьToolStripMenuItem->Text = L"Переименовать";
			this->переименоватьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::переименоватьToolStripMenuItem_Click);
			// 
			// найтиToolStripMenuItem
			// 
			this->найтиToolStripMenuItem->CheckOnClick = true;
			this->найтиToolStripMenuItem->Name = L"найтиToolStripMenuItem";
			this->найтиToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+F";
			this->найтиToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F));
			this->найтиToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->найтиToolStripMenuItem->Text = L"Найти";
			this->найтиToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::найтиToolStripMenuItem_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(199, 6);
			// 
			// настроитьТекстToolStripMenuItem
			// 
			this->настроитьТекстToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->шрифтToolStripMenuItem,
					this->размерToolStripMenuItem
			});
			this->настроитьТекстToolStripMenuItem->Name = L"настроитьТекстToolStripMenuItem";
			this->настроитьТекстToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->настроитьТекстToolStripMenuItem->Text = L"Настроить текст";
			// 
			// шрифтToolStripMenuItem
			// 
			this->шрифтToolStripMenuItem->Name = L"шрифтToolStripMenuItem";
			this->шрифтToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->шрифтToolStripMenuItem->Text = L"Шрифт";
			this->шрифтToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::шрифтToolStripMenuItem_Click);
			// 
			// размерToolStripMenuItem
			// 
			this->размерToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripComboBox1 });
			this->размерToolStripMenuItem->Name = L"размерToolStripMenuItem";
			this->размерToolStripMenuItem->Size = System::Drawing::Size(114, 22);
			this->размерToolStripMenuItem->Text = L"Размер";
			this->размерToolStripMenuItem->Visible = false;
			// 
			// toolStripComboBox1
			// 
			this->toolStripComboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"25", L"50", L"100", L"125", L"150",
					L"200"
			});
			this->toolStripComboBox1->Name = L"toolStripComboBox1";
			this->toolStripComboBox1->Size = System::Drawing::Size(121, 23);
			// 
			// папкаСохраненийToolStripMenuItem
			// 
			this->папкаСохраненийToolStripMenuItem->Name = L"папкаСохраненийToolStripMenuItem";
			this->папкаСохраненийToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->папкаСохраненийToolStripMenuItem->Text = L"Настройки открытия";
			this->папкаСохраненийToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::настройкиОткрытияToolStripMenuItem_Click);
			// 
			// настройкиToolStripMenuItem
			// 
			this->настройкиToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->кнопкиОткрытьСохранитьToolStripMenuItem,
					this->показыватьНастройкуЦветаToolStripMenuItem, this->toolStripSeparator6, this->ShowSavePopUpToolStripMenuItem, this->активированныеРежимыToolStripMenuItem,
					this->показыватьИмяФайлаToolStripMenuItem
			});
			this->настройкиToolStripMenuItem->Name = L"настройкиToolStripMenuItem";
			this->настройкиToolStripMenuItem->Size = System::Drawing::Size(79, 20);
			this->настройкиToolStripMenuItem->Text = L"Настройки";
			// 
			// кнопкиОткрытьСохранитьToolStripMenuItem
			// 
			this->кнопкиОткрытьСохранитьToolStripMenuItem->Checked = true;
			this->кнопкиОткрытьСохранитьToolStripMenuItem->CheckOnClick = true;
			this->кнопкиОткрытьСохранитьToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->кнопкиОткрытьСохранитьToolStripMenuItem->Name = L"кнопкиОткрытьСохранитьToolStripMenuItem";
			this->кнопкиОткрытьСохранитьToolStripMenuItem->Size = System::Drawing::Size(253, 22);
			this->кнопкиОткрытьСохранитьToolStripMenuItem->Text = L"Кнопки \"Открыть\", \"Сохранить\"";
			this->кнопкиОткрытьСохранитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::кнопкиОткрытьСохранитьToolStripMenuItem_Click);
			// 
			// показыватьНастройкуЦветаToolStripMenuItem
			// 
			this->показыватьНастройкуЦветаToolStripMenuItem->Checked = true;
			this->показыватьНастройкуЦветаToolStripMenuItem->CheckOnClick = true;
			this->показыватьНастройкуЦветаToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->показыватьНастройкуЦветаToolStripMenuItem->Name = L"показыватьНастройкуЦветаToolStripMenuItem";
			this->показыватьНастройкуЦветаToolStripMenuItem->Size = System::Drawing::Size(253, 22);
			this->показыватьНастройкуЦветаToolStripMenuItem->Text = L"Показывать настройку цвета";
			this->показыватьНастройкуЦветаToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MyForm::показыватьНастройкуЦветаToolStripMenuItem_CheckedChanged);
			// 
			// toolStripSeparator6
			// 
			this->toolStripSeparator6->Name = L"toolStripSeparator6";
			this->toolStripSeparator6->Size = System::Drawing::Size(250, 6);
			// 
			// ShowSavePopUpToolStripMenuItem
			// 
			this->ShowSavePopUpToolStripMenuItem->Checked = true;
			this->ShowSavePopUpToolStripMenuItem->CheckOnClick = true;
			this->ShowSavePopUpToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->ShowSavePopUpToolStripMenuItem->Name = L"ShowSavePopUpToolStripMenuItem";
			this->ShowSavePopUpToolStripMenuItem->Size = System::Drawing::Size(253, 22);
			this->ShowSavePopUpToolStripMenuItem->Text = L"Всплывающее окно сохранения";
			this->ShowSavePopUpToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ShowSavePopUpToolStripMenuItem_Click);
			// 
			// активированныеРежимыToolStripMenuItem
			// 
			this->активированныеРежимыToolStripMenuItem->AutoToolTip = true;
			this->активированныеРежимыToolStripMenuItem->CheckOnClick = true;
			this->активированныеРежимыToolStripMenuItem->Name = L"активированныеРежимыToolStripMenuItem";
			this->активированныеРежимыToolStripMenuItem->Size = System::Drawing::Size(253, 22);
			this->активированныеРежимыToolStripMenuItem->Text = L"Активированные режимы";
			this->активированныеРежимыToolStripMenuItem->ToolTipText = L"Показывает нажаты ли кнопки:\r\n* CAPSLOCK\r\n* NUMLOCK\r\n* INSLOCK";
			this->активированныеРежимыToolStripMenuItem->Visible = false;
			// 
			// показыватьИмяФайлаToolStripMenuItem
			// 
			this->показыватьИмяФайлаToolStripMenuItem->Checked = true;
			this->показыватьИмяФайлаToolStripMenuItem->CheckOnClick = true;
			this->показыватьИмяФайлаToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->показыватьИмяФайлаToolStripMenuItem->Name = L"показыватьИмяФайлаToolStripMenuItem";
			this->показыватьИмяФайлаToolStripMenuItem->Size = System::Drawing::Size(253, 22);
			this->показыватьИмяФайлаToolStripMenuItem->Text = L"Показывать имя файла";
			this->показыватьИмяФайлаToolStripMenuItem->Visible = false;
			// 
			// справкаToolStripMenuItem
			// 
			this->справкаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->оПрограммеToolStripMenuItem });
			this->справкаToolStripMenuItem->Name = L"справкаToolStripMenuItem";
			this->справкаToolStripMenuItem->Size = System::Drawing::Size(65, 20);
			this->справкаToolStripMenuItem->Text = L"Справка";
			// 
			// оПрограммеToolStripMenuItem
			// 
			this->оПрограммеToolStripMenuItem->Name = L"оПрограммеToolStripMenuItem";
			this->оПрограммеToolStripMenuItem->Overflow = System::Windows::Forms::ToolStripItemOverflow::Always;
			this->оПрограммеToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->оПрограммеToolStripMenuItem->Text = L"О программе";
			this->оПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::оПрограммеToolStripMenuItem_Click);
			// 
			// системаToolStripMenuItem
			// 
			this->системаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->выйтиИзСистемыToolStripMenuItem });
			this->системаToolStripMenuItem->Name = L"системаToolStripMenuItem";
			this->системаToolStripMenuItem->Size = System::Drawing::Size(66, 20);
			this->системаToolStripMenuItem->Text = L"Система";
			// 
			// выйтиИзСистемыToolStripMenuItem
			// 
			this->выйтиИзСистемыToolStripMenuItem->Name = L"выйтиИзСистемыToolStripMenuItem";
			this->выйтиИзСистемыToolStripMenuItem->Size = System::Drawing::Size(175, 22);
			this->выйтиИзСистемыToolStripMenuItem->Text = L"Выйти из системы";
			this->выйтиИзСистемыToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::выйтиИзСистемыToolStripMenuItem_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(384, 2);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(100, 22);
			this->progressBar1->TabIndex = 4;
			this->progressBar1->Visible = false;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripStatusLabel1 });
			this->statusStrip1->Location = System::Drawing::Point(0, 451);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(496, 22);
			this->statusStrip1->TabIndex = 5;
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(76, 17);
			this->toolStripStatusLabel1->Text = L"Символов: 0";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = L"txt";
			// 
			// richTextBox1
			// 
			this->richTextBox1->AcceptsTab = true;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->ContextMenuStrip = this->richTextBox_contextMenuStrip;
			this->richTextBox1->EnableAutoDragDrop = true;
			this->richTextBox1->Location = System::Drawing::Point(13, 54);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(471, 357);
			this->richTextBox1->TabIndex = 8;
			this->richTextBox1->Text = L"";
			this->richTextBox1->SelectionChanged += gcnew System::EventHandler(this, &MyForm::richTextBox1_SelectionChanged);
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox1_TextChanged);
			// 
			// richTextBox_contextMenuStrip
			// 
			this->richTextBox_contextMenuStrip->BackColor = System::Drawing::SystemColors::Control;
			this->richTextBox_contextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(12) {
				this->копироватьЦветToolStripMenuItem,
					this->toolStripSeparator3, this->копироватьToolStripMenuItem, this->вырезатьToolStripMenuItem, this->вставитьToolStripMenuItem,
					this->очиститьToolStripMenuItem, this->toolStripSeparator5, this->очиститьВыделениеToolStripMenuItem, this->выделитьЖирнымToolStripMenuItem,
					this->выделитьКурсивомToolStripMenuItem, this->выделитьПодчеркиваниемToolStripMenuItem, this->выделитьЗачеркиваниемToolStripMenuItem
			});
			this->richTextBox_contextMenuStrip->Name = L"contextMenuStrip1";
			this->richTextBox_contextMenuStrip->Size = System::Drawing::Size(267, 236);
			// 
			// копироватьЦветToolStripMenuItem
			// 
			this->копироватьЦветToolStripMenuItem->Name = L"копироватьЦветToolStripMenuItem";
			this->копироватьЦветToolStripMenuItem->Size = System::Drawing::Size(266, 22);
			this->копироватьЦветToolStripMenuItem->Text = L"Копировать цвет";
			this->копироватьЦветToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::копироватьЦветToolStripMenuItem_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(263, 6);
			// 
			// копироватьToolStripMenuItem
			// 
			this->копироватьToolStripMenuItem->Name = L"копироватьToolStripMenuItem";
			this->копироватьToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+C";
			this->копироватьToolStripMenuItem->Size = System::Drawing::Size(266, 22);
			this->копироватьToolStripMenuItem->Text = L"Копировать";
			this->копироватьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::копироватьToolStripMenuItem_Click);
			// 
			// вырезатьToolStripMenuItem
			// 
			this->вырезатьToolStripMenuItem->Name = L"вырезатьToolStripMenuItem";
			this->вырезатьToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+X";
			this->вырезатьToolStripMenuItem->Size = System::Drawing::Size(266, 22);
			this->вырезатьToolStripMenuItem->Text = L"Вырезать";
			this->вырезатьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::вырезатьToolStripMenuItem_Click);
			// 
			// вставитьToolStripMenuItem
			// 
			this->вставитьToolStripMenuItem->Name = L"вставитьToolStripMenuItem";
			this->вставитьToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+V";
			this->вставитьToolStripMenuItem->Size = System::Drawing::Size(266, 22);
			this->вставитьToolStripMenuItem->Text = L"Вставить";
			this->вставитьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::вставитьToolStripMenuItem_Click);
			// 
			// очиститьToolStripMenuItem
			// 
			this->очиститьToolStripMenuItem->Name = L"очиститьToolStripMenuItem";
			this->очиститьToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+Shift+B";
			this->очиститьToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				| System::Windows::Forms::Keys::B));
			this->очиститьToolStripMenuItem->Size = System::Drawing::Size(266, 22);
			this->очиститьToolStripMenuItem->Text = L"Очистить всё";
			this->очиститьToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::очиститьToolStripMenuItem_Click);
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(263, 6);
			// 
			// очиститьВыделениеToolStripMenuItem
			// 
			this->очиститьВыделениеToolStripMenuItem->Name = L"очиститьВыделениеToolStripMenuItem";
			this->очиститьВыделениеToolStripMenuItem->Size = System::Drawing::Size(266, 22);
			this->очиститьВыделениеToolStripMenuItem->Text = L"Очистить выделение";
			this->очиститьВыделениеToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::очиститьВыделениеToolStripMenuItem_Click);
			// 
			// выделитьЖирнымToolStripMenuItem
			// 
			this->выделитьЖирнымToolStripMenuItem->Name = L"выделитьЖирнымToolStripMenuItem";
			this->выделитьЖирнымToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+B";
			this->выделитьЖирнымToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::B));
			this->выделитьЖирнымToolStripMenuItem->Size = System::Drawing::Size(266, 22);
			this->выделитьЖирнымToolStripMenuItem->Text = L"Выделить жирным";
			this->выделитьЖирнымToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::выделитьЖирнымToolStripMenuItem_Click);
			// 
			// выделитьКурсивомToolStripMenuItem
			// 
			this->выделитьКурсивомToolStripMenuItem->Name = L"выделитьКурсивомToolStripMenuItem";
			this->выделитьКурсивомToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+I";
			this->выделитьКурсивомToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::I));
			this->выделитьКурсивомToolStripMenuItem->Size = System::Drawing::Size(266, 22);
			this->выделитьКурсивомToolStripMenuItem->Text = L"Выделить курсивом";
			this->выделитьКурсивомToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::выделитьКурсивомToolStripMenuItem_Click);
			// 
			// выделитьПодчеркиваниемToolStripMenuItem
			// 
			this->выделитьПодчеркиваниемToolStripMenuItem->Name = L"выделитьПодчеркиваниемToolStripMenuItem";
			this->выделитьПодчеркиваниемToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+U";
			this->выделитьПодчеркиваниемToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::U));
			this->выделитьПодчеркиваниемToolStripMenuItem->Size = System::Drawing::Size(266, 22);
			this->выделитьПодчеркиваниемToolStripMenuItem->Text = L"Выделить подчеркиванием";
			this->выделитьПодчеркиваниемToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::выделитьПодчеркиваниемToolStripMenuItem_Click);
			// 
			// выделитьЗачеркиваниемToolStripMenuItem
			// 
			this->выделитьЗачеркиваниемToolStripMenuItem->Name = L"выделитьЗачеркиваниемToolStripMenuItem";
			this->выделитьЗачеркиваниемToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl+M";
			this->выделитьЗачеркиваниемToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::M));
			this->выделитьЗачеркиваниемToolStripMenuItem->Size = System::Drawing::Size(266, 22);
			this->выделитьЗачеркиваниемToolStripMenuItem->Text = L"Выделить зачеркиванием";
			this->выделитьЗачеркиваниемToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::выделитьЗачеркиваниемToolStripMenuItem_Click);
			// 
			// open_button
			// 
			this->open_button->Location = System::Drawing::Point(13, 418);
			this->open_button->Name = L"open_button";
			this->open_button->Size = System::Drawing::Size(75, 23);
			this->open_button->TabIndex = 9;
			this->open_button->Text = L"Открыть";
			this->open_button->UseVisualStyleBackColor = true;
			this->open_button->Click += gcnew System::EventHandler(this, &MyForm::open_button_Click);
			// 
			// save_button
			// 
			this->save_button->Location = System::Drawing::Point(94, 418);
			this->save_button->Name = L"save_button";
			this->save_button->Size = System::Drawing::Size(75, 23);
			this->save_button->TabIndex = 10;
			this->save_button->Text = L"Сохранить";
			this->save_button->UseVisualStyleBackColor = true;
			this->save_button->Click += gcnew System::EventHandler(this, &MyForm::save_button_Click);
			// 
			// filename_textBox
			// 
			this->filename_textBox->Location = System::Drawing::Point(85, 28);
			this->filename_textBox->Name = L"filename_textBox";
			this->filename_textBox->ReadOnly = true;
			this->filename_textBox->Size = System::Drawing::Size(399, 20);
			this->filename_textBox->TabIndex = 11;
			this->filename_textBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::filename_textBox_KeyDown);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(67, 13);
			this->label1->TabIndex = 12;
			this->label1->Text = L"Имя файла:";
			// 
			// buttonRenameSave
			// 
			this->buttonRenameSave->Location = System::Drawing::Point(389, 26);
			this->buttonRenameSave->Name = L"buttonRenameSave";
			this->buttonRenameSave->Size = System::Drawing::Size(95, 23);
			this->buttonRenameSave->TabIndex = 13;
			this->buttonRenameSave->Text = L"Сохранить";
			this->buttonRenameSave->UseVisualStyleBackColor = true;
			this->buttonRenameSave->Visible = false;
			this->buttonRenameSave->Click += gcnew System::EventHandler(this, &MyForm::buttonRenameSave_Click);
			// 
			// find_textBox
			// 
			this->find_textBox->Location = System::Drawing::Point(85, 54);
			this->find_textBox->Name = L"find_textBox";
			this->find_textBox->Size = System::Drawing::Size(186, 20);
			this->find_textBox->TabIndex = 15;
			this->find_textBox->Visible = false;
			this->find_textBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::find_textBox_KeyDown);
			// 
			// find_label2
			// 
			this->find_label2->AutoSize = true;
			this->find_label2->Location = System::Drawing::Point(16, 57);
			this->find_label2->Name = L"find_label2";
			this->find_label2->Size = System::Drawing::Size(63, 13);
			this->find_label2->TabIndex = 16;
			this->find_label2->Text = L"Ненайдено";
			this->find_label2->Visible = false;
			// 
			// find_button
			// 
			this->find_button->Location = System::Drawing::Point(277, 54);
			this->find_button->Name = L"find_button";
			this->find_button->Size = System::Drawing::Size(47, 20);
			this->find_button->TabIndex = 17;
			this->find_button->Text = L"Найти";
			this->find_button->UseVisualStyleBackColor = true;
			this->find_button->Visible = false;
			this->find_button->Click += gcnew System::EventHandler(this, &MyForm::find_button_Click);
			// 
			// fontDialog1
			// 
			this->fontDialog1->ShowColor = true;
			// 
			// Color_button_10
			// 
			this->Color_button_10->Enabled = false;
			this->Color_button_10->FlatAppearance->BorderSize = 0;
			this->Color_button_10->Location = System::Drawing::Point(469, 419);
			this->Color_button_10->Name = L"Color_button_10";
			this->Color_button_10->Size = System::Drawing::Size(22, 22);
			this->Color_button_10->TabIndex = 29;
			this->toolTip1->SetToolTip(this->Color_button_10, L"Additional color for copying");
			this->Color_button_10->UseVisualStyleBackColor = true;
			this->Color_button_10->Click += gcnew System::EventHandler(this, &MyForm::Color_button_Click);
			// 
			// Color_button_1
			// 
			this->Color_button_1->BackColor = System::Drawing::Color::Red;
			this->Color_button_1->ContextMenuStrip = this->Color_contextMenuStrip;
			this->Color_button_1->FlatAppearance->BorderSize = 0;
			this->Color_button_1->ForeColor = System::Drawing::Color::Black;
			this->Color_button_1->Location = System::Drawing::Point(217, 420);
			this->Color_button_1->Name = L"Color_button_1";
			this->Color_button_1->Size = System::Drawing::Size(22, 22);
			this->Color_button_1->TabIndex = 18;
			this->Color_button_1->UseVisualStyleBackColor = false;
			this->Color_button_1->Click += gcnew System::EventHandler(this, &MyForm::Color_button_Click);
			// 
			// Color_contextMenuStrip
			// 
			this->Color_contextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ChangeColorToolStripMenuItem,
					this->добавитьВИзбранноеToolStripMenuItem
			});
			this->Color_contextMenuStrip->Name = L"Color_contextMenuStrip";
			this->Color_contextMenuStrip->Size = System::Drawing::Size(198, 48);
			// 
			// ChangeColorToolStripMenuItem
			// 
			this->ChangeColorToolStripMenuItem->Name = L"ChangeColorToolStripMenuItem";
			this->ChangeColorToolStripMenuItem->Size = System::Drawing::Size(197, 22);
			this->ChangeColorToolStripMenuItem->Text = L"Изменить цвет";
			this->ChangeColorToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ChangeColorToolStripMenuItem_Click);
			// 
			// добавитьВИзбранноеToolStripMenuItem
			// 
			this->добавитьВИзбранноеToolStripMenuItem->Name = L"добавитьВИзбранноеToolStripMenuItem";
			this->добавитьВИзбранноеToolStripMenuItem->Size = System::Drawing::Size(197, 22);
			this->добавитьВИзбранноеToolStripMenuItem->Text = L"Добавить в избранное";
			this->добавитьВИзбранноеToolStripMenuItem->Visible = false;
			// 
			// label__Color__
			// 
			this->label__Color__->AutoSize = true;
			this->label__Color__->Location = System::Drawing::Point(176, 425);
			this->label__Color__->Name = L"label__Color__";
			this->label__Color__->Size = System::Drawing::Size(34, 13);
			this->label__Color__->TabIndex = 19;
			this->label__Color__->Text = L"Color:";
			// 
			// Color_button_2
			// 
			this->Color_button_2->BackColor = System::Drawing::Color::Lime;
			this->Color_button_2->ContextMenuStrip = this->Color_contextMenuStrip;
			this->Color_button_2->FlatAppearance->BorderSize = 0;
			this->Color_button_2->ForeColor = System::Drawing::Color::Black;
			this->Color_button_2->Location = System::Drawing::Point(245, 420);
			this->Color_button_2->Name = L"Color_button_2";
			this->Color_button_2->Size = System::Drawing::Size(22, 22);
			this->Color_button_2->TabIndex = 20;
			this->Color_button_2->UseVisualStyleBackColor = false;
			this->Color_button_2->Click += gcnew System::EventHandler(this, &MyForm::Color_button_Click);
			// 
			// Color_button_4
			// 
			this->Color_button_4->BackColor = System::Drawing::Color::Black;
			this->Color_button_4->ContextMenuStrip = this->Color_contextMenuStrip;
			this->Color_button_4->FlatAppearance->BorderSize = 0;
			this->Color_button_4->ForeColor = System::Drawing::Color::Black;
			this->Color_button_4->Location = System::Drawing::Point(301, 420);
			this->Color_button_4->Name = L"Color_button_4";
			this->Color_button_4->Size = System::Drawing::Size(22, 22);
			this->Color_button_4->TabIndex = 22;
			this->Color_button_4->UseVisualStyleBackColor = false;
			this->Color_button_4->Click += gcnew System::EventHandler(this, &MyForm::Color_button_Click);
			// 
			// Color_button_3
			// 
			this->Color_button_3->BackColor = System::Drawing::Color::Blue;
			this->Color_button_3->ContextMenuStrip = this->Color_contextMenuStrip;
			this->Color_button_3->FlatAppearance->BorderSize = 0;
			this->Color_button_3->ForeColor = System::Drawing::Color::Black;
			this->Color_button_3->Location = System::Drawing::Point(273, 420);
			this->Color_button_3->Name = L"Color_button_3";
			this->Color_button_3->Size = System::Drawing::Size(22, 22);
			this->Color_button_3->TabIndex = 21;
			this->Color_button_3->UseVisualStyleBackColor = false;
			this->Color_button_3->Click += gcnew System::EventHandler(this, &MyForm::Color_button_Click);
			// 
			// EditColors
			// 
			this->EditColors->Location = System::Drawing::Point(329, 450);
			this->EditColors->Name = L"EditColors";
			this->EditColors->Size = System::Drawing::Size(106, 23);
			this->EditColors->TabIndex = 23;
			this->EditColors->Text = L"Настройка цвета";
			this->EditColors->UseVisualStyleBackColor = true;
			this->EditColors->Visible = false;
			this->EditColors->Click += gcnew System::EventHandler(this, &MyForm::EditColors_Click);
			// 
			// Color_button_5
			// 
			this->Color_button_5->BackColor = System::Drawing::Color::Gold;
			this->Color_button_5->ContextMenuStrip = this->Color_contextMenuStrip;
			this->Color_button_5->FlatAppearance->BorderSize = 0;
			this->Color_button_5->ForeColor = System::Drawing::Color::Black;
			this->Color_button_5->Location = System::Drawing::Point(329, 420);
			this->Color_button_5->Name = L"Color_button_5";
			this->Color_button_5->Size = System::Drawing::Size(22, 22);
			this->Color_button_5->TabIndex = 24;
			this->Color_button_5->UseVisualStyleBackColor = false;
			this->Color_button_5->Click += gcnew System::EventHandler(this, &MyForm::Color_button_Click);
			// 
			// Color_button_7
			// 
			this->Color_button_7->BackColor = System::Drawing::Color::Magenta;
			this->Color_button_7->ContextMenuStrip = this->Color_contextMenuStrip;
			this->Color_button_7->FlatAppearance->BorderSize = 0;
			this->Color_button_7->Location = System::Drawing::Point(385, 420);
			this->Color_button_7->Name = L"Color_button_7";
			this->Color_button_7->Size = System::Drawing::Size(22, 22);
			this->Color_button_7->TabIndex = 26;
			this->Color_button_7->UseVisualStyleBackColor = false;
			this->Color_button_7->Click += gcnew System::EventHandler(this, &MyForm::Color_button_Click);
			// 
			// Color_button_6
			// 
			this->Color_button_6->BackColor = System::Drawing::Color::DeepSkyBlue;
			this->Color_button_6->ContextMenuStrip = this->Color_contextMenuStrip;
			this->Color_button_6->FlatAppearance->BorderSize = 0;
			this->Color_button_6->ForeColor = System::Drawing::Color::Black;
			this->Color_button_6->Location = System::Drawing::Point(357, 420);
			this->Color_button_6->Name = L"Color_button_6";
			this->Color_button_6->Size = System::Drawing::Size(22, 22);
			this->Color_button_6->TabIndex = 25;
			this->Color_button_6->UseVisualStyleBackColor = false;
			this->Color_button_6->Click += gcnew System::EventHandler(this, &MyForm::Color_button_Click);
			// 
			// Color_button_9
			// 
			this->Color_button_9->BackColor = System::Drawing::Color::DimGray;
			this->Color_button_9->ContextMenuStrip = this->Color_contextMenuStrip;
			this->Color_button_9->FlatAppearance->BorderSize = 0;
			this->Color_button_9->Location = System::Drawing::Point(441, 419);
			this->Color_button_9->Name = L"Color_button_9";
			this->Color_button_9->Size = System::Drawing::Size(22, 22);
			this->Color_button_9->TabIndex = 28;
			this->Color_button_9->UseVisualStyleBackColor = false;
			this->Color_button_9->Click += gcnew System::EventHandler(this, &MyForm::Color_button_Click);
			// 
			// Color_button_8
			// 
			this->Color_button_8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->Color_button_8->ContextMenuStrip = this->Color_contextMenuStrip;
			this->Color_button_8->FlatAppearance->BorderSize = 0;
			this->Color_button_8->Location = System::Drawing::Point(413, 419);
			this->Color_button_8->Name = L"Color_button_8";
			this->Color_button_8->Size = System::Drawing::Size(22, 22);
			this->Color_button_8->TabIndex = 27;
			this->Color_button_8->UseVisualStyleBackColor = false;
			this->Color_button_8->Click += gcnew System::EventHandler(this, &MyForm::Color_button_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(496, 473);
			this->Controls->Add(this->Color_button_10);
			this->Controls->Add(this->Color_button_9);
			this->Controls->Add(this->Color_button_8);
			this->Controls->Add(this->Color_button_7);
			this->Controls->Add(this->Color_button_6);
			this->Controls->Add(this->Color_button_5);
			this->Controls->Add(this->EditColors);
			this->Controls->Add(this->Color_button_4);
			this->Controls->Add(this->Color_button_3);
			this->Controls->Add(this->Color_button_2);
			this->Controls->Add(this->label__Color__);
			this->Controls->Add(this->Color_button_1);
			this->Controls->Add(this->find_button);
			this->Controls->Add(this->find_label2);
			this->Controls->Add(this->find_textBox);
			this->Controls->Add(this->buttonRenameSave);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->filename_textBox);
			this->Controls->Add(this->save_button);
			this->Controls->Add(this->open_button);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MinimumSize = System::Drawing::Size(320, 188);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"My Notebook";
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->richTextBox_contextMenuStrip->ResumeLayout(false);
			this->Color_contextMenuStrip->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

   // VARIABLES
   // OTHER FUNCTIONS
	private: bool save();
	private: void updateRichBoxSize();
	private: void updateBottomButtons();
   // BUTTONS CLICKS
	private: System::Void open_button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void save_button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void buttonRenameSave_Click(System::Object^ sender, System::EventArgs^ e);
   // TEXT BOXES
   // RESIZE
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e);
   // MENU STRIP
	private: System::Void переименоватьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->переименоватьToolStripMenuItem->Checked)
		{
			this->filename_textBox->ReadOnly = false;
			this->filename_textBox->Size = System::Drawing::Size(MyForm::Size.Width - 113 - 100, 20);
			this->buttonRenameSave->Visible = true;
		}
		else
		{
			this->filename_textBox->ReadOnly = true;
			this->filename_textBox->Size = System::Drawing::Size(MyForm::Size.Width - 113 - 100, 20);
			this->buttonRenameSave->Visible = false;
		}
	}
	private: System::Void выйтиИзСистемыToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void найтиToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void оПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void настройкиОткрытияToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
   // RICH_TEXT_BOX
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void очиститьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void копироватьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void вырезатьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void вставитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	
	private: System::Void создатьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void find_button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void find_textBox_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void шрифтToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void richTextBox1_SelectionChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void активированныеРежимыToolStripMenuItem_MouseEnter(System::Object^ sender, System::EventArgs^ e);
	private: System::Void кнопкиОткрытьСохранитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void Color_button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ChangeColorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void EditColors_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void показыватьНастройкуЦветаToolStripMenuItem_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void filename_textBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
	private: System::Void find_textBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
	private: System::Void копироватьЦветToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void выделитьЖирнымToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void выделитьКурсивомToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void выделитьПодчеркиваниемToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void выделитьЗачеркиваниемToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void очиститьВыделениеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void ShowSavePopUpToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
};
}
