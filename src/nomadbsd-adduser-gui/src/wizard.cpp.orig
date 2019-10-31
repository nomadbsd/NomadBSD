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

#include <QVariant>
#include <QStyle>
#include <QProcess>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTranslator>
#include <QCoreApplication>
#include <QScrollArea>
#include "wizard.h"
#include "backend.h"

//////////////////////////////////////////////////////////////////////////////
//
// Global variables to hold the configuration
//
//////////////////////////////////////////////////////////////////////////////
static bool    cfg_use_geli = false;
static QString cfg_geli;
static QString cfg_locale;
static QString cfg_region;
static QString cfg_kbdlayout;
static QString cfg_kbdvariant;
static QString cfg_kbdmodel;
static QString cfg_timezone;
static QString cfg_shell;
static QString cfg_password;
static QString cfg_geli_password;
static QString cfg_browser;
static QString cfg_editor;
static QString cfg_gui_editor;
static QString cfg_email_client;
static QString cfg_file_manager;
//////////////////////////////////////////////////////////////////////////////

static QTranslator translator;

SetupWizard::SetupWizard(QWidget *parent) : QWizard(parent)
{
	resize(640, 480);
	setWindowTitle(tr("NomadBSD Setup"));
	setWindowIcon(QPixmap(":/images/logo.png"));
	addPage(new LocalePage);
	addPage(new WelcomePage);
	addPage(new KbdLayoutPage);
	addPage(new TimezonePage);
	addPage(new PasswordPage);
	addPage(new GeliPage);
	addPage(new ProgramsPage);
	addPage(new SummaryPage);
	addPage(new CommitPage);
}

void SetupWizard::accept()
{
	system(REBOOT_CMD);
	QDialog::accept();
}

void SetupWizard::reject()
{
	cancelMenu();
}

//////////////////////////////////////////////////////////////////////////////
//
// Welcome page
//
//////////////////////////////////////////////////////////////////////////////
WelcomePage::WelcomePage(QWidget *parent) : QWizardPage(parent)
{
	intro		    = new QLabel;
	title		    = new QLabel;
	QVBoxLayout *layout = new QVBoxLayout;

	intro->setWordWrap(true);
	title->setStyleSheet("font-weight: bold;");
	setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/logo.png"));
	setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));
	layout->addWidget(title);
	layout->addWidget(intro);
	setLayout(layout);
}

void WelcomePage::initializePage()
{
	title->setText(tr("Welcome to the NomadBSD setup wizard.\n\n"));
	intro->setText(tr("Before you can use NomadBSD, there are some " \
			  "things that need to be set up.\n\n"	    	 \
			  "The setup will only write to the USB "   	 \
			  "flash drive it is currently running "	 \
			  "from. It will not change your system."));
}

//////////////////////////////////////////////////////////////////////////////
//
// Language/locale Page
//
//////////////////////////////////////////////////////////////////////////////
LocalePage::LocalePage(QWidget *parent) : QWizardPage(parent)
{
	localels	   = new QListWidget(this);
	QVBoxLayout *vbox  = new QVBoxLayout;
	QLabel	    *label = new QLabel;
	QProcess    proc;
        QByteArray  line;
       
  	proc.setReadChannel(QProcess::StandardOutput);
	proc.start(BACKEND_GET_LOCALES);
	(void)proc.waitForStarted(-1);

	//
	// According to the Qt docs, we can not rely on the return value.
	// We have to check state().
	//
	if (proc.state() == QProcess::NotRunning) {
		SetupWizard::errAndOut(tr("Couldn't start backend '%1': %2")
		    .arg(BACKEND_GET_LOCALES).arg(proc.errorString()));
	}
	while (proc.waitForReadyRead(-1)) {
		while (!(line = proc.readLine()).isEmpty()) {
			// Remove trailing newline
			line.truncate(line.size() - 1);
			QList<QByteArray>fields = line.split('|');
			if (fields.count() < 2)
				continue;
			QString label = fields.at(1);
			QString code  = fields.at(0);
			QListWidgetItem *item = new QListWidgetItem(label);
			item->setData(Qt::UserRole, QVariant(code));
			localels->addItem(item);
		}
        }
	proc.waitForFinished(-1);
	if (proc.exitCode() != 0) {
		SetupWizard::errAndOut(
		    QString("Command '%1' returned with an error.")
			.arg(BACKEND_GET_LOCALES));
	}
	label->setStyleSheet("font-weight: bold;");
	label->setText(tr("Please select your language/locale"));

	vbox->addWidget(label);
	vbox->addWidget(localels);
	setLayout(vbox);
	if (localels->count() > 0)
		localels->setCurrentRow(0);
	connect(localels, SIGNAL(currentRowChanged(int)), this,
	    SLOT(localeSelected(int)));
}

