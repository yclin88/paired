#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    
    // Connect button signals to slots
    connect(ui->submitButton, &QPushButton::clicked, this, &Dialog::onSubmitClicked);
    connect(ui->clearButton, &QPushButton::clicked, this, &Dialog::onClearClicked);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onSubmitClicked()
{
    // Get all the input values
    QString name = ui->nameEdit->text().trimmed();
    QString email = ui->emailEdit->text().trimmed();
    QString phone = ui->phoneEdit->text().trimmed();
    QString id = ui->idEdit->text().trimmed();
    QString birth = ui->birthEdit->text().trimmed();
    QString address = ui->addressEdit->toPlainText().trimmed();
    
    // Basic validation
    if (name.isEmpty()) {
        QMessageBox::warning(this, "警告", "請輸入姓名！");
        ui->nameEdit->setFocus();
        return;
    }
    
    if (email.isEmpty()) {
        QMessageBox::warning(this, "警告", "請輸入電子郵件！");
        ui->emailEdit->setFocus();
        return;
    }
    
    // Show success message with all the information
    QString message = QString("已成功提交您的資料：\n\n"
                             "姓名：%1\n"
                             "電子郵件：%2\n"
                             "電話號碼：%3\n"
                             "身份證字號：%4\n"
                             "出生日期：%5\n"
                             "地址：%6")
                        .arg(name)
                        .arg(email)
                        .arg(phone)
                        .arg(id)
                        .arg(birth)
                        .arg(address);
    
    QMessageBox::information(this, "提交成功", message);
}

void Dialog::onClearClicked()
{
    // Confirm before clearing
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, 
        "確認清除", 
        "確定要清除所有輸入的資料嗎？",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        // Clear all input fields
        ui->nameEdit->clear();
        ui->emailEdit->clear();
        ui->phoneEdit->clear();
        ui->idEdit->clear();
        ui->birthEdit->clear();
        ui->addressEdit->clear();
        
        // Set focus to the first field
        ui->nameEdit->setFocus();
        
        QMessageBox::information(this, "已清除", "所有資料已清除！");
    }
}
