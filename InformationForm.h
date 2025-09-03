#pragma once

namespace MyNotebook {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для Information
	/// </summary>
	public ref class Information : public System::Windows::Forms::Form
	{
	public:
		Information(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Information()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::LinkLabel^ Telegram_linkLabel;

	private: System::Windows::Forms::LinkLabel^ Youtube_linkLabel;
	private: System::Windows::Forms::Button^ button1;

	protected:

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->Telegram_linkLabel = (gcnew System::Windows::Forms::LinkLabel());
			this->Youtube_linkLabel = (gcnew System::Windows::Forms::LinkLabel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(218, 39);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Это тестовая программа.\r\nЗапрограммированная в целях обучения.\r\nАвтор:";
			// 
			// Telegram_linkLabel
			// 
			this->Telegram_linkLabel->AutoSize = true;
			this->Telegram_linkLabel->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->Telegram_linkLabel->Location = System::Drawing::Point(52, 39);
			this->Telegram_linkLabel->Name = L"Telegram_linkLabel";
			this->Telegram_linkLabel->Size = System::Drawing::Size(90, 13);
			this->Telegram_linkLabel->TabIndex = 1;
			this->Telegram_linkLabel->TabStop = true;
			this->Telegram_linkLabel->Text = L"Телеграм канал";
			this->Telegram_linkLabel->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Information::Telegram_linkLabel_LinkClicked);
			// 
			// Youtube_linkLabel
			// 
			this->Youtube_linkLabel->AutoSize = true;
			this->Youtube_linkLabel->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->Youtube_linkLabel->Location = System::Drawing::Point(55, 54);
			this->Youtube_linkLabel->Name = L"Youtube_linkLabel";
			this->Youtube_linkLabel->Size = System::Drawing::Size(51, 13);
			this->Youtube_linkLabel->TabIndex = 2;
			this->Youtube_linkLabel->TabStop = true;
			this->Youtube_linkLabel->Text = L"YouTube";
			this->Youtube_linkLabel->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Information::Youtube_linkLabel_LinkClicked);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(230, 54);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 3;
			this->button1->Text = L"ОК";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Information::button1_Click);
			// 
			// Information
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(317, 84);
			this->ControlBox = false;
			this->Controls->Add(this->button1);
			this->Controls->Add(this->Youtube_linkLabel);
			this->Controls->Add(this->Telegram_linkLabel);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"Information";
			this->Text = L"Information";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Telegram_linkLabel_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		System::Diagnostics::Process::Start("https://t.me/OnlineRecycleBin");
	}
	private: System::Void Youtube_linkLabel_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		System::Diagnostics::Process::Start("https://t.me/OnlineRecycleBin");
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}
	};
}