void LocalePage::localeSelected(int row)
{
	cfg_locale = localels->item(row)->data(Qt::UserRole).toString();
	cfg_region = cfg_locale.split('_').at(1);

	qApp->removeTranslator(&translator);
	if (translator.load(QLocale(cfg_locale), QLatin1String(PROGRAM),
	    QLatin1String("_"), QLatin1String(":/locale")))
		qApp->installTranslator(&translator);
	wizard()->setButtonText(QWizard::NextButton,   tr("Next"));
	wizard()->setButtonText(QWizard::BackButton,   tr("Back"));
	wizard()->setButtonText(QWizard::CommitButton, tr("Commit"));
	wizard()->setButtonText(QWizard::FinishButton, tr("Finish"));
	wizard()->setButtonText(QWizard::CancelButton, tr("Cancel"));
}

//////////////////////////////////////////////////////////////////////////////
//
// Keyboard layout and variant page
//
//////////////////////////////////////////////////////////////////////////////
KbdLayoutPage::KbdLayoutPage(QWidget *parent) : QWizardPage(parent)
{
	llabel		    = new QLabel;
	vlabel		    = new QLabel;
	tlabel		    = new QLabel;
	layoutls	    = new QListWidget(this);
	variantls	    = new QListWidget(this);
	QLineEdit   *test   = new QLineEdit;
	QVBoxLayout *lvbox  = new QVBoxLayout;
	QVBoxLayout *vvbox  = new QVBoxLayout;
	QVBoxLayout *layout = new QVBoxLayout;
	QHBoxLayout *hbox   = new QHBoxLayout;
	QProcess    proc;
        QByteArray  line;

	proc.setReadChannel(QProcess::StandardOutput);
	proc.start(BACKEND_GET_KBDLAYOUTS);
	(void)proc.waitForStarted(-1);

	//
	// According to the Qt docs, we can not rely on the return value.
	// We have to check state().
	//
	if (proc.state() == QProcess::NotRunning) {
		SetupWizard::errAndOut(tr("Couldn't start backend '%1': %2")
		    .arg(BACKEND_GET_KBDLAYOUTS).arg(proc.errorString()));
	}
	while (proc.waitForReadyRead(-1)) {
		while (!(line = proc.readLine()).isEmpty()) {
			// Remove trailing newline
			line.truncate(line.size() - 1);
			QList<QByteArray>fields = line.split('|');
			if (fields.count() < 2)
				continue;
			QString label = fields.at(1);
			QString code  = fields.at(0);
			QListWidgetItem *item = new QListWidgetItem(label);
			item->setData(Qt::UserRole, QVariant(code));
			layoutls->addItem(item);
		}
        }
	proc.waitForFinished(-1);
	if (proc.exitCode() != 0) {
		SetupWizard::errAndOut(
		    QString("Command '%1' returned with an error.")
			.arg(BACKEND_GET_KBDLAYOUTS));
	}
	//
	// Read keyboard variants.
	//
	proc.start(BACKEND_GET_KBDVARIANTS);

	(void)proc.waitForStarted(-1);

	if (proc.state() == QProcess::NotRunning) {
		SetupWizard::errAndOut(tr("Couldn't start backend '%1': %2")
		    .arg(BACKEND_GET_KBDVARIANTS).arg(proc.errorString()));
	}
	while (proc.waitForReadyRead(-1)) {
		while (!(line = proc.readLine()).isEmpty()) {
			// Remove trailing newline
			line.truncate(line.size() - 1);
			QList<QByteArray>fields = line.split('|');
			if (fields.count() < 3)
				continue;
			kbdvariant_s kv;
			kv.descr   = fields.at(1);
			kv.layout  = fields.at(2);
			kv.variant = fields.at(0);
			kbdvariant.append(kv);
		}
        }
	proc.waitForFinished(-1);
	if (proc.exitCode() != 0) {
		SetupWizard::errAndOut(
		    QString("Command '%1' returned with an error.")
			.arg(BACKEND_GET_KBDVARIANTS));
	}
	llabel->setStyleSheet("font-weight: bold;");
	vlabel->setStyleSheet("font-weight: bold;");
	tlabel->setStyleSheet("font-weight: bold;");

	lvbox->addWidget(llabel);
	lvbox->addWidget(layoutls);
	vvbox->addWidget(vlabel);
	vvbox->addWidget(variantls);
	hbox->addLayout(lvbox);
	hbox->addLayout(vvbox);

	layout->setSpacing(15);
	layout->addLayout(hbox);
	layout->addWidget(tlabel);
	layout->addWidget(test);
	setLayout(layout);

	if (layoutls->count() > 0)
		layoutls->setCurrentRow(0);
	connect(layoutls, SIGNAL(currentRowChanged(int)), this,
	    SLOT(kbdLayoutSelected(int)));
}

