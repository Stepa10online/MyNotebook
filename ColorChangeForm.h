#include <Windows.h>
#include <vector>

//std::vector<System::Drawing::Color> Colors = {
//		   System::Drawing::Color::Red,
//		   System::Drawing::Color::Red,
//		   System::Drawing::Color::Red,
//		   System::Drawing::Color::Red,
//};
//
//std::vector<System::Drawing::Color> getColorButtons()
//{
//	return Colors;
//}


namespace MyNotebook {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	/// <summary>
	/// Сводка для ChangeColorForm
	/// </summary>
	public ref class ChangeColorForm : public System::Windows::Forms::Form
	{
	public:
		ChangeColorForm(void)
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
		~ChangeColorForm()
		{
			if (components)
			{
				delete components;
			}
		}

		System::Windows::Forms::ButtonBase^ color;




	private: System::Windows::Forms::ColorDialog^ colorDialog1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button;

	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::ComponentModel::IContainer^ components;







	protected:

	protected:

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
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Black;
			this->button2->Location = System::Drawing::Point(35, 19);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(23, 23);
			this->button2->TabIndex = 3;
			this->button2->UseVisualStyleBackColor = false;
			// 
			// button
			// 
			this->button->BackColor = System::Drawing::Color::Black;
			this->button->Location = System::Drawing::Point(6, 19);
			this->button->Name = L"button";
			this->button->Size = System::Drawing::Size(23, 23);
			this->button->TabIndex = 2;
			this->button->UseVisualStyleBackColor = false;
			this->button->Click += gcnew System::EventHandler(this, &ChangeColorForm::button_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::Black;
			this->button3->Location = System::Drawing::Point(93, 19);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(23, 23);
			this->button3->TabIndex = 5;
			this->button3->UseVisualStyleBackColor = false;
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::Black;
			this->button4->Location = System::Drawing::Point(64, 19);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(23, 23);
			this->button4->TabIndex = 4;
			this->button4->UseVisualStyleBackColor = false;
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::Black;
			this->button5->Location = System::Drawing::Point(151, 19);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(23, 23);
			this->button5->TabIndex = 7;
			this->button5->UseVisualStyleBackColor = false;
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::Black;
			this->button6->Location = System::Drawing::Point(122, 19);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(23, 23);
			this->button6->TabIndex = 6;
			this->button6->UseVisualStyleBackColor = false;
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::Color::Black;
			this->button7->Location = System::Drawing::Point(209, 19);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(23, 23);
			this->button7->TabIndex = 9;
			this->button7->UseVisualStyleBackColor = false;
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::Color::Black;
			this->button8->Location = System::Drawing::Point(180, 19);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(23, 23);
			this->button8->TabIndex = 8;
			this->button8->UseVisualStyleBackColor = false;
			// 
			// button9
			// 
			this->button9->BackColor = System::Drawing::Color::Black;
			this->button9->Location = System::Drawing::Point(238, 19);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(23, 23);
			this->button9->TabIndex = 10;
			this->button9->UseVisualStyleBackColor = false;
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(138, 8);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(23, 23);
			this->button10->TabIndex = 11;
			this->toolTip1->SetToolTip(this->button10, L"Отображаемый текст");
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &ChangeColorForm::button10_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(42, 10);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(26, 20);
			this->textBox1->TabIndex = 12;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &ChangeColorForm::textBox_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(7, 13);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(34, 13);
			this->label1->TabIndex = 13;
			this->label1->Text = L"Color:";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->button);
			this->groupBox1->Controls->Add(this->button2);
			this->groupBox1->Controls->Add(this->button4);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->button9);
			this->groupBox1->Controls->Add(this->button6);
			this->groupBox1->Controls->Add(this->button7);
			this->groupBox1->Controls->Add(this->button5);
			this->groupBox1->Controls->Add(this->button8);
			this->groupBox1->Location = System::Drawing::Point(10, 37);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(274, 57);
			this->groupBox1->TabIndex = 14;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Current Colors";
			this->toolTip1->SetToolTip(this->groupBox1, L"Заменить цвет на выбранный");
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(74, 10);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(26, 20);
			this->textBox2->TabIndex = 15;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &ChangeColorForm::textBox_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(106, 10);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(26, 20);
			this->textBox3->TabIndex = 16;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &ChangeColorForm::textBox_TextChanged);
			// 
			// ChangeColorForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(293, 98);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button10);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"ChangeColorForm";
			this->Text = L"ChangeColorForm";
			this->groupBox1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	public:
		void setBottonSColor(/*std::vector<System::Drawing::Color> newColors*/)
		{
			//Colors = newColors;
			//this->color_button1->ForeColor = Colors[0];
			//this->color_button2->ForeColor = Colors[1];
			//this->color_button3->ForeColor = Colors[2];
			//this->color_button4->ForeColor = Colors[3];
		}



	private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e) {
		//System::Windows::Forms::DialogResult dialog_res = this->colorDialog1->ShowDialog();
		/*if (dialog_res == System::Windows::Forms::DialogResult::OK);
			this->button10->ForeColor = System::Drawing::Color::FromArgb(color->R, color->G, color->B);
		if (dialog_res == System::Windows::Forms::DialogResult::Cancel)
			return;*/

		if (this->colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {

			Button^ button = dynamic_cast<Button^>(this->ActiveControl);

			if (button != nullptr)
			{
				button->BackColor = this->colorDialog1->Color;
				this->textBox1->Text = Convert::ToString(button->BackColor.R);
				this->textBox2->Text = Convert::ToString(button->BackColor.G);
				this->textBox3->Text = Convert::ToString(button->BackColor.B);
			}

		}
	}
	private: System::Void button_Click(System::Object^ sender, System::EventArgs^ e) {

		Button^ button = dynamic_cast<Button^>(sender);

		button->BackColor = color->BackColor;

	}
	private: System::Void textBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {

		if (this->textBox1->Text == "" || this->textBox2->Text == "" || this->textBox3->Text == "")
			return;

		this->button10->BackColor = System::Drawing::Color::FromArgb(
			Convert::ToInt32(this->textBox1->Text),
			Convert::ToInt32(this->textBox2->Text),
			Convert::ToInt32(this->textBox3->Text)
		);

	}
	};
}
