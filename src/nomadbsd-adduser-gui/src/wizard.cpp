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
#include <QFormLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTranslator>
#include <QCoreApplication>
#include <QScrollArea>
#include <QShortcut>
#include <QFontMetricsF>
#include <QFormLayout>
#include <QFile>
#include "wizard.h"
#include "backend.h"

//////////////////////////////////////////////////////////////////////////////
//
// Global variables to hold the configuration
//
//////////////////////////////////////////////////////////////////////////////
static QString cfg_username;
static QString cfg_name;
static QString cfg_locale = "en";
static QString cfg_localedescr = "English (US)";
static QString cfg_region = "US";
static QString cfg_shell;
static QString cfg_password;
static QString cfg_editor;
static QString cfg_email_client;
static QString cfg_browser;
static QString cfg_gui_editor;
static QString cfg_file_manager;
//////////////////////////////////////////////////////////////////////////////

static QTranslator translator;

Wizard::Wizard(QWidget *parent) : QWizard(parent)
{
	setWindowTitle(tr("Add user"));
	setWindowIcon(loadIcon("system-users", NULL));
	setButtonText(QWizard::NextButton,   tr("Next"));
	setButtonText(QWizard::BackButton,   tr("Back"));
	setButtonText(QWizard::CommitButton, tr("Commit"));
	setButtonText(QWizard::FinishButton, tr("Finish"));
	setButtonText(QWizard::CancelButton, tr("Cancel"));

	addPage(new UsernamePage);
	addPage(new PasswordPage);
	addPage(new LocalePage);
	addPage(new ProgramsPage);
	addPage(new SummaryPage);
	addPage(new CommitPage);
}

void Wizard::accept()
{
	QDialog::accept();
}

void Wizard::reject()
{
	cancelMenu();
}

QIcon Wizard::loadIcon(const char *name, ...)
{
	va_list    ap;
	const char *s;

	va_start(ap, name);
	for (s = name; s != NULL || (s = va_arg(ap, char *)); s = NULL) {
		if (!QIcon::hasThemeIcon(s))
			continue;
		QIcon icon = QIcon::fromTheme(s);
		if (icon.isNull())
			continue;
		if (icon.name().isEmpty() || icon.name().length() < 1)
			continue;
		return (icon);
	}
	return (QIcon());
}

//////////////////////////////////////////////////////////////////////////////
//
// Username page
//
//////////////////////////////////////////////////////////////////////////////
UsernamePage::UsernamePage(QWidget *parent) : QWizardPage(parent)
{
	QLabel	    *text   = new QLabel;
	QLabel	    *ulabel = new QLabel;
	QLabel	    *nlabel = new QLabel;
	QVBoxLayout *layout = new QVBoxLayout;
	QFormLayout *form  = new QFormLayout;
	QRegExp	    uchars  = QRegExp("[a-z]+");
	QRegExp	    nchars  = QRegExp("[^:,]+");
	namele		    = new QLineEdit;
	usernamele	    = new QLineEdit;
	status		    = new QLabel;

	nlabel->setText(tr("Full name:"));
	namele->setMaxLength(32);
	namele->setValidator(new QRegExpValidator(nchars));
	form->addRow(nlabel, namele);

	readUsernames();
	ulabel->setText(tr("Username:"));
	usernamele->setMaxLength(16);
	usernamele->setValidator(new QRegExpValidator(uchars));
	form->addRow(ulabel, usernamele);

	status->setStyleSheet("color: red;");	
	text->setText(tr("Add a new user to the system\n\n"));
	text->setWordWrap(true);
	text->setStyleSheet("font-weight: bold;");
	text->setAlignment(Qt::AlignHCenter);
	layout->addWidget(text);
	layout->addLayout(form);
	layout->addWidget(status);
	setLayout(layout);

	connect(namele, SIGNAL(textChanged(const QString &)), this,
	    SLOT(nameChanged(const QString &)));
	connect(usernamele, SIGNAL(textChanged(const QString &)), this,
	    SLOT(usernameChanged(const QString &)));
}

bool UsernamePage::validateUsername(const QString &username) const
{
	if (cfg_username.length() < 1) {
		status->setText(tr("Username must not be empty"));
		return (false);
	}
	for (int i = 0; i < usernames.count(); i++) {
		if (username == usernames.at(i)) {
			status->setText(tr("Username already in use"));
			return (false);
		}
	}
	status->setText("");
	return (true);
}