//
// Show keyboard variants matching the keyboard layout code.
//
void KbdLayoutPage::kbdLayoutSelected(int row)
{
	cfg_kbdlayout = layoutls->item(row)->data(Qt::UserRole).toString();

	// Unset a previously set keyboard variant.
	cfg_kbdvariant = "";

	//
	// Disconnect the slot to prevent it from being called when
	// removing items.
	//
	variantls->disconnect();
	
	for (int i = variantls->count(); i > 0; i--) {
		QListWidgetItem *item = variantls->takeItem(0);
		delete(item);
	}
	for (int i = 0; i < kbdvariant.count(); i++) {
		if (kbdvariant.at(i).layout != cfg_kbdlayout)
			continue;
		QListWidgetItem *item =
		    new QListWidgetItem(kbdvariant.at(i).descr);
		item->setData(Qt::UserRole,
		    QVariant(kbdvariant.at(i).variant));
		variantls->addItem(item);
	}
	if (variantls->count() > 0) {
		variantls->setCurrentRow(0);
		variantls->item(0)->setSelected(false);
	}
	connect(variantls, SIGNAL(currentRowChanged(int)), this,
	    SLOT(kbdVariantSelected(int)));
	system(QString("setxkbmap -layout %1")
	    .arg(cfg_kbdlayout).toStdString().c_str());
}

void KbdLayoutPage::kbdVariantSelected(int row)
{
	cfg_kbdvariant = variantls->item(row)->data(Qt::UserRole).toString();
	system(QString("setxkbmap -layout %1 -variant %2")
	    .arg(cfg_kbdlayout).arg(cfg_kbdvariant).toStdString().c_str());
}

void KbdLayoutPage::initializePage()
{
	//
	// Select the first layout matching the region code.
	//
	QString reg = cfg_region.toLower();
	for (int n = 0; n < layoutls->count(); n++) {
		QString l = layoutls->item(n)->data(Qt::UserRole).toString();
		if (reg == l) {
			layoutls->setCurrentRow(n);
			break;
		}
	}
	llabel->setText(tr("Keyboard layout"));
	vlabel->setText(tr("Keyboard variant"));
	tlabel->setText(tr("Test your keyboard settings"));
}

