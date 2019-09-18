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
 
#pragma once
#include <QDebug>
#include <QWizard>
#include <QWizardPage>
#include <QString>
#include <QProcess>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCheckBox>
#include <QComboBox>
#include <QMessageBox>
#include <QPushButton>
#include <QProgressBar>

#include "password.h"

#define SHUTDOWN_CMD	"shutdown -p now"
#define REBOOT_CMD	"shutdown -r now"

class SetupWizard : public QWizard
{
	Q_OBJECT

public:
	SetupWizard(QWidget *parent = 0);
	void accept() override;
	void reject() override;

	static void errAndOut(QString message)
	{
		QMessageBox msgBox;
		msgBox.setWindowModality(Qt::WindowModal);
		msgBox.setText(tr("Fatal error"));
		msgBox.setWindowTitle(tr("Error"));
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.setWindowIcon(msgBox.iconPixmap());
		message.append(tr("\n\nPlease send a bug report to the "    \
				  "NomadBSD mailing list.\n\nWe are sorry " \
				  "for the inconvenience\n"));
		msgBox.setInformativeText(message);
		QPushButton *shutdown = msgBox.addButton(tr("Shutdown"),
		    QMessageBox::ActionRole);
		QPushButton *reboot   = msgBox.addButton(tr("Reboot"),
		    QMessageBox::ActionRole);
		msgBox.addButton(tr("Exit setup"), QMessageBox::ActionRole);
		msgBox.exec();
		if (msgBox.clickedButton() == shutdown) {
			system(SHUTDOWN_CMD);
		} else if (msgBox.clickedButton() == reboot) {
			system(REBOOT_CMD);
		} else {
			std::exit(1);
		}
	}

	static void cancelMenu()
	{
		QMessageBox msgBox;
		msgBox.setWindowModality(Qt::WindowModal);
		msgBox.setText(tr("Sure you want to cancel the setup?"));
		msgBox.setWindowTitle(tr("Cancel setup"));
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setWindowIcon(msgBox.iconPixmap());
		QPushButton *shutdown = msgBox.addButton(tr("Shutdown"),
		    QMessageBox::ActionRole);
		QPushButton *reboot = msgBox.addButton(tr("Reboot"),
		    QMessageBox::ActionRole);
		QPushButton *leave = msgBox.addButton(tr("Exit setup"),
		    QMessageBox::ActionRole);
		msgBox.setStandardButtons(QMessageBox::Cancel);
		msgBox.setButtonText(QMessageBox::Cancel, tr("Cancel"));
		msgBox.exec();
		if (msgBox.clickedButton() == shutdown) {
			system(SHUTDOWN_CMD);
		} else if (msgBox.clickedButton() == reboot) {
			system(REBOOT_CMD);
		} else if (msgBox.clickedButton() == leave) {
			std::exit(0);
		}
	}
};

//////////////////////////////////////////////////////////////////////////////
//
// Welcome page
//
//////////////////////////////////////////////////////////////////////////////
class WelcomePage : public QWizardPage
{
	Q_OBJECT

public:
	WelcomePage(QWidget *parent = 0);
protected:
	void initializePage(void);
private:
	QLabel *title;
	QLabel *intro;
};

//////////////////////////////////////////////////////////////////////////////
//
// Language/locale page
//
//////////////////////////////////////////////////////////////////////////////
class LocalePage : public QWizardPage
{
	Q_OBJECT

public:
	LocalePage(QWidget *parent = 0);
public slots:
	void localeSelected(int row);
private:
	QListWidget *localels;
};

//////////////////////////////////////////////////////////////////////////////
//
// Keyboard layout and variant  page
//
//////////////////////////////////////////////////////////////////////////////
class KbdLayoutPage : public QWizardPage
{
	Q_OBJECT

public:
	KbdLayoutPage(QWidget *parent = 0);
public slots:
	void kbdLayoutSelected(int row);
	void kbdVariantSelected(int row);
protected:
	void initializePage();
private:
	QLabel	    *title;
	QLabel	    *info;
	QLabel	    *llabel;
	QLabel	    *vlabel;
	QLabel	    *tlabel;
	QListWidget *layoutls;
	QListWidget *variantls;
	//
	// Struct to hold a keyboard variant record.
	//
	struct kbdvariant_s {
		QString layout;		// Layout code (e.g, ru, de, etc.)
		QString variant;	// Variant (e.g, nodeadkeys)
		QString descr;		// Description (e.g, "Swedish (Dvorak)")
	};
	QList<kbdvariant_s> kbdvariant;	// List of all keyboard variants.
};

