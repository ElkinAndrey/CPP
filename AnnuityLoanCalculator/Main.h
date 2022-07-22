
#pragma once
#include "Error.h"


namespace Calculator {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections::Generic;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Main : public System::Windows::Forms::Form
	{
	private:
		double sum; // Сумма кредита
		double percent; // Годовой процент
		double time; // Количество лет, на которое берется кредит
		System::DateTime date; // День, когда был взят кредит
		bool datePrint = false; // Указан ли день
		System::String^ period; // Как часто будет выплачиваться кредит



	private: System::Windows::Forms::Panel^ TablePanel;
	public:
		Main(void)
		{
			InitializeComponent();

			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D; // Изменение стиля окна

			// Заполнение ComboBox
			this->PeriodСomboBox->Items->Add("Ежегодно");
			this->PeriodСomboBox->Items->Add("Ежеквартально");
			this->PeriodСomboBox->Items->Add("Ежемесячно");
			this->PeriodСomboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PeriodСomboBox->Text = "Ежегодно";

			TotalPaymentTextBox->ReadOnly = true;// Нельзя писать в поле с итоговой суммой 
			OverPaymentTextBox->ReadOnly = true; // Нельзя писать в поле с переплатой
			CalculationResultsPanel->Visible = false; // Пока скрыть результаты расчета
			TablePanel->Visible = false; // Пока скрыть таблицу
		}

	protected:
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ HeaderPanel;
	private: System::Windows::Forms::Label^ HeaderText;
	private: System::Diagnostics::EventLog^ eventLog1;
	private: System::Windows::Forms::Panel^ OptionsPanel;
	private: System::Windows::Forms::Label^ OptionsText;
	private: System::Windows::Forms::TextBox^ SumTextBox;




	private: System::Windows::Forms::Label^ SumText;
	private: System::Windows::Forms::Label^ PercentText;
	private: System::Windows::Forms::TextBox^ PercentTextBox;
	private: System::Windows::Forms::TextBox^ TimeTextBox;





	private: System::Windows::Forms::Label^ TimeText;

	private: System::Windows::Forms::TextBox^ DateTextBox;
	private: System::Windows::Forms::Label^ DateText;
	private: System::Windows::Forms::ComboBox^ PeriodСomboBox;
	private: System::Windows::Forms::Label^ PeriodText;
	private: System::Windows::Forms::Button^ CalculateButton;
	private: System::Windows::Forms::Panel^ CalculationResultsPanel;
	private: System::Windows::Forms::TextBox^ TotalPaymentTextBox;
	private: System::Windows::Forms::Label^ TotalPaymentText;
	private: System::Windows::Forms::Label^ СalculationResultsText;
	private: System::Windows::Forms::TextBox^ OverPaymentTextBox;
	private: System::Windows::Forms::Label^ OverPaymentText;
	protected:

