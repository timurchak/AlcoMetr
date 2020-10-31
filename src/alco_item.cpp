#include "alco_item.h"

AlcoItem::AlcoItem(AlcoLine line, const QString& type, QObject* par)
    : QObject(par)
    , name(new QLabel)
    , company(new QLineEdit)
    , volume(new QSpinBox)
    , volumeBottle(new QSpinBox)
    , per(new QLabel)
    , enable(new QCheckBox)
    , data(line)
    , typeAlco(type)
{
    volume->setSuffix(" мл");
    volumeBottle->setSuffix(" мл");
    volume->setMaximum(9999);
    volumeBottle->setMaximum(9999);
    volume->setSingleStep(100);
    volumeBottle->setSingleStep(100);
    volume->setMaximumWidth(100);
    volumeBottle->setMaximumWidth(100);
    per->setAutoFillBackground(true);
    enable->setText("Остлеживать");
    enable->setChecked(data.st);
    connect(volume, QOverload<int>::of(&QSpinBox::valueChanged), this, &AlcoItem::changeValue);
    connect(volumeBottle, QOverload<int>::of(&QSpinBox::valueChanged), this, &AlcoItem::changeValue);
    connect(company, &QLineEdit::textChanged, this, &AlcoItem::companyChange);
    connect(enable, &QCheckBox::clicked, this, &AlcoItem::clickEnable);
    name->setText(line.name);
    company->setText(line.company);
    volume->setValue(line.volume);
    volumeBottle->setValue(line.volumeBottle);
    enable->setChecked(data.st);
    volume->setEnabled(data.st);
    volumeBottle->setEnabled(data.st);
    changeValue(0);
}

void AlcoItem::changeValue(int)
{

    data.volume = volume->value();
    data.volumeBottle = volumeBottle->value();
    data.st = enable->isChecked();
    if(!data.st) {
        return;
    }
    if (volumeBottle->value() == 0) {
        return;
    }
    double perV = (static_cast<double>(data.volume) / static_cast<double>(data.volumeBottle)) * 100.0;
    if (perV <= 10.0 && perV > 0) {
        per->setAutoFillBackground(true);
        per->setStyleSheet("QLabel { background-color : yellow; color : black; }");

    } else if (perV == 0) {
        per->setStyleSheet("QLabel { background-color : red; color : black; }");
    } else {
        per->setStyleSheet("");
    }
    per->setText(QString::number(perV) + " %");
}

void AlcoItem::clickEnable(bool st)
{
    volume->setEnabled(st);
    volumeBottle->setEnabled(st);
    if(!st) {
        per->setText("100 %");
    }
}

QString AlcoItem::getTypeAlco() const
{
    return typeAlco;
}

void AlcoItem::setTypeAlco(const QString &value)
{
    typeAlco = value;
}

AlcoLine *AlcoItem::getData()
{
    return &data;
}

void AlcoItem::reloadData()
{
    QSignalBlocker blockerV(volume);
    QSignalBlocker blockerVB(volumeBottle);
    company->setText(data.company);
    volume->setValue(data.volume);
    volumeBottle->setValue(data.volumeBottle);
    name->setText(data.name);
    blockerV.unblock();
    blockerVB.unblock();
    changeValue(0);
}

QString AlcoItem::toString()
{
    return QString("%1|%2|%3|%4|%5|%6\n")
        .arg(typeAlco)
        .arg(data.name)
        .arg(data.company)
        .arg(data.volume)
    .arg(data.volumeBottle)
        .arg(enable->isChecked() ? "T" : "F");
}

QString AlcoItem::toShortString()
{
    return QString("%1|%2|%3\n")
        .arg(typeAlco)
        .arg(data.name)
        .arg(data.volume);
}

void AlcoItem::companyChange(QString)
{
    data.company = company->text();
}