//////////////////////////////////////////////////////////////////////////////
//
// Timezone page
//
//////////////////////////////////////////////////////////////////////////////
TimezonePage::TimezonePage(QWidget *parent) : QWizardPage(parent)
{
	title		  = new QLabel;
	timezonels	  = new QListWidget(this);
	QVBoxLayout *vbox = new QVBoxLayout;
	QProcess    proc;
        QByteArray  line;

	proc.setReadChannel(QProcess::StandardOutput);
	proc.start(BACKEND_GET_TIMEZONES);
	(void)proc.waitForStarted(-1);

	//
	// According to the Qt docs, we can not rely on the return value.
	// We have to check state().
	//
	if (proc.state() == QProcess::NotRunning) {
		QString error;
		SetupWizard::errAndOut(tr("Couldn't start backend '%1': %2")
		    .arg(BACKEND_GET_TIMEZONES).arg(proc.errorString()));
	}
	while (proc.waitForReadyRead(-1)) {
		while (!(line = proc.readLine()).isEmpty()) {
			// Remove trailing newline.
			line.truncate(line.size() - 1);
			QList<QByteArray>fields = line.split('|');
			if (fields.count() < 2)
				continue;
			QString label = fields.at(0);
			QString code  = fields.at(1);
			QListWidgetItem *item = new QListWidgetItem(label);
			item->setData(Qt::UserRole, QVariant(code));
			timezonels->addItem(item);
		}
        }
	proc.waitForFinished(-1);
	if (proc.exitCode() != 0) {
		SetupWizard::errAndOut(
		    QString("Command '%1' returned with an error.")
			.arg(BACKEND_GET_TIMEZONES));
	}
	title->setStyleSheet("font-weight: bold;");
	vbox->addWidget(title);
	vbox->addWidget(timezonels);
	setLayout(vbox);
	if (timezonels->count() > 0)
		timezonels->setCurrentRow(0);
	connect(timezonels, SIGNAL(currentRowChanged(int)), this,
	    SLOT(timezoneSelected(int)));
}

void TimezonePage::initializePage()
{
	//
	// Select the first timezone matching the chosen region
	//
	for (int n = 0; n < timezonels->count(); n++) {
		QString region = timezonels->item(n)->data(Qt::UserRole)
		    .toString();
		if (region == cfg_region) {
			timezonels->setCurrentRow(n);
			break;
		}
	}
	title->setText(tr("Please select your timezone"));
}

void TimezonePage::timezoneSelected(int row)
{
	cfg_timezone = timezonels->item(row)->text();
}

//////////////////////////////////////////////////////////////////////////////
//
// Password page
//
//////////////////////////////////////////////////////////////////////////////
PasswordPage::PasswordPage(QWidget *parent) : QWizardPage(parent)
{
	pass		    = new PasswordWidget;
	title		    = new QLabel;
	intro		    = new QLabel;
	QVBoxLayout *layout = new QVBoxLayout;

	title->setStyleSheet("font-weight: bold;");
	intro->setWordWrap(true);
	layout->addWidget(title);
	layout->addWidget(intro);
	layout->addWidget(pass);
	setLayout(layout);
	connect(pass, SIGNAL(passwordChanged()), this,
	    SLOT(passwordChanged()));
}

void PasswordPage::initializePage()
{
	title->setText(tr("Set password for user and root\n"));
	intro->setText(tr("The password you choose here will be used "	\
			  "for your user account (nomad), and for the "	\
			  "administration account (root)\n\n"));
}

void PasswordPage::passwordChanged()
{
	if (pass->isValid())
		cfg_password = pass->password();
	emit completeChanged();
}

bool PasswordPage::isComplete() const
{
	if (!pass->isValid())
		return (false);
	return (true);
}

//////////////////////////////////////////////////////////////////////////////
//
// Geli page
//
//////////////////////////////////////////////////////////////////////////////
GeliPage::GeliPage(QWidget *parent) : QWizardPage(parent)
{
	pass			  = new PasswordWidget;
	gelicb			  = new QCheckBox;
	passContainer		  = new QWidget;
	intro			  = new QLabel;
	title			  = new QLabel;
	pwdLabel		  = new QLabel;
	QVBoxLayout *layout	  = new QVBoxLayout;
	QVBoxLayout *containerBox = new QVBoxLayout(passContainer);

	title->setStyleSheet("font-weight: bold;");
	intro->setWordWrap(true);
	containerBox->addWidget(pwdLabel);
	containerBox->addWidget(pass);

	passContainer->setEnabled(cfg_use_geli);
	gelicb->setTristate(false);
	
	layout->addWidget(title);
	layout->addWidget(intro);
	layout->addWidget(gelicb);
	layout->addWidget(passContainer);
	setLayout(layout);

	connect(pass, SIGNAL(passwordChanged()), this,
	    SLOT(passwordChanged()));
	connect(gelicb, SIGNAL(toggled(bool)), this, SLOT(setGeli(bool)));
}	