void UsernamePage::readUsernames()
{
	QFile file(PATH_ETC_PASSWD);

	if (!file.open(QIODevice::ReadOnly)) {
		Wizard::errAndOut(tr("Couldn't read '%1': %2")
		    .arg(PATH_ETC_PASSWD).arg(file.error()));
		return;
	}
	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		QList<QByteArray>fields = line.split(':');
		usernames.append(fields[0]);
	}
	file.close();
}

void UsernamePage::usernameChanged(const QString &username)
{
	cfg_username = username;
	emit completeChanged();
}

void UsernamePage::nameChanged(const QString &name)
{
	cfg_name = name;
}

bool UsernamePage::isComplete() const
{
	return (validateUsername(cfg_username));
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
		Wizard::errAndOut(tr("Couldn't start backend '%1': %2")
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
		Wizard::errAndOut(
		    tr("Command '%1' returned with an error.")
		    .arg(BACKEND_GET_LOCALES));
	}
	label->setStyleSheet("font-weight: bold;");
	label->setText(tr("Please select language/locale for the new user"));
	label->setAlignment(Qt::AlignHCenter);

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
	cfg_locale	= localels->item(row)->data(Qt::UserRole).toString();
	cfg_region	= cfg_locale.split('_').at(1);
	cfg_localedescr	= localels->item(row)->text();
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
	QVBoxLayout *layout = new QVBoxLayout;

	title->setStyleSheet("font-weight: bold;");
	title->setAlignment(Qt::AlignHCenter);
	layout->addWidget(title);
	layout->addWidget(pass);
	setLayout(layout);
	connect(pass, SIGNAL(passwordChanged()), this,
	    SLOT(passwordChanged()));
}