	protected:

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->HeaderPanel = (gcnew System::Windows::Forms::Panel());
			this->HeaderText = (gcnew System::Windows::Forms::Label());
			this->eventLog1 = (gcnew System::Diagnostics::EventLog());
			this->OptionsPanel = (gcnew System::Windows::Forms::Panel());
			this->CalculateButton = (gcnew System::Windows::Forms::Button());
			this->PeriodText = (gcnew System::Windows::Forms::Label());
			this->PeriodСomboBox = (gcnew System::Windows::Forms::ComboBox());
			this->DateTextBox = (gcnew System::Windows::Forms::TextBox());
			this->DateText = (gcnew System::Windows::Forms::Label());
			this->TimeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->TimeText = (gcnew System::Windows::Forms::Label());
			this->PercentText = (gcnew System::Windows::Forms::Label());
			this->PercentTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SumTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SumText = (gcnew System::Windows::Forms::Label());
			this->OptionsText = (gcnew System::Windows::Forms::Label());
			this->CalculationResultsPanel = (gcnew System::Windows::Forms::Panel());
			this->OverPaymentTextBox = (gcnew System::Windows::Forms::TextBox());
			this->OverPaymentText = (gcnew System::Windows::Forms::Label());
			this->TotalPaymentTextBox = (gcnew System::Windows::Forms::TextBox());
			this->TotalPaymentText = (gcnew System::Windows::Forms::Label());
			this->СalculationResultsText = (gcnew System::Windows::Forms::Label());
			this->TablePanel = (gcnew System::Windows::Forms::Panel());
			this->HeaderPanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->eventLog1))->BeginInit();
			this->OptionsPanel->SuspendLayout();
			this->CalculationResultsPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// HeaderPanel
			// 
			this->HeaderPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(87)), static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(158)));
			this->HeaderPanel->Controls->Add(this->HeaderText);
			this->HeaderPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->HeaderPanel->Location = System::Drawing::Point(0, 0);
			this->HeaderPanel->Margin = System::Windows::Forms::Padding(0);
			this->HeaderPanel->Name = L"HeaderPanel";
			this->HeaderPanel->Size = System::Drawing::Size(482, 72);
			this->HeaderPanel->TabIndex = 0;
			// 
			// HeaderText
			// 
			this->HeaderText->Dock = System::Windows::Forms::DockStyle::Fill;
			this->HeaderText->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->HeaderText->Location = System::Drawing::Point(0, 0);
			this->HeaderText->Name = L"HeaderText";
			this->HeaderText->Size = System::Drawing::Size(482, 72);
			this->HeaderText->TabIndex = 0;
			this->HeaderText->Text = L"Калькулятор выплат по кредиту";
			this->HeaderText->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// eventLog1
			// 
			this->eventLog1->SynchronizingObject = this;
			// 
			// OptionsPanel
			// 
			this->OptionsPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->OptionsPanel->AutoSize = true;
			this->OptionsPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->OptionsPanel->Controls->Add(this->CalculateButton);
			this->OptionsPanel->Controls->Add(this->PeriodText);
			this->OptionsPanel->Controls->Add(this->PeriodСomboBox);
			this->OptionsPanel->Controls->Add(this->DateTextBox);
			this->OptionsPanel->Controls->Add(this->DateText);
			this->OptionsPanel->Controls->Add(this->TimeTextBox);
			this->OptionsPanel->Controls->Add(this->TimeText);
			this->OptionsPanel->Controls->Add(this->PercentText);
			this->OptionsPanel->Controls->Add(this->PercentTextBox);
			this->OptionsPanel->Controls->Add(this->SumTextBox);
			this->OptionsPanel->Controls->Add(this->SumText);
			this->OptionsPanel->Controls->Add(this->OptionsText);
			this->OptionsPanel->Location = System::Drawing::Point(12, 84);
			this->OptionsPanel->Name = L"OptionsPanel";
			this->OptionsPanel->Size = System::Drawing::Size(458, 233);
			this->OptionsPanel->TabIndex = 1;
			// 
			// CalculateButton
			// 
			this->CalculateButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(87)), static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(158)));
			this->CalculateButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->CalculateButton->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->CalculateButton->ForeColor = System::Drawing::SystemColors::ControlText;
			this->CalculateButton->Location = System::Drawing::Point(7, 180);
			this->CalculateButton->Name = L"CalculateButton";
			this->CalculateButton->Size = System::Drawing::Size(175, 46);
			this->CalculateButton->TabIndex = 11;
			this->CalculateButton->Text = L"Рассчитать ";
			this->CalculateButton->UseVisualStyleBackColor = false;
			this->CalculateButton->Click += gcnew System::EventHandler(this, &Main::CalculateButton_Click);
			// 
			// PeriodText
			// 
			this->PeriodText->AutoSize = true;
			this->PeriodText->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PeriodText->Location = System::Drawing::Point(3, 134);
			this->PeriodText->Name = L"PeriodText";
			this->PeriodText->Size = System::Drawing::Size(216, 24);
			this->PeriodText->TabIndex = 10;
			this->PeriodText->Text = L"Периодичность погашения";
			// 
			// PeriodСomboBox
			// 
			this->PeriodСomboBox->BackColor = System::Drawing::Color::White;
			this->PeriodСomboBox->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PeriodСomboBox->FormattingEnabled = true;
			this->PeriodСomboBox->Location = System::Drawing::Point(225, 131);
			this->PeriodСomboBox->Name = L"PeriodСomboBox";
			this->PeriodСomboBox->Size = System::Drawing::Size(151, 32);
			this->PeriodСomboBox->TabIndex = 9;
			this->PeriodСomboBox->Text = L"Ежегодно";
			// 
			// DateTextBox
			// 
			this->DateTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(87)), static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(158)));
			this->DateTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->DateTextBox->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->DateTextBox->Location = System::Drawing::Point(345, 90);
			this->DateTextBox->Name = L"DateTextBox";
			this->DateTextBox->Size = System::Drawing::Size(100, 30);
			this->DateTextBox->TabIndex = 8;
			this->DateTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// DateText
			// 
			this->DateText->AutoSize = true;
			this->DateText->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->DateText->Location = System::Drawing::Point(237, 92);
			this->DateText->Name = L"DateText";
			this->DateText->Size = System::Drawing::Size(110, 24);
			this->DateText->TabIndex = 7;
			this->DateText->Text = L"Дата выдачи";
			// 
			// TimeTextBox
			// 
			this->TimeTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(87)), static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(158)));
			this->TimeTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->TimeTextBox->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->TimeTextBox->Location = System::Drawing::Point(174, 90);
			this->TimeTextBox->Name = L"TimeTextBox";
			this->TimeTextBox->Size = System::Drawing::Size(45, 30);
			this->TimeTextBox->TabIndex = 6;
			this->TimeTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// TimeText
			// 
			this->TimeText->AutoSize = true;
			this->TimeText->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->TimeText->Location = System::Drawing::Point(3, 92);
			this->TimeText->Name = L"TimeText";
			this->TimeText->Size = System::Drawing::Size(165, 24);
			this->TimeText->TabIndex = 5;
			this->TimeText->Text = L"Срок кредита (годы)";
			// 
			// PercentText
			// 
			this->PercentText->AutoSize = true;
			this->PercentText->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PercentText->Location = System::Drawing::Point(290, 51);
			this->PercentText->Name = L"PercentText";
			this->PercentText->Size = System::Drawing::Size(87, 24);
			this->PercentText->TabIndex = 4;
			this->PercentText->Text = L"Проценты";
			// 
			// PercentTextBox
			// 
			this->PercentTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(87)), static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(158)));
			this->PercentTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->PercentTextBox->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->PercentTextBox->Location = System::Drawing::Point(383, 49);
			this->PercentTextBox->Name = L"PercentTextBox";
			this->PercentTextBox->Size = System::Drawing::Size(62, 30);
			this->PercentTextBox->TabIndex = 3;
			this->PercentTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// SumTextBox
			// 
			this->SumTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(87)), static_cast<System::Int32>(static_cast<System::Byte>(196)),
				static_cast<System::Int32>(static_cast<System::Byte>(158)));
			this->SumTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->SumTextBox->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SumTextBox->Location = System::Drawing::Point(137, 49);
			this->SumTextBox->Name = L"SumTextBox";
			this->SumTextBox->Size = System::Drawing::Size(110, 30);
			this->SumTextBox->TabIndex = 2;
			this->SumTextBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->SumTextBox->TextChanged += gcnew System::EventHandler(this, &Main::SumTextBox_TextChanged);
			// 
			// SumText
			// 
			this->SumText->AutoSize = true;
			this->SumText->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->SumText->Location = System::Drawing::Point(3, 51);
			this->SumText->Name = L"SumText";
			this->SumText->Size = System::Drawing::Size(128, 24);
			this->SumText->TabIndex = 1;
			this->SumText->Text = L"Сумма кредита";
			// 
			// OptionsText
			// 
			this->OptionsText->AutoSize = true;
			this->OptionsText->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->OptionsText->Location = System::Drawing::Point(2, 2);
			this->OptionsText->Name = L"OptionsText";
			this->OptionsText->Size = System::Drawing::Size(201, 30);
			this->OptionsText->TabIndex = 0;
			this->OptionsText->Text = L"Параметры кредита";
			// 
			// CalculationResultsPanel
			// 
			this->CalculationResultsPanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->CalculationResultsPanel->AutoSize = true;
			this->CalculationResultsPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->CalculationResultsPanel->Controls->Add(this->OverPaymentTextBox);
			this->CalculationResultsPanel->Controls->Add(this->OverPaymentText);
			this->CalculationResultsPanel->Controls->Add(this->TotalPaymentTextBox);
			this->CalculationResultsPanel->Controls->Add(this->TotalPaymentText);
			this->CalculationResultsPanel->Controls->Add(this->СalculationResultsText);
			this->CalculationResultsPanel->Location = System::Drawing::Point(12, 336);
			this->CalculationResultsPanel->Name = L"CalculationResultsPanel";
			this->CalculationResultsPanel->Size = System::Drawing::Size(458, 136);
			this->CalculationResultsPanel->TabIndex = 2;
			// 
			// OverPaymentTextBox
			// 
			this->OverPaymentTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->OverPaymentTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->OverPaymentTextBox->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->OverPaymentTextBox->Location = System::Drawing::Point(103, 90);
			this->OverPaymentTextBox->Name = L"OverPaymentTextBox";
			this->OverPaymentTextBox->Size = System::Drawing::Size(110, 30);
			this->OverPaymentTextBox->TabIndex = 13;
			// 
			// OverPaymentText
			// 
			this->OverPaymentText->AutoSize = true;
			this->OverPaymentText->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->OverPaymentText->Location = System::Drawing::Point(3, 92);
			this->OverPaymentText->Name = L"OverPaymentText";
			this->OverPaymentText->Size = System::Drawing::Size(94, 24);
			this->OverPaymentText->TabIndex = 14;
			this->OverPaymentText->Text = L"Переплата";
			// 
			// TotalPaymentTextBox
			// 
			this->TotalPaymentTextBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(238)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)), static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->TotalPaymentTextBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->TotalPaymentTextBox->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->TotalPaymentTextBox->Location = System::Drawing::Point(143, 49);
			this->TotalPaymentTextBox->Name = L"TotalPaymentTextBox";
			this->TotalPaymentTextBox->Size = System::Drawing::Size(110, 30);
			this->TotalPaymentTextBox->TabIndex = 12;
			// 
			// TotalPaymentText
			// 
			this->TotalPaymentText->AutoSize = true;
			this->TotalPaymentText->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->TotalPaymentText->Location = System::Drawing::Point(3, 51);
			this->TotalPaymentText->Name = L"TotalPaymentText";
			this->TotalPaymentText->Size = System::Drawing::Size(134, 24);
			this->TotalPaymentText->TabIndex = 12;
			this->TotalPaymentText->Text = L"Общая выплата";
			// 
			// СalculationResultsText
			// 
			this->СalculationResultsText->AutoSize = true;
			this->СalculationResultsText->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->СalculationResultsText->Location = System::Drawing::Point(2, 2);
			this->СalculationResultsText->Name = L"СalculationResultsText";
			this->СalculationResultsText->Size = System::Drawing::Size(203, 30);
			this->СalculationResultsText->TabIndex = 12;
			this->СalculationResultsText->Text = L"Результаты расчета";
			// 
			// TablePanel
			// 
			this->TablePanel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->TablePanel->AutoScroll = true;
			this->TablePanel->BackColor = System::Drawing::Color::White;
			this->TablePanel->Location = System::Drawing::Point(12, 493);
			this->TablePanel->Name = L"TablePanel";
			this->TablePanel->Size = System::Drawing::Size(458, 291);
			this->TablePanel->TabIndex = 15;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(120, 120);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(482, 796);
			this->Controls->Add(this->TablePanel);
			this->Controls->Add(this->CalculationResultsPanel);
			this->Controls->Add(this->OptionsPanel);
			this->Controls->Add(this->HeaderPanel);
			this->Name = L"MyForm";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Click += gcnew System::EventHandler(this, &Main::CalculateButton_Click);
			this->HeaderPanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->eventLog1))->EndInit();
			this->OptionsPanel->ResumeLayout(false);
			this->OptionsPanel->PerformLayout();
			this->CalculationResultsPanel->ResumeLayout(false);
			this->CalculationResultsPanel->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		// Метод вызывается при нажатии кнопки Расчитать
	private: System::Void CalculateButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Выдать ошибку если сумма кредита указана неверно
		if (!double::TryParse(this->SumTextBox->Text->Replace('.', ','), sum)) {
			Error^ view = (gcnew Error("Неправильно указана сумма кредита!!!"));
			view->ShowDialog();
			return;
		}

		// Выдать ошибку если неправильно указана процентная ставка
		if (!double::TryParse(this->PercentTextBox->Text->Replace('.', ','), percent)) {
			Error^ view = (gcnew Error("Неправильно указана процентная ставка!!!"));
			view->ShowDialog();
			return;
		}

		// Выдать ошибку если процентная ставка меньше 0
		if (percent < 0) {
			Error^ view = (gcnew Error("Неправильно указана процентная ставка!!!"));
			view->ShowDialog();
			return;
		}

		// Выдать ошибку если неправильно указан срок кредита
		if (!double::TryParse(this->TimeTextBox->Text->Replace('.', ','), time)) {
			Error^ view = (gcnew Error("Неправильно указан срок кредита!!!"));
			view->ShowDialog();
			return;
		}

		// Попытаться получить время, если время указано неверно, то в таблице строки будут идти по возрастанию начиная с 1
		try {
			date = Convert::ToDateTime(this->DateTextBox->Text);
			datePrint = true;
		}
		catch (...) {
			datePrint = false;
		}

		// Получение времени по периоду
		period = this->PeriodСomboBox->Text;
		if (period == "Ежегодно") {
			percent /= 100;
		}
		else if (period == "Ежеквартально") {
			percent /= 400;
			time *= 4;
		}
		else if (period == "Ежемесячно") {
			percent /= 1200;
			time *= 12;
		}

		// Расчеты
		double pay = sum * (percent + (percent / (System::Math::Pow(1 + percent, time) - 1)));
		this->TotalPaymentTextBox->Text = Convert::ToString(Math::Round(pay * time * 100) / 100);
		this->OverPaymentTextBox->Text = Convert::ToString(Math::Round((pay * time - sum) * 100) / 100);

		/// <summary>
		/// Создание таблицы
		/// </summary>
		// Первый столбик
		this->TablePanel->Controls->Clear();
		System::Windows::Forms::Panel^ p1 = (gcnew System::Windows::Forms::Panel());
		this->TablePanel->Controls->Add(p1);
		p1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)));
		p1->Location = System::Drawing::Point(1, 1);
		p1->Name = L"panel";
		p1->Size = System::Drawing::Size(85, 35);
		System::Windows::Forms::Label^ l1 = (gcnew System::Windows::Forms::Label());
		p1->Controls->Add(l1);
		l1->Dock = System::Windows::Forms::DockStyle::Fill;
		l1->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		l1->Location = System::Drawing::Point(0, 0);
		l1->Name = L"label";
		l1->Size = System::Drawing::Size(85, 35);
		l1->TabIndex = 0;
		l1->Text = L"Дата выплаты";
		l1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

		// Второй столбик
		System::Windows::Forms::Panel^ p2 = (gcnew System::Windows::Forms::Panel());
		this->TablePanel->Controls->Add(p2);
		p2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)));
		p2->Location = System::Drawing::Point(87, 1);
		p2->Name = L"panel";
		p2->Size = System::Drawing::Size(85, 35);
		System::Windows::Forms::Label^ l2 = (gcnew System::Windows::Forms::Label());
		p2->Controls->Add(l2);
		l2->Dock = System::Windows::Forms::DockStyle::Fill;
		l2->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		l2->Location = System::Drawing::Point(0, 0);
		l2->Name = L"label";
		l2->Size = System::Drawing::Size(85, 35);
		l2->TabIndex = 0;
		l2->Text = L"Сумма выплаты";
		l2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

		// Третий столбик
		System::Windows::Forms::Panel^ p3 = (gcnew System::Windows::Forms::Panel());
		this->TablePanel->Controls->Add(p3);
		p3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)));
		p3->Location = System::Drawing::Point(173, 1);
		p3->Name = L"panel";
		p3->Size = System::Drawing::Size(85, 35);
		System::Windows::Forms::Label^ l3 = (gcnew System::Windows::Forms::Label());
		p3->Controls->Add(l3);
		l3->Dock = System::Windows::Forms::DockStyle::Fill;
		l3->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		l3->Location = System::Drawing::Point(0, 0);
		l3->Name = L"label";
		l3->Size = System::Drawing::Size(85, 35);
		l3->TabIndex = 0;
		l3->Text = L"Долговая часть";
		l3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

		// Четвертый столбик
		System::Windows::Forms::Panel^ p4 = (gcnew System::Windows::Forms::Panel());
		this->TablePanel->Controls->Add(p4);
		p4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)));
		p4->Location = System::Drawing::Point(259, 1);
		p4->Name = L"panel";
		p4->Size = System::Drawing::Size(85, 35);
		System::Windows::Forms::Label^ l4 = (gcnew System::Windows::Forms::Label());
		p4->Controls->Add(l4);
		l4->Dock = System::Windows::Forms::DockStyle::Fill;
		l4->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		l4->Location = System::Drawing::Point(0, 0);
		l4->Name = L"label";
		l4->Size = System::Drawing::Size(85, 35);
		l4->TabIndex = 0;
		l4->Text = L"Процентная часть";
		l4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

		// Заполнение данных
		double s1 = sum;
		for (int i = 1; i < time + 0.5; i++) {
			for (int j = 0; j < 4; j++) {
				System::Windows::Forms::Panel^ panel = (gcnew System::Windows::Forms::Panel());
				this->TablePanel->Controls->Add(panel);
				panel->Size = System::Drawing::Size(85, 35);
				panel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)));
				panel->Location = System::Drawing::Point(1 + j * 86, 1 + i * 36);

				System::Windows::Forms::Label^ label = (gcnew System::Windows::Forms::Label());
				panel->Controls->Add(label);

				label->Dock = System::Windows::Forms::DockStyle::Fill;
				label->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
				label->Location = System::Drawing::Point(0, 0);
				label->Name = L"label";
				label->Size = System::Drawing::Size(85, 35);
				label->TabIndex = 0;
				if (j == 0) {
					if (datePrint)
						label->Text = Convert::ToString(date.Day) + "." + Convert::ToString(date.Month) + "." + Convert::ToString(date.Year);
					else
						label->Text = Convert::ToString(i);
				}
				else if (j == 1) {
					label->Text = Convert::ToString(Math::Round(pay * 100) / 100);
				}
				else if (j == 2) {
					label->Text = Convert::ToString(Math::Round((pay - s1 * percent) * 100) / 100);
				}
				else if (j == 3) {
					label->Text = Convert::ToString(Math::Round((s1 * percent) * 100) / 100);
				}

				label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			}
			if (period == "Ежегодно") {
				date = date.AddYears(1);
			}
			else if (period == "Ежеквартально") {
				date = date.AddMonths(3);
			}
			else if (period == "Ежемесячно") {
				date = date.AddMonths(1);
			}
			s1 -= (pay - s1 * percent);
		}
		CalculationResultsPanel->Visible = true;
		TablePanel->Visible = true;
	}
	private: System::Void SumTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