void GeliPage::initializePage()
{
	gelicb->setChecked(cfg_use_geli);
	cfg_geli = cfg_use_geli ? tr("Yes") : tr("No");
	gelicb->setText(tr("Encrypt /home using Geli"));
	title->setText(tr("Geli encrypted /home\n"));
	intro->setText(tr("NomadBSD allows you to protect your personal "  \
			  "files by encrypting the /home partition using " \
			  "geli(8). If you don't know what geli(8) is, "  \
			  "you should skip this page.\n\n"));
	pwdLabel->setText(tr("Define a password required to decrypt /home"));
}

void GeliPage::passwordChanged()
{
	if (pass->isValid())
		cfg_geli_password = pass->password();
	emit completeChanged();
}

void GeliPage::setGeli(bool state)
{
	passContainer->setEnabled(state);
	cfg_geli = state ? tr("Yes") : tr("No");
	cfg_use_geli = state;
	emit completeChanged();
}

bool GeliPage::isComplete() const
{
	if (gelicb->isChecked() && !pass->isValid())
		return (false);
	return (true);
}

//////////////////////////////////////////////////////////////////////////////
//
// Default applications page
//
//////////////////////////////////////////////////////////////////////////////
ProgramsPage::ProgramsPage(QWidget *parent) : QWizardPage(parent)
{
	intro		    = new QLabel;
	title		    = new QLabel;
	QVBoxLayout *layout = new QVBoxLayout;

	struct apps_s {
		const char *command;
		QString	   *cfg_var;
		QComboBox  **box;
	} apps[ncats] = {
		{ BACKEND_GET_SHELLS,	    &cfg_shell,        &shells       },
		{ BACKEND_GET_EDITORS,      &cfg_editor,       &editors      },
		{ BACKEND_GET_GUIEDITORS,   &cfg_gui_editor,   &guiEditors   },
		{ BACKEND_GET_EMAILCLIENTS, &cfg_email_client, &emailClients },
		{ BACKEND_GET_BROWSERS,     &cfg_browser,      &browsers     },
		{ BACKEND_GET_FILEMANAGERS, &cfg_file_manager, &fileManagers }

	};
	layout->setSpacing(10);
	layout->addWidget(title);
	layout->addWidget(intro);

	intro->setWordWrap(true);
	title->setStyleSheet("font-weight: bold;");

	for (int n = 0; n < ncats; n++) {
		QProcess   proc;
		QByteArray line;

		*apps[n].box = new QComboBox;
		proc.setReadChannel(QProcess::StandardOutput);
		proc.start(apps[n].command);

		(void)proc.waitForStarted(-1);
		//
		// According to the Qt docs, we can not rely on the return value.
		// We have to check state().
		//
		if (proc.state() == QProcess::NotRunning) {
			SetupWizard::errAndOut(
			    tr("Couldn't start backend '%1': %2")
			    .arg(apps[n].command).arg(proc.errorString()));
		}
		while (proc.waitForReadyRead(-1)) {
			while (!(line = proc.readLine()).isEmpty()) {
				// Remove trailing newline.
				line.truncate(line.size() - 1);
				QList<QByteArray>fields = line.split('|');
				if (fields.count() < 2)
					continue;
				QString id    = fields.at(0);
				QString descr = QString("%1 - %2")
				    .arg(QString(fields.at(0)))
				    .arg(QString(fields.at(1)));
				(*apps[n].box)->addItem(descr, QVariant(id));
				if ((*apps[n].box)->count() == 1)
					*apps[n].cfg_var = id;
			}
		}
		proc.waitForFinished(-1);
		if (proc.exitCode() != 0) {
			SetupWizard::errAndOut(
			    QString("Command '%1' returned with an error.")
			        .arg(apps[n].command));
		}
		if ((*apps[n].box)->count() == 0)
			*apps[n].cfg_var = "";
		connect(*apps[n].box, SIGNAL(currentIndexChanged(int)), this,
		    SLOT(selectionChanged(int)));
		catLabel[n]	   = new QLabel;
		QVBoxLayout *vbox  = new QVBoxLayout;
		catLabel[n]->setStyleSheet("font-weight: bold;");
		vbox->addWidget(catLabel[n]);
		vbox->addWidget(*apps[n].box);
		layout->addLayout(vbox);	
	}
	setLayout(layout);
}

