#include "account.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QIODevice>
#include <QByteArray>
#include <QJsonArray>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QRegularExpression>

Account::Account(QWidget *parent)
    : QWidget(parent)
{
    // 전체 레이아웃
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);


    // 제목 라벨
    QLabel *titleLabel = new QLabel("계정 생성", this);
    titleLabel->setStyleSheet("color:black; font-size: 20px; font-weight: bold;");
    titleLabel->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(titleLabel);

    // 아이디
    QLabel *labelId = new QLabel("아이디", this);
    editId = new QLineEdit(this);
    mainLayout->addWidget(labelId);
    mainLayout->addWidget(editId);

    // 비밀번호
    QLabel *labelPw = new QLabel("비밀번호", this);
    editPw = new QLineEdit(this);
    editPw->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(labelPw);
    mainLayout->addWidget(editPw);

    // 계정 생성 버튼
    createButton = new QPushButton("계정 생성", this);
    createButton->setStyleSheet("color:black;padding: 6px; background-color: #cce0ff; border-radius: 8px;");
    mainLayout->addWidget(createButton);

    QString inputFilePath = ("/Users/yeseongmoon/QtExample/veda_qt/db/user.json");
    // JSON 파일 로딩
    QFile file(inputFilePath);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        file.close();
        QJsonDocument doc1 = QJsonDocument::fromJson(data.toLocal8Bit());
        QJsonObject Obj2 = doc1.object();
        users1 = Obj2["users"].toArray();
    }
 //계정 버튼 누를떄
    connect(createButton, &QPushButton::clicked, this, [=]() {
        QString makeId = editId->text();
        QString makePw = editPw->text();
        bool loginSuccess = false;

        for (auto userVal : users1) {
            QJsonObject user = userVal.toObject();
            QString userId = user["id"].toString();
            QString userPw = user["password"].toString();

            //이미 계정이 있는 경우
            if (editId->text() == userId) {
                QMessageBox::warning(this, "중복된 아이디", "이미 계정이 있습니다.");
                return;
            }
            //비밀번호 생성오류
            QRegularExpression regex("^(?=.*[A-Za-z])(?=.*\\d)(?=.*[!@#$%^&*()_+=-]).{6,}$");
            if (!regex.match(makePw).hasMatch()) {
                QMessageBox::warning(this, "비밀번호 오류", "비밀번호는 6자 이상이며, 영어/숫자/특수문자를 포함해야 합니다.");
                return;
            }

        }
        //새로운 정보 추가
        QJsonObject newUser;
        newUser["id"] = editId->text();
        newUser["password"] = editPw->text();
        users1.append(newUser);

        //다시 JSON 문서로 저장
        QJsonObject n_jason;
        n_jason["users"] = users1;

        QJsonDocument newDoc(n_jason);
        QFile outFile("/Users/yeseongmoon/QtExample/veda_qt/db/user.json");
        if (outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            outFile.write(newDoc.toJson(QJsonDocument::Indented));
            outFile.close();
            QMessageBox::information(this, "성공", "계정이 추가되었습니다!");
            emit returnToLogin();
        }
    });


}


Account::~Account() {}


