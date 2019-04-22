<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.1" language="ru_RU">
<context>
    <name>CommitPage</name>
    <message>
        <location filename="../src/wizard.cpp" line="296"/>
        <source>Last chance to quit installation.</source>
        <translation>Последняя возможность прервать установку.</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="297"/>
        <source>Last chance</source>
        <translation>Последняя возможность</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="300"/>
        <source>Quit</source>
        <translation>Выход</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="303"/>
        <source>Install</source>
        <translation>Установка</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="320"/>
        <source>Couldn&apos;t start backend &apos;%1&apos;: %2</source>
        <translation>Фоновый процесс не может быть запущен %1: %2</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="337"/>
        <source>An unexpected error occured while executing %1: %2</source>
        <translation>Возникла неизвестная ошибка в процессе выполнения %1: %2</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="379"/>
        <source>Press &quot;Finish&quot; to reboot</source>
        <translation>Нажмите &quot;Завершить&quot; для перезагрузки</translation>
    </message>
</context>
<context>
    <name>InstallWizard</name>
    <message>
        <location filename="../src/wizard.cpp" line="52"/>
        <source>NomadBSD Installation Wizard</source>
        <translation>Мастер установки NomadBSD</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="55"/>
        <source>Next</source>
        <translation>Далее</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="56"/>
        <source>Back</source>
        <translation>Назад</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="57"/>
        <source>Commit</source>
        <translation>Применить</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="58"/>
        <source>Finish</source>
        <translation>Завершить</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="59"/>
        <location filename="../src/wizard.h" line="85"/>
        <source>Cancel</source>
        <translation>Отмена</translation>
    </message>
    <message>
        <location filename="../src/wizard.h" line="62"/>
        <source>Fatal error</source>
        <translation>Критическая ошибка</translation>
    </message>
    <message>
        <location filename="../src/wizard.h" line="63"/>
        <source>Error</source>
        <translation>Ошибка</translation>
    </message>
    <message>
        <location filename="../src/wizard.h" line="66"/>
        <source>

Please send a bug report to the NomadBSD mailing list.

We are sorry for the inconvenience
</source>
        <translatorcomment>Could we provide a name of the mailing list here? It removes a need to search the web for the end user.</translatorcomment>
        <translation>

Пожалуйста, отправьте отчет об ошибке в список рассылки NomadBSD.

Извините за неудобства
</translation>
    </message>
    <message>
        <location filename="../src/wizard.h" line="78"/>
        <source>Are you sure you want to quit?</source>
        <translation>Вы уверены что хотите выйти?</translation>
    </message>
    <message>
        <location filename="../src/wizard.h" line="79"/>
        <source>Quit installation</source>
        <translation>Выход из мастера установки</translation>
    </message>
    <message>
        <location filename="../src/wizard.h" line="82"/>
        <source>Quit</source>
        <translation>Выход</translation>
    </message>
</context>
<context>
    <name>SettingsPage</name>
    <message>
        <location filename="../src/wizard.cpp" line="129"/>
        <source>Couldn&apos;t start backend &apos;%1&apos;: %2</source>
        <translation>Фоновый процесс не может быть запущен %1: %2</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="153"/>
        <source>&lt;b&gt;Please select the device you want to install NomadBSD on&lt;/b&gt;</source>
        <translation>&lt;b&gt;Пожалуйста, выберите устройство на которое нужно установить NomadBSD&lt;/b&gt;</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="161"/>
        <source>&lt;b&gt;Desired size of the swap partition&lt;/b&gt;</source>
        <translatorcomment>Или все же использовать англицизм и раздел подкачки переименовать в swap раздел так как это слово широко известно и употребимо как технический термин в русском языке?</translatorcomment>
        <translation>&lt;b&gt;Размер раздела подкачки&lt;/b&gt;</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="174"/>
        <source>&lt;b&gt;Username*&lt;/b&gt;</source>
        <translation>&lt;b&gt;Имя пользователя*&lt;/b&gt;</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="178"/>
        <source>&lt;i&gt;* The installation script will adopt nomad&apos;s complete account. Only the username changes.&lt;/i&gt;</source>
        <translation>&lt;i&gt;* Мастер установки будет использовать профиль пользователя &quot;nomad&quot;. Только имя пользователя будет изменено.&lt;/i&gt;</translation>
    </message>
</context>
<context>
    <name>SummaryPage</name>
    <message>
        <location filename="../src/wizard.cpp" line="239"/>
        <source>&lt;b&gt;Summary:&lt;/b&gt;&lt;br/&gt;&lt;br/&gt;</source>
        <translation>&lt;b&gt;Сводка:&lt;/b&gt;&lt;br/&gt;&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="252"/>
        <source>Target disk:</source>
        <translation>Диск:</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="253"/>
        <source>Swap (in MB):</source>
        <translatorcomment>We could try to be precise and use MiB instead of MB here. It&apos;s important, I guess.</translatorcomment>
        <translation>Раздел подкачки (в МиБ):</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="254"/>
        <source>Username:</source>
        <translation>Имя пользователя:</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="260"/>
        <source>&lt;br/&gt;&lt;br/&gt;&lt;b&gt;Warning:&lt;br/&gt;&lt;br/&gt;&lt;/b&gt;
If you click &lt;i&gt;commit&lt;/i&gt;, the system will be written to &lt;i&gt;%1&lt;/i&gt;. All data on &lt;i&gt;%1&lt;/i&gt; will be lost!</source>
        <translation>&lt;br/&gt;&lt;br/&gt;&lt;b&gt;Внимание:&lt;br/&gt;&lt;br/&gt;&lt;/b&gt;
Если Вы нажмете &lt;i&gt;Применить&lt;/i&gt;, система будет записана на &lt;i&gt;%1&lt;/i&gt;. Все данные на &lt;i&gt;%1&lt;/i&gt; будут потеряны!</translation>
    </message>
</context>
<context>
    <name>WelcomePage</name>
    <message>
        <location filename="../src/wizard.cpp" line="89"/>
        <source>&lt;b&gt;Welcome to the NomadBSD installation wizard.&lt;/b&gt;&lt;br/&gt;&lt;br/&gt;</source>
        <translation>&lt;b&gt;Добро пожаловать в мастер установки NomadBSD.&lt;/b&gt;&lt;br/&gt;&lt;br/&gt;</translation>
    </message>
    <message>
        <location filename="../src/wizard.cpp" line="91"/>
        <source>This program will install your NomadBSD with its current configuration on a hard disk.

</source>
        <translation>Эта программа установит NomadBSD в её текущей конфигурации на жесткий диск.

</translation>
    </message>
</context>
</TS>