void ProgramsPage::initializePage()
{
	QString label[ncats] = {
		tr("Shell"),	    tr("Editor"), tr("GUI Editor"),
		tr("Email client"), tr("Web browser"), tr("File manager")
	};
	for (int n = 0; n < ncats; n++)
		catLabel[n]->setText(label[n]);
	title->setText(tr("Choose your default applications\n"));
	intro->setText(tr("Please choose your preferred shell, editors, " \
			  "browser, and email client\n"));
}

QString ProgramsPage::getBoxVal(QComboBox *box)
{
	return (box->itemData(box->currentIndex()).toString());
}

void ProgramsPage::selectionChanged(int /* unused */)
{
	cfg_shell	 = getBoxVal(shells);
	cfg_editor	 = getBoxVal(editors);
	cfg_browser	 = getBoxVal(browsers);
	cfg_gui_editor	 = getBoxVal(guiEditors);
	cfg_email_client = getBoxVal(emailClients);
	cfg_file_manager = getBoxVal(fileManagers);
}

//////////////////////////////////////////////////////////////////////////////
//
// Summary page
//
//////////////////////////////////////////////////////////////////////////////
SummaryPage::SummaryPage(QWidget *parent) : QWizardPage(parent)
{
	QVBoxLayout *vbox = new QVBoxLayout;
	text = new QLabel;
	for (int n = 0; n < nkeys; n++) {
		key[n]		  = new QLabel;
		val[n]		  = new QLabel;
		QHBoxLayout *hbox = new QHBoxLayout;
		key[n]->setStyleSheet("font-weight: bold;");
		hbox->addWidget(key[n]);
		hbox->addWidget(val[n]);
		vbox->addLayout(hbox);
	}
	vbox->addWidget(text);
	setLayout(vbox);
	setCommitPage(true);
}

void SummaryPage::initializePage()
{
	struct summary_s {
		QString key;
		QString val;
	} summary[] = {
		{ tr("Locale:"),	   cfg_locale	    },
		{ tr("Keyboard layout:"),  cfg_kbdlayout    },
		{ tr("Keyboard variant:"), cfg_kbdvariant   },
		{ tr("Timezone:"),	   cfg_timezone     },
		{ tr("Encrypt /home:"),	   cfg_geli	    },
		{ tr("Shell:"),		   cfg_shell	    },
		{ tr("Editor:"),	   cfg_editor	    },
		{ tr("GUI editor:"),	   cfg_gui_editor   },
		{ tr("Email client:"),	   cfg_email_client },
		{ tr("Web browser:"),	   cfg_browser	    },
		{ tr("File manager:"),	   cfg_file_manager }

	};
	for (int n = 0; n < nkeys; n++) {
		key[n]->setText(summary[n].key);
		val[n]->setText(summary[n].val);
	}
	text->setText(tr("\n\nIf you click \"commit\", the changes " \
			 "will be written to your USB flash drive"));
	text->setWordWrap(true);
}

CommitPage::CommitPage(QWidget *parent) : QWizardPage(parent)
{
	statusMsg	       = new QLabel;
	commandMsg	       = new QLabel;
	errorMsg	       = new QLabel;
	QWidget	    *container = new QWidget;
	QVBoxLayout *vbox      = new QVBoxLayout(container);
	QVBoxLayout *layout    = new QVBoxLayout;
	QScrollArea *sa	       = new QScrollArea(this);

	sa->setWidget(container);
	sa->setWidgetResizable(true);

	layout->addWidget(statusMsg, 0, Qt::AlignCenter);
	layout->addWidget(sa);

	statusMsg->setStyleSheet("font-weight: bold;");
	commandMsg->setStyleSheet("font-style: italic;");
	errorMsg->setStyleSheet("color: red;");
	vbox->addWidget(commandMsg, 1, Qt::AlignCenter);
	vbox->addWidget(errorMsg, 1, Qt::AlignCenter);
	setLayout(layout);
}

