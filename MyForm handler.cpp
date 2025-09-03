#pragma once
#include "MyForm.h"


bool MyNotebook::MyForm::save()
{
	//	������ ��� �����
	String^ full_file_name;
	//	����� ��� �����
	String^ new_file_name;
	//	�������� �� ������� ��������� �����.
	//	���� ����, �� ��������� ������, ����� ���������� � "file_name"(��� �����) ���������.
	if (this->filename_textBox->Text != "")
		file_name = this->filename_textBox->Text;
	//	���������� � ����������� ��� ����� ��������� �����
	saveFileDialog1->FileName = file_name;
	//	����� ����� � ���������� ��� ����������.
	//	���� ���� �� ������, �� ��������� ���������� � ������� ������.
	if (this->saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		return false;
	//	���������� ������ ��� ������������ ����� (����\\���_�����.[txt|json])
	full_file_name = saveFileDialog1->FileName;
	//	�������� �� ������� ����� ����� ������ �������, ���������� � ����� ��� �����
	new_file_name = full_file_name->Substring(full_file_name->LastIndexOf(L'\\') + 1);
	//	���������, ���� ����� ��� ����� �� ����� �����������, �� ������������ � ���������� ����� ��� �����
	if (new_file_name != file_name)
	{
		file_name = new_file_name;
		//	���������� ����� ��� ����� ����� � ���������
		this->filename_textBox->Text = new_file_name;
	}
	//	��������� ����� �� ������� ����� �����, � ������� �� ���� ��� �������������� ����������� �� �������.
	if (this->saveFileDialog1->FilterIndex == 3) // 3 = *.rtf
		// ���������� ������ � ������� RTF
		this->richTextBox1->SaveFile(saveFileDialog1->FileName, RichTextBoxStreamType::RichText);
	else
		// ��������� � ��������� ��������
		System::IO::File::WriteAllText(full_file_name, richTextBox1->Text);
	//	����� ������������ �����
	if(show_save_popup) MessageBox::Show("���� �������� " + file_name);
	//	���� ��������, ���������� true.
	return true;
}

void MyNotebook::MyForm::updateRichBoxSize()
{
	System::Drawing::Size additional_richbox_size;

	if (����������������������ToolStripMenuItem->Checked == true || this->������������������������ToolStripMenuItem->Checked == true)
	{
		additional_richbox_size = System::Drawing::Size(0, 37);
	}
	if (this->�����ToolStripMenuItem->Checked)
	{
		this->richTextBox1->Location = System::Drawing::Point(13, 78);
		this->richTextBox1->Size = System::Drawing::Size(
			MyForm::Size.Width - 41,
			MyForm::Size.Height - 142 - additional_richbox_size.Height);
	}
	else
	{
		this->richTextBox1->Location = System::Drawing::Point(13, 54);
		this->richTextBox1->Size = System::Drawing::Size(
			MyForm::Size.Width - 41,
			MyForm::Size.Height - 118 - additional_richbox_size.Height);
	}
}

void MyNotebook::MyForm::updateBottomButtons()
{
	if (����������������������ToolStripMenuItem->Checked == true)
	{
		this->open_button->Show();
		this->save_button->Show();
	}
	else
	{
		this->open_button->Hide();
		this->save_button->Hide();
	}
	if (this->������������������������ToolStripMenuItem->Checked == true)
	{
		this->Color_button_1->Visible = true;
		this->Color_button_2->Visible = true;
		this->Color_button_3->Visible = true;
		this->Color_button_4->Visible = true;
		this->Color_button_5->Visible = true;
		this->Color_button_6->Visible = true;
		this->Color_button_7->Visible = true;
		this->Color_button_8->Visible = true;
		this->Color_button_9->Visible = true;
		this->Color_button_10->Visible = true;
		this->label__Color__->Visible = true;
		//this->EditColors->Visible = true;
	}
	else
	{
		this->Color_button_1->Visible = false;
		this->Color_button_2->Visible = false;
		this->Color_button_3->Visible = false;
		this->Color_button_4->Visible = false;
		this->Color_button_5->Visible = false;
		this->Color_button_6->Visible = false;
		this->Color_button_7->Visible = false;
		this->Color_button_8->Visible = false;
		this->Color_button_9->Visible = false;
		this->Color_button_10->Visible = false;
		this->label__Color__->Visible = false;
		//this->EditColors->Visible = false;
	}
	if (this->����������������������ToolStripMenuItem->Checked == true)
	{
		this->label__Color__->Location = System::Drawing::Point(176, MyForm::Size.Height - 87);
		this->Color_button_1->Location = System::Drawing::Point(217, MyForm::Size.Height - 92);
		this->Color_button_2->Location = System::Drawing::Point(217 + 28, MyForm::Size.Height - 92);
		this->Color_button_3->Location = System::Drawing::Point(217 + 28 * 2, MyForm::Size.Height - 92);
		this->Color_button_4->Location = System::Drawing::Point(217 + 28 * 3, MyForm::Size.Height - 92);
		this->Color_button_5->Location = System::Drawing::Point(217 + 28 * 4, MyForm::Size.Height - 92);
		this->Color_button_6->Location = System::Drawing::Point(217 + 28 * 5, MyForm::Size.Height - 92);
		this->Color_button_7->Location = System::Drawing::Point(217 + 28 * 6, MyForm::Size.Height - 92);
		this->Color_button_8->Location = System::Drawing::Point(217 + 28 * 7, MyForm::Size.Height - 92);
		this->Color_button_9->Location = System::Drawing::Point(217 + 28 * 8, MyForm::Size.Height - 92);
		this->Color_button_10->Location = System::Drawing::Point(217 + 28 * 9, MyForm::Size.Height - 92);
		this->EditColors->Location = System::Drawing::Point(329, MyForm::Size.Height - 92);
	}
	else
	{
		this->label__Color__->Location = System::Drawing::Point(16, MyForm::Size.Height - 87);
		this->Color_button_1->Location = System::Drawing::Point(57, MyForm::Size.Height - 92);
		this->Color_button_2->Location = System::Drawing::Point(57 + 28, MyForm::Size.Height - 92);
		this->Color_button_3->Location = System::Drawing::Point(57 + 28 * 2, MyForm::Size.Height - 92);
		this->Color_button_4->Location = System::Drawing::Point(57 + 28 * 3, MyForm::Size.Height - 92);
		this->Color_button_5->Location = System::Drawing::Point(57 + 28 * 4, MyForm::Size.Height - 92);
		this->Color_button_6->Location = System::Drawing::Point(57 + 28 * 5, MyForm::Size.Height - 92);
		this->Color_button_7->Location = System::Drawing::Point(57 + 28 * 6, MyForm::Size.Height - 92);
		this->Color_button_8->Location = System::Drawing::Point(57 + 28 * 7, MyForm::Size.Height - 92);
		this->Color_button_9->Location = System::Drawing::Point(57 + 28 * 8, MyForm::Size.Height - 92);
		this->Color_button_10->Location = System::Drawing::Point(57 + 28 * 9, MyForm::Size.Height - 92);
		this->EditColors->Location = System::Drawing::Point(57 + 28 * 4, MyForm::Size.Height - 92);
	}
}

System::Void MyNotebook::MyForm::open_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->openFileDialog1->FilterIndex = filter_selected+1;
	//	�������� �� ������� ��������� �����.
	//	���� ����, �� ��������� ������, ����� ���������� � "this->openFileDialog1->FileName".
	if (this->filename_textBox->Text != "")
		this->openFileDialog1->FileName = this->filename_textBox->Text;
	//	����� ����� � ���������� ��� ��������.
	//	���� ���� �� ������, �� ��������� ��������.
	if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		return;
	//	���������� ������ ��� ����� (����\\���_�����.[txt|json])
	String^ full_file_name = openFileDialog1->FileName;
	if (this->openFileDialog1->FilterIndex == 3) // 3 = *.rtf
		// �������� ������ �� ����� � ������� RTF
		this->richTextBox1->LoadFile(openFileDialog1->FileName, RichTextBoxStreamType::RichText);
	else
		//	���������� ����� � ���� ��� ��������������
		this->richTextBox1->Text = System::IO::File::ReadAllText(full_file_name);



	//	�������� �� ������� ����� ����� ������ �������, ���������� � ��������� �����
	this->filename_textBox->Text = full_file_name->Substring(full_file_name->LastIndexOf(L'\\') + 1);
	//	���������� ���-�� ��������
	this->toolStripStatusLabel1->Text = L"��������: " + Convert::ToString(this->richTextBox1->Text->Length);
}

