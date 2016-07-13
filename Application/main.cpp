

//Project
#include "Settings.h"
#include "IntermodWidget.h"

// RsaToolbox
#include <About.h>
#include <GenericBus.h>
#include <Keys.h>
#include <Log.h>
#include <Vna.h>
#include <Wizard.h>
using namespace RsaToolbox;

// Qt
#include <QApplication>
#include <QMessageBox>

// Functions
bool isAboutMenu(int argc, char *argv[]);
bool isRohdeSchwarzVna(Vna &vna);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // --about flag?
    if (isAboutMenu(argc, argv))
        return 0;

    // Vna connection, log
    Vna vna(CONNECTION_TYPE, ADDRESS);
    Log log(LOG_FILENAME, APP_NAME, APP_VERSION);
    log.printHeader();
    vna.useLog(&log);
    if (!isRohdeSchwarzVna(vna))
        return 0;

    // Keys / saved settings
    Keys keys(KEY_PATH);

    // Title
    QString title = "%1 %2";
    title = title.arg(APP_NAME);
    title = title.arg(APP_VERSION);

    // Pages
    IntermodWidget *settings = new IntermodWidget(&vna);

    // Wizard
    Wizard wizard;
    wizard.setWindowTitle(title);
    wizard.hideBreadcrumbs();
    wizard.setRestartOnCancel(false);
    wizard.addPage(settings);
//  wizard.addPage(...);
//  ...
    wizard.show();

    // Connections
    QObject::connect(settings, SIGNAL(error(IntermodError)),
                     &wizard, SLOT(shake()));
    QObject::connect(settings, SIGNAL(errorMessage(QString)),
                     &wizard,  SLOT(shake()));

    // Start event loop
    return a.exec();
}

// Functions
bool isAboutMenu(int argc, char *argv[]) {
    if (argc != 2)
        return false;

    QString arg(argv[1]);
    arg = arg.trimmed().toUpper();
    if (arg == "-ABOUT" || arg == "--ABOUT") {
        Q_INIT_RESOURCE(AboutResources);
        About about;
        about.setAppName(APP_NAME);
        about.setVersion(APP_VERSION);
        about.setDescription(APP_DESCRIPTION);
        about.setContactInfo(CONTACT_INFO);
        about.exec();
        return true;
    }

    return false;
}
bool isRohdeSchwarzVna(Vna &vna) {
    if (!vna.isConnected() || vna.idString().isEmpty()) {
        QString msg = "Could not connect to instrument.\n"
                      "Please check your VISA installation and\n"
                      "run this application on the instrument.";
        QMessageBox::critical(NULL,
                              APP_NAME,
                              msg);
        vna.print(msg);
        return false;
    }
    vna.settings().setEmulationOff();
    if (!vna.properties().isKnownModel()) {
        QString msg = "Instrument not recognized.\n"
                      "Please use %1 with a Rohde & Schwarz VNA\n"
                      "with emulation mode turned off.";
        msg = msg.arg(APP_NAME);
        QMessageBox::critical(NULL,
                              APP_NAME,
                              msg);
        vna.print(msg);
        return false;
    }

    return true;
}