void CommitPage::initializePage()
{
	struct config_s {
		QString var;
		QString val;
	} config[] = {
		{ "cfg_locale",		cfg_locale	  },
		{ "cfg_timezone",	cfg_timezone	  },
		{ "cfg_kbdlayout",	cfg_kbdlayout	  },
		{ "cfg_kbdvariant",	cfg_kbdvariant	  },
		{ "cfg_password",	cfg_password	  },
		{ "cfg_geli_password",	cfg_geli_password },
		{ "cfg_shell",		cfg_shell	  },
		{ "cfg_editor",		cfg_editor	  },
		{ "cfg_gui_editor",	cfg_gui_editor	  },
		{ "cfg_browser",	cfg_browser	  },
		{ "cfg_email_client",	cfg_email_client  },
		{ "cfg_file_manager",	cfg_file_manager  }
	};
	proc.setReadChannel(QProcess::StandardOutput);
	proc.start(BACKEND_COMMIT);
	(void)proc.waitForStarted(-1);

	//
	// According to the Qt docs, we can not rely on the return value.
	// We have to check state().
	//
	if (proc.state() == QProcess::NotRunning) {
		SetupWizard::errAndOut(tr("Couldn't start backend '%1': %2")
		    .arg(BACKEND_COMMIT).arg(proc.errorString()));
	}
	for (size_t n = 0; n < sizeof(config) / sizeof(config[0]); n++) {
		QString ln = QString("%1 = %2\n").arg(config[n].var)
				.arg(config[n].val);
		proc.write(ln.toLocal8Bit());
	}
	// Terminate config list
	proc.closeWriteChannel();
	
	connect(&proc, SIGNAL(readyReadStandardOutput()), this,
	    SLOT(readCmdOutput()));
	connect(&proc, SIGNAL(readyReadStandardError()), this,
	    SLOT(readError()));
	connect(&proc, SIGNAL(finished(int, QProcess::ExitStatus)), this,
	    SLOT(cleanup(int, QProcess::ExitStatus)));
	connect(&proc, SIGNAL(errorOccurred(QProcess::ProcessError)), this,
	    SLOT(catchError(QProcess::ProcessError)));
}

void CommitPage::catchError(QProcess::ProcessError /* perr */)
{
	SetupWizard::errAndOut(
	    QString(tr("An unexpected error occured while executing %1: %2")
	        .arg(PATH_NOMADBSD_SETUP).arg(proc.errorString())));
}

void CommitPage::readCmdOutput()
{
	QByteArray line;

	proc.setReadChannel(QProcess::StandardOutput);
	while (!(line = proc.readLine()).isEmpty()) {
		if (line[0] == '!') {
			// Status message
			line.remove(0, 1);
			errorMsgBuf   = "";
			commandMsgBuf = "";
			errorMsg->setText("");
			commandMsg->setText("");
			statusMsg->setText(line);
		} else {
			// Command output
			commandMsgBuf.append(line);
			commandMsg->setText(commandMsgBuf);
		}
	}
}

void CommitPage::readError()
{
	QByteArray line;	

	proc.setReadChannel(QProcess::StandardError);
	while (!(line = proc.readLine()).isEmpty()) {
		errorMsgBuf.append(line);
		errorMsg->setText(errorMsgBuf);
	}
}

void CommitPage::cleanup(int exitCode, QProcess::ExitStatus /* exitStatus */)
{
	if (exitCode != 0) {
		SetupWizard::errAndOut(
		    QString("%1 returned with error code %2")
			.arg(BACKEND_COMMIT).arg(exitCode));
	}
	statusMsg->setText(tr("Press \"Finish\" to reboot"));
	emit completeChanged();
}

bool CommitPage::isComplete() const
{
	if (proc.state() == QProcess::NotRunning)
		return (true);
	return (false);
}