//////////////////////////////////////////////////////////////////////////////
//
// Additional keyboard layouts page
//
//////////////////////////////////////////////////////////////////////////////
class ExtraKbdLayoutPage : public QWizardPage
{
	Q_OBJECT

public:
	ExtraKbdLayoutPage(QWidget *parent = 0);
public slots:
	void kbdLayoutSelected(int row);
	void kbdVariantSelected(int row);
	void addLayout(void);
	void removeLayout(void);
protected:
	void initializePage();
private:
	int	    lrow = -1;
	int	    vrow = -1;
	QLabel	    *title;
	QLabel	    *info;
	QLabel	    *llabel;
	QLabel	    *xllabel;
	QLabel	    *vlabel;
	QLabel	    *tlabel;
	QPushButton *addBt;
	QPushButton *removeBt;
	QListWidget *layoutls;
	QListWidget *xlayoutls;
	QListWidget *variantls;
	//
	// Struct to hold a keyboard variant record.
	//
	struct kbdvariant_s {
		QString layout;		// Layout code (e.g, ru, de, etc.)
		QString variant;	// Variant (e.g, nodeadkeys)
		QString descr;		// Description (e.g, "Swedish (Dvorak)")
	};
	QList<kbdvariant_s> kbdvariant;	// List of all keyboard variants.
};


//////////////////////////////////////////////////////////////////////////////
//
// Timezone page
//
//////////////////////////////////////////////////////////////////////////////
class TimezonePage : public QWizardPage
{
	Q_OBJECT

public:
	TimezonePage(QWidget *parent = 0);
public slots:
	void timezoneSelected(int row);
protected:
	void initializePage(void);
private:
	QLabel	    *title;
	QListWidget *timezonels;
};

//////////////////////////////////////////////////////////////////////////////
//
// Password page
//
//////////////////////////////////////////////////////////////////////////////
class PasswordPage : public QWizardPage
{
	Q_OBJECT
	
public:
	PasswordPage(QWidget *parent = 0);
	bool isComplete() const;
public slots:
	void passwordChanged();
protected:
	void initializePage();
private:
	QLabel	       *title;
	QLabel	       *intro;
	PasswordWidget *pass;
};

//////////////////////////////////////////////////////////////////////////////
//
// Geli page
//
//////////////////////////////////////////////////////////////////////////////
class GeliPage : public QWizardPage
{
	Q_OBJECT
public:
	GeliPage(QWidget *parent = 0);
	bool isComplete() const;
public slots:
	void setGeli(bool state);
	void passwordChanged(void);
protected:
	void initializePage();
private:
	QWidget	       *passContainer;
	QCheckBox      *gelicb;
	QLabel	       *title;
	QLabel	       *intro;
	QLabel	       *pwdLabel;
	PasswordWidget *pass;
};

//////////////////////////////////////////////////////////////////////////////
//
// Default application page
//
//////////////////////////////////////////////////////////////////////////////
class ProgramsPage : public QWizardPage
{
	Q_OBJECT

public:
	ProgramsPage(QWidget *parent = 0);
public slots:
	void selectionChanged(int);
private:
	QString getBoxVal(QComboBox *box);
protected:
	void initializePage(void);
private:
	static const int ncats = 4;
	QLabel	  *catLabel[ncats];
	QLabel	  *intro;
	QLabel	  *title;
	QComboBox *shells;
	QComboBox *editors;
	QComboBox *guiEditors;
	QComboBox *fileManagers;
};

//////////////////////////////////////////////////////////////////////////////
//
// Summary page
//
//////////////////////////////////////////////////////////////////////////////
class SummaryPage : public QWizardPage
{
	Q_OBJECT
public:
	SummaryPage(QWidget *parent = 0);
protected:
	void initializePage();
private:
	static const int nkeys = 9;
	QLabel *val[nkeys];
	QLabel *key[nkeys];
	QLabel *title;
	QLabel *text;
};

class CommitPage : public QWizardPage
{
	Q_OBJECT
public:
	CommitPage(QWidget *parent = 0);
	bool isComplete() const;
public slots:
	void readCmdOutput();
	void readError();
	void catchError(QProcess::ProcessError);
	void cleanup(int, QProcess::ExitStatus);
protected:
	void initializePage();
private:
	QLabel	     *commandMsg;
	QLabel	     *statusMsg;
	QString	     commandMsgBuf;
	QString	     errorMsgBuf;
	QProcess     proc;
	QProgressBar *progBar;
};
