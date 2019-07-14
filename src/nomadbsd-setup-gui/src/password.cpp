//-
// Copyright (c) 2019 The NomadBSD Project. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include <QRegExp>
#include <QFormLayout>
#include <QRegExpValidator>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "password.h"

PasswordWidget::PasswordWidget(QWidget *parent) : QWidget(parent)
{
	status		  = new QLabel(tr("Passwords do not match"));
	pfield1		  = new QLineEdit;
	pfield2		  = new QLineEdit;
	pl1		  = new QLabel(tr("Password:"));
	pl2		  = new QLabel(tr("Repeat password:"));
	QVBoxLayout *vbox = new QVBoxLayout;
	QFormLayout *form = new QFormLayout;
	QRegExp	    chars = QRegExp("[ -~]+");

	pfield1->setEchoMode(QLineEdit::Password);
	pfield2->setEchoMode(QLineEdit::Password);

	pfield1->setValidator(new QRegExpValidator(chars));
	pfield2->setValidator(new QRegExpValidator(chars));

	pl1->setStyleSheet("font-weight: bold;");
	pl2->setStyleSheet("font-weight: bold;");
	status->setStyleSheet("font-style: italic;");

	form->addRow(pl1, pfield1);
	form->addRow(pl2, pfield2);

	vbox->addLayout(form);
	vbox->addWidget(status);
	setLayout(vbox);
	valid = false;

	pfield2->setEnabled(false);
	connect(pfield1, SIGNAL(textChanged(const QString &)), this,
	    SLOT(setActive(const QString &)));
	connect(pfield2, SIGNAL(textChanged(const QString &)), this,
	    SLOT(compareFields(const QString &)));
	connect(pfield1, SIGNAL(textChanged(const QString &)), this,
	    SLOT(compareFields(const QString &)));
	connect(pfield1, SIGNAL(inputRejected()), this,
	    SLOT(notifyInvalidChar()));
	connect(pfield2, SIGNAL(inputRejected()), this,
	    SLOT(notifyInvalidChar()));
}

void PasswordWidget::notifyInvalidChar()
{
	status->setText(tr("Only 7-bit ASCII characters are allowed"));
}

void PasswordWidget::setActive(const QString &input)
{
	if (input == "") {
		valid = false;
		pfield2->setEnabled(false);
	} else
		pfield2->setEnabled(true);
	compareFields(input);
}

void PasswordWidget::compareFields(const QString &input)
{
	if (input != "" && pfield2->text() == pfield1->text()) {
		valid = true;
		status->setText(tr("OK"));
	} else {
		valid = false;
		status->setText(tr("Passwords do not match"));
	}
	emit passwordChanged();
}

QString PasswordWidget::password()
{
	return (pfield1->text());
}

bool PasswordWidget::isValid()
{
	return (valid);
}

void PasswordWidget::setPl1Text(const QString &text)
{
	pl1->setText(text);
}

void PasswordWidget::setPl2Text(const QString &text)
{
	pl2->setText(text);
}

void PasswordWidget::setStatusText(const QString &text)
{
	status->setText(text);
}