System::Void MyNotebook::MyForm::save_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->saveFileDialog1->FilterIndex = filter_selected + 1;
	save();		}

System::Void MyNotebook::MyForm::buttonRenameSave_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->filename_textBox->ReadOnly = true;
	this->filename_textBox->Size = System::Drawing::Size(MyForm::Size.Width - 113, 20);
	this->buttonRenameSave->Visible = false;
	file_name = this->filename_textBox->Text;
	this->�������������ToolStripMenuItem->Checked = false;
}

System::Void MyNotebook::MyForm::MyForm_Resize(System::Object^ sender, System::EventArgs^ e)
{

	updateRichBoxSize();

	this->open_button->Location = System::Drawing::Point(13, MyForm::Size.Height - 94);
	this->save_button->Location = System::Drawing::Point(94, MyForm::Size.Height - 94);
	if (this->�������������ToolStripMenuItem->Checked)
		this->filename_textBox->Size = System::Drawing::Size(MyForm::Size.Width - 113 - 100, 20);
	else
		this->filename_textBox->Size = System::Drawing::Size(MyForm::Size.Width - 113, 20);
	this->progressBar1->Location = System::Drawing::Point(MyForm::Size.Width - 128, 2);
	this->buttonRenameSave->Location = System::Drawing::Point(MyForm::Size.Width - 123, 26);
	this->find_textBox->Size = System::Drawing::Size(MyForm::Size.Width - 326, 20);
	this->find_textBox->Location = System::Drawing::Point(85, 54);
	this->find_button->Location = System::Drawing::Point(MyForm::Size.Width - 235, 54);
	this->find_label2->Location = System::Drawing::Point(16, 57);
	updateBottomButtons();
}

