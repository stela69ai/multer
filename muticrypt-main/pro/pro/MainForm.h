#pragma once

namespace EncryptionTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Security::Cryptography;
	using namespace System::Text;
	using namespace System::Runtime::InteropServices;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			encryptionAlgorithms = gcnew array<String^>{ "AES", "RC4", "ChaCha20", "Blowfish", "3DES" };
			InitializeEncryption();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		// Encryption data
		array<String^>^ encryptionAlgorithms;
		String^ key;
		String^ iv;

		// UI Controls
		System::Windows::Forms::Label^ label1;
		System::Windows::Forms::TextBox^ textBox1;
		System::Windows::Forms::Label^ label2;
		System::Windows::Forms::ComboBox^ comboBox1;
		System::Windows::Forms::ComboBox^ comboBox2;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::Button^ button1;
		System::Windows::Forms::Button^ button2;
		System::Windows::Forms::Label^ label4;
		System::Windows::Forms::Label^ label5;
		System::Windows::Forms::Label^ label6;
		System::Windows::Forms::TextBox^ textBox2;
		System::Windows::Forms::Button^ button3;
		System::Windows::Forms::Button^ button4;
		System::Windows::Forms::Button^ button5;
		System::Windows::Forms::Label^ label7;
		System::Windows::Forms::RichTextBox^ richTextBox1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(27, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(143, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Text to Encrypt/Decrypt:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(30, 57);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(730, 80);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"Enter your text here...";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(30, 160);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(86, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Select Algorithm:";
			// 
			// comboBox1
			// 
			this->comboBox1->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Location = System::Drawing::Point(30, 176);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 3;
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MainForm::comboBox1_SelectedIndexChanged);
			// 
			// comboBox2
			// 
			this->comboBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Location = System::Drawing::Point(170, 176);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 21);
			this->comboBox2->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(167, 160);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(52, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Key Size:";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::LightGreen;
			this->button1->Location = System::Drawing::Point(310, 176);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(100, 23);
			this->button1->TabIndex = 6;
			this->button1->Text = L"Encrypt String";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::LightBlue;
			this->button2->Location = System::Drawing::Point(420, 176);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(100, 23);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Decrypt String";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(30, 210);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(28, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Key:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(30, 230);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(22, 13);
			this->label5->TabIndex = 9;
			this->label5->Text = L"IV:";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(30, 260);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(96, 13);
			this->label6->TabIndex = 10;
			this->label6->Text = L"File Operations:";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(30, 285);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(590, 20);
			this->textBox2->TabIndex = 11;
			this->textBox2->Text = L"Select a file...";
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::LightGray;
			this->button3->Location = System::Drawing::Point(630, 283);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 12;
			this->button3->Text = L"Browse";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::LightGreen;
			this->button4->Location = System::Drawing::Point(30, 320);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(100, 23);
			this->button4->TabIndex = 13;
			this->button4->Text = L"Encrypt File";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::Color::LightBlue;
			this->button5->Location = System::Drawing::Point(140, 320);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(100, 23);
			this->button5->TabIndex = 14;
			this->button5->Text = L"Decrypt File";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &MainForm::button5_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(30, 360);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(51, 13);
			this->label7->TabIndex = 15;
			this->label7->Text = L"Results:";
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->richTextBox1->Location = System::Drawing::Point(30, 385);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(730, 200);
			this->richTextBox1->TabIndex = 16;
			this->richTextBox1->Text = L"";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 611);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Name = L"MainForm";
			this->Text = L"Advanced Encryption Tool";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		// Event handlers
		void button1_Click(System::Object^ sender, System::EventArgs^ e);
		void button2_Click(System::Object^ sender, System::EventArgs^ e);
		void button3_Click(System::Object^ sender, System::EventArgs^ e);
		void button4_Click(System::Object^ sender, System::EventArgs^ e);
		void button5_Click(System::Object^ sender, System::EventArgs^ e);
		void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);

		// Encryption methods
		void InitializeEncryption();
		String^ GenerateRandomKey(int size);
		String^ GenerateRandomIV(int size);
		void UpdateKeySizes();
		int GetKeySizeInBytes();
		String^ EncryptString(String^ plainText, String^ algorithm);
		String^ DecryptString(String^ cipherText, String^ algorithm);
		bool EncryptFile(String^ inputFile, String^ outputFile, String^ algorithm);
		bool DecryptFile(String^ inputFile, String^ outputFile, String^ algorithm);

		// Algorithm implementations
		array<Byte>^ AES_Encrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv);
		array<Byte>^ AES_Decrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv);
		array<Byte>^ RC4_Encrypt(array<Byte>^ data, array<Byte>^ key);
		array<Byte>^ RC4_Decrypt(array<Byte>^ data, array<Byte>^ key);
		array<Byte>^ ChaCha20_Encrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ nonce);
		array<Byte>^ ChaCha20_Decrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ nonce);
		array<Byte>^ TripleDES_Encrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv);
		array<Byte>^ TripleDES_Decrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv);
		array<Byte>^ Blowfish_Encrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv);
		array<Byte>^ Blowfish_Decrypt(array<Byte>^ data, array<Byte>^ key, array<Byte>^ iv);
		UInt32 RotateLeft(UInt32 value, int offset);
		void QuarterRound(array<UInt32>^ state, int a, int b, int c, int d);
	};
}