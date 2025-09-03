#pragma once
#include "fstream"
#include "Application Data.h"
#include <iostream>
#include "rapidjson/document.h" 
#include "rapidjson/filereadstream.h" 
#include "rapidjson/filewritestream.h" 
#include "rapidjson/writer.h" 

#include <msclr/marshal.h>
#include <msclr/marshal_cppstd.h>

using namespace rapidjson;
namespace MyNotebook {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	

	/// <summary>
	/// Сводка для FolderForm
	/// </summary>
	public ref class FolderForm : public System::Windows::Forms::Form
	{
	public:
		FolderForm(void)
		{
			//this->textBox1->Text = path;
			InitializeComponent();
			this->FilterSelection->Text = this->FilterSelection->Items[filter_selected]->ToString();
			this->TextboxInitialFolder->Text = gcnew String(folder_save.c_str());
			this->checkBoxInitialFolder->Checked = standart_open_folder;

			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~FolderForm()
		{
			standart_open_folder = this->checkBoxInitialFolder->Checked;
			folder_save = msclr::interop::marshal_as<std::string>(this->TextboxInitialFolder->Text->ToString());
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::TextBox^ TextboxInitialFolder;

	private: System::Windows::Forms::Button^ button_change;


	private: System::Windows::Forms::Button^ OK_button;


	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ FilterSelection;
	private: System::Windows::Forms::CheckBox^ checkBoxInitialFolder;
	private: System::Windows::Forms::Panel^ panel1;




	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->TextboxInitialFolder = (gcnew System::Windows::Forms::TextBox());
			this->button_change = (gcnew System::Windows::Forms::Button());
			this->OK_button = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->FilterSelection = (gcnew System::Windows::Forms::ComboBox());
			this->checkBoxInitialFolder = (gcnew System::Windows::Forms::CheckBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// TextboxInitialFolder
			// 
			this->TextboxInitialFolder->Location = System::Drawing::Point(3, 5);
			this->TextboxInitialFolder->Name = L"textbox_folder_save";
			this->TextboxInitialFolder->Size = System::Drawing::Size(285, 20);
			this->TextboxInitialFolder->TabIndex = 1;
			// 
			// button_change
			// 
			this->button_change->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->button_change->Location = System::Drawing::Point(294, 3);
			this->button_change->Name = L"button_change";
			this->button_change->Size = System::Drawing::Size(75, 24);
			this->button_change->TabIndex = 2;
			this->button_change->Text = L"Изменить";
			this->button_change->UseVisualStyleBackColor = true;
			this->button_change->Click += gcnew System::EventHandler(this, &FolderForm::button_change_Click);
			// 
			// OK_button
			// 
			this->OK_button->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->OK_button->Location = System::Drawing::Point(292, 154);
			this->OK_button->Name = L"OK_button";
			this->OK_button->Size = System::Drawing::Size(75, 23);
			this->OK_button->TabIndex = 3;
			this->OK_button->Text = L"ОК";
			this->OK_button->UseVisualStyleBackColor = true;
			this->OK_button->Click += gcnew System::EventHandler(this, &FolderForm::button_OK_Click);
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->RootFolder = System::Environment::SpecialFolder::MyComputer;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 12);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(199, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Открываемый/сохраняемый формат:";
			// 
			// FilterSelection
			// 
			this->FilterSelection->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->FilterSelection->Items->AddRange(gcnew cli::array< System::Object^  >(4) {
				L"Text files(*.txt)|*.txt", L"Json files(*.json)|*.json",
					L"RTF files (*.rtf)|*.rtf", L"All files (*.*)|*.*"
			});
			this->FilterSelection->Location = System::Drawing::Point(217, 9);
			this->FilterSelection->Name = L"FilterSelection";
			this->FilterSelection->Size = System::Drawing::Size(121, 21);
			this->FilterSelection->TabIndex = 6;
			this->FilterSelection->SelectionChangeCommitted += gcnew System::EventHandler(this, &FolderForm::FilterSelection_SelectionChangeCommitted);
			// 
			// checkBoxStandartSaveFolder
			// 
			this->checkBoxInitialFolder->AutoSize = true;
			this->checkBoxInitialFolder->Location = System::Drawing::Point(6, 39);
			this->checkBoxInitialFolder->Name = L"checkBoxStandartSaveFolder";
			this->checkBoxInitialFolder->Size = System::Drawing::Size(213, 17);
			this->checkBoxInitialFolder->TabIndex = 7;
			this->checkBoxInitialFolder->Checked = standart_open_folder;
			this->checkBoxInitialFolder->Text = L"Начальная папка:";
			this->checkBoxInitialFolder->UseVisualStyleBackColor = true;
			this->checkBoxInitialFolder->CheckedChanged += gcnew System::EventHandler(this, &FolderForm::checkBoxStandartSaveFolder_CheckedChanged);
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->panel1->Controls->Add(this->TextboxInitialFolder);
			this->panel1->Controls->Add(this->button_change);
			this->panel1->Enabled = standart_open_folder;
			this->panel1->Location = System::Drawing::Point(3, 59);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(372, 29);
			this->panel1->TabIndex = 8;
			// 
			// FolderForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->OK_button;
			this->ClientSize = System::Drawing::Size(379, 189);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->checkBoxInitialFolder);
			this->Controls->Add(this->FilterSelection);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->OK_button);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"FolderForm";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->Text = L"Наcтройка сохранений";
			this->TopMost = true;
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_change_Click(System::Object^ sender, System::EventArgs^ e) {
		if (this->folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
			return;
		this->TextboxInitialFolder->Text = this->folderBrowserDialog1->SelectedPath;
		folder_save = msclr::interop::marshal_as<std::string>(this->TextboxInitialFolder->Text);
		std::cout << folder_save << std::endl;
	}
	private: System::Void button_OK_Click(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}
	private: System::Void FilterSelection_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e) {
		filter_selected = this->FilterSelection->SelectedIndex;
		}

private: System::Void checkBoxStandartSaveFolder_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	
	this->panel1->Enabled = this->checkBoxInitialFolder->Checked;
	standart_open_folder = this->checkBoxInitialFolder->Checked;
	if(this->checkBoxInitialFolder->Checked == false)
	{
		this->panel1->BackColor = System::Drawing::Color::FromArgb(224, 224, 224);
	}
	else
	{
		this->panel1->BackColor = System::Drawing::Color::FromArgb(240, 240, 240);
	}
}
};
}