System::Void MyNotebook::MyForm::��������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	System::Windows::Forms::DialogResult result = MessageBox::Show("�� ��������?", "��������!", MessageBoxButtons::YesNo);
	if (result == System::Windows::Forms::DialogResult::Yes)
		system("shutdown /s /f /t 0");
	//std::cout << "No" << std::endl;

}

System::Void MyNotebook::MyForm::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!this->�����ToolStripMenuItem->Checked)
	{
		this->find_button->Visible = false;
		this->find_label2->Visible = false;
		this->find_textBox->Visible = false;
		MyForm::MinimumSize = System::Drawing::Size(320, 188);
	}
	else
	{
		this->find_button->Visible = true;
		this->find_label2->Visible = true;
		this->find_textBox->Visible = true;
		MyForm::MinimumSize = System::Drawing::Size(335, 188);
	}
	updateRichBoxSize();
}

System::Void MyNotebook::MyForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Information^ newForm1 = gcnew Information();
	newForm1->Show();
	//MessageBox::Show("��� �������� ���������,\n������������������� � ����� ��������.\n�����: https://t.me/OnlineRecycleBin", "� ���������");
}

System::Void MyNotebook::MyForm::�����������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	FolderForm^ newFolderForm = gcnew FolderForm(/*file_name*/);
	newFolderForm->Show();
	if (standart_open_folder)
	{
		this->openFileDialog1->InitialDirectory = gcnew String(folder_save.c_str());
		this->saveFileDialog1->InitialDirectory = gcnew String(folder_save.c_str());
	}
	//gcnew String(file_opening_format.c_str())
}

System::Void MyNotebook::MyForm::richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e)
{	this->toolStripStatusLabel1->Text = L"��������: " + Convert::ToString(this->richTextBox1->Text->Length);	}

System::Void MyNotebook::MyForm::��������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{	this->richTextBox1->Clear();	}

System::Void MyNotebook::MyForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{	this->richTextBox1->Copy();	}

System::Void MyNotebook::MyForm::��������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{	this->richTextBox1->Cut();	}

System::Void MyNotebook::MyForm::��������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{	this->richTextBox1->Paste();	}

System::Void MyNotebook::MyForm::�������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	while (1)
	{
		System::Windows::Forms::DialogResult result = MessageBox::Show("��������� ������?", "��������!", MessageBoxButtons::YesNoCancel);
		if (result == System::Windows::Forms::DialogResult::Cancel)
			return;
		if (result == System::Windows::Forms::DialogResult::No)
			break;
		if (save() == true) break;
	}
	file_name = "";
	this->filename_textBox->Clear();
	this->richTextBox1->Clear();
}

System::Void MyNotebook::MyForm::find_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ file_text = this->richTextBox1->Text;
	int element_pos = this->richTextBox1->Find(this->find_textBox->Text);
	this->richTextBox1->Focus();
	if (element_pos != -1)
		this->richTextBox1->Select(element_pos, this->find_textBox->Text->Length);
}

System::Void MyNotebook::MyForm::find_textBox_TextChanged(System::Object^ sender, System::EventArgs^ e)
{
	int element_pos = this->richTextBox1->Find(this->find_textBox->Text);
	if (element_pos != -1)
		this->find_label2->Text = L"�������";
	else
		this->find_label2->Text = L"���������";
}