void PasswordPage::initializePage()
{
	title->setText(tr("Set password for new user\n"));
	pass->setPl1Text(tr("Password:"));
	pass->setPl2Text(tr("Repeat password:"));
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
// Default applications page
//
//////////////////////////////////////////////////////////////////////////////
ProgramsPage::ProgramsPage(QWidget *parent) : QWizardPage(parent)
{
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
		{ BACKEND_GET_FILEMANAGERS, &cfg_file_manager, &fileManagers },
		{ BACKEND_GET_EMAILCLIENTS, &cfg_email_client, &emailClients },
		{ BACKEND_GET_BROWSERS,	    &cfg_browser,      &browsers     }
	};
	layout->setSpacing(10);
	layout->addWidget(title);

	title->setStyleSheet("font-weight: bold;");
	title->setAlignment(Qt::AlignHCenter);

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
			Wizard::errAndOut(
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
			Wizard::errAndOut(
			    tr("Command '%1' returned with an error.")
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
		tr("Shell"), tr("Editor"), tr("GUI Editor"),
		tr("File manager"), tr("Mail client"), tr("Web browser")
	};
	for (int n = 0; n < ncats; n++)
		catLabel[n]->setText(label[n]);
	title->setText(tr("Default applications\n"));
}

QString ProgramsPage::getBoxVal(QComboBox *box)
{
	return (box->itemData(box->currentIndex()).toString());
}

void ProgramsPage::selectionChanged(int /* unused */)
{
	cfg_shell	 = getBoxVal(shells);
	cfg_editor	 = getBoxVal(editors);
	cfg_gui_editor	 = getBoxVal(guiEditors);
	cfg_file_manager = getBoxVal(fileManagers);
	cfg_browser	 = getBoxVal(browsers);
	cfg_email_client = getBoxVal(emailClients);
}

//////////////////////////////////////////////////////////////////////////////
//
// Summary page
//
//////////////////////////////////////////////////////////////////////////////
SummaryPage::SummaryPage(QWidget *parent) : QWizardPage(parent)
{
	title		  = new QLabel;
	QFormLayout *form = new QFormLayout;
	QVBoxLayout *vbox = new QVBoxLayout;

	title->setAlignment(Qt::AlignHCenter);
	title->setStyleSheet("font-weight: bold;");

	for (int n = 0; n < nkeys; n++) {
		key[n]		  = new QLabel;
		val[n]		  = new QLabel;
		key[n]->setStyleSheet("font-weight: bold;");
		form->addRow(key[n], val[n]);
	}
	vbox->addWidget(title);
	vbox->addLayout(form);
	setLayout(vbox);
	setCommitPage(true);
}

void SummaryPage::initializePage()
{
	struct summary_s {
		QString key;
		QString val;
	} summary[] = {
		{ tr("Full name:"),			cfg_name	   },
		{ tr("Username:"),			cfg_username	   },
		{ tr("Locale:"),			cfg_localedescr	   },
		{ tr("Shell:"),				cfg_shell	   },
		{ tr("Editor:"),			cfg_editor	   },
		{ tr("GUI editor:"),			cfg_gui_editor     },
		{ tr("File manager:"),			cfg_file_manager   },
		{ tr("Mail client:"),			cfg_email_client   },
		{ tr("Web browser:"),			cfg_browser	   }
	};
	for (int n = 0; n < nkeys; n++) {
		key[n]->setText(summary[n].key);
		val[n]->setText(summary[n].val);
	}
	title->setText(tr("Summary\n"));
}

CommitPage::CommitPage(QWidget *parent) : QWizardPage(parent)
{
	statusMsg	       = new QLabel;
	commandMsg	       = new QLabel;
	progBar		       = new QProgressBar;
	QWidget	    *container = new QWidget;
	QVBoxLayout *vbox      = new QVBoxLayout(container);
	QVBoxLayout *layout    = new QVBoxLayout;
	QScrollArea *sa	       = new QScrollArea(this);

	sa->setWidget(container);
	sa->setWidgetResizable(true);

	progBar->setRange(0, 0);
	progBar->setValue(0);
	progBar->setVisible(false);

	layout->addWidget(statusMsg, 0, Qt::AlignCenter);
	layout->addWidget(sa);

	statusMsg->setStyleSheet("font-weight: bold;");
	commandMsg->setStyleSheet("font-style: italic;");
	vbox->addWidget(commandMsg, 1, Qt::AlignLeft);
	vbox->addWidget(progBar, 1, Qt::AlignCenter);
	setLayout(layout);
}

void CommitPage::initializePage()
{

	struct config_s {
		QString var;
		QString val;
	} config[] = {
		{ "cfg_name",		cfg_name	  },
		{ "cfg_username",	cfg_username	  },
		{ "cfg_locale",		cfg_locale	  },
		{ "cfg_password",	cfg_password	  },
		{ "cfg_shell",		cfg_shell	  },
		{ "cfg_editor",		cfg_editor	  },
		{ "cfg_gui_editor",	cfg_gui_editor	  },
		{ "cfg_file_manager",	cfg_file_manager  },
		{ "cfg_email_client",	cfg_email_client  },
		{ "cfg_browser",	cfg_browser	  },
	};
	proc.setReadChannel(QProcess::StandardOutput);
	proc.start(BACKEND_COMMIT);
	(void)proc.waitForStarted(-1);

	//
	// According to the Qt docs, we can not rely on the return value.
	// We have to check state().
	//
	if (proc.state() == QProcess::NotRunning) {
		Wizard::errAndOut(tr("Couldn't start backend '%1': %2")
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
	Wizard::errAndOut(
	    QString(tr("An unexpected error occured while executing %1: %2")
	        .arg(PATH_NOMADBSD_ADDUSER).arg(proc.errorString())));
}

void CommitPage::readCmdOutput()
{
	QByteArray line;
	QFontMetrics fm(commandMsg->font());
	const int maxc = fm.horizontalAdvance("m") * 40;

	proc.setReadChannel(QProcess::StandardOutput);
	while (!(line = proc.readLine()).isEmpty()) {
		if (line[0] == '%') {
			// Progress
			line.remove(0, 1);
			int n = line.toInt(0, 10);
			if (!progBar->isVisible())
				progBar->setVisible(true);
			progBar->setRange(0, n < 0 ? 0 : 100);
			progBar->setValue(n < 0 ? 0 : n);
		} else if (line[0] == '!') {
			// Status message
			line.remove(0, 1);
			errorMsgBuf   = "";
			commandMsgBuf = "";
			commandMsg->setText("");
			statusMsg->setText(line);
			progBar->setVisible(false);
		} else if (line[0] == '>') {
			// Single line output
			line.remove(0, 1);
			//
			// Use elided version of the string with "..." in the
			// middle if the string is too long.
			//
			QString s = fm.elidedText(line,	Qt::ElideMiddle, maxc);
			commandMsg->setText(s);
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
	while (!(line = proc.readLine()).isEmpty())
		errorMsgBuf.append(line);
}

void CommitPage::cleanup(int exitCode, QProcess::ExitStatus /* exitStatus */)
{
	if (exitCode != 0) {
		Wizard::errAndOut(
		    tr("%1 returned with error code %2:\n\"%3\"")
		    .arg(BACKEND_COMMIT).arg(exitCode).arg(errorMsgBuf));
	}
	statusMsg->setText(tr("User %1 successfully added").arg(cfg_username));
	emit completeChanged();
}

bool CommitPage::isComplete() const
{
	if (proc.state() == QProcess::NotRunning)
		return (true);
	return (false);
}