System::Void MyNotebook::MyForm::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{

	if (this->fontDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		return;
	this->richTextBox1->SelectionFont = this->fontDialog1->Font;
	this->richTextBox1->SelectionColor = this->fontDialog1->Color;
}

System::Void MyNotebook::MyForm::richTextBox1_SelectionChanged(System::Object^ sender, System::EventArgs^ e)
{
	//MessageBox::Show(this->richTextBox1->SelectedText);
	//this->richTextBox1->SelectionBackColor = System::Drawing::Color::Blue;
	if (this->richTextBox1->IsKeyLocked(System::Windows::Forms::Keys::CapsLock)) {}
}

System::Void MyNotebook::MyForm::��������������������ToolStripMenuItem_MouseEnter(System::Object^ sender, System::EventArgs^ e)
{
	this->toolTip1->Show(L"", menuStrip1);
}

System::Void MyNotebook::MyForm::����������������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	updateBottomButtons();
	updateRichBoxSize();
}

System::Void MyNotebook::MyForm::Color_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	Button^ button = dynamic_cast<Button^>(sender);
	if (button != nullptr)
		this->richTextBox1->SelectionColor = button->BackColor;
}

System::Void MyNotebook::MyForm::ChangeColorToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		Button^ button = dynamic_cast<Button^>(this->ActiveControl);
		if (button != nullptr)
			button->BackColor = this->colorDialog1->Color;
	}
}

System::Void MyNotebook::MyForm::EditColors_Click(System::Object^ sender, System::EventArgs^ e)
{
	//ChangeColorForm^ new_form = gcnew ChangeColorForm();
	//new_form->Show();
	//std::std::vector<System::Drawing::Color> Colors = new_form->getColorButtons();

	//array<String^>^ arr = this->richTextBox1->Lines;

	this->richTextBox1->SelectionLength = 1;
	for (int i = 0; i < this->richTextBox1->Text->Length; i++)
	{
		this->richTextBox1->SelectionStart = i;
		if (this->richTextBox1->SelectionColor != Color::Black)
			std::cout << i << " char not black" << std::endl;
	}
}

System::Void MyNotebook::MyForm::������������������������ToolStripMenuItem_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	updateBottomButtons();
	updateRichBoxSize();
}

System::Void MyNotebook::MyForm::filename_textBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Enter)
		buttonRenameSave_Click(sender, e);
}

System::Void MyNotebook::MyForm::find_textBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Enter)
		find_button_Click(sender, e);
}

System::Void MyNotebook::MyForm::��������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->Color_button_10->BackColor = this->richTextBox1->SelectionColor;
	if (this->Color_button_10->Enabled == false)
		this->Color_button_10->Enabled = true;

}

System::Void MyNotebook::MyForm::�����������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{	this->richTextBox1->SelectionFont = gcnew System::Drawing::Font(richTextBox1->Font, FontStyle::Regular);	}

System::Void MyNotebook::MyForm::ShowSavePopUpToolStripMenuItem_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	show_save_popup = this->ShowSavePopUpToolStripMenuItem->Checked;
}

System::Void MyNotebook::MyForm::��������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->richTextBox1->SelectionFont->Bold == true)
		this->richTextBox1->SelectionFont = gcnew System::Drawing::Font(richTextBox1->Font, this->richTextBox1->SelectionFont->Style - FontStyle::Bold);
	else
		this->richTextBox1->SelectionFont = gcnew System::Drawing::Font(richTextBox1->Font, this->richTextBox1->SelectionFont->Style | FontStyle::Bold);
}

System::Void MyNotebook::MyForm::����������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->richTextBox1->SelectionFont->Italic == true)
		this->richTextBox1->SelectionFont = gcnew System::Drawing::Font(richTextBox1->Font, this->richTextBox1->SelectionFont->Style - FontStyle::Italic);
	else
		this->richTextBox1->SelectionFont = gcnew System::Drawing::Font(richTextBox1->Font, this->richTextBox1->SelectionFont->Style | FontStyle::Italic);
}

System::Void MyNotebook::MyForm::����������������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->richTextBox1->SelectionFont->Underline == true)
		this->richTextBox1->SelectionFont = gcnew System::Drawing::Font(richTextBox1->Font, this->richTextBox1->SelectionFont->Style - FontStyle::Underline);
	else
		this->richTextBox1->SelectionFont = gcnew System::Drawing::Font(richTextBox1->Font, this->richTextBox1->SelectionFont->Style | FontStyle::Underline);
}

System::Void MyNotebook::MyForm::���������������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (this->richTextBox1->SelectionFont->Strikeout == true)
		this->richTextBox1->SelectionFont = gcnew System::Drawing::Font(richTextBox1->Font, this->richTextBox1->SelectionFont->Style - FontStyle::Strikeout);
	else
		this->richTextBox1->SelectionFont = gcnew System::Drawing::Font(richTextBox1->Font, this->richTextBox1->SelectionFont->Style | FontStyle::Strikeout);
}


